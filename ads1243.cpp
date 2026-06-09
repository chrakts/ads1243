#include "ads1243_class.h"
#include <util/delay.h>

// ==== DRDY warten ====
void ADS1243_class::ADS1243_WaitDRDY()
{
    while (_drdyPort->IN & _drdyPin);
}

// ==== Reset ====
void ADS1243_class::ADS1243_Reset()
{
    select();
    transceiveByte(ADS1243_CMD_RESET);
    //SPI_MasterTransceiveByte(&_spi, ADS1243_CMD_RESET);
    LEDROT_OFF;
    unselect();

    // kleines Delay nötig (~0.6 ms laut Datenblatt)
    _delay_ms(1);
}

// ==== Register schreiben ====
void ADS1243_class::ADS1243_WriteReg(uint8_t reg, uint8_t value) {
    select();

    transceiveByte(ADS1243_CMD_WREG | reg);
    //SPI_MasterTransceiveByte(&_spi, ADS1243_CMD_WREG | reg);
    transceiveByte(0x00); // 1 Register
    transceiveByte(value);

    unselect();
}

// ==== Register lesen ====
uint8_t ADS1243_class::ADS1243_ReadReg(uint8_t reg) {
    uint8_t val;

    select();

    transceiveByte(ADS1243_CMD_RREG | reg);
    transceiveByte(0x00);

    val = transceiveByte(0xFF);

    unselect();

    return val;
}

// ==== Daten lesen (24 Bit) ====
int32_t ADS1243_class::ADS1243_ReadData()
{
    uint8_t b1, b2, b3;
    int32_t result;

    ADS1243_WaitDRDY();

    select();

    transceiveByte(ADS1243_CMD_RDATA);

    b1 = transceiveByte(0xFF);
    b2 = transceiveByte(0xFF);
    b3 = transceiveByte(0xFF);

    unselect();

    result = ((int32_t)b1 << 16) |
             ((int32_t)b2 << 8)  |
             (int32_t)b3;

    // Sign extension (24 → 32 Bit)
    if (result & 0x800000) {
        result |= 0xFF000000;
    }

    return result;
}
