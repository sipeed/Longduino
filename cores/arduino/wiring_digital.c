/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "gd32vf103_gpio.h"

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

void pinMode(pin_size_t pinNumber, PinMode pinMode)
{
    if (pinNumber >= VARIANT_GPIO_NUM) return;
    uint8_t mode;
    switch (pinMode)
    {
    case INPUT:
        mode = GPIO_MODE_IN_FLOATING;
        break;
    case OUTPUT:
        mode = GPIO_MODE_OUT_PP;
        break;
    case INPUT_PULLUP:
        mode = GPIO_MODE_IPU;
        break;
    case INPUT_PULLDOWN:
        mode = GPIO_MODE_IPD;
        break;
    default:
        return;
    }
    rcu_periph_clock_enable(PIN_MAP[pinNumber].gpio_device->clk_id);
    gpio_init(PIN_MAP[pinNumber].gpio_device->gpio_port, VARIANT_GPIO_OSPEED, mode, PIN_MAP[pinNumber].gpio_bit);
    GPIO_BC(PIN_MAP[pinNumber].gpio_device->gpio_port) = (uint32_t)PIN_MAP[pinNumber].gpio_bit;
    return;
}

void digitalWrite(pin_size_t pinNumber , PinStatus status)
{
    if (pinNumber >= VARIANT_GPIO_NUM) return;
    if (LOW != status) {
        GPIO_BOP(PIN_MAP[pinNumber].gpio_device->gpio_port) = (uint32_t)PIN_MAP[pinNumber].gpio_bit;
    } else {
        GPIO_BC(PIN_MAP[pinNumber].gpio_device->gpio_port) = (uint32_t)PIN_MAP[pinNumber].gpio_bit;
    }
    return;
}

// PinStatus digitalRead(pin_map_t ulPin)
// {
//     if ((uint32_t) LOW != (GPIO_ISTAT(pinToPort(ulPin)) & (pinToGpioPin(ulPin)))) {
//         return HIGH;
//     } else {
//         return LOW;
//     }
// }

// void digitalToggle(pin_map_t ulPin)
// {
//     return gpio_bit_write(pinToPort(ulPin), pinToGpioPin(ulPin), gpio_output_bit_get(pinToPort(ulPin), pinToGpioPin(ulPin)));
// }


#ifdef __cplusplus
}
#endif
