#include "rcc.h"

int main(void)
{
    RCC_enuCTRLPeripheral(Peripheral_GPIOC, Peripheral_Enable);
    RCC_enuCTRLPeripheral(Peripheral_GPIOB, Peripheral_Enable);
    while (1)
        ;
}