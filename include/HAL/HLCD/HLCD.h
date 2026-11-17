#ifndef _HLCD_H_
#define _HLCD_H_

#include "GPIO.h"
#include "HLCD_cfg.h"

typedef enum
{
    HLCD_OK,
    HLCD_InvalidCFG,
    HLCD_InvalidPIN,
    HLCD_InvalidCommand,
    HLCD_Busy,
    HLCD_InvalidLCDNumber,
    HLCD_AlreadyInitilized,
    HLCD_LCDLimit,
    HLCD_LCDNotInitilized,

    HLCD_RCC_Timeout,
    HLCD_RCC_InvalidParam,
    HLCD_RCC_ClockInUse,
    HLCD_RCC_CLKDisabled,
    HLCD_RCC_PLLEnabled,
    HLCD_RCC_InvalidPLLDivisiors,
    HLCD_RCC_PLLSRCDisabled,

    HLCD_GPIO_InvalidParam,
    HLCD_Sched_InvalidPeriortyNumber,
    HLCD_Sched_PeriortyNotFree,

} HLCD_Error_Status_t;

typedef struct
{
    GPIO_Port_t PORT;
    GPIO_PIN_Number_t PIN;
} HLCD_PIN_cfg_t;

HLCD_Error_Status_t HLCD_enuInit(LCD_Numbers_t Copy_enuLCDNumber,u8 Copy_u8Priority);
HLCD_Error_Status_t HLCD_enuWriteString(LCD_Numbers_t Copy_enuLCDNumber, u8 *Copy_u8String);
#endif