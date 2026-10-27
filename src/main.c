#include "rcc.h"
#include "GPIO.h"

int main(void)
{
    RCC_enuCTRLPeripheral(Peripheral_GPIOC,Peripheral_Enable);
    GPIO_enuCfgPINMode(GPIO_PORTC,PIN13,Mode_General_Purpose_Output);

    
    while (1)
    {
        GPIO_enuPinWrite(GPIO_PORTC, PIN13, PIN_LOW);
        for(volatile u32 i=0; i<500000; i++);
        GPIO_enuPinWrite(GPIO_PORTC, PIN13, PIN_HIGH);
        for(volatile u32 i=0; i<500000; i++);
    }
}