#include "HSwitch_cfg.h"
#include "HSwitch.h"


const HSwitch_cfg_t HSwitch_cfg[NUM_OF_Switches] =
    {
        [Switch_no_1] = {
            .PORT = GPIO_PORTB,
            .PIN = PIN8,
            .PIN_PUPD = Pull_down,
            .Pressed_State = Pressed_High
        },
        [Switch_no_2] = {
            .PORT = GPIO_PORTB,
            .PIN = PIN9,
            .PIN_PUPD = Pull_down,
            .Pressed_State = Pressed_High
        },
        [Switch_no_3] = {
            .PORT = GPIO_PORTB,
            .PIN = PIN10,
            .PIN_PUPD = Pull_down,
            .Pressed_State = Pressed_High
        },
        [Switch_no_4] = {
            .PORT = GPIO_PORTB,
            .PIN = PIN12,
            .PIN_PUPD = Pull_down,
            .Pressed_State = Pressed_High
        }
    };