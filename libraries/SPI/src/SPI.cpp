#include "SPI.h"
#include <gd32vf103.h>
#include "Common.h"

SPIClass::SPIClass(uint8_t mosi, uint8_t miso, uint8_t sclk, uint8_t ssel)
    : _dev(0)
    , _dev_clk(RCU_SPI0)
    , _mosi_bank(0)
    , _miso_bank(0)
    , _sclk_bank(0)
    , _ssel_bank(0)
    , _mosi_bit(0)
    , _miso_bit(0)
    , _sclk_bit(0)
    , _ssel_bit(0)
    , _mosi_bank_clk(RCU_GPIOA)
    , _miso_bank_clk(RCU_GPIOA)
    , _sclk_bank_clk(RCU_GPIOA)
    , _ssel_bank_clk(RCU_GPIOA) {
    if (mosi < VARIANT_GPIO_NUM && digitalPinSPIAvailiable(mosi)) {
        _dev = digitalPinToSPIDevice(mosi);
        _dev_clk = digitalPinToSPIClockId(mosi);
        _mosi_bank = digitalPinToPort(mosi);
        _mosi_bit = digitalPinToBitMask(mosi);
        _mosi_bank_clk = digitalPinToClkid(mosi);
    }
    if (miso < VARIANT_GPIO_NUM && digitalPinSPIAvailiable(miso)) {
        _dev = digitalPinToSPIDevice(miso);
        _dev_clk = digitalPinToSPIClockId(miso);
        _miso_bank = digitalPinToPort(miso);
        _miso_bit = digitalPinToBitMask(miso);
        _miso_bank_clk = digitalPinToClkid(miso);
    }
    if (sclk < VARIANT_GPIO_NUM && digitalPinSPIAvailiable(sclk)) {
        _sclk_bank = digitalPinToPort(sclk);
        _sclk_bit = digitalPinToBitMask(sclk);
        _sclk_bank_clk = digitalPinToClkid(sclk);
    }
    if (ssel < VARIANT_GPIO_NUM) {}
    _ssel_bank = digitalPinToPort(ssel);
    _ssel_bit = digitalPinToBitMask(ssel);
    _ssel_bank_clk = digitalPinToClkid(ssel);
    if (digitalPinSPIAvailiable(ssel)) {
        _ssel_hard = 1;
    }
}

void SPIClass::begin() {
    if (_dev == 0) {
        return;
    }
    if (_mosi_bank != 0) {
        rcu_periph_clock_enable((rcu_periph_enum)_mosi_bank_clk);
        gpio_init(_mosi_bank, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, _mosi_bit);
    }
    if (_miso_bank != 0) {
        rcu_periph_clock_enable((rcu_periph_enum)_miso_bank_clk);
        gpio_init(
            _miso_bank, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, _miso_bit);
    }
    if (_sclk_bank != 0) {
        rcu_periph_clock_enable((rcu_periph_enum)_sclk_bank_clk);
        gpio_init(_sclk_bank, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, _sclk_bit);
    }
    if (_ssel_bank != 0) {
        rcu_periph_clock_enable((rcu_periph_enum)_ssel_bank_clk);
        gpio_init(_ssel_bank, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, _ssel_bit);
        if (_ssel_hard == 0) {
            gpio_bit_set(_ssel_bank, _ssel_bit);
        }
    }
    rcu_periph_clock_enable((rcu_periph_enum)_dev_clk);
    spi_i2s_deinit((uint32_t)_dev);
}

void SPIClass::end() {
    if (_dev == 0) {
        return;
    }
    if (_mosi_bank != 0) {
        gpio_init(_mosi_bank, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, _mosi_bit);
    }
    if (_miso_bank != 0) {
        gpio_init(_miso_bank, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, _miso_bit);
    }
    if (_sclk_bank != 0) {
        gpio_init(_sclk_bank, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, _sclk_bit);
    }
    if (_ssel_bank != 0) {
        gpio_init(_ssel_bank, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, _ssel_bit);
    }
    spi_i2s_deinit((uint32_t)_dev);
    rcu_periph_clock_disable((rcu_periph_enum)_dev_clk);
}

void SPIClass::beginTransaction(SPISettings settings) {
    if (_dev == 0) {
        return;
    }
    if (settings._freq == 0) {
        return;
    }
    if (_dev == SPI0 && settings._freq > rcu_clock_freq_get(CK_APB2)) {
        return;
    }
    else if (settings._freq > rcu_clock_freq_get(CK_APB1)) {
        return;
    }
    _dataMode = settings._dataMode;
    _bitOrder = settings._bitOrder;
    _freq = settings._freq;
    beginTransaction();
}

void SPIClass::endTransaction() {
    if (_dev == 0) {
        return;
    }
    spi_disable(_dev);
}

void SPIClass::transfer(uint8_t* data, uint32_t size, uint32_t timeout) {
    if (_dev == 0 || data == nullptr) {
        return;
    }
    uint64_t startT = millis();

    if (_ssel_hard == 0 && _ssel_bank != 0) {
        gpio_bit_reset(_ssel_bank, _ssel_bit);
    }

    for (size_t i = 0; i < size; i++) {
        while (!spi_i2s_flag_get(_dev, SPI_FLAG_TBE)) {
            if (millis() > startT + timeout) {
                if (_ssel_hard == 0 && _ssel_bank != 0) {
                    gpio_bit_set(_ssel_bank, _ssel_bit);
                }
                return;
            }
        }
        spi_i2s_data_transmit(_dev, *data);
        data++;
    }

    if (_ssel_hard == 0 && _ssel_bank != 0) {
        gpio_bit_set(_ssel_bank, _ssel_bit);
    }
}

void SPIClass::transfer(
    uint8_t* txdata, uint8_t* rxdata, uint32_t size, uint32_t timeout) {
    if (_dev == 0 || txdata == nullptr || rxdata == nullptr) {
        return;
    }
    uint64_t startT = millis();

    if (_ssel_hard == 0 && _ssel_bank != 0) {
        gpio_bit_reset(_ssel_bank, _ssel_bit);
    }

    for (size_t i = 0; i < size; i++) {
        while (!spi_i2s_flag_get(_dev, SPI_FLAG_TBE)) {
            if (millis() > startT + timeout) {
                if (_ssel_hard == 0 && _ssel_bank != 0) {
                    gpio_bit_set(_ssel_bank, _ssel_bit);
                }
                return;
            }
        }
        spi_i2s_data_transmit(_dev, *txdata);
        txdata++;
        while (!spi_i2s_flag_get(_dev, SPI_FLAG_RBNE)) {
            if (millis() > startT + timeout) {
                if (_ssel_hard == 0 && _ssel_bank != 0) {
                    gpio_bit_set(_ssel_bank, _ssel_bit);
                }
                return;
            }
        }
        *rxdata = spi_i2s_data_receive(_dev);
        rxdata++;
    }

    if (_ssel_hard == 0 && _ssel_bank != 0) {
        gpio_bit_set(_ssel_bank, _ssel_bit);
    }
}

void SPIClass::setBitOrder(uint8_t bitOrder) {
    _bitOrder = bitOrder;
    beginTransaction();
}

void SPIClass::setDataMode(uint8_t dataMode) {
    _dataMode = dataMode;
    beginTransaction();
}

void SPIClass::setFrequency(uint32_t freq) {
    if (_dev == 0) {
        return;
    }
    if (freq == 0) {
        return;
    }
    if (_dev == SPI0 && freq > rcu_clock_freq_get(CK_APB2)) {
        return;
    }
    else if (freq > rcu_clock_freq_get(CK_APB1)) {
        return;
    }
    _freq = freq;
    beginTransaction();
}

void SPIClass::beginTransaction() {
    if (_dev == 0) {
        return;
    }
    spi_parameter_struct param;
    switch (_dataMode) {
    case SPI_MODE0:
        param.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        break;
    case SPI_MODE1:
        param.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
        break;
    case SPI_MODE2:
        param.clock_polarity_phase = SPI_CK_PL_LOW_PH_2EDGE;
        break;
    case SPI_MODE3:
        param.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
        break;
    default:
        return;
    }
    param.device_mode = SPI_MASTER;
    param.endian = _bitOrder == MSBFIRST ? SPI_ENDIAN_MSB : SPI_ENDIAN_LSB;
    param.frame_size = SPI_FRAMESIZE_8BIT;
    param.nss = _ssel_hard ? SPI_NSS_HARD : SPI_NSS_SOFT;
    uint32_t prescale = 0;
    if (_dev == SPI0) {
        prescale = rcu_clock_freq_get(CK_APB2) / _freq - 1;
    }
    else {
        prescale = rcu_clock_freq_get(CK_APB1) / _freq - 1;
    }
    param.prescale = prescale;
    param.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init(_dev, &param);
    spi_enable(_dev);
}