#include "rcc.h"

int main(void)
{
    RCC_enuCTRLPeripheral(Peripheral_GPIOC, Peripheral_Enable);
    while (1)
        ;
}