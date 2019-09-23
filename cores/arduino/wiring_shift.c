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
    gpio_bit_reset(
        PIN_MAP[clockPin].gpio_device->gpio_port, PIN_MAP[clockPin].gpio_bit);
    for (size_t i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            gpio_bit_write(PIN_MAP[dataPin].gpio_device->gpio_port,
                PIN_MAP[dataPin].gpio_bit, (val & 0x01) == 0 ? RESET : SET);
            val = val >> 1;
        }
        else {
            gpio_bit_write(PIN_MAP[dataPin].gpio_device->gpio_port,
                PIN_MAP[dataPin].gpio_bit, (val & 0x80) == 0 ? RESET : SET);
            val = val << 1;
        }
        gpio_bit_set(PIN_MAP[clockPin].gpio_device->gpio_port,
            PIN_MAP[clockPin].gpio_bit);
        gpio_bit_reset(PIN_MAP[clockPin].gpio_device->gpio_port,
            PIN_MAP[clockPin].gpio_bit);
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
    gpio_bit_reset(
        PIN_MAP[clockPin].gpio_device->gpio_port, PIN_MAP[clockPin].gpio_bit);
    for (size_t i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            ret = ret >> 1;
            ret = ret
                & (gpio_input_bit_get(PIN_MAP[dataPin].gpio_device->gpio_port,
                       PIN_MAP[dataPin].gpio_bit)
                    << 7);
        }
        else {
            ret = ret << 1;
            ret = ret
                & gpio_input_bit_get(PIN_MAP[dataPin].gpio_device->gpio_port,
                    PIN_MAP[dataPin].gpio_bit);
        }
        gpio_bit_set(PIN_MAP[clockPin].gpio_device->gpio_port,
            PIN_MAP[clockPin].gpio_bit);
        gpio_bit_reset(PIN_MAP[clockPin].gpio_device->gpio_port,
            PIN_MAP[clockPin].gpio_bit);
    }
    return ret;
}
