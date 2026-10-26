#include "rcc.h"
#include "rcc_cfg.h"
#include "rcc_priv.h"
#include "Bit_math.h"

inline CLK_Type_t RCC_enuGetPLLSRCCLK()
{
    u8 Loc_u8PLLSRC = Get_bit(RCC_reg->RCC_PLLCFGR, RCC_PLLCFGR_PLLSRC);
    CLK_Type_t Loc_enuPLLSRCCLKType;
    if (Loc_u8PLLSRC)
    {
        Loc_enuPLLSRCCLKType = HSE;
    }
    else
    {
        Loc_enuPLLSRCCLKType = HSI;
    }
    return Loc_enuPLLSRCCLKType;
}

inline CLK_Status_t RCC_enuGetCLKStatus(CLK_Type_t Copy_enuCLKType)
{
    CLK_Status_t CLKState = CLK_Enable;
    u8 check_bit;
    switch (Copy_enuCLKType)
    {
    case HSI:
        check_bit = RCC_CR_HSION;
        break;
    case HSE:
        check_bit = RCC_CR_HSEON;
        break;
    case PLL:
        check_bit = RCC_CR_PLLON;
        break;
    default:
        CLKState = UNDEFINED;
        break;
    }
    if (CLKState != UNDEFINED && !(Get_bit(RCC_reg->RCC_CR, check_bit)))
    {
        CLKState = CLK_Disable;
    }
    return CLKState;
}

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
            if (Loc_u8targetbit == RCC_CR_PLLON)
            {
                CLK_Type_t Loc_enuPLLSRCCLK = RCC_enuGetPLLSRCCLK();
                CLK_Status_t Loc_enuPLLSRCCLKState = RCC_enuGetCLKStatus(Loc_enuPLLSRCCLK);
                if (Loc_enuPLLSRCCLKState != CLK_Enable)
                {
                    Loc_enuRCC_Error_Status = RCC_PLLSRCDisabled;
                    break;
                }
            }
            Set_Bit(RCC_reg->RCC_CR, Loc_u8targetbit);
            Loc_u8check = 1;
            break;
        case CLK_Disable:
            switch (Loc_u8targetbit)
            {
            case RCC_CR_HSION:
            {
                CLK_Type_t Loc_enuPLLSRCCLK = RCC_enuGetPLLSRCCLK();
                CLK_Type_t Loc_enuSysCLK = RCC_enuGetSysCLK();
                if ((Loc_enuPLLSRCCLK == HSI && Get_bit(RCC_reg->RCC_CR, RCC_CR_PLLON)) || Loc_enuSysCLK == HSI)
                {
                    Loc_enuRCC_Error_Status = RCC_ClockInUse;
                    break;
                }
                Clear_Bit(RCC_reg->RCC_CR, Loc_u8targetbit);
                Loc_u8check = 0;
                break;
            }
            case RCC_CR_HSEON:
            {
                CLK_Type_t Loc_enuPLLSRCCLK = RCC_enuGetPLLSRCCLK();
                CLK_Type_t Loc_enuSysCLK = RCC_enuGetSysCLK();
                if ((Loc_enuPLLSRCCLK == HSE && Get_bit(RCC_reg->RCC_CR, RCC_CR_PLLON)) || Loc_enuSysCLK == HSE)
                {
                    Loc_enuRCC_Error_Status = RCC_ClockInUse;
                    break;
                }
                Clear_Bit(RCC_reg->RCC_CR, Loc_u8targetbit);
                Loc_u8check = 0;
                break;
            }
            default:
                CLK_Type_t Loc_enuSysCLK = RCC_enuGetSysCLK();
                if (Loc_enuSysCLK == PLL)
                {
                    Loc_enuRCC_Error_Status = RCC_ClockInUse;
                    break;
                }
                Clear_Bit(RCC_reg->RCC_CR, Loc_u8targetbit);
                Loc_u8check = 0;
                break;
            }
        default:
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
            break;
        }
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
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
    CLK_Status_t Loc_enuCLKState = RCC_enuGetCLKStatus(Copy_enuCLKType);
    if (Loc_enuCLKState != CLK_Enable)
    {
        Loc_enuRCC_Error_Status = RCC_CLKDisabled;
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        switch (Copy_enuCLKType)
        {
        case HSI:
        {
            Loc_u8targetSWValue = HSI;
            break;
        }
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

RCC_Error_Status_t RCC_enuCTRLPeripheral(Peripheral_t Copy_enuPeripheral, Peripheral_State_t Copy_enuPeripheralState)
{
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    Peripheral_Bus_t Loc_enuBUSCODE = Get_Mask(Copy_enuPeripheral, BUS_CODE_MASK);
    volatile u32 *Loc_u32Targetreg;
    switch (Loc_enuBUSCODE)
    {
    case AHB1_BUS:
        Loc_u32Targetreg = &(RCC_reg->RCC_AHB1ENR);
        break;
    case AHB2_BUS:
        Loc_u32Targetreg = &(RCC_reg->RCC_AHB2ENR);
        break;
    case APB1_BUS:
        Loc_u32Targetreg = &(RCC_reg->RCC_APB1ENR);
        break;
    case APB2_BUS:
        Loc_u32Targetreg = &(RCC_reg->RCC_APB2ENR);
        break;
    default:
        Loc_enuRCC_Error_Status = RCC_InvalidParam;
        break;
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        Clear_Mask(Copy_enuPeripheral, BUS_CODE_MASK);
        switch (Copy_enuPeripheralState)
        {
        case Peripheral_Enable:
            Set_Bit(*Loc_u32Targetreg, Copy_enuPeripheral);
            break;
        case Peripheral_Disable:
            Clear_Bit(*Loc_u32Targetreg, Copy_enuPeripheral);
            break;
        default:
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
            break;
        }
    }
    return Loc_enuRCC_Error_Status;
}

inline u8 RCC_PLLDivisionFactorsCheck(PLL_Config_t *Copy_strPLLConfig, u8 Copy_u8CLKFreq)
{
    u8 is_valid;
    float VCO_input = (float)((float)Copy_u8CLKFreq / (float)Copy_strPLLConfig->M);
    float VCO_output = (float)(VCO_input * (float)(Copy_strPLLConfig->N));
    if (Copy_strPLLConfig->M > M_MAX || Copy_strPLLConfig->M < M_MIN)
    {
        is_valid = 0;
    }
    else if (VCO_input > VIN_MAX || VCO_input < VIN_MIN)
    {
        is_valid = 0;
    }
    else if (Copy_strPLLConfig->N > N_MAX || Copy_strPLLConfig->N < N_MIN)
    {
        is_valid = 0;
    }
    else if (Copy_strPLLConfig->Q > Q_MAX || Copy_strPLLConfig->Q < Q_MIN)
    {
        is_valid = 0;
    }
    else if (VCO_output > VOUT_MAX || VCO_output < VOUT_MIN)
    {
        is_valid = 0;
    }
    else if (VCO_output != USBOTG_Freq * Copy_strPLLConfig->Q)
    {
        is_valid = 0;
    }
    else if (VCO_output / Copy_strPLLConfig->P > MAX_SYSCLKFreq)
    {
        is_valid = 0;
    }
    else
    {
        is_valid = 1;
    }
    return is_valid;
}

RCC_Error_Status_t RCC_enuConfigurePLL(PLL_Config_t *Copy_strPLLConfig)
{
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    u8 Copy_u8CLKFreq;
    if (RCC_enuGetCLKStatus(PLL) == CLK_Enable)
    {
        Loc_enuRCC_Error_Status = RCC_PLLEnabled;
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        switch (Copy_strPLLConfig->SRC)
        {
        case RCC_PLLCFGR_PLLSRC_HSI:
            Copy_u8CLKFreq = blackpill_f401cc_STM32F401CC_HSI_Freq;
            break;
        case RCC_PLLCFGR_PLLSRC_HSE:
            Copy_u8CLKFreq = blackpill_f401cc_STM32F401CC_HSE_Freq;
            break;
        default:
        Loc_enuRCC_Error_Status = RCC_InvalidPLLDivisiors;
            break;
        }
        if (!RCC_PLLDivisionFactorsCheck(Copy_strPLLConfig,Copy_u8CLKFreq))
        {
            Loc_enuRCC_Error_Status = RCC_InvalidPLLDivisiors;
        }
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        u32 Loc_RCC_PLLCFGR = 0x00UL;
        Loc_RCC_PLLCFGR |= Masking_Value(Copy_strPLLConfig->M,RCC_PLLCFGR_PLLM);
        Loc_RCC_PLLCFGR |= Masking_Value(Copy_strPLLConfig->N,RCC_PLLCFGR_PLLN);
        Loc_RCC_PLLCFGR |= Masking_Value(Copy_strPLLConfig->Q,RCC_PLLCFGR_PLLQ);
        Loc_RCC_PLLCFGR |= Masking_Value(Copy_strPLLConfig->P,RCC_PLLCFGR_PLLP);
        Loc_RCC_PLLCFGR |= Masking_Value(Copy_strPLLConfig->SRC,RCC_PLLCFGR_PLLSRC);
        RCC_reg->RCC_PLLCFGR = Loc_RCC_PLLCFGR;
    }
    return Loc_enuRCC_Error_Status;
}

CLK_Type_t RCC_enuGetSysCLK()
{
    u8 Loc_u8RCC_CFGR_SWS = Get_Mask(RCC_reg->RCC_CFGR, RCC_CFGR_SWS_MASK);
    Loc_u8RCC_CFGR_SWS = Get_Mask_Value(Loc_u8RCC_CFGR_SWS, RCC_CFGR_SWS);
    CLK_Type_t Loc_enuCLKType;
    switch (Loc_u8RCC_CFGR_SWS)
    {
    case 0x00UL:
        Loc_enuCLKType = HSI;
        break;
    case 0x01UL:
        Loc_enuCLKType = HSE;
        break;
    case 0x02UL:
        Loc_enuCLKType = PLL;
        break;
    default:
        Loc_enuCLKType = Not_applicable;
        break;
    }
    return Loc_enuCLKType;
}
