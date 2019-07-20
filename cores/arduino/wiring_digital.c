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

#define pinToPort(p) (_pin_to_port[(uint8_t)(p)])

uint32_t _pin_to_port[80] = {  GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA,
                               GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB,
                               GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC,
                               GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,
                               GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE
};

#define pinToGpioPin(p) (_pin_to_gpio_pin[p])

uint32_t _pin_to_gpio_pin[80] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,   
                                  GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,
                                  GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,
                                  GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,
                                  GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
};

void pinMode(pin_map_t ulPin, PinMode ulMode)
{
    uint8_t mode;
    uint32_t port = pinToPort(ulPin);
    uint32_t pin = pinToGpioPin(ulPin);
    switch (ulMode)
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
        break;
    }
    gpio_init(port, GPIO_OSPEED_10MHZ, mode, pin);
    return;
}

void digitalWrite(pin_map_t ulPin, PinStatus ulVal)
{
    uint32_t port = pinToPort(ulPin);
    uint32_t pin = pinToGpioPin(ulPin);
    if (LOW != ulVal) {
        GPIO_BOP(port) = (uint32_t)pin;
    } else {
        GPIO_BC(port) = (uint32_t)pin;
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
