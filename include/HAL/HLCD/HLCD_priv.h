#ifndef _HLCD_PRIV_H_
#define _HLCD_PRIV_H_
#include "HLCD_cfg.h"
#include "Bit_math.h"

#define Function_Set_8_BIT (0b00110000UL | Shift_Left(Number_Of_Lines,3) |  Shift_Left(Dots_Mode,2))

#define Function_Set_4_BIT_1 (0b0010UL)
#define Function_Set_4_BIT_2 (0b0010UL)
#define Function_Set_4_BIT_3 (0b0000UL | Shift_Left(Number_Of_Lines,3) |  Shift_Left(Dots_Mode,2))




#endif