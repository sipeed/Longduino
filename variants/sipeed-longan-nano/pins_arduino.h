#ifndef _VARIANT_SIPEED_LONGAN_NANO
#define _VARIANT_SIPEED_LONGAN_NANO

#include "Arduino.h"
#include "gd32vf103.h"
#include "gd32vf103_libopt.h"

/* BOARD  PIN DEFINE */

/* LEDs */
#define LED_BUILTIN  PC13
#define LED_RED      PC13
#define LED_GREEN    PA1
#define LED_BLUE     PA2

#ifdef __cplusplus
extern "C" {
#endif

/* Pin aliases: these give the GPIO port/bit for each pin as an
 * enum. These are optional, but recommended. They make it easier to
 * write code using low-level GPIO functionality. */
enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
};

typedef struct _gpio_dev_t
{
    uint32_t gpio_port;
    rcu_periph_enum clk_id;

}gpio_dev_t;

typedef struct _adc_dev_t
{
    uint32_t adc_dev;
    rcu_periph_enum clk_id;

}adc_dev_t;

typedef struct _timer_dev_t {
    uint32_t timer_dev;
    rcu_periph_enum clk_id;
}timer_dev_t;

typedef struct _gd32v_pin_info_t
{
    gpio_dev_t * gpio_device;
    timer_dev_t * timer_device;
    adc_dev_t * adc_device;
    uint8_t gpio_bit;
    uint8_t timer_channel;
    uint8_t adc_channel;
    IRQn_Type irqn;
} gd32v_pin_info_t;

#define VARIANT_GPIO_NUM (80)

extern const gd32v_pin_info_t PIN_MAP[VARIANT_GPIO_NUM];

#define digitalPinToPort(p) ((PIN_MAP[p].gpio_device)->gpio_port)
#define digitalPinToBitMask(p) (BIT(PIN_MAP[p].gpio_bit))
#define digitalPinToClkid(p) (PIN_MAP[p].gpio_device->clk_id)


#define VARIANT_GPIO_OSPEED GPIO_OSPEED_50MHZ //

#ifdef __cplusplus
}
#endif

#endif