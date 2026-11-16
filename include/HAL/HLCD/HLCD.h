#ifndef _HLCD_H_
#define _HLCD_H_

#include "GPIO.h"


typedef enum
{
    HLCD_OK,
    HLCD_InvalidCFG,
    HLCD_InvalidPIN,
    HLCD_InvalidCommand,
    HLCD_Busy,

    HLCD_RCC_Timeout,
    HLCD_RCC_InvalidParam,
    HLCD_RCC_ClockInUse,
    HLCD_RCC_CLKDisabled,
    HLCD_RCC_PLLEnabled,
    HLCD_RCC_InvalidPLLDivisiors,
    HLCD_RCC_PLLSRCDisabled,

    HLCD_GPIO_InvalidParam
} HLCD_Error_Status_t;

typedef struct
{
    GPIO_Port_t PORT;
    GPIO_PIN_Number_t PIN;
} HLCD_PIN_cfg_t;

#endif