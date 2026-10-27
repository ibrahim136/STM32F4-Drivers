#include "rcc.h"

int main(void)
{
    RCC_enuCLKControl(HSE, CLK_Enable);
    PLL_Config_t P = {16, 336, 4, 0, 7};
    RCC_enuConfigurePLL(&P);
    RCC_enuCLKControl(PLL, CLK_Enable);
    RCC_enuSelectSysCLK(HSE);
    RCC_enuCLKControl(PLL, CLK_Disable);
    while (1)
        ;
}