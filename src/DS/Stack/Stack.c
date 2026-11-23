#include "Stack.h"

static inline u8 Increment(u8 pos)
{
    return (pos + 1) % Stack_Max;
}

static inline u8 Decrement(u8 pos)
{
    return (pos + Stack_Max - 1) % Stack_Max;
}

Stacku64 CreateStacku64()
{
    Stacku64 s;
    s.size = 0;
    s.front = 0;
    s.rear = 0;
    return s;
}

Bool_t IsEmptyStacku64(Stacku64 s)
{
    Bool_t Loc_enuBool = False_Bool;
    if (s.size == 0)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t IsFullStacku64(Stacku64 s)
{
    Bool_t Loc_enuBool = False_Bool;
    if (s.size == Stack_Max)
    {
        Loc_enuBool = True_Bool;
    }
    return Loc_enuBool;
}

Bool_t Stacku64Push(Stacku64 *s, u64 data)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsFullStacku64(*s))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*s).arr[(*s).rear] = data;
        (*s).rear = Increment((*s).rear);
        (*s).size++;
    }
    return Loc_enuBool;
}

Bool_t Stacku64Pop(Stacku64 *s)
{
    Bool_t Loc_enuBool = True_Bool;
    if (IsEmptyStacku64(*s))
    {
        Loc_enuBool = False_Bool;
    }
    else
    {
        (*s).rear = Decrement((*s).rear);
        (*s).size--;
    }
    return Loc_enuBool;
}

u64 Stacku64Back(Stacku64 s)
{
    if (IsEmptyStacku64(s))
    {
        return 0;
    }
    return s.arr[Decrement(s.rear)];
}