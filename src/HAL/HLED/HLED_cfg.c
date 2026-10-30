#include "HLED_cfg.h"
#include "HLED.h"


const HLED_cfg_t HLED_cfg[NUM_OF_STATES] =
    {
        [Break_LED] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN0,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},

        [Turn_Indicator_LED] = {
            .PORT = GPIO_PORTA,
             .PIN = PIN1,
             .PIN_Speed = Low_Speed,
             .Active_State = Active_HIGH,
             .PIN_Type = Push_Pull}
    };