#include "Calculator_cfg.h"

Row_Conf_t Row_PINs[NUM_OF_Rows] =
{
    [Row_1_OUT] = {.PORT=GPIO_PORTB,.PIN=PIN4},
    [Row_2_OUT] = {.PORT=GPIO_PORTB,.PIN=PIN5},
    [Row_3_OUT] = {.PORT=GPIO_PORTB,.PIN=PIN6},
    [Row_4_OUT] = {.PORT=GPIO_PORTB,.PIN=PIN7}
};
