#include <gd32vf103.h>
#include <stdlib.h>
#include "pins_arduino.h"

typedef struct _handler_list_t {
    uint8_t pinId;
    void* handler;
    PinStatus mode;
    void* param;
    struct _handler_list_t* next;
} handler_list_t;

static handler_list_t* handler_list = 0;

static void attachInterruptInternal(handler_list_t* ptr, uint8_t pinId,
    void* callback, PinStatus mode, void* param) {
    eclic_irq_enable(PIN_MAP[pinId].irqn, 0, 0);
    gpio_exti_source_select(pinId >> 4, pinId & 0xF);
    if (mode == RISING) {
        exti_init(pinId & 0xF, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    }
    else if (mode == FALLING) {
        exti_init(pinId & 0xF, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    }
    else if (mode == CHANGE) {
        exti_init(pinId & 0xF, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
    }
    else if (mode == RISING) {
        exti_init(pinId & 0xF, EXTI_INTERRUPT, EXTI_TRIG_NONE);
    }
    exti_interrupt_flag_clear(pinId & 0xF);
    exti_interrupt_enable(pinId & 0xF);
    ptr->handler = callback;
    ptr->pinId = pinId;
    ptr->mode = mode;
    ptr->param = param;
}

void attachInterrupt(pin_size_t pinId, voidFuncPtr callback, PinStatus mode) {
    attachInterruptParam(pinId, (voidFuncPtrParam)callback, mode, 0);
}

void attachInterruptParam(
    pin_size_t pinId, voidFuncPtrParam callback, PinStatus mode, void* param) {
    if (pinId >= VARIANT_GPIO_NUM) {
        return;
    }
    if (callback == 0) {
        return;
    }
    if (handler_list == 0) {
        handler_list = calloc(1, sizeof(handler_list_t));
        attachInterruptInternal(handler_list, pinId, callback, mode, 0);
        handler_list->next = 0;
        return;
    }
    handler_list_t* ptr = handler_list;
    handler_list_t* previousPtr = handler_list;
    while (ptr != 0) {
        if (ptr->pinId == pinId) {
            attachInterruptInternal(ptr, pinId, callback, mode, 0);
            return;
        }
        previousPtr = ptr;
        ptr = ptr->next;
    }
    previousPtr->next = calloc(1, sizeof(handler_list_t));
    ptr = previousPtr->next;
    attachInterruptInternal(ptr, pinId, callback, mode, 0);
    ptr->next = 0;
    return;
}

void detachInterrupt(pin_size_t pinId) {
    if (handler_list == 0) {
        return;
    }
    if (handler_list->pinId == pinId) {
        if (handler_list->next == 0) {
            free(handler_list);
            handler_list = 0;
            return;
        }
        else {
            handler_list_t* ptr = handler_list;
            handler_list = handler_list->next;
            free(ptr);
            return;
        }
    }
    handler_list_t* ptr = handler_list->next;
    handler_list_t* previousPtr = handler_list;
    while (ptr != 0) {
        if (ptr->pinId == pinId) {
            previousPtr->next = ptr->next;
            free(ptr);
            return;
        }
        previousPtr = ptr;
        ptr = ptr->next;
    }
    return;
}

static void generic_IRQHandler(void) {
    handler_list_t* ptr = handler_list;
    while (ptr != 0) {
        if (exti_interrupt_flag_get(ptr->pinId & 0xF)) {
            if (ptr->param == 0) {}
            else {
                ((void (*)(void*))(ptr->handler))(ptr->param);
            }
            exti_interrupt_flag_clear(ptr->pinId & 0xF);
            break;
        }
        ptr = ptr->next;
    }
    return;
}

void __attribute__((interrupt)) EXTI0_IRQHandler(void) { generic_IRQHandler(); }
void __attribute__((interrupt)) EXTI1_IRQHandler(void) { generic_IRQHandler(); }
void __attribute__((interrupt)) EXTI2_IRQHandler(void) { generic_IRQHandler(); }
void __attribute__((interrupt)) EXTI3_IRQHandler(void) { generic_IRQHandler(); }
void __attribute__((interrupt)) EXTI4_IRQHandler(void) { generic_IRQHandler(); }
void __attribute__((interrupt)) EXTI5_9_IRQHandler(void) {
    generic_IRQHandler();
}
void __attribute__((interrupt)) EXTI10_15_IRQHandler(void) {
    generic_IRQHandler();
}
