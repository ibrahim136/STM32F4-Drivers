#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "rcc.h"
#include "GPIO.h"

extern const HSwitch_cfg_t HSwitch_cfg[NUM_OF_Switches];

const Peripheral_t GPIOS_Pheripheral_Enable[GPIO_Count] = {
    Peripheral_GPIOA,
    Peripheral_GPIOB,
    Peripheral_GPIOC,
    Peripheral_GPIOD,
    Peripheral_GPIOE,
    Peripheral_GPIOH};

static inline HSwitch_Error_Status_t HSwitch_enuRCCErrorToHSwitchError(RCC_Error_Status_t Copy_enuRCC_Error_Status)
{
    HSwitch_Error_Status_t Loc_enuHSwitch_Error_Status;
    switch (Copy_enuRCC_Error_Status)
    {
    case RCC_Timeout:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_Timeout;
        break;
    case RCC_InvalidParam:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_InvalidParam;
        break;
    case RCC_ClockInUse:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_ClockInUse;
        break;
    case RCC_CLKDisabled:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_CLKDisabled;
        break;
    case RCC_PLLEnabled:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_PLLEnabled;
        break;
    case RCC_InvalidPLLDivisiors:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_InvalidPLLDivisiors;
        break;
    case RCC_PLLSRCDisabled:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_PLLSRCDisabled;
        break;
    default:
        Loc_enuHSwitch_Error_Status = HSwitch_OK;
        break;
    }
    return Loc_enuHSwitch_Error_Status;
}

static inline HSwitch_Error_Status_t HSwitch_enuGPIOErrorToHSwitchError(GPIO_Error_Status_t Copy_enuGPIO_Error_Status)
{
    HSwitch_Error_Status_t Loc_enuHSwitch_Error_Status;
    switch (Copy_enuGPIO_Error_Status)
    {
    case GPIO_InvalidParam:
        Loc_enuHSwitch_Error_Status = HSwitch_GPIO_InvalidParam;
        break;
    default:
        Loc_enuHSwitch_Error_Status = HSwitch_OK;
        break;
    }
    return Loc_enuHSwitch_Error_Status;
}

HSwitch_Error_Status_t HSwitch_enuInit()
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    HSwitch_Error_Status_t Loc_enuHSwitch_Error_Status = HSwitch_OK;
}
