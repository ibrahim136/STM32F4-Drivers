#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"


void ControlLED0(void)
{
    Switch_State_t Loc_enuSwitchState;
    HSwitch_enuReadState(Switch_no_1,&Loc_enuSwitchState);
    switch(Loc_enuSwitchState)
    {
        case Pressed:
        HLED_enuTurnOn(PINA0);
        break;
        case Released:
        HLED_enuTurnOff(PINA0);
        break;
        default:
        break;
    }
}

void ToggleLED1(void)
{
    HLED_enuToggle(PINA1);
}

int main(void)
{
    RCC_enuCLKControl(HSI,CLK_Enable);
    RCC_enuSelectSysCLK(HSI);
    HLED_enuInit();
    HSwitch_enuInit(1);
    Sched_enuInit();
    Sched_Runnable_t r0 = {.p2f = ControlLED0 , .CyclicTime_ms=1,.periorty=0,.first_delay=0};
    Sched_Runnable_t r1 = {.p2f = ToggleLED1 , .CyclicTime_ms=300,.periorty=2,.first_delay=3000};

    Sched_enuAddRunnable(&r0);
    Sched_enuAddRunnable(&r1);
    Sched_Start();
}