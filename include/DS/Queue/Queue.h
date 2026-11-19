#ifndef _Queue_H_
#define _Queue_H_
#include "STD_types.h"

#define Queue_Max 100
#define Queueu8ptr_Max Queue_Max

typedef enum{
    False_Bool,
    True_Bool
}Bool_t;

typedef struct
{
    u8 arr[Queue_Max];
    u8 front;
    u8 rear;
    u8 size;
}Queue;

Queue CreateQueue();
Bool_t IsEmptyQueue(Queue q);
Bool_t IsFullQueue(Queue q);
Bool_t QueuePush(Queue *q, u8 data);
Bool_t QueuePop(Queue *q);
u8 QueueFront(Queue q);


typedef struct
{
    u8 *arr[Queueu8ptr_Max];
    u8 front;
    u8 rear;
    u8 size;
}Queueu8ptr;

Queueu8ptr CreateQueueu8ptr();
Bool_t IsEmptyQueueu8ptr(Queueu8ptr q);
Bool_t IsFullQueueu8ptr(Queueu8ptr q);
Bool_t Queueu8ptrPush(Queueu8ptr *q, u8 *data);
Bool_t Queueu8ptrPop(Queueu8ptr *q);
u8* Queueu8ptrFront(Queueu8ptr q);
#endif