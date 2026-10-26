#include "GPIO_priv.h"
#include "GPIO.h"
#include "Bit_math.h"
#include "STD_types.h"

static volatile GPIO_reg_t *GPIOS[6] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH};

GPIO_Error_Status_t GPIO_enuPinWrite(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t COPY_enuPIN, GPIO_PIN_State_t Copy_enuState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
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
            GPIOS[Copy_enuPORT]->GPIO_BSRR = Masking_bit ( BR(COPY_enuPIN));
            break;
        }
        case PIN_HIGH:
        {
            GPIOS[Copy_enuPORT]->GPIO_BSRR = Masking_bit ( BS(COPY_enuPIN));
            break;
        }
        default:
            Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
            break;
        }
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuPinRead(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t COPY_enuPIN, GPIO_PIN_State_t* Ref_enuState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    if (!Ref_enuState)
    {
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
    }
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
        *Ref_enuState = (GPIO_PIN_State_t) Get_bit (GPIOS[Copy_enuPORT]->GPIO_IDR,COPY_enuPIN);
    }
    return Loc_enuGPIO_Error_Status;
}



