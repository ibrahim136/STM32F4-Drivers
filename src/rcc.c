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
    switch(Copy_enuCLKType)
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
    if (Loc_enuRCC_Error_Status == RCC_OK){
            switch (Copy_enuCLKStatus)
        {
        case CLK_Enable:
            Set_Bit(RCC_reg->RCC_CR,Loc_u8targetbit);
            Loc_u8check =1;
            break;
        case CLK_Disable:
            Clear_Bit(RCC_reg->RCC_CR,Loc_u8targetbit);
            Loc_u8check =0;
            break;
        default:
            Loc_enuRCC_Error_Status = RCC_InvalidParam;
            break;
        }
    }
    if (Loc_enuRCC_Error_Status == RCC_OK)
    {
        u32 Loc_u8readytbit_MASK = (1UL << Loc_u8readytbit);
        while ( (Get_bit(RCC_reg->RCC_CR,Loc_u8readytbit) == Loc_u8check )&& (Loc_u32TimeOut--));
        if (!Loc_u32TimeOut)
        {
            Loc_enuRCC_Error_Status = RCC_Timeout;
        }
    }


    return Loc_enuRCC_Error_Status;
}
