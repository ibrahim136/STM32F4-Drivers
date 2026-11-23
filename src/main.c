#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "HLCD.h"
#include "Clock.h"
#include "Calculator.h"

int main(void)
{
    Calculatorenu_On(LCD_1);
    Sched_Start();
}