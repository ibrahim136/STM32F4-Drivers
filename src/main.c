#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "HLCD.h"

int main(void)
{
    RCC_enuCLKControl(HSI, CLK_Enable);
    RCC_enuSelectSysCLK(HSI);
    HLCD_enuInit(LCD_1, 5);
    Sched_enuInit();
    HLCD_enuSetCursorPos(LCD_1, Row_2, Col_3);
    HLCD_enuWriteString(LCD_1, "Patlimos II");
    Sched_Start();
}