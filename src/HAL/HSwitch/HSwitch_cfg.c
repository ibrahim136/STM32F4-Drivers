#include "HSwitch_cfg.h"
#include "HSwitch.h"


const HSwitch_cfg_t HSwitch_cfg[NUM_OF_Switches] =
    {
        [Switch_no_1] = {
            .PORT = GPIO_PORTB,
            .PIN = PIN0,
            .PIN_PUPD = Pull_up,
            .Pressed_State = Pressed_Low
        }
    };