#include "HLED_cfg.h"
#include "HLED.h"


const HLED_cfg_t HLED_cfg[NUM_OF_LED] =
    {
        [PINA0] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN0,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},
        [PINA1] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN1,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},
        [PINA2] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN2,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},
        [PINA3] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN3,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},
        [PINA4] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN4,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},
        [PINA5] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN5,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},
        [PINA6] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN6,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull},
        [PINA7] = {
            .PORT = GPIO_PORTA,
            .PIN = PIN7,
            .PIN_Speed = Low_Speed,
            .Active_State = Active_HIGH,
            .PIN_Type = Push_Pull}
    };