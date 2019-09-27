#if !defined(__SPI_COM_H__)
#define __SPI_COM_H__

#include <gd32vf103.h>
#include "pins_arduino.h"

#ifdef __cplusplus

// AVAILIABLE IN CPP SOURCES ONLY (spi_init conflict)

struct spi_s {
    uint32_t handle; // not used
    void* spi; // not used
    uint8_t pin_miso;
    uint8_t pin_mosi;
    uint8_t pin_sclk;
    uint8_t pin_ssel;
};

typedef struct spi_s spi_t;

#define SPI_SPEED_CLOCK_DIV2_MHZ ((uint32_t)2)
#define SPI_SPEED_CLOCK_DIV4_MHZ ((uint32_t)4)
#define SPI_SPEED_CLOCK_DIV8_MHZ ((uint32_t)8)
#define SPI_SPEED_CLOCK_DIV16_MHZ ((uint32_t)16)
#define SPI_SPEED_CLOCK_DIV32_MHZ ((uint32_t)32)
#define SPI_SPEED_CLOCK_DIV64_MHZ ((uint32_t)64)
#define SPI_SPEED_CLOCK_DIV128_MHZ ((uint32_t)128)
#define SPI_SPEED_CLOCK_DIV256_MHZ ((uint32_t)256)

///@brief speficies the SPI mode to use
// Mode          Clock Polarity (CPOL)       Clock Phase (CPHA)
// SPI_MODE0             0                         0
// SPI_MODE1             0                         1
// SPI_MODE2             1                         0
// SPI_MODE3             1                         1
// enum definitions coming from SPI.h of SAM
typedef enum {
    SPI_MODE_0 = 0x00,
    SPI_MODE_1 = 0x01,
    SPI_MODE_2 = 0x02,
    SPI_MODE_3 = 0x03,
    SPI_MODE_MAX = 0x04,
} spi_mode_e;

///@brief SPI errors
typedef enum { SPI_OK = 0, SPI_TIMEOUT = 1, SPI_ERROR = 2 } spi_status_e;

/* Exported functions ------------------------------------------------------- */
void spi_init(spi_t* obj, uint32_t speed, spi_mode_e mode, uint8_t msb);
void spi_deinit(spi_t* obj);
spi_status_e spi_send(
    spi_t* obj, uint8_t* Data, uint16_t len, uint32_t Timeout);
spi_status_e spi_transfer(spi_t* obj, uint8_t* tx_buffer, uint8_t* rx_buffer,
    uint16_t len, uint32_t Timeout);
uint32_t spi_getClkFreq(spi_t* obj);

#endif

#endif // __SPI_COM_H__
