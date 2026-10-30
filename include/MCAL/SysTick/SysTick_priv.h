#ifndef _SYS_TICK_PRIV_H_
#define _SYS_TICK_PRIV_H_

#include "STD_types.h"

#define Sys_Tick_reg_BASE ((volatile u32 *)(0xE000E010UL))

typedef struct
{
    u32 STK_CTRL;
    u32 STK_LOAD;
    u32 STK_VAL;
    u32 STK_CALIB;
} Sys_Tick_reg_t;

#define Sys_Tick_reg ((volatile Sys_Tick_reg_t *)Sys_Tick_reg_BASE)

// Sys_Tick_STK_CTRL register

// bit numbers
#define Sys_Tick_STK_CTRL_ENABLE 0
#define Sys_Tick_STK_CTRL_TICKINT 1
#define Sys_Tick_STK_CTRL_CLKSOURCE 2
#define Sys_Tick_STK_CTRL_COUNTFLAG 16

// Sys_Tick_STK_LOAD register

// bit numbers
#define Sys_Tick_STK_LOAD_RELOAD 0
// bit masking
#define Sys_Tick_STK_LOAD_RELOAD_MASK (0xFFFFFFUL << Sys_Tick_STK_LOAD_RELOAD)


// Sys_Tick_STK_VAL register

// bit numbers
#define Sys_Tick_STK_VAL_CURRENT 0
// bit masking
#define Sys_Tick_STK_VAL_CURRENT_MASK (0xFFFFFFUL << Sys_Tick_STK_VAL_CURRENT)

// Sys_Tick_STK_CALIB register

// bit numbers
#define Sys_Tick_STK_CALIB_TENMS 0
#define Sys_Tick_STK_CALIB_SKEW 30
#define Sys_Tick_STK_CALIB_NOREF 31

// bit masking
#define Sys_Tick_STK_CALIB_TENMS_MASK (0xFFFFFFFUL << Sys_Tick_STK_CALIB_TENMS)

#endif