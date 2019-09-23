#include "gd32vf103.h"
#include "pins_arduino.h"

uint8_t analog_reference = DEFAULT;
uint8_t b_adc_initialized = 0;

static void testInitAnalogRead(void) {
    if (b_adc_initialized == 0) {
        /* configure clock */
        rcu_periph_clock_enable(RCU_ADC0);
        rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV2);
        /* reset ADC0 */
        adc_deinit(ADC0);
        /* configure ADC0 */
        adc_external_trigger_source_config(
            ADC0, ADC_INSERTED_CHANNEL, ADC0_1_EXTTRIG_INSERTED_NONE);
        adc_external_trigger_config(ADC0, ADC_INSERTED_CHANNEL, ENABLE);
        adc_channel_length_config(ADC0, ADC_INSERTED_CHANNEL, 1);
        adc_enable(ADC0);
        delayMicroseconds(1000);
        adc_calibration_enable(ADC0);
        b_adc_initialized = 1;
    }
}

void analogReference(AnalogReferenceMode mode) {
#ifdef _VARIANT_SIPEED_LONGAN_NANO
    /* Longan nano does not have external vref pin, do nothing here */
#else
    analog_reference = mode;
#endif
}

int analogRead(pin_size_t pinNumber) {
    if (pinNumber > VARIANT_GPIO_NUM) {
        return -1;
    }
    testInitAnalogRead();
#ifdef _VARIANT_SIPEED_LONGAN_NANO
    if (PIN_MAP[pinNumber].adc_device != 0
        && PIN_MAP[pinNumber].gpio_device != 0) {
        adc_inserted_channel_config(
            ADC0, 0, PIN_MAP[pinNumber].adc_channel, ADC_SAMPLETIME_1POINT5);
        adc_flag_clear(ADC0, ADC_FLAG_EOIC);
        adc_software_trigger_enable(ADC0, ADC_INSERTED_CHANNEL);
        while (adc_flag_get(ADC0, ADC_FLAG_EOIC) != SET) {
            delayMicroseconds(1);
        }
        return ADC_IDATA0(ADC0);
    }
    else {
        return -1;
    }
#endif
}
