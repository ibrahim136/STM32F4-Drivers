#include "rcc.h"
#include "rcc_priv.h"
#include "Bit_math.h"

RCC_Error_Status_t RCC_enuCLKControl(CLK_Type_t Copy_enuCLKType, CLK_Status_t Copy_enuCLKStatus)
{
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    u32 Loc_u32TimeOut = TIMEOUT;
    u8 Loc_u8targetbit;
    u8 Loc_u8readytbit;
    u8 Loc_u8check;
    switch (Copy_enuCLKType)
    {
    case HSI:
        Loc_u8targetbit = RCC_CR_HSION;
        Loc_u8readytbit = RCC_CR_HSIRDY;
        break;
    case HSE:
        Loc_u8targetbit = RCC_CR_HSEON;
        Loc_u8readytbit = RCC_CR_HSERDY;
        break;
    case PLL:
        Loc_u8targetbit = RCC_CR_PLLON;
        Loc_u8readytbit = RCC_CR_PLLRDY;
        break;
    default:
        Loc_enuRCC_Error_Status = RCC_InvalidParam;
        break;
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        switch (Copy_enuCLKStatus)
        {
        case CLK_Enable:
            Set_Bit(RCC_reg->RCC_CR, Loc_u8targetbit);
            Loc_u8check = 1;
            break;
        case CLK_Disable:
            Clear_Bit(RCC_reg->RCC_CR, Loc_u8targetbit);
            Loc_u8check = 0;
            break;
        default:
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
            break;
        }
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        u32 Loc_u8readytbit_MASK = (1UL << Loc_u8readytbit);
        while ((Get_bit(RCC_reg->RCC_CR, Loc_u8readytbit) != Loc_u8check) && (Loc_u32TimeOut--))
            ;
        if (!Loc_u32TimeOut)
        {
            Loc_enuRCC_Error_Status = RCC_Timeout;
        }
    }

    return Loc_enuRCC_Error_Status;
}

RCC_Error_Status_t RCC_enuSelectSysCLK(CLK_Type_t Copy_enuCLKType)
{
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    u32 Loc_u32TimeOut = TIMEOUT;
    u8 Loc_u8targetSWValue;
    switch (Copy_enuCLKType)
    {
    case HSI:
        Loc_u8targetSWValue = HSI;
        break;
    case HSE:
        Loc_u8targetSWValue = HSE;
        break;
    case PLL:
        Loc_u8targetSWValue = PLL;
        break;
    default:
        Loc_enuRCC_Error_Status = RCC_InvalidParam;
        break;
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        Clear_Mask(RCC_reg->RCC_CFGR, RCC_CFGR_SW_MASK);
        Set_Mask(RCC_reg->RCC_CFGR, Loc_u8targetSWValue << RCC_CFGR_SW);
        while ((RCC_reg->RCC_CFGR & RCC_CFGR_SWS_MASK) != (Loc_u8targetSWValue << RCC_CFGR_SWS) && --Loc_u32TimeOut)
            ;
        if (Loc_u32TimeOut == 0)
        {
            Loc_enuRCC_Error_Status = RCC_Timeout;
        }
    }

    return Loc_enuRCC_Error_Status;
}

RCC_Error_Status_t RCC_enuSetBusPrescaler(BUS_Type_t Copy_enuBus, Prescaler_t Copy_enuPrescaler)
{
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    u32 Loc_u8TargetToSetMask = 0x00UL;
    u32 Loc_u8TargetToClearMask = 0x00UL;
    switch (Copy_enuBus)
    {
    case AHB:
        if (Copy_enuPrescaler > AHB_PRE_512 || Copy_enuPrescaler < AHB_PRE_1)
        {
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
        }
        else
        {
            Loc_u8TargetToSetMask = Copy_enuPrescaler;
        }
        break;
    case APB1:
        if (Copy_enuPrescaler > APB1_PRE_16 || Copy_enuPrescaler < APB1_PRE_1)
        {
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
        }
        else
        {
            Loc_u8TargetToSetMask = Copy_enuPrescaler;
        }
        break;
    case APB2:
        if (Copy_enuPrescaler > APB2_PRE_16 || Copy_enuPrescaler < APB2_PRE_1)
        {
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
        }
        else
        {
            Loc_u8TargetToSetMask = Copy_enuPrescaler;
        }
        break;
    default:
        Loc_enuRCC_Error_Status = RCC_InvalidParam;
        break;
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        Loc_u8TargetToSetMask |= Copy_enuPrescaler;
        switch (Copy_enuBus)
        {
        case AHB:
            Loc_u8TargetToSetMask <<= RCC_CFGR_HPRE;
            Loc_u8TargetToClearMask = RCC_CFGR_HPRE_MASK;
            break;
        case APB1:
            Loc_u8TargetToSetMask <<= RCC_CFGR_PPRE1;
            Loc_u8TargetToClearMask = RCC_CFGR_PPRE1_MASK;
            break;
        case APB2:
            Loc_u8TargetToSetMask <<= RCC_CFGR_PPRE2;
            Loc_u8TargetToClearMask = RCC_CFGR_PPRE2_MASK;
            break;
        default:
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
            break;
        }
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        Clear_Mask(RCC_reg->RCC_CFGR, Loc_u8TargetToClearMask);
        Set_Mask(RCC_reg->RCC_CFGR, Loc_u8TargetToSetMask);
    }
    return Loc_enuRCC_Error_Status;
}
