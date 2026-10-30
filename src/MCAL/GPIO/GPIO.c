#include "GPIO_priv.h"
#include "GPIO.h"
#include "Bit_math.h"
#include "STD_types.h"

static volatile GPIO_reg_t *GPIOS[GPIO_COUNT] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH};

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

static inline GPIO_Error_Status_t STATE_Check(GPIO_PIN_State_t Copy_enuPINState)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    switch (Copy_enuPINState)
    {
    case PIN_LOW ... PIN_State_Count - 1:
        break;
    default:
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
        break;
    }
    return Loc_enuGPIO_Error_Status;
}

static inline GPIO_Error_Status_t PIN_CONF_Check(PIN_PORT_Conf_t * Ref_strPINConf){
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    if (!Ref_strPINConf)
    {
        Loc_enuGPIO_Error_Status = GPIO_InvalidParam;
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PORT_Check(Ref_strPINConf->PORT);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PIN_Check(Ref_strPINConf->PIN);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = MODE_Check(Ref_strPINConf->PIN_Mode);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = SPEED_Check(Ref_strPINConf->PIN_Speed);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = PUPD_Check(Ref_strPINConf->PIN_PUPD);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = AF_Check(Ref_strPINConf->PIN_AF);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = STATE_Check(Ref_strPINConf->PIN_State);
    }
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        Loc_enuGPIO_Error_Status = TYPE_Check(Ref_strPINConf->PIN_Type);
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
            Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRH, Masking_Value(GPIO_AF_MASK, Quad_pos(Low_to_high_shif(Copy_enuPIN))));
            Set_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRH, Masking_Value(Copy_enuPINAF, Quad_pos(Low_to_high_shif(Copy_enuPIN))));
            break;
        default:
            break;
        }
    }
    return Loc_enuGPIO_Error_Status;
}



GPIO_Error_Status_t GPIO_enuPinInit(PIN_PORT_Conf_t * Ref_strPINConf)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PIN_CONF_Check(Ref_strPINConf);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        switch (Ref_strPINConf->PIN_State) //low or high
        {
        case PIN_LOW:
            GPIOS[Ref_strPINConf->PORT]->GPIO_BSRR = Masking_bit(BR(Ref_strPINConf->PIN));
            break;
        default:
            GPIOS[Ref_strPINConf->PORT]->GPIO_BSRR = Masking_bit(BS(Ref_strPINConf->PIN));
            break;
        }
        //setting speed
        Clear_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_OSPEEDR, Masking_Value(GPIO_OSPEEDR_MASK, Double_pos(Ref_strPINConf->PIN)));
        Set_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_OSPEEDR, Masking_Value(Ref_strPINConf->PIN_Speed, Double_pos(Ref_strPINConf->PIN)));

        //setting PUPD
        Clear_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_PUPDR, Masking_Value(GPIO_PUPDR_MASK, Double_pos(Ref_strPINConf->PIN)));
        Set_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_PUPDR, Masking_Value(Ref_strPINConf->PIN_PUPD, Double_pos(Ref_strPINConf->PIN)));

        //setting Mode
        Clear_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_MODER, Masking_Value(GPIO_MODE_MASK, Double_pos(Ref_strPINConf->PIN)));
        Set_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_MODER, Masking_Value(Ref_strPINConf->PIN_Mode, Double_pos(Ref_strPINConf->PIN)));

        //setting Type
        Clear_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_OTYPER, Masking_Value(GPIO_Type_MASK, Ref_strPINConf->PIN));
        Set_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_OTYPER, Masking_Value(Ref_strPINConf->PIN_Type, Ref_strPINConf->PIN));

        //setting AF
        switch (Ref_strPINConf->PIN)
        {
        case PIN0 ... PIN7:
            Clear_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_AFRL, Masking_Value(GPIO_AF_MASK, Quad_pos(Ref_strPINConf->PIN)));
            Set_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_AFRL, Masking_Value(Ref_strPINConf->PIN_AF, Quad_pos(Ref_strPINConf->PIN)));
            break;
        default:
            Clear_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_AFRH, Masking_Value(GPIO_AF_MASK, Quad_pos(Low_to_high_shif(Ref_strPINConf->PIN))));
            Set_Mask(GPIOS[Ref_strPINConf->PORT]->GPIO_AFRH, Masking_Value(Ref_strPINConf->PIN_AF, Quad_pos(Low_to_high_shif(Ref_strPINConf->PIN))));
            break;
        }

    }



    return Loc_enuGPIO_Error_Status;
}

static inline volatile u32 GPIO_u32OneBitMode (u32 Copy_u32Reg,u8 Copy_BitsToSet)
{
    volatile u32 Loc_u32Reg = Copy_u32Reg;
    for (u8 i =0;i<16;i++){
        Loc_u32Reg <<= 1;
        Loc_u32Reg |= Copy_BitsToSet;
    }
    return Loc_u32Reg;
}
static inline volatile u32 GPIO_u32TwoBitMode (u32 Copy_u32Reg,u8 Copy_BitsToSet)
{
    volatile u32 Loc_u32Reg = Copy_u32Reg;
    for (u8 i =0;i<16;i++){
        Loc_u32Reg <<= 2;
        Loc_u32Reg |= Copy_BitsToSet;
    }
    return Loc_u32Reg;
}
static inline volatile u32 GPIO_u32FourBitMode (u32 Copy_u32Reg,u8 Copy_BitsToSet)
{
    volatile u32 Loc_u32Reg = Copy_u32Reg;
    for (u8 i =0;i<16;i++){
        Loc_u32Reg <<= 4;
        Loc_u32Reg |= Copy_BitsToSet;
    }
    return Loc_u32Reg;
    
}

static inline void GPIO_voidClearingAllRegByMasking(GPIO_Port_t Copy_enuPORT )
{
    Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_MODER,GPIO_Moder_Reg_MASK);
    Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_OSPEEDR,GPIO_OSPEEDR_Reg_MASK);
    Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_PUPDR,GPIO_PUPDR_Reg_MASK);
    Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRL,GPIO_AFRL_Reg_MASK);
    Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_AFRH,GPIO_AFRH_Reg_MASK);
    Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_ODR,GPIO_ODR_Reg_MASK);
    Clear_Mask(GPIOS[Copy_enuPORT]->GPIO_OTYPER,GPIO_OTYPER_Reg_MASK);
}

GPIO_Error_Status_t GPIO_enuPORTInit(PIN_PORT_Conf_t * Ref_strPORTConf)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    Loc_enuGPIO_Error_Status = PIN_CONF_Check(Ref_strPORTConf);
    if (Loc_enuGPIO_Error_Status == GPIO_OK)
    {
        GPIO_voidClearingAllRegByMasking(Ref_strPORTConf->PORT);

        volatile u32 Loc_u32ModeReg = GPIO_u32TwoBitMode(GPIOS[Ref_strPORTConf->PORT]->GPIO_MODER,Ref_strPORTConf->PIN_Mode);
        volatile u32 Loc_u32TypeReg = GPIO_u32OneBitMode(GPIOS[Ref_strPORTConf->PORT]->GPIO_OTYPER,Ref_strPORTConf->PIN_Type);
        volatile u32 Loc_u32SpeedReg = GPIO_u32TwoBitMode(GPIOS[Ref_strPORTConf->PORT]->GPIO_OSPEEDR,Ref_strPORTConf->PIN_Speed);
        volatile u32 Loc_u32PUPDReg = GPIO_u32TwoBitMode(GPIOS[Ref_strPORTConf->PORT]->GPIO_PUPDR,Ref_strPORTConf->PIN_PUPD);
        volatile u32 Loc_u32ODRReg = GPIO_u32OneBitMode(GPIOS[Ref_strPORTConf->PORT]->GPIO_ODR,Ref_strPORTConf->PIN_State);
        volatile u32 Loc_u32AFRLReg = GPIO_u32FourBitMode(GPIOS[Ref_strPORTConf->PORT]->GPIO_AFRL,Ref_strPORTConf->PIN_AF);
        volatile u32 Loc_u32AFRHReg = GPIO_u32FourBitMode(GPIOS[Ref_strPORTConf->PORT]->GPIO_AFRH,Ref_strPORTConf->PIN_AF);

        GPIOS[Ref_strPORTConf->PORT]->GPIO_MODER = Loc_u32ModeReg;
        GPIOS[Ref_strPORTConf->PORT]->GPIO_OTYPER = Loc_u32TypeReg;
        GPIOS[Ref_strPORTConf->PORT]->GPIO_OSPEEDR = Loc_u32SpeedReg;
        GPIOS[Ref_strPORTConf->PORT]->GPIO_PUPDR = Loc_u32PUPDReg;
        GPIOS[Ref_strPORTConf->PORT]->GPIO_ODR = Loc_u32ODRReg;
        GPIOS[Ref_strPORTConf->PORT]->GPIO_AFRL = Loc_u32AFRLReg;
        GPIOS[Ref_strPORTConf->PORT]->GPIO_AFRH = Loc_u32AFRHReg;
    }
    return Loc_enuGPIO_Error_Status;
}