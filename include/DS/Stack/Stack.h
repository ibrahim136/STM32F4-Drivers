#ifndef _STACK_H_
#define _STACK_H_
#include "STD_types.h"

#define Stack_Max 100

typedef enum{
    False_Bool,
    True_Bool
}Bool_t;

typedef struct
{
    u64 arr[Stack_Max];
    u8 front;
    u8 rear;
    u8 size;
}Stacku64;

Stacku64 CreateStacku64();
Bool_t IsEmptyStacku64(Stacku64 q);
Bool_t IsFullStacku64(Stacku64 q);
Bool_t Stacku64Push(Stacku64 *q, u64 data);
Bool_t Stacku64Pop(Stacku64 *q);
u64 Stacku64Back(Stacku64 q);


#endif