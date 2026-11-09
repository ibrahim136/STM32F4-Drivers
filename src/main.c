#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"

#define TEST_MODE  2

void App_ToggleLED(void)
{
    HLED_enuToggle(LED_BUILTIN_PINC13);
}

int main(void)
{
    RCC_enuCLKControl(HSI, CLK_Enable);
    RCC_enuSelectSysCLK(HSI);
    
    STK_enuInit();
    HLED_enuInit();

#if TEST_MODE == 1
    while(1)
    {
        App_ToggleLED();
        STK_enuDelay_ms(1000);
    }

#elif TEST_MODE == 2
    STK_enuSetCbf(App_ToggleLED);
    STK_enuNotify_on_ms(1000);
    STK_enuStart();

    while(1)
    {
        
    }
#endif

    return 0;
}