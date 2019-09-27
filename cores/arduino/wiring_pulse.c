#include "gd32vf103.h"
#include "pins_arduino.h"
#include <stdint.h>

#define _ClockCyclesPerMicrosecond() (SystemCoreClock / 1000000)
#define _ClockCyclesToMicroseconds(n) (n * 1000000 / SystemCoreClock)

union _mcycle_full {
    uint64_t v;
    uint32_t v_part[2];
};


static inline uint64_t get_mcycle(void) {
    union _mcycle_full ret;
    __asm("rdcycle %[l]" : [ l ] "=r"(ret.v_part[0]) :);
    __asm("rdcycleh %[h]" : [ h ] "=r"(ret.v_part[1]) :);
    return ret.v;
}

unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout) {
    if (pin > VARIANT_GPIO_NUM) {
        return 0;
    }
    uint64_t timeoutInCycles = timeout * _ClockCyclesPerMicrosecond();
    uint64_t start = get_mcycle();
    while (gpio_input_bit_get(digitalPinToPort(pin), digitalPinToBitMask(pin))
        != state) {
        if (get_mcycle() - start > timeoutInCycles) {
            return 0;
        }
    }
    uint64_t pulseBegin = get_mcycle();
    while (gpio_input_bit_get(digitalPinToPort(pin), digitalPinToBitMask(pin))
        == state) {
        if (get_mcycle() - start > timeoutInCycles) {
            return 0;
        }
    }
    uint64_t pulseEnd = get_mcycle();
    return _ClockCyclesToMicroseconds(pulseEnd - pulseBegin);
}

unsigned long pulseInLong(
    pin_size_t pin, uint8_t state, unsigned long timeout) {
    /* as counted cycles are based on mcycle[h] */
    return pulseIn(pin, state, timeout);
}