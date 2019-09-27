#include "spi_com.h"

void spi_init(spi_t* obj, uint32_t speed, spi_mode_e mode, uint8_t msb) {
    if (obj->pin_miso >= VARIANT_GPIO_NUM || obj->pin_mosi >= VARIANT_GPIO_NUM
        || obj->pin_sclk >= VARIANT_GPIO_NUM
        || obj->pin_ssel >= VARIANT_GPIO_NUM) {
        return;
    }
    if (PIN_MAP[obj->pin_miso].spi_device == 0
        || PIN_MAP[obj->pin_mosi].spi_device == 0
        || PIN_MAP[obj->pin_sclk].spi_device == 0
        || PIN_MAP[obj->pin_ssel].spi_device == 0) {
        return;
    }
    if (PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_mosi].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_sclk].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_ssel].spi_device->spi_dev) {
        return;
    }
    if (mode >= SPI_MODE_MAX) {
        return;
    }
    rcu_periph_clock_enable(digitalPinToClkid(obj->pin_miso));
    rcu_periph_clock_enable(digitalPinToClkid(obj->pin_mosi));
    rcu_periph_clock_enable(digitalPinToClkid(obj->pin_sclk));
    rcu_periph_clock_enable(digitalPinToClkid(obj->pin_ssel));
    gpio_init(digitalPinToPort(obj->pin_miso), GPIO_MODE_IN_FLOATING,
        GPIO_OSPEED_50MHZ, digitalPinToBitMask(obj->pin_miso));
    gpio_init(digitalPinToPort(obj->pin_mosi), GPIO_MODE_AF_PP,
        GPIO_OSPEED_50MHZ, digitalPinToBitMask(obj->pin_mosi));
    gpio_init(digitalPinToPort(obj->pin_sclk), GPIO_MODE_AF_PP,
        GPIO_OSPEED_50MHZ, digitalPinToBitMask(obj->pin_mosi));
    gpio_init(digitalPinToPort(obj->pin_ssel), GPIO_MODE_AF_PP,
        GPIO_OSPEED_50MHZ, digitalPinToBitMask(obj->pin_mosi));
    rcu_periph_clock_enable(PIN_MAP[obj->pin_miso].spi_device->clk_id);
    spi_i2s_deinit(PIN_MAP[obj->pin_miso].spi_device->spi_dev);
    spi_parameter_struct param;
    switch (mode) {
    case SPI_MODE_0:
        param.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        break;
    case SPI_MODE_1:
        param.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
        break;
    case SPI_MODE_2:
        param.clock_polarity_phase = SPI_CK_PL_LOW_PH_2EDGE;
        break;
    case SPI_MODE_3:
        param.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
        break;
    default:
        param.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        break;
    }
    param.device_mode = SPI_MASTER;
    param.endian = msb ? SPI_ENDIAN_MSB : SPI_ENDIAN_LSB;
    param.frame_size = SPI_FRAMESIZE_8BIT;
    param.nss = SPI_NSS_HARD;
    switch (speed) {
    case SPI_SPEED_CLOCK_DIV2_MHZ:
        param.prescale = SPI_PSC_2;
        break;
    case SPI_SPEED_CLOCK_DIV4_MHZ:
        param.prescale = SPI_PSC_4;
        break;
    case SPI_SPEED_CLOCK_DIV8_MHZ:
        param.prescale = SPI_PSC_8;
        break;
    case SPI_SPEED_CLOCK_DIV16_MHZ:
        param.prescale = SPI_PSC_16;
        break;
    case SPI_SPEED_CLOCK_DIV32_MHZ:
        param.prescale = SPI_PSC_32;
        break;
    case SPI_SPEED_CLOCK_DIV64_MHZ:
        param.prescale = SPI_PSC_64;
        break;
    case SPI_SPEED_CLOCK_DIV128_MHZ:
        param.prescale = SPI_PSC_128;
        break;
    case SPI_SPEED_CLOCK_DIV256_MHZ:
        param.prescale = SPI_PSC_256;
        break;
    }
    param.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init(PIN_MAP[obj->pin_miso].spi_device->spi_dev, &param);
    spi_enable(PIN_MAP[obj->pin_miso].spi_device->spi_dev);
}

void spi_deinit(spi_t* obj) {
    if (obj->pin_miso >= VARIANT_GPIO_NUM || obj->pin_mosi >= VARIANT_GPIO_NUM
        || obj->pin_sclk >= VARIANT_GPIO_NUM
        || obj->pin_ssel >= VARIANT_GPIO_NUM) {
        return;
    }
    if (PIN_MAP[obj->pin_miso].spi_device == 0
        || PIN_MAP[obj->pin_mosi].spi_device == 0
        || PIN_MAP[obj->pin_sclk].spi_device == 0
        || PIN_MAP[obj->pin_ssel].spi_device == 0) {
        return;
    }
    if (PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_mosi].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_sclk].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_ssel].spi_device->spi_dev) {
        return;
    }
    spi_disable(PIN_MAP[obj->pin_miso].spi_device->spi_dev);
    spi_i2s_deinit(PIN_MAP[obj->pin_miso].spi_device->spi_dev);
    rcu_periph_clock_disable(PIN_MAP[obj->pin_miso].spi_device->clk_id);
    gpio_init(digitalPinToPort(obj->pin_miso), GPIO_MODE_AIN, GPIO_OSPEED_50MHZ,
        digitalPinToBitMask(obj->pin_miso));
    gpio_init(digitalPinToPort(obj->pin_mosi), GPIO_MODE_AIN, GPIO_OSPEED_50MHZ,
        digitalPinToBitMask(obj->pin_mosi));
    gpio_init(digitalPinToPort(obj->pin_sclk), GPIO_MODE_AIN, GPIO_OSPEED_50MHZ,
        digitalPinToBitMask(obj->pin_sclk));
    gpio_init(digitalPinToPort(obj->pin_ssel), GPIO_MODE_AIN, GPIO_OSPEED_50MHZ,
        digitalPinToBitMask(obj->pin_ssel));
}

spi_status_e spi_send(
    spi_t* obj, uint8_t* Data, uint16_t len, uint32_t Timeout) {
    if (obj->pin_miso >= VARIANT_GPIO_NUM || obj->pin_mosi >= VARIANT_GPIO_NUM
        || obj->pin_sclk >= VARIANT_GPIO_NUM
        || obj->pin_ssel >= VARIANT_GPIO_NUM) {
        return SPI_ERROR;
    }
    if (PIN_MAP[obj->pin_miso].spi_device == 0
        || PIN_MAP[obj->pin_mosi].spi_device == 0
        || PIN_MAP[obj->pin_sclk].spi_device == 0
        || PIN_MAP[obj->pin_ssel].spi_device == 0) {
        return SPI_ERROR;
    }
    if (PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_mosi].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_sclk].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_ssel].spi_device->spi_dev) {
        return SPI_ERROR;
    }
    if (Data == nullptr) {
        return SPI_ERROR;
    }
    while (len) {
        while (!spi_i2s_flag_get(
            PIN_MAP[obj->pin_ssel].spi_device->spi_dev, SPI_FLAG_TBE)) {
            Timeout--;
            delay(1);
            if (Timeout == 0) {
                return SPI_TIMEOUT;
            }
        }
        spi_i2s_data_transmit(
            PIN_MAP[obj->pin_ssel].spi_device->spi_dev, *Data);
        Data++;
        len--;
    }
    while (spi_i2s_flag_get(
        PIN_MAP[obj->pin_ssel].spi_device->spi_dev, SPI_FLAG_TRANS)) {
        Timeout--;
        delay(1);
        if (Timeout == 0) {
            return SPI_TIMEOUT;
        }
    }
    return SPI_OK;
}

spi_status_e spi_transfer(spi_t* obj, uint8_t* tx_buffer, uint8_t* rx_buffer,
    uint16_t len, uint32_t Timeout) {
    if (obj->pin_miso >= VARIANT_GPIO_NUM || obj->pin_mosi >= VARIANT_GPIO_NUM
        || obj->pin_sclk >= VARIANT_GPIO_NUM
        || obj->pin_ssel >= VARIANT_GPIO_NUM) {
        return SPI_ERROR;
    }
    if (PIN_MAP[obj->pin_miso].spi_device == 0
        || PIN_MAP[obj->pin_mosi].spi_device == 0
        || PIN_MAP[obj->pin_sclk].spi_device == 0
        || PIN_MAP[obj->pin_ssel].spi_device == 0) {
        return SPI_ERROR;
    }
    if (PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_mosi].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_sclk].spi_device->spi_dev
        || PIN_MAP[obj->pin_miso].spi_device->spi_dev
            != PIN_MAP[obj->pin_ssel].spi_device->spi_dev) {
        return SPI_ERROR;
    }
    if (tx_buffer == nullptr) {
        return SPI_ERROR;
    }
    if (rx_buffer == nullptr) {
        return SPI_ERROR;
    }
    while (len) {
        while (!spi_i2s_flag_get(
            PIN_MAP[obj->pin_ssel].spi_device->spi_dev, SPI_FLAG_TBE)) {
            Timeout--;
            delay(1);
            if (Timeout == 0) {
                return SPI_TIMEOUT;
            }
        }
        spi_i2s_data_transmit(
            PIN_MAP[obj->pin_ssel].spi_device->spi_dev, *tx_buffer);
        tx_buffer++;
        while (!spi_i2s_flag_get(
            PIN_MAP[obj->pin_ssel].spi_device->spi_dev, SPI_FLAG_RBNE)) {
            Timeout--;
            delay(1);
            if (Timeout == 0) {
                return SPI_TIMEOUT;
            }
        }
        *rx_buffer
            = spi_i2s_data_receive(PIN_MAP[obj->pin_ssel].spi_device->spi_dev);
        rx_buffer++;
        len--;
    }
    while (spi_i2s_flag_get(
        PIN_MAP[obj->pin_ssel].spi_device->spi_dev, SPI_FLAG_TRANS)) {
        Timeout--;
        delay(1);
        if (Timeout == 0) {
            return SPI_TIMEOUT;
        }
    }
    return SPI_OK;
}