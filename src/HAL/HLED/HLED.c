#include "HLED_cfg.h"
#include "HLED.h"
#include "rcc.h"
#include "GPIO.h"

extern const HLED_cfg_t HLED_cfg[];
const Peripheral_t GPIOS_Pheripheral_Enable[GPIO_Count] = {
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
    for (int i = 0; i < NUM_OF_LED; i++)
    {
        Loc_enuRCC_Error_Status = RCC_enuCTRLPeripheral(GPIOS_Pheripheral_Enable[HLED_cfg[i].PORT], Peripheral_Enable);
        if (Loc_enuRCC_Error_Status != RCC_OK)
        {
            Loc_enuHLED_Error_Status = HLED_enuRCCErrorToHLEDError(Loc_enuRCC_Error_Status);
            break;
        }
        //         typedef struct{
        //     GPIO_Port_t PORT;
        //     GPIO_PIN_State_t PIN_State;
        //     GPIO_PIN_Speed_t PIN_Speed;
        //     GPIO_PIN_PUPD_t PIN_PUPD;
        //     GPIO_PIN_Moder_t PIN_Mode;
        //     GPIO_PIN_Output_Type_t PIN_Type;
        //     GPIO_PIN_Alernative_Func_t PIN_AF;
        //     GPIO_PIN_Number_t PIN;
        // }PIN_PORT_Conf_t;
        PIN_PORT_Conf_t Loc_strPIN_PORT_Conf = {
            .PORT = HLED_cfg[i].PORT,
            .PIN_State = HLED_cfg[i].Active_State == Active_HIGH ? PIN_LOW : PIN_HIGH,
            .PIN_Speed = HLED_cfg[i].PIN_Speed,
            .PIN_PUPD = No_pull_up_pull_down,
            .PIN_Mode = Mode_General_Purpose_Output,
            .PIN_Type = HLED_cfg[i].PIN_Type,
            .PIN_AF = 0x00,
            .PIN = HLED_cfg[i].PIN

        };
        Loc_enuGPIO_Error_Status =  GPIO_enuPinInit(&Loc_strPIN_PORT_Conf);
        if (Loc_enuGPIO_Error_Status != GPIO_OK)
        {
            Loc_enuHLED_Error_Status = HLED_enuGPIOErrorToHLEDError(Loc_enuGPIO_Error_Status);
        }
        
    }

    return Loc_enuHLED_Error_Status;
}
