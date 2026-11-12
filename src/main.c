#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"

#define TEST_MODE 2

void ToggleLED0(void)
{
    HLED_enuToggle(PINA0);
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
    Sched_enuInit();
    Sched_Runnable_t r0 = {.p2f = ToggleLED0 , .CyclicTime_ms=900,.periorty=0,.first_delay=0};
    Sched_Runnable_t r1 = {.p2f = ToggleLED1 , .CyclicTime_ms=300,.periorty=1,.first_delay=3000};

    Sched_enuAddRunnable(&r0);
    Sched_enuAddRunnable(&r1);
    Sched_Start();
}