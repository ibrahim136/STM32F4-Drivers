#include "rcc.h"
#include "GPIO.h"
#include "HLED_cfg.h"
#include "HLED.h"

/*int main(void)
{
    RCC_enuCTRLPeripheral(Peripheral_GPIOA, Peripheral_Enable);
    RCC_enuCTRLPeripheral(Peripheral_GPIOB, Peripheral_Enable);

    for (int i = 0; i < 3; i++)
    {
        PIN_PORT_Conf_t PINAN = {GPIO_PORTA, 0, 0, Pull_down, Mode_Input, 0, 0, i};
        GPIO_enuPinInit(&PINAN);
    }
    for (int i = 0; i < 7; i++)
    {
        PIN_PORT_Conf_t PINBN = {GPIO_PORTB, PIN_LOW, Low_Speed, Pull_up, Mode_General_Purpose_Output,
                                 0, 0, i};
        GPIO_enuPinInit(&PINBN);
    }
    while (1)
    {

        u8 sum = 0;
        for (int i = 0; i < 3; i++)
        {
            u8 temp = 0;
            GPIO_enuPinReadInput(GPIO_PORTA, i, &temp);
            for(int i=0;i<5000;i++);
            u8 temp_2 =0;
            GPIO_enuPinReadInput(GPIO_PORTA, i, &temp_2);
            temp = temp & temp_2;
            for (int j = 0; j < i; j++)
            {
                temp *= 2;
            }
            sum += temp;

        }
        for (int i = 0; i < 7; i++)
        {
            if (i < sum)
            {
                GPIO_enuPinWrite(GPIO_PORTB, i, PIN_HIGH);
            }
            else
            {
                GPIO_enuPinWrite(GPIO_PORTB, i, PIN_LOW);
            }
        }
    }
}
    */

int main (){
    HLED_enuInit();
    while(1)
    {
        HLED_enuTurnOn(Break_LED);
        for (volatile u32 i=0;i<500000;i++);
        HLED_enuTurnOff(Break_LED);
        for (volatile u32 i=0;i<500000;i++);
        
    }
}