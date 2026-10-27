#include "rcc.h"
#include "GPIO.h"

int main(void)
{
    RCC_enuCTRLPeripheral(Peripheral_GPIOA, Peripheral_Enable);
    RCC_enuCTRLPeripheral(Peripheral_GPIOB, Peripheral_Enable);

    for (int i = 0; i < 3; i++)
    {
        PIN_PORT_Conf_t PINAN = {GPIO_PORTA, 0, 0, Pull_up, Mode_Input, 0, 0, 0, i};
        GPIO_enuPinInit(&PINAN);
    }
    for (int i = 0; i < 7; i++)
    {
        PIN_PORT_Conf_t PINBN = {GPIO_PORTB, PIN_LOW, 0, Pull_up, Mode_General_Purpose_Output, 0, 0, 0, i};
        GPIO_enuPinInit(&PINBN);
    }
    while (1)
    {
        u8 sum =0;
        for (int i = 0; i < 3; i++)
        {
            u8 temp =0;
            GPIO_enuPinRead(GPIO_PORTA,i,&temp);
            for (int j=0;j<i;j++)
            {
                temp *=2;
            }
            sum += temp;
        }
        for (int i=0;i<sum;i++){
            GPIO_enuPinWrite(GPIO_PORTB,i,PIN_HIGH);
        }
    }
}