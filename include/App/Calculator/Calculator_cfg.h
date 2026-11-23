#ifndef _Calculator_CFG_H_
#define _Calculator_CFG_H_

#include "GPIO.h"

typedef enum{
    Row_1_OUT,
    Row_2_OUT,
    Row_3_OUT,
    Row_4_OUT,
    NUM_OF_Rows
}Row_PINs_t;

typedef enum{
    Col_1_IN,
    Col_2_IN,
    Col_3_IN,
    Col_4_IN,
    NUM_OF_Cols
}Col_PINs_t;

typedef struct
{
    GPIO_Port_t PORT;
    GPIO_PIN_Number_t PIN;
} Row_Conf_t;

#endif