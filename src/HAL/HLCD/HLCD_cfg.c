#include "HLCD_cfg.h"
#include "HLCD.h"

const HLCD_PIN_cfg_t HLCD_cfg[NUM_OF_Control_Data_PINs] =
    {
        [RS] = {.PORT = GPIO_PORTB, .PIN = PIN0},
        [RW] = {.PORT = GPIO_PORTB, .PIN = PIN1},
        [E] = {.PORT = GPIO_PORTB, .PIN = PIN2},
        
        #if BIT_MODE == _8_BIT_MODE
        [D0] = {.PORT = GPIO_PORTA, .PIN = PIN0},
        [D1] = {.PORT = GPIO_PORTA, .PIN = PIN1},
        [D2] = {.PORT = GPIO_PORTA, .PIN = PIN2},
        [D3] = {.PORT = GPIO_PORTA, .PIN = PIN3},
        #endif
        [D4] = {.PORT = GPIO_PORTA, .PIN = PIN4},
        [D5] = {.PORT = GPIO_PORTA, .PIN = PIN5},
        [D6] = {.PORT = GPIO_PORTA, .PIN = PIN6},
        [D7] = {.PORT = GPIO_PORTA, .PIN = PIN7},
};
