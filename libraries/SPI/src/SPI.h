#ifndef __LIB_SPI_H__
#define __LIB_SPI_H__

#include "stdint.h"

#define SPI_LSBFIRST 0
#define SPI_MSBFIRST 1

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3


class SPISettings {
public:
    SPISettings()
        : _freq(1000000)
        , _bitOrder(SPI_MSBFIRST)
        , _dataMode(SPI_MODE0) {}
    SPISettings(uint32_t freq, uint8_t bitOrder, uint8_t dataMode);
    uint32_t _freq;
    uint8_t _bitOrder;
    uint8_t _dataMode;
};

class SPIClass {
private:
    uint32_t _dev;
    uint32_t _dev_clk;
    uint32_t _mosi_bank;
    uint32_t _miso_bank;
    uint32_t _sclk_bank;
    uint32_t _ssel_bank;
    uint32_t _mosi_bit;
    uint32_t _miso_bit;
    uint32_t _sclk_bit;
    uint32_t _ssel_bit;
    uint32_t _mosi_bank_clk;
    uint32_t _miso_bank_clk;
    uint32_t _sclk_bank_clk;
    uint32_t _ssel_bank_clk;
    uint8_t _dataMode;
    uint8_t _bitOrder;
    uint32_t _freq;
    uint8_t _ssel_hard;

    void beginTransaction();

public:
    SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel = -1);
    void begin();
    void end();

    void beginTransaction(SPISettings settings);
    void endTransaction();

    // timeout in ms
    void transfer(uint8_t* data, uint32_t size, uint32_t timeout = 1);
    void transfer(
        uint8_t* txdata, uint8_t* rxdata, uint32_t size, uint32_t timeout = 1);

    void setBitOrder(uint8_t bitOrder);
    void setDataMode(uint8_t dataMode);
    void setFrequency(uint32_t freq);
};

extern SPIClass SPI;


#endif //__LIB_SPI_H__