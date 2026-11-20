#include "HLCD_cfg.h"
#include "HLCD.h"

const LCD_Init_cfg_t LCDs_Init_Conf[LCD_Count] =
    {
        [LCD_1] = {.DL = _4_BIT_MODE, .N = _2_Line_MODE, .F = _5x7_dots, .D = DisplayOn, .C = CursorOff, .B = BlinkOff, .I_D = Increase_Cursor, .S = ShiftScreenOff},
        [LCD_2] = {.DL = _8_BIT_MODE, .N = _2_Line_MODE, .F = _5x7_dots, .D = DisplayOn, .C = CursorOn, .B = BlinkOn, .I_D = Increase_Cursor, .S = ShiftScreenOff}};

const HLCD_PIN_cfg_t HLCD_PIN_cfg[LCD_Count][NUM_OF_Control_Data_PINs] =
    {
        {
            [RS] = {.PORT = GPIO_PORTB, .PIN = PIN0},
            [RW] = {.PORT = GPIO_PORTB, .PIN = PIN1},
            [E] = {.PORT = GPIO_PORTB, .PIN = PIN2},
            [D0] = {.PORT = GPIO_PORTA, .PIN = PIN0},
            [D1] = {.PORT = GPIO_PORTA, .PIN = PIN1},
            [D2] = {.PORT = GPIO_PORTA, .PIN = PIN2},
            [D3] = {.PORT = GPIO_PORTA, .PIN = PIN3},
            [D4] = {.PORT = GPIO_PORTA, .PIN = PIN4},
            [D5] = {.PORT = GPIO_PORTA, .PIN = PIN5},
            [D6] = {.PORT = GPIO_PORTA, .PIN = PIN6},
            [D7] = {.PORT = GPIO_PORTA, .PIN = PIN7},
        },
        {
            [RS] = {.PORT = GPIO_PORTB, .PIN = PIN3},
            [RW] = {.PORT = GPIO_PORTB, .PIN = PIN4},
            [E] = {.PORT = GPIO_PORTB, .PIN = PIN5},
            [D0] = {.PORT = GPIO_PORTA, .PIN = PIN8},
            [D1] = {.PORT = GPIO_PORTA, .PIN = PIN9},
            [D2] = {.PORT = GPIO_PORTA, .PIN = PIN10},
            [D3] = {.PORT = GPIO_PORTA, .PIN = PIN11},
            [D4] = {.PORT = GPIO_PORTB, .PIN = PIN8},
            [D5] = {.PORT = GPIO_PORTB, .PIN = PIN9},
            [D6] = {.PORT = GPIO_PORTB, .PIN = PIN10},
            [D7] = {.PORT = GPIO_PORTB, .PIN = PIN12},
        }

};
