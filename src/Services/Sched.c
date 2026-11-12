#include "Sched.h"
#include "STK.h"

#define Runnables_Count 100

static Sched_Runnable_t *Sched_Runnables[Runnables_Count];
static volatile u8 Is_Triggered =0;
static volatile u8 Sched_Running =0;
static u64 Timems=0;
static void Sched_Handler(void);


Sched_Error_Status_t Sched_enuAddRunnable(Sched_Runnable_t *Ref_strRunnable)
{
    Sched_Error_Status_t Loc_enuSched_Error_Status = Sched_OK;
    if (!Ref_strRunnable)
    {
        Loc_enuSched_Error_Status = Sched_NullPtr;
    }
    if (Loc_enuSched_Error_Status == Sched_OK)
    {
        switch (Ref_strRunnable->periorty)
        {
        case 0 ... Runnables_Count-1:
            break;
        default:
            Loc_enuSched_Error_Status = Sched_InvalidPeriortyNumber;
            break;
        }
    }
    if (Loc_enuSched_Error_Status == Sched_OK && Ref_strRunnable->CyclicTime_ms ==0)
    {
        Loc_enuSched_Error_Status = Sched_InvalidCyclicTime;
    }
    if (Loc_enuSched_Error_Status == Sched_OK)
    {
        if (!Sched_Runnables[Ref_strRunnable->periorty])
        {
            Sched_Runnables[Ref_strRunnable->periorty] = Ref_strRunnable;
        }
        else
        {
            Loc_enuSched_Error_Status = Sched_PeriortyNotFree;
        }
    }
    return Loc_enuSched_Error_Status;
}

Sched_Error_Status_t Sched_enuRemoveRunnable(Sched_Runnable_t *Ref_strRunnable)
{
    Sched_Error_Status_t Loc_enuSched_Error_Status = Sched_OK;
    if (!Ref_strRunnable)
    {
        Loc_enuSched_Error_Status = Sched_NullPtr;
    }
    if (Loc_enuSched_Error_Status == Sched_OK)
    {
        switch (Ref_strRunnable->periorty)
        {
        case 0 ... Runnables_Count - 1:
            break;
        default:
            Loc_enuSched_Error_Status = Sched_InvalidPeriortyNumber;
            break;
        }
    }
    if (Loc_enuSched_Error_Status == Sched_OK)
    {
        if (!Sched_Runnables[Ref_strRunnable->periorty])
        {
            Loc_enuSched_Error_Status = Sched_PeriortyAlreadyFree;
        }
        else
        {
            if (Sched_Runnables[Ref_strRunnable->periorty]->CyclicTime_ms == Ref_strRunnable->CyclicTime_ms &&
                Sched_Runnables[Ref_strRunnable->periorty]->first_delay == Ref_strRunnable->first_delay &&
                Sched_Runnables[Ref_strRunnable->periorty]->p2f == Ref_strRunnable->p2f)
            {
                Sched_Runnables[Ref_strRunnable->periorty] = nullptr;
            }
            else
            {
                Loc_enuSched_Error_Status = Sched_InvalidStructToRemove;
            }
        }
    }
    return Loc_enuSched_Error_Status;
}

Sched_Error_Status_t Sched_enuInit(void)
{
    STK_enuInit();
    STK_enuSetCbf(Sched_Handler);
    STK_enuNotify_on_ms(1);
    return Sched_OK;
}

static void Sched_Handler(void)
{
    Is_Triggered =1;
}

Sched_Error_Status_t Sched_Start(void)
{
    STK_enuStart();
    Sched_Running =1;
    while(Sched_Running)
    {
        if (Is_Triggered)
        {
            Is_Triggered=0;
            Timems++;
            for (int i=0;i<Runnables_Count;i++)
            {
                if (Sched_Runnables[i] != nullptr && Sched_Runnables[i]->p2f != nullptr)
                {
                    if ( (Timems >= Sched_Runnables[i]->first_delay) &&
                     ((Timems - Sched_Runnables[i]->first_delay) % Sched_Runnables[i]->CyclicTime_ms == 0) )
                    {
                        Sched_Runnables[i]->p2f();
                    }
                }

            }
        }
    }
    return Sched_OK;
}

Sched_Error_Status_t Sched_Stop(void)
{
    Sched_Running=0;
    return Sched_OK;
}