#ifndef _CLOCK_H_
#define _CLOCK_H_


typedef enum
{
    Clock_OK,
    Clock_InvalidLCD,
    Clock_InvalidParam
} Clock_Error_Status_t;

Clock_Error_Status_t Clockenu_On(LCD_Numbers_t Copy_enuLCD, u8* Copy_enuWelcomeString);
Clock_Error_Status_t Clock_enuAddCustomChar(u8 Copy_u8Index,u8 *Copy_pu8Pattern);

#endif