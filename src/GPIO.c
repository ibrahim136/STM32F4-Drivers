#include "GPIO_priv.h"
#include "GPIO.h"
#include "Bit_math.h"
#include "STD_types.h"

GPIO_reg_t *GPIOS[6] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH};

GPIO_Error_Status_t GPIO_enuPinWrite(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t COPY_enuPIN, GPIO_PIN_State_t Copy_enuState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    u32 Loc_u32TimeOut = TIMEOUT;
    switch (Copy_enuPORT)
    {
    case GPIO_PORTA ... GPIO_Count - 1:
        break;

    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        switch (COPY_enuPIN)
        {
        case PIN0 ... PIN_COUNT - 1:
            break;
        default:
            Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
            break;
        }
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        switch (Copy_enuState)
        {
        case PIN_LOW:
        {
            u32 Loc_u32GPIOBSRR = 0x00;
            Set_Bit(Loc_u32GPIOBSRR, BR(COPY_enuPIN));
            GPIOS[Copy_enuPORT]->GPIO_BSRR = Loc_u32GPIOBSRR;
            break;
        }
        case PIN_HIGH:
        {
            u32 Loc_u32GPIOBSRR = 0x00;
            Set_Bit(Loc_u32GPIOBSRR, BS(COPY_enuPIN));
            GPIOS[Copy_enuPORT]->GPIO_BSRR = Loc_u32GPIOBSRR;
            break;
        }
        default:
            Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
            break;
        }
    }
    return Loc_enuGPIO_Error_Status;
}

