#ifndef _HLCD_CFG_H_
#define _HLCD_CFG_H_

#define _8_BIT_MODE 0
#define _4_BIT_MODE 1

#define BIT_MODE _8_BIT_MODE

#define _1_Line_MODE 0
#define _2_Line_MODE 1

#define Number_Of_Lines _2_Line_MODE

#define _5x7_dots 0
#define _5x11_dots 1

#define Dots_Mode _5x7_dots

#define DisplayOff 0
#define DisplayOn 1

#define DisplayOnOffMode DisplayOn

#define CursorOn 1
#define CursorOff 0

#define Cursor CursorOn

#define BlinkOn 1
#define BlinkOff 1

#define Blink BlinkOn

#define Decrease_Cursor 0
#define Increase_Cursor 1

#define Move_Cursor Increase_Cursor

#define ShiftScreenOn 1
#define ShiftScreenOff 0

#define ShiftCursorMode ShiftScreenOn

typedef enum{
    RS,
    RW,
    E,
    #if BIT_MODE == _8_BIT_MODE
    D0,
    D1,
    D2,
    D3,
    #endif
    D4,
    D5,
    D6,
    D7,
    NUM_OF_Control_Data_PINs
}Control_Data_PINs_t;

#define Data_Start_Index (E+1)

#endif