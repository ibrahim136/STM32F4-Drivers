#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "HLCD.h"

void Clock()
{
    static u64 sec = 0;
    u64 display_hr = sec / 3600;
    u64 display_min = (sec - display_hr * 3600) / 60;
    u64 display_sec = (sec - display_hr * 3600 - display_min * 60);
    HLCD_enuSetCursorPos(LCD_1, Row_2, Col_3);
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

int main(void)
{
    RCC_enuCLKControl(HSI, CLK_Enable);
    RCC_enuSelectSysCLK(HSI);
    HLCD_enuInit(LCD_1, 5);
    Sched_enuInit();
    HLCD_enuSetCursorPos(LCD_1, Row_1, Col_1);
    HLCD_enuWriteString(LCD_1, "   Hello ITI");
    Sched_Runnable_t r0 = {.CyclicTime_ms = 1000, .first_delay = 0, .p2f = Clock, .periorty = 10};
    Sched_enuAddRunnable(&r0);
    Sched_Start();
}