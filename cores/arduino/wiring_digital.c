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
    case INPUT_ANALOG:
        mode = GPIO_MODE_AIN;
        break;
    case OUTPUT_ANALOG:
        mode = GPIO_MODE_AF_PP;
        break;
    default:
        return;
    }
    rcu_periph_clock_enable(digitalPinToClkid(pinNumber));
    gpio_init(digitalPinToPort(pinNumber), mode, VARIANT_GPIO_OSPEED, digitalPinToBitMask(pinNumber));
    GPIO_BC(digitalPinToPort(pinNumber)) = digitalPinToBitMask(pinNumber);
    return;
}

void digitalWrite(pin_size_t pinNumber , PinStatus status)
{
    if (pinNumber >= VARIANT_GPIO_NUM) return;
    if (LOW != status) {
        //gpio_bit_set(PIN_MAP[pinNumber].gpio_device->gpio_port, PIN_MAP[pinNumber].gpio_bit);
        GPIO_BOP(digitalPinToPort(pinNumber)) = digitalPinToBitMask(pinNumber);
    } else {
       //gpio_bit_reset(PIN_MAP[pinNumber].gpio_device->gpio_port, PIN_MAP[pinNumber].gpio_bit);
        GPIO_BC(digitalPinToPort(pinNumber)) = digitalPinToBitMask(pinNumber);
    }
    return;
}

PinStatus digitalRead(pin_size_t pinNumber)
{
    if (pinNumber >= VARIANT_GPIO_NUM) return LOW;

    if ((uint32_t) LOW != (GPIO_ISTAT(digitalPinToPort(pinNumber)) & digitalPinToBitMask(pinNumber))) {
        return HIGH;
    } else {
        return LOW;
    }
}

void digitalToggle(pin_size_t pinNumber)
{
    return gpio_bit_write(digitalPinToPort(pinNumber), digitalPinToBitMask(pinNumber), !gpio_output_bit_get(digitalPinToPort(pinNumber), digitalPinToBitMask(pinNumber)));
}


#ifdef __cplusplus
}
#endif
