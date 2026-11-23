#include "Queue.h"

Queueu8 CreateQueueu8()
{
    Queueu8 q;
    q.size = 0;
    q.front = 0;
    q.rear = 0;
    return q;
}

static inline u8 Increment(u8 pos)
{
    return (pos + 1) % Queue_Max;
}

Bool_t IsEmptyQueueu8(Queueu8 q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == 0)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t IsFullQueueu8(Queueu8 q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == Queue_Max)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t Queueu8Push(Queueu8 *q, u8 data)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsFullQueueu8(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).arr[(*q).rear] = data;
        (*q).rear = Increment((*q).rear);
        (*q).size++;
    }
    return Loc_enuBool;
}

Bool_t Queueu8Pop(Queueu8 *q)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsEmptyQueueu8(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).front = Increment((*q).front);
        (*q).size--;
    }
    return Loc_enuBool;
}

u8 Queueu8Front(Queueu8 q)
{
    return q.arr[q.front];
}
//-----------------------------------------------------------------


Queueu8ptr CreateQueueu8ptr()
{
    Queueu8ptr q;
    q.size = 0;
    q.front = 0;
    q.rear = 0;
    return q;
}

Bool_t IsEmptyQueueu8ptr(Queueu8ptr q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == 0)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t IsFullQueueu8ptr(Queueu8ptr q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == Queue_Max)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t Queueu8ptrPush(Queueu8ptr *q, u8* data)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsFullQueueu8ptr(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).arr[(*q).rear] = data;
        (*q).rear = Increment((*q).rear);
        (*q).size++;
    }
    return Loc_enuBool;
}

Bool_t Queueu8ptrPop(Queueu8ptr *q)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsEmptyQueueu8ptr(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).front = Increment((*q).front);
        (*q).size--;
    }
    return Loc_enuBool;
}

u8* Queueu8ptrFront(Queueu8ptr q)
{
    return q.arr[q.front];
}

//---------------------------------------------------------------

QueueOrders CreateQueueOrders()
{
    QueueOrders q;
    q.size = 0;
    q.front = 0;
    q.rear = 0;
    return q;
}


Bool_t IsEmptyQueueOrders(QueueOrders q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == 0)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t IsFullQueueOrders(QueueOrders q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == Queue_Max)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t QueueOrdersPush(QueueOrders *q, Orders_t data)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsFullQueueOrders(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).arr[(*q).rear] = data;
        (*q).rear = Increment((*q).rear);
        (*q).size++;
    }
    return Loc_enuBool;
}

Bool_t QueueOrdersPop(QueueOrders *q)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsEmptyQueueOrders(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).front = Increment((*q).front);
        (*q).size--;
    }
    return Loc_enuBool;
}

Orders_t QueueOrdersFront(QueueOrders q)
{
    return q.arr[q.front];
}

//...........................................................

Queueu64 CreateQueueu64()
{
    Queueu64 q;
    q.size = 0;
    q.front = 0;
    q.rear = 0;
    return q;
}

Bool_t IsEmptyQueueu64(Queueu64 q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == 0)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t IsFullQueueu64(Queueu64 q)
{
    Bool_t Loc_enuBool = False_Bool;
    if (q.size == Queue_Max)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t Queueu64Push(Queueu64 *q, u64 data)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsFullQueueu64(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).arr[(*q).rear] = data;
        (*q).rear = Increment((*q).rear);
        (*q).size++;
    }
    return Loc_enuBool;
}

Bool_t Queueu64Pop(Queueu64 *q)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsEmptyQueueu64(*q))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*q).front = Increment((*q).front);
        (*q).size--;
    }
    return Loc_enuBool;
}

u64 Queueu64Front(Queueu64 q)
{
    return q.arr[q.front];
}