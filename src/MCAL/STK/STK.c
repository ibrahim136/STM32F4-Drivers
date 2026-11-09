#include "STK_priv.h"
#include "STK_cfg.h"
#include "STK.h"
#include "Bit_math.h"
#include "rcc.h"


static STK_Cbf_t STK_pfCallback = nullptr;


static u32 STK_u32RequiredTime = 0; 
static u32 STK_u32TickCounter = 0;


static inline u32 STK_u32GetSysTickFreq(void)
{
    u32 Loc_u32SysFreq = 0;

    RCC_enuGetSysCLKFreq(&Loc_u32SysFreq);

#if STK_CLOCK_SOURCE == STK_AHB_DIV_8
    Loc_u32SysFreq /= 8;
#endif

    return Loc_u32SysFreq;
}

STK_Error_Status_t STK_enuInit(void)
{
    Clear_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);
    Clear_Bit(STK_reg->STK_CTRL, STK_CTRL_TICKINT);

#if STK_CLOCK_SOURCE == STK_AHB
    Set_Bit(STK_reg->STK_CTRL, STK_CTRL_CLKSOURCE);
#elif STK_CLOCK_SOURCE == STK_AHB_DIV_8
    Clear_Bit(STK_reg->STK_CTRL, STK_CTRL_CLKSOURCE);
#endif

    return STK_OK;
}

STK_Error_Status_t STK_enuStart(void)
{
    Set_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);
    return STK_OK;
}

STK_Error_Status_t STK_enuStop(void)
{
    Clear_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);
    return STK_OK;
}

STK_Error_Status_t STK_enuSetCbf(STK_Cbf_t Copy_pfCallback)
{
    STK_Error_Status_t Loc_enuErrorStatus = STK_OK;

    if (Copy_pfCallback)
    {
        STK_pfCallback = Copy_pfCallback;
    }
    else
    {
        Loc_enuErrorStatus = STK_InvalidPtr;
    }

    return Loc_enuErrorStatus;
}

void SysTick_Handler(void)
{
    (void)STK_reg->STK_CTRL;
    STK_u32TickCounter++;
    if (STK_u32TickCounter == STK_u32RequiredTime)
    {
        STK_u32TickCounter = 0;

        if (STK_pfCallback != nullptr)
        {
            STK_pfCallback();
        }
    }
}

STK_Error_Status_t STK_enuNotify_on_ms(u32 Copy_u32TimeMs)
{
    STK_Error_Status_t Loc_enuErrorStatus = STK_OK;

    if (Copy_u32TimeMs == 0)
    {
        Loc_enuErrorStatus = STK_InvalidTime;
    }
    else
    {
        Clear_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);
        STK_u32RequiredTime = Copy_u32TimeMs;
        STK_u32TickCounter = 0;
        u32 Loc_u32TickFreq = STK_u32GetSysTickFreq();
        u32 Ticks_Per_1ms = (Loc_u32TickFreq / 1000);
        STK_reg->STK_LOAD = Ticks_Per_1ms - 1;
        Clear_reg(STK_reg->STK_VAL);
        Set_Bit(STK_reg->STK_CTRL, STK_CTRL_TICKINT);
        Set_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);
    }
    return Loc_enuErrorStatus;
}

STK_Error_Status_t STK_enuDelay_ms(u32 Copy_u32DelayMs)
{
    STK_Error_Status_t Loc_enuErrorStatus = STK_OK;

    if (Copy_u32DelayMs == 0)
    {
        Loc_enuErrorStatus = STK_InvalidTime;
    }
    else
    {
        u32 Loc_u32TickFreq = STK_u32GetSysTickFreq();
        u32 Ticks_Per_1ms = (Loc_u32TickFreq / 1000);

        STK_reg->STK_LOAD = Ticks_Per_1ms - 1;
        Clear_reg(STK_reg->STK_VAL);

        Set_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);

        for (u32 i = 0; i < Copy_u32DelayMs; i++)
        {
            while (!Get_bit(STK_reg->STK_CTRL, STK_CTRL_COUNTFLAG));
        }

        Clear_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);
    }
    return Loc_enuErrorStatus;
}

STK_Error_Status_t STK_enuDelay_us(u32 Copy_u32DelayUs)
{
    STK_Error_Status_t Loc_enuErrorStatus = STK_OK;

    if (Copy_u32DelayUs == 0)
    {
        Loc_enuErrorStatus = STK_InvalidTime;
    }
    else
    {
        u32 Loc_u32TickFreq = STK_u32GetSysTickFreq();
        u32 Ticks_Per_1us = (Loc_u32TickFreq / 1000000);

        STK_reg->STK_LOAD = Ticks_Per_1us - 1;
        Clear_reg(STK_reg->STK_VAL);

        Set_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);

        for (u32 i = 0; i < Copy_u32DelayUs; i++)
        {
            while (!Get_bit(STK_reg->STK_CTRL, STK_CTRL_COUNTFLAG));
        }

        Clear_Bit(STK_reg->STK_CTRL, STK_CTRL_ENABLE);
    }
    return Loc_enuErrorStatus;
}