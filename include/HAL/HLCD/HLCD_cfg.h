#ifndef _HLCD_CFG_H_
#define _HLCD_CFG_H_

#define _8_BIT_MODE 0
#define _4_BIT_MODE 1

#define BIT_MODE _4_BIT_MODE

typedef enum{
    RS,
    RW,
    E,
    #if BIT_MODE == _8_BIT_MODE
    D0,
    D1,
    D2,
    D3,
    #endif
    D4,
    D5,
    D6,
    D7,
    NUM_OF_Control_Data_PINs
}Control_Data_PINs_t;

#define Data_Start_Index (E+1)

#endif