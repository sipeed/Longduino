#ifndef _VARIANT_GD32VF103_EVAL
#define _VARIANT_GD32VF103_EVAL

#include "Arduino.h"
#include "gd32vf103_gpio.h"

/* BOARD  PIN DEFINE */

/* LEDs */
#define LED_BUILTIN  PC0

#ifdef __cplusplus
extern "C" {
#endif


typedef enum{
    PA0 = 0,
    PA1 = 1,
    PA2 = 2,
    PB0 = 16,
    PC0 = 32,
    PD0 = 48,
    PE0 = 64
} pin_map_t;



#ifdef __cplusplus
}
#endif

#endif