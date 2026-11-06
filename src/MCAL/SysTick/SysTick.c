#include "SysTick_priv.h"
#include "SysTick.h"

static inline void SysTick_voidInit()
{
    Clear_Bit( Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_TICKINT);
    Clear_Bit( Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_CLKSOURCE);
    Clear_reg(Sys_Tick_reg->STK_VAL);
    u32 Loc_u32Sys_Tick_STK_VAL_CURRENT = Counter_For_AHB_divided_8_to_get_1us;
    Loc_u32Sys_Tick_STK_VAL_CURRENT = Masking_Value(Loc_u32Sys_Tick_STK_VAL_CURRENT,Sys_Tick_STK_VAL_CURRENT);
    Clear_Mask (Sys_Tick_reg->STK_LOAD,Sys_Tick_STK_LOAD_RELOAD_MASK);
    Set_Mask(Sys_Tick_reg->STK_LOAD,Loc_u32Sys_Tick_STK_VAL_CURRENT );
}



void STK_voidDelay_us(u32 Copy_u64Delayus)
{
    u32 Total_Ticks = Copy_u64Delayus * 2;
    Sys_Tick_reg->STK_LOAD = Total_Ticks - 1;
    Clear_reg(Sys_Tick_reg->STK_VAL);
    Set_Bit(Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_ENABLE);
    while (!Get_bit(Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_COUNTFLAG));
    Clear_Bit(Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_ENABLE);
}

void STK_voidDelay_ms(u32 Copy_u64Delayms)
{
    u32 Total_Ticks = Copy_u64Delayms * 2000;
    
    Sys_Tick_reg->STK_LOAD = Total_Ticks - 1;
    
    Clear_reg(Sys_Tick_reg->STK_VAL);
    
    Set_Bit(Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_ENABLE);
    
    while (!Get_bit(Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_COUNTFLAG));
    
    Clear_Bit(Sys_Tick_reg->STK_CTRL, Sys_Tick_STK_CTRL_ENABLE);
}
