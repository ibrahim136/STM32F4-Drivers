#ifndef _HSwitch_H_
#define _HSwitch_H_

#include "GPIO.h"

typedef enum
{
    HSwitch_OK,

    
    HSwitch_RCC_Timeout,
    HSwitch_RCC_InvalidParam,
    HSwitch_RCC_ClockInUse,
    HSwitch_RCC_CLKDisabled,
    HSwitch_RCC_PLLEnabled,
    HSwitch_RCC_InvalidPLLDivisiors,
    HSwitch_RCC_PLLSRCDisabled,


    HSwitch_GPIO_InvalidParam
} HSwitch_Error_Status_t;

typedef enum
{
    Pressed_High,
    Pressed_Low
}Pressed_State_t;

typedef struct{
    GPIO_Port_t PORT;
    GPIO_PIN_Number_t PIN;
    GPIO_PIN_PUPD_t PIN_PUPD;
    Pressed_State_t Pressed_State;
}HSwitch_cfg_t;

HSwitch_Error_Status_t HSwitch_enuInit();







#endif