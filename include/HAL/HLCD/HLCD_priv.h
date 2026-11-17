#ifndef _HLCD_PRIV_H_
#define _HLCD_PRIV_H_
#include "HLCD_cfg.h"
#include "Bit_math.h"

#define Data_Start_Index(DL) (7-DL*4)

#define Cylic_ms 2
#define FirstDelay_ms 30

#define Number_Of_Pins_to_cfg(DL) (7+DL*4)

#define Full_4_bit_ones (0b1111)

#define HigherNippleMask (0b11110000)
#define LowerNippleMask (0b00001111)

#define Get_HigherNipple(reg) Get_Mask_Value(Get_Mask(reg,HigherNippleMask),4)
#define Get_LowerNipple(reg) Get_Mask(reg,LowerNippleMask)

#define Function_Set_Command(DL,Number_Of_Lines,Dots_Mode) (0b00100000UL | Shift_Left(DL,4) | Shift_Left(Number_Of_Lines,3) |  Shift_Left(Dots_Mode,2))


#define Display_On_Off_Command(DisplayOnOffMode,Cursor,Blink) (0b00001000 | Shift_Left(DisplayOnOffMode,2) | Shift_Left(Cursor,1) | (Blink &Cursor) )


#define Clear_Display_Command (0b00000001UL)

#define Entry_Mode_Command(Move_Cursor,ShiftCursorMode) (0b00000100UL | Shift_Left(Move_Cursor,1) |  ShiftCursorMode)



#endif