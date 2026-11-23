#ifndef _Queue_H_
#define _Queue_H_
#include "STD_types.h"

#define Queue_Max 100

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
}Queueu8;

Queueu8 CreateQueueu8();
Bool_t IsEmptyQueueu8(Queueu8 q);
Bool_t IsFullQueueu8(Queueu8 q);
Bool_t Queueu8Push(Queueu8 *q, u8 data);
Bool_t Queueu8Pop(Queueu8 *q);
u8 Queueu8Front(Queueu8 q);

//--------------------------------------------------------------------

typedef struct
{
    u8 *arr[Queue_Max];
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

//------------------------------------------------------------

typedef enum
{
    CMD,
    Data,
    String
}Orders_t;

typedef struct
{
    Orders_t arr[Queue_Max];
    u8 front;
    u8 rear;
    u8 size;
}QueueOrders;

QueueOrders CreateQueueOrders();
Bool_t IsEmptyQueueOrders(QueueOrders q);
Bool_t IsFullQueueOrders(QueueOrders q);
Bool_t QueueOrdersPush(QueueOrders *q, Orders_t data);
Bool_t QueueOrdersPop(QueueOrders *q);
Orders_t QueueOrdersFront(QueueOrders q);



//....................................................................

typedef struct
{
    u8 arr[Queue_Max];
    u8 front;
    u8 rear;
    u8 size;
}Queueu64;

Queueu64 CreateQueueu64();
Bool_t IsEmptyQueueu64(Queueu64 q);
Bool_t IsFullQueueu64(Queueu64 q);
Bool_t Queueu64Push(Queueu64 *q, u64 data);
Bool_t Queueu64Pop(Queueu64 *q);
u64 Queueu64Front(Queueu64 q);


#endif