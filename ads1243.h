#ifndef ADS1243_H
#define ADS1243_H

#include <stdint.h>
#include "spi_driver.h"

// ==== Struct ====
typedef struct {
    SPI_Master_t *spi;
    PORT_t *cs_port;
    uint8_t cs_pin;
    PORT_t *drdy_port;
    uint8_t drdy_pin;
} ADS1243_t;

// ==== API ====

#endif
