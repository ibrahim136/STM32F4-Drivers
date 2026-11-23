#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "HLCD.h"
#include "Clock.h"

int main(void)
{

    Clockenu_On(LCD_1,"   Hello ITI");
    Sched_Start();
}