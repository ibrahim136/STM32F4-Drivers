#ifndef Sched_H
#define Sched_H

#include "STD_types.h"
typedef void(*ptr2func)(void);

typedef enum
{
    Sched_OK,
    Sched_NullPtr,
    Sched_InvalidPeriortyNumber,
    Sched_PeriortyNotFree,
    Sched_PeriortyAlreadyFree,
    Sched_InvalidStructToRemove,
    Sched_InvalidCyclicTime,

} Sched_Error_Status_t;

typedef struct
{
    ptr2func p2f;
    u64 CyclicTime_ms;
    u8 periorty;
    u64 first_delay;
}Sched_Runnable_t;

Sched_Error_Status_t Sched_enuAddRunnable(Sched_Runnable_t * Copy_strRunnable);
Sched_Error_Status_t Sched_enuRemoveRunnable(Sched_Runnable_t *Ref_strRunnable);
Sched_Error_Status_t Sched_Start(void);
Sched_Error_Status_t Sched_Stop(void);


#endif