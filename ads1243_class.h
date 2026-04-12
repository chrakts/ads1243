#ifndef ADS1243_CLASS_H_INCLUDED
#define ADS1243_CLASS_H_INCLUDED

#include "../spi/spiDevice.h"

// ==== Commands ====
#define ADS1243_CMD_WAKEUP   0x00
#define ADS1243_CMD_SLEEP    0x02
#define ADS1243_CMD_SYNC     0xFC
#define ADS1243_CMD_RESET    0xFE
#define ADS1243_CMD_RDATA    0x01
#define ADS1243_CMD_RREG     0x10
#define ADS1243_CMD_WREG     0x50



class ADS1243_class : public spiDevice
{
  public:
    ADS1243_class(SPI_t *module,
                   PORT_t *spiPort,
                   PORT_t *csPort,
                   uint8_t csPin,
                   bool lsbFirst,
                   SPI_MODE_t mode,
                   SPI_INTLVL_t intLevel,
                   bool clk2x,
                   SPI_PRESCALER_t clockDivision,
                   PORT_t *drdyPort,
                   uint8_t drdyPin)
      : spiDevice(module, spiPort, csPort, csPin, lsbFirst, mode, intLevel, clk2x, clockDivision),
        _drdyPort(drdyPort),
        _drdyPin(drdyPin)
    {
      unselect();
      // DataReady als Eingang
      _drdyPort->DIRCLR = _drdyPin;
    }

    virtual ~ADS1243_class() {}

    PORT_t* getDrdyPort() { return _drdyPort; }
    uint8_t getDrdyPin() { return _drdyPin; }

    bool isDataReady()
    {
        return (_drdyPort->IN & (1 << _drdyPin));
    }

  protected:

  private:
    PORT_t *_drdyPort;
    uint8_t _drdyPin;

  public:
    void ADS1243_Reset();
    void ADS1243_WriteReg(uint8_t reg, uint8_t value);
    uint8_t ADS1243_ReadReg(uint8_t reg);
    int32_t ADS1243_ReadData();
    void ADS1243_WaitDRDY();

};

#endif // ADS1243_CLASS_H_INCLUDED
