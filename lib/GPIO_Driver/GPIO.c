#include "GPIO_priv.h"
#include "GPIO.h"
#include "Bit_math.h"
#include "STD_types.h"

static volatile GPIO_reg_t *GPIOS[6] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH};

static inline GPIO_Error_Status_t PORT_Check(GPIO_Port_t Copy_enuPORT)
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
    return Loc_enuGPIO_Error_Status;
}

static inline GPIO_Error_Status_t PIN_Check(GPIO_PIN_Number_t Copy_enuPIN)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    switch (Copy_enuPIN)
    {
    case PIN0 ... PIN_COUNT - 1:
        break;
    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    return Loc_enuGPIO_Error_Status;
}

static inline GPIO_Error_Status_t SPEED_Check(GPIO_PIN_Speed_t Copy_enuPINSpeed)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    switch (Copy_enuPINSpeed)
    {
    case Low_Speed ... Speed_Count - 1:
        break;
    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    return Loc_enuGPIO_Error_Status;
}

static inline GPIO_Error_Status_t PUPD_Check(GPIO_PIN_PUPD_t Copy_enuPINPUPD)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    switch (Copy_enuPINPUPD)
    {
    case No_pull_up_pull_down ... PUPD_Count - 1:
        break;
    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    return Loc_enuGPIO_Error_Status;
}

static inline GPIO_Error_Status_t MODE_Check(GPIO_PIN_Moder_t Copy_enuPINMODE)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    switch (Copy_enuPINMODE)
    {
    case Mode_Input ... Mode_Count - 1:
        break;
    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    return Loc_enuGPIO_Error_Status;
}

static inline GPIO_Error_Status_t TYPE_Check(GPIO_PIN_Output_Type_t Copy_enuPINOutType)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    switch (Copy_enuPINOutType)
    {
    case Push_Pull ... Type_Count - 1:
        break;
    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    return Loc_enuGPIO_Error_Status;
}

static inline GPIO_Error_Status_t AF_Check(GPIO_PIN_Alernative_Func_t Copy_enuPINAF)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    switch (Copy_enuPINAF)
    {
    case AF0 ... AF_Count - 1:
        break;
    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuPinWrite(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_State_t Copy_enuState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Copy_enuPIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        switch (Copy_enuState)
        {
        case PIN_LOW:
        {
            GPIOS[Copy_enuPORT]->GPIO_BSRR = Masking_bit(BR(Copy_enuPIN));
            break;
        }
        case PIN_HIGH:
        {
            GPIOS[Copy_enuPORT]->GPIO_BSRR = Masking_bit(BS(Copy_enuPIN));
            break;
        }
        default:
            Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
            break;
        }
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuPinRead(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_State_t *Ref_enuState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    if (!Ref_enuState)
    {
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Copy_enuPIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        *Ref_enuState = (GPIO_PIN_State_t)Get_bit(GPIOS[Copy_enuPORT]->GPIO_IDR, Copy_enuPIN);
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuPORTWrite(GPIO_Port_t Copy_enuPORT, u16 Copy_u16PORTState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        GPIOS[Copy_enuPORT]->GPIO_ODR = Copy_u16PORTState;
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuPORTRead(GPIO_Port_t Copy_enuPORT, u16 *Ref_u16PORTState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    if (!Ref_u16PORTState)
    {
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        *Ref_u16PORTState = GPIOS[Copy_enuPORT]->GPIO_IDR;
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuCfgSpeed(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_Speed_t Copy_enuPINSpeed)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Copy_enuPIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = SPEED_Check(Copy_enuPINSpeed);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_OSPEEDR, Masking_Value(GPIO_OSPEEDR_MASK, Double_pos(Copy_enuPIN)));
        Set_Mask(GPIOS[Copy_enuPORT]->GPIO_OSPEEDR, Masking_Value(Copy_enuPINSpeed, Double_pos(Copy_enuPIN)));
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuCfgPINPUPD(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_PUPD_t Copy_enuPINPUPD)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Copy_enuPIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PUPD_Check(Copy_enuPINPUPD);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_PUPDR, Masking_Value(GPIO_PUPDR_MASK, Double_pos(Copy_enuPIN)));
        Set_Mask(GPIOS[Copy_enuPORT]->GPIO_PUPDR, Masking_Value(Copy_enuPINPUPD, Double_pos(Copy_enuPIN)));
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuCfgPINMode(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_Moder_t Copy_enuPINMODE)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Copy_enuPIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = MODE_Check(Copy_enuPINMODE);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_MODER, Masking_Value(GPIO_MODE_MASK, Double_pos(Copy_enuPIN)));
        Set_Mask(GPIOS[Copy_enuPORT]->GPIO_MODER, Masking_Value(Copy_enuPINMODE, Double_pos(Copy_enuPIN)));
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuCfgPINOutType(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_Output_Type_t Copy_enuPINOutType)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Copy_enuPIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = TYPE_Check(Copy_enuPINOutType);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_OTYPER, Masking_Value(GPIO_Type_MASK, Copy_enuPIN));
        Set_Mask(GPIOS[Copy_enuPORT]->GPIO_OTYPER, Masking_Value(Copy_enuPINOutType, Copy_enuPIN));
    }
    return Loc_enuGPIO_Error_Status;
}

GPIO_Error_Status_t GPIO_enuCfgPINAlternativeFunc(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_Alernative_Func_t Copy_enuPINAF)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PORT_Check(Copy_enuPORT);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Copy_enuPIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = AF_Check(Copy_enuPINAF);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        switch (Copy_enuPIN)
        {
        case PIN0 ... PIN7:
            Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRL, Masking_Value(GPIO_AF_MASK, Quad_pos(Copy_enuPIN)));
            Set_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRL, Masking_Value(Copy_enuPINAF, Quad_pos(Copy_enuPIN)));
            break;
        case PIN8 ... PIN15:
            Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRL, Masking_Value(GPIO_AF_MASK, Quad_pos(Low_to_high_shif(Copy_enuPIN))));
            Set_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRL, Masking_Value(Copy_enuPINAF, Quad_pos(Low_to_high_shif(Copy_enuPIN))));
            break;
        default:
            break;
        }
    }
    return Loc_enuGPIO_Error_Status;
}