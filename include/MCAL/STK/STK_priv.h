#ifndef _STK_PRIV_H_
#define _STK_PRIV_H_

#include "STD_types.h"

#define STK_reg_BASE ((volatile u32 *)(0xE000E010UL))

typedef struct
{
    u32 STK_CTRL;
    u32 STK_LOAD;
    u32 STK_VAL;
    u32 STK_CALIB;
} STK_reg_t;

#define STK_reg ((volatile STK_reg_t *)STK_reg_BASE)

/* STK_CTRL register bits*/
#define STK_CTRL_ENABLE    0
#define STK_CTRL_TICKINT   1
#define STK_CTRL_CLKSOURCE 2
#define STK_CTRL_COUNTFLAG 16

/* STK_LOAD register bits & mask */
#define STK_LOAD_RELOAD 0
#define STK_LOAD_RELOAD_MASK (0xFFFFFFUL << STK_LOAD_RELOAD)

/* STK_VAL register bits & mask*/
#define STK_VAL_CURRENT 0
#define STK_VAL_CURRENT_MASK (0xFFFFFFUL << STK_VAL_CURRENT)

/* STK_CALIB register bits*/
#define STK_CALIB_TENMS 0
#define STK_CALIB_SKEW  30
#define STK_CALIB_NOREF 31
#define STK_CALIB_TENMS_MASK (0xFFFFFFFUL << STK_CALIB_TENMS)

#define Ticks_per_ms(freq) (freq/1000)
#define Ticks_per_us(freq) (freq/1000000)

#endif