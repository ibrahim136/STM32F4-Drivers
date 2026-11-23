#ifndef _CLOCK_H_
#define _CLOCK_H_


typedef enum
{
    Clock_OK,
    Clock_InvalidLCD,
    Clock_InvalidParam
} Clock_Error_Status_t;

Clock_Error_Status_t Clockenu_On(LCD_Numbers_t Copy_enuLCD, u8* Copy_enuWelcomeString);

#endif