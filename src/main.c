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

u8 ITI_Logo[8] = {
    0b10000,
    0b00000,
    0b10001,
    0b11110,
    0b10101,
    0b10101,
    0b00101,
    0b00001};
    #define Clock 0
    #define Calculator 1
    #define Mode Calculator
int main(void)
{
    #if Mode==Clock
    Clockenu_On(LCD_1, (u8 *)"   Hello ITI ");
    Clock_enuAddCustomChar(0, ITI_Logo);
    #elif Mode == Calculator
    Calculatorenu_On(LCD_1);

    #endif
    Sched_Start();


}