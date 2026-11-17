#ifndef _HLCD_CFG_H_
#define _HLCD_CFG_H_

typedef enum{
    _4_BIT_MODE,
    _8_BIT_MODE
}BIT_MODE_t;

typedef enum{
    _1_Line_MODE,
    _2_Line_MODE
}Number_Of_Lines_t;

typedef enum{
    _5x7_dots,
    _5x11_dots
}Dots_Mode_t;

typedef enum{
    DisplayOff,
    DisplayOn
}DisplayOnOffMode_t;

typedef enum{
    CursorOff,
    CursorOn
}Cursor_t;

typedef enum{
    BlinkOff,
    BlinkOn
}Blink_t;

typedef enum{
    Decrease_Cursor,
    Increase_Cursor
}Move_Cursor_t;

typedef enum{
    ShiftScreenOff,
    ShiftScreenOn
}ShiftCursorMode_t;

typedef struct {
    const BIT_MODE_t DL;
    Number_Of_Lines_t N;
    Dots_Mode_t F;
    DisplayOnOffMode_t D; 
    Cursor_t C;
    Blink_t B;
    Move_Cursor_t I_D;
    ShiftCursorMode_t S;
}LCD_Init_cfg_t;

typedef enum{
    LCD_1,
    LCD_2,
    LCD_Count
}LCD_Numbers_t;

typedef enum{
    RS,
    RW,
    E,
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    NUM_OF_Control_Data_PINs
}Control_Data_PINs_t;

#define Data_Start_Index (E+1)

#endif