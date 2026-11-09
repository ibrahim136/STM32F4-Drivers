#ifndef _STK_H_
#define _STK_H_

#include "STD_types.h"


typedef enum
{
    STK_OK,
    STK_InvalidPtr,
    STK_InvalidTime
} STK_Error_Status_t;


typedef void (*STK_Cbf_t)(void);


STK_Error_Status_t STK_enuInit(void);
STK_Error_Status_t STK_enuStart(void);
STK_Error_Status_t STK_enuStop(void);


STK_Error_Status_t STK_enuDelay_ms(u32 Copy_u32DelayMs);
STK_Error_Status_t STK_enuDelay_us(u32 Copy_u32DelayUs);


STK_Error_Status_t STK_enuNotify_on_ms(u32 Copy_u32TimeMs);
STK_Error_Status_t STK_enuSetCbf(STK_Cbf_t Copy_pfCallback);

#endif