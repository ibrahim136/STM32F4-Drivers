#ifndef _HLED_H_
#define _HLED_H_

#include "GPIO.h"

typedef enum
{
    HLED_OK,

    
    HLED_RCC_Timeout,
    HLED_RCC_InvalidParam,
    HLED_RCC_ClockInUse,
    HLED_RCC_CLKDisabled,
    HLED_RCC_PLLEnabled,
    HLED_RCC_InvalidPLLDivisiors,
    HLED_RCC_PLLSRCDisabled,


    HLED_GPIO_InvalidParam
} HLED_Error_Status_t;

typedef enum{
    Active_HIGH,
    Active_LOW,
    NUM_OF_STATES
}HLED_Active_state_t;

typedef struct{
    GPIO_Port_t PORT;
    GPIO_PIN_Number_t PIN;
    GPIO_PIN_Speed_t PIN_Speed;
    GPIO_PIN_Output_Type_t PIN_Type;
    HLED_Active_state_t Active_State;
}HLED_cfg_t;

HLED_Error_Status_t HLED_enuInit();
HLED_Error_Status_t HLED_enuTurnOn(HLED_LEDS_t Copy_enuLED);
HLED_Error_Status_t HLED_enuTurnOff(HLED_LEDS_t Copy_enuLED);
HLED_Error_Status_t HLED_enuToggle(HLED_LEDS_t Copy_enuLED);






#endif