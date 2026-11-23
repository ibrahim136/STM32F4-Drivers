#include "STD_types.h"
#include "Sched.h"
#include "HLCD.h"
#include "Clock.h"

static LCD_Numbers_t LCD_NO;
static u8* WelcomeString;
static void Clock(void)
{
    static u64 sec = 0;
    u64 display_hr = sec / 3600;
    u64 display_min = (sec - display_hr * 3600) / 60;
    u64 display_sec = (sec - display_hr * 3600 - display_min * 60);
    HLCD_enuSetCursorPos(LCD_NO, Row_2, Col_3);
    static u8 string[12] = {'U', 'P', ':'};
    string[3] = ('0' + display_hr / 10);
    string[4] = '0' + display_hr % 10;
    string[5] = ':';
    string[6] = '0' + display_min / 10;
    string[7] = '0' + display_min % 10;
    string[8] = ':';
    string[9] = '0' + display_sec / 10;
    string[10] = ('0' + display_sec % 10);
    string[11] = 0;
    HLCD_enuWriteString(LCD_1, string);

    sec++;
}

static inline Clock_Error_Status_t Check_LCD(LCD_Numbers_t Copy_enuLCD)
{
    Clock_Error_Status_t Loc_enuClock_Error_Status = Clock_OK;
    switch (Copy_enuLCD)
    {
    case LCD_1 ... LCD_Count - 1:
        break;
    default:
        Loc_enuClock_Error_Status = Clock_InvalidLCD;
        break;
    }
    return Loc_enuClock_Error_Status;
}

Clock_Error_Status_t Clockenu_On(LCD_Numbers_t Copy_enuLCD, u8* Copy_enuWelcomeString)
{
    Clock_Error_Status_t Loc_enuClock_Error_Status = Clock_OK;
    Loc_enuClock_Error_Status = Check_LCD(Copy_enuLCD);
    if (Loc_enuClock_Error_Status == Clock_OK)
    {
        LCD_NO = Copy_enuLCD;
    }
    Sched_enuInit();
    HLCD_enuInit(LCD_NO, 5);
    HLCD_enuSetCursorPos(LCD_1, Row_1, Col_1);
    WelcomeString = Copy_enuWelcomeString;
    HLCD_enuWriteString(LCD_NO, WelcomeString);
    static Sched_Runnable_t r0 = {.CyclicTime_ms = 1000, .first_delay = 0, .p2f = Clock, .periorty = 10};
    Sched_enuAddRunnable(&r0);
    return Loc_enuClock_Error_Status;
}
