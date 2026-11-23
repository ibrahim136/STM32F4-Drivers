#ifndef _Calculator_H_
#define _Calculator_H_

#include "HLCD.h"

typedef enum
{
    Calculator_OK,
    Calculator_InvalidParam,
    Calculator_InvalidSwitch,
    Calculator_InvalCalculator,
    Calculator_InvalidLCD,

    Calculator_RCC_Timeout,
    Calculator_RCC_InvalidParam,
    Calculator_RCC_ClockInUse,
    Calculator_RCC_CLKDisabled,
    Calculator_RCC_PLLEnabled,
    Calculator_RCC_InvalidPLLDivisiors,
    Calculator_RCC_PLLSRCDisabled,


    Calculator_GPIO_InvalidParam
} Calculator_Error_Status_t;

Calculator_Error_Status_t Calculatorenu_On(LCD_Numbers_t Copy_enuLCD);

#endif