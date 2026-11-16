#ifndef _HLCD_PRIV_H_
#define _HLCD_PRIV_H_
#include "HLCD_cfg.h"
#include "Bit_math.h"

#define Function_Set_8_BIT (0b00110000UL | Shift_Left(Number_Of_Lines,3) |  Shift_Left(Dots_Mode,2))

#define Function_Set_4_BIT_1 (0b0010UL)
#define Function_Set_4_BIT_2 (0b0010UL)
#define Function_Set_4_BIT_3 (0b0000UL | Shift_Left(Number_Of_Lines,3) |  Shift_Left(Dots_Mode,2))

#define Display_On_Off_8_BIT (0b00001000 | Shift_Left(DisplayOnOffMode,2) | Shift_Left(Cursor,1) | (Blink &Cursor) )

#define Display_On_Off_4_BIT_1 (0b0000UL)
#define Display_On_Off_4_BIT_2 ( 0b1000UL | Shift_Left(DisplayOnOffMode,2) | Shift_Left(Cursor,1) | (Blink &Cursor) )

#define Clear_Display_8_BIT (0b00000001UL)

#define Clear_Display_4_BIT_1 (0b0000UL)
#define Clear_Display_4_BIT_2 (0b0001UL)

#define Entry_Mode_8_Bit (0b00000100UL | Shift_Left(Move_Cursor,1) |  ShiftCursorMode)

#define Entry_Mode_4_Bit_1 (0b0000UL)
#define Entry_Mode_4_Bit_2 (0b01  | Shift_Left(Move_Cursor,1) |  ShiftCursorMode )



#endif