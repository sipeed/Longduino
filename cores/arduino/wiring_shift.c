#include "gd32vf103.h"
#include "pins_arduino.h"
#include <stdint.h>

void shiftOut(
    pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t val) {
    if (dataPin > VARIANT_GPIO_NUM) {
        return;
    }
    if (clockPin > VARIANT_GPIO_NUM) {
        return;
    }
    gpio_bit_reset(digitalPinToPort(clockPin), digitalPinToBitMask(clockPin));
    for (size_t i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            gpio_bit_write(digitalPinToPort(dataPin),
                digitalPinToBitMask(dataPin), (val & 0x01) == 0 ? RESET : SET);
            val = val >> 1;
        }
        else {
            gpio_bit_write(digitalPinToPort(dataPin),
                digitalPinToBitMask(dataPin), (val & 0x80) == 0 ? RESET : SET);
            val = val << 1;
        }
        gpio_bit_set(digitalPinToPort(clockPin), digitalPinToBitMask(clockPin));
        gpio_bit_reset(
            digitalPinToPort(clockPin), digitalPinToBitMask(clockPin));
    }
}

pin_size_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder) {
    pin_size_t ret = 0;
    if (dataPin > VARIANT_GPIO_NUM) {
        return 0;
    }
    if (clockPin > VARIANT_GPIO_NUM) {
        return 0;
    }
    gpio_bit_reset(digitalPinToPort(clockPin), digitalPinToBitMask(clockPin));
    for (size_t i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            ret = ret >> 1;
            ret = ret
                & (gpio_input_bit_get(
                       digitalPinToPort(dataPin), digitalPinToBitMask(dataPin))
                    << 7);
        }
        else {
            ret = ret << 1;
            ret = ret
                & gpio_input_bit_get(
                    digitalPinToPort(dataPin), digitalPinToBitMask(dataPin));
        }
        gpio_bit_set(digitalPinToPort(clockPin), digitalPinToBitMask(clockPin));
        gpio_bit_reset(
            digitalPinToPort(clockPin), digitalPinToBitMask(clockPin));
    }
    return ret;
}
