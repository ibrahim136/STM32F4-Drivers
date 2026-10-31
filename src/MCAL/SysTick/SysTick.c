#include "SysTick_priv.h"
#include "SysTick.h"

static inline void SysTick_voidInit()
{
    Clear_Bit( Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_TICKINT);
    Clear_Bit( Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_CLKSOURCE);
    Clear_reg(Sys_Tick_reg->STK_VAL);
    u32 Loc_u32Sys_Tick_STK_VAL_CURRENT = Counter_For_AHB_divided_8_to_get_1ms;
    Loc_u32Sys_Tick_STK_VAL_CURRENT = Masking_Value(Loc_u32Sys_Tick_STK_VAL_CURRENT,Sys_Tick_STK_VAL_CURRENT);
    Clear_Mask (Sys_Tick_reg->STK_LOAD,Sys_Tick_STK_LOAD_RELOAD_MASK);
    Set_Mask(Sys_Tick_reg->STK_LOAD,Loc_u32Sys_Tick_STK_VAL_CURRENT );
}

static inline void SysTick_u8Delay1ms()
{
    Clear_reg(Sys_Tick_reg->STK_VAL);
    Set_Bit(Sys_Tick_reg->STK_CTRL,Sys_Tick_STK_CTRL_ENABLE );
    while (!Get_bit(Sys_Tick_reg->STK_CTRL,Sys_Tick_STK_CTRL_COUNTFLAG));
    Clear_Bit(Sys_Tick_reg->STK_CTRL,Sys_Tick_STK_CTRL_ENABLE );
}

void STK_voidDelay(u32 Copy_u64Delayms)
{
    SysTick_voidInit();
    for (u32 i=0;i<Copy_u64Delayms;i++)
    {
        SysTick_u8Delay1ms();
    }
}