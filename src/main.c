#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "HLCD.h"

void WriteString(void)
{
        HLCD_enuSetCursorPos(LCD_1, Row_2, Col_3);
       HLCD_enuWriteString(LCD_1, "Patlimos II");
}

int main(void)
{
    RCC_enuCLKControl(HSI, CLK_Enable);
    RCC_enuSelectSysCLK(HSI);
    HLCD_enuInit(LCD_1, 5);
    Sched_enuInit();
    Sched_Runnable_t r1 = {.p2f = WriteString, .CyclicTime_ms = 2, .periorty = 6, .first_delay = 30};
    Sched_enuAddRunnable(&r1);
    Sched_Start();
}