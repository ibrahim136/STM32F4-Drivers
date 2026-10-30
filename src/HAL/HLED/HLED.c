#include "HLED_cfg.h"
#include "HLED.h"
#include "rcc.h"
#include "GPIO.h"

extern const HLED_cfg_t HLED_cfg[];
const GPIOS_Pheripheral_Enable[GPIO_Count] = {
    Peripheral_GPIOA,
    Peripheral_GPIOB,
    Peripheral_GPIOC,
    Peripheral_GPIOD,
    Peripheral_GPIOE,
    Peripheral_GPIOH};

static inline HLED_Error_Status_t HLED_enuRCCErrorToHLEDError(RCC_Error_Status_t Copy_enuRCC_Error_Status)
{
    HLED_Error_Status_t Loc_enuHLED_Error_Status;
    switch (Copy_enuRCC_Error_Status)
    {
    case RCC_Timeout:
        Loc_enuHLED_Error_Status = HLED_RCC_Timeout;
        break;
    case RCC_InvalidParam:
        Loc_enuHLED_Error_Status = HLED_RCC_InvalidParam;
        break;
    case RCC_ClockInUse:
        Loc_enuHLED_Error_Status = HLED_RCC_ClockInUse;
        break;
    case RCC_CLKDisabled:
        Loc_enuHLED_Error_Status = HLED_RCC_CLKDisabled;
        break;
    case RCC_PLLEnabled:
        Loc_enuHLED_Error_Status = HLED_RCC_PLLEnabled;
        break;
    case RCC_InvalidPLLDivisiors:
        Loc_enuHLED_Error_Status = HLED_RCC_InvalidPLLDivisiors;
        break;
    case RCC_PLLSRCDisabled:
        Loc_enuHLED_Error_Status = HLED_RCC_PLLSRCDisabled;
        break;
    default:
        Loc_enuHLED_Error_Status = RCC_OK;
        break;
    }
    return Loc_enuHLED_Error_Status;
}

static inline HLED_Error_Status_t HLED_enuGPIOErrorToHLEDError(GPIO_Error_Status_t Copy_enuGPIO_Error_Status)
{
    HLED_Error_Status_t Loc_enuHLED_Error_Status;
    switch (Copy_enuGPIO_Error_Status)
    {
    case GPIO_InvalidParam:
        Loc_enuHLED_Error_Status = HLED_GPIO_InvalidParam;
        break;
    default:
        Loc_enuHLED_Error_Status = GPIO_OK;
        break;
    }
    return Loc_enuHLED_Error_Status;
}

HLED_Error_Status_t HLED_enuInit()
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    HLED_Error_Status_t Loc_enuHLED_Error_Status = HLED_OK;
    for (int i=0;i<NUM_OF_LED;i++)
    {
        Loc_enuRCC_Error_Status= RCC_enuCTRLPeripheral(GPIOS_Pheripheral_Enable[HLED_cfg[i].PORT], Peripheral_Enable);
        if (Loc_enuRCC_Error_Status != RCC_OK){
            Loc_enuHLED_Error_Status = HLED_enuRCCErrorToHLEDError(Loc_enuRCC_Error_Status);
            break;
        }
        
    }



    return Loc_enuHLED_Error_Status;
}

