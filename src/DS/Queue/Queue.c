#include "Queue.h"

Queue CreateQueue()
{
    Queue q;
    q.size = 0;
    q.front = 0;
    q.rear = 0;
    return q;
}

static inline u8 Increment(u8 pos)
{
    return (pos + 1) % Queue_Max;
}

Bool_t IsEmptyQueue(Queue q)
{
    Bool_t bool = False_Bool;
    if (q.size == 0)
    {
        bool = True_Bool;
    }
    return bool;
}

Bool_t IsFullQueue(Queue q)
{
    Bool_t bool = False_Bool;
    if (q.size == Queue_Max)
    {
        bool = True_Bool;
    }
    return bool;
}

Bool_t QueuePush(Queue *q, u8 data)
{
    Bool_t bool = True_Bool;
    if (IsFullQueue(*q))
    {
        bool = False_Bool;
    }
    else
    {
        (*q).arr[(*q).rear] = data;
        (*q).rear = Increment((*q).rear);
        (*q).size++;
    }
    return bool;
}

Bool_t QueuePop(Queue *q)
{
    Bool_t bool = True_Bool;
    if (IsEmptyQueue(*q))
    {
        bool = False_Bool;
    }
    else
    {
        (*q).front = Increment((*q).front);
    }
    return bool;
}

u8 QueueFront(Queue q)
{
    return q.arr[q.front];
}
