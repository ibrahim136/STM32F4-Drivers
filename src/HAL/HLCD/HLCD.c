#include "HLCD.h"
#include "HLCD_cfg.h"
#include "HLCD_priv.h"
#include "rcc.h"
#include "Bit_math.h"
#include "Sched.h"

typedef enum
{
    Function_Set_Wait_1,
    Function_Set_Wait_2,
    Function_Set_Wait_3,
    Function_Set_DONE,

} Function_Set_Instruction_Status_t;

typedef enum
{
    Display_ON_OFF_Wait_1,
    Display_ON_OFF_Wait_2,
    Display_ON_OFF_DONE
} Display_ON_OFF_Status_t;

typedef enum
{
    Display_Clear_Wait_1,
    Display_Clear_Wait_2,
    Display_Clear_DONE
} Display_Clear_Status_t;

typedef enum
{
    Entry_Mode_Wait_1,
    Entry_Mode_Wait_2,
    Entry_Mode_DONE
} Entry_Mode_Status_t;

typedef enum
{
    Write_wait_1,
    Write_wait_2,
    Write_DONE,
}Write_Status_t;

typedef enum
{
    No_Req,
    Init_Pins,
    Function_Set,
    Function_Set_Wait,
    Display_ON_OFF,
    Display_ON_OFF_Wait,
    Display_Clear,
    Display_Clear_Wait,
    Entry_Mode_Set,
    Entry_Mode_Set_Wait,
    Init_Done
} HLCD_InitSeq_t;

typedef enum{
    
}

typedef enum
{
    Available,
    Busy
} HLCD_Busy_t;

static HLCD_Busy_t HLCD_State = Available;

HLCD_InitSeq_t HLCD_InitSeq = No_Req;

Function_Set_Instruction_Status_t HLCD_FunctionSetInstructionStatus = Function_Set_Wait_1;
Display_ON_OFF_Status_t HLCD_DisplayOnOffStatus = Display_ON_OFF_Wait_1;
Display_Clear_Status_t HLCD_DisplayClearStatus = Display_ON_OFF_Wait_1;
Entry_Mode_Status_t HLCD_EntryModeStatus = Entry_Mode_Wait_1;
Write_Status_t HLCD_WriteStatus = Write_wait_1;

extern const HLCD_PIN_cfg_t HLCD_cfg[NUM_OF_Control_Data_PINs];
static void HLCD_Runnable(void);
static Sched_Runnable_t SchedRunnable = {.p2f = HLCD_Runnable, .CyclicTime_ms = 2, .first_delay = 30};

static const Peripheral_t GPIOS_Pheripheral_Enable[GPIO_Count] = {
    Peripheral_GPIOA,
    Peripheral_GPIOB,
    Peripheral_GPIOC,
    Peripheral_GPIOD,
    Peripheral_GPIOE,
    Peripheral_GPIOH};

static inline HLCD_Error_Status_t HLCD_enuRCCErrorToHLCDError(RCC_Error_Status_t Copy_enuRCC_Error_Status)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status;
    switch (Copy_enuRCC_Error_Status)
    {
    case RCC_Timeout:
        Loc_enuHLCD_Error_Status = HLCD_RCC_Timeout;
        break;
    case RCC_InvalidParam:
        Loc_enuHLCD_Error_Status = HLCD_RCC_InvalidParam;
        break;
    case RCC_ClockInUse:
        Loc_enuHLCD_Error_Status = HLCD_RCC_ClockInUse;
        break;
    case RCC_CLKDisabled:
        Loc_enuHLCD_Error_Status = HLCD_RCC_CLKDisabled;
        break;
    case RCC_PLLEnabled:
        Loc_enuHLCD_Error_Status = HLCD_RCC_PLLEnabled;
        break;
    case RCC_InvalidPLLDivisiors:
        Loc_enuHLCD_Error_Status = HLCD_RCC_InvalidPLLDivisiors;
        break;
    case RCC_PLLSRCDisabled:
        Loc_enuHLCD_Error_Status = HLCD_RCC_PLLSRCDisabled;
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_OK;
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuGPIOErrorToHLCDError(GPIO_Error_Status_t Copy_enuGPIO_Error_Status)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status;
    switch (Copy_enuGPIO_Error_Status)
    {
    case GPIO_InvalidParam:
        Loc_enuHLCD_Error_Status = HLCD_GPIO_InvalidParam;
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_OK;
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuInitPINs()
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    switch (BIT_MODE)
    {
    case _8_BIT_MODE:
    case _4_BIT_MODE:
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_InvalidCFG;
        break;
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        for (u8 i = 0; i < NUM_OF_Control_Data_PINs; i++)
        {
            Loc_enuRCC_Error_Status = RCC_enuCTRLPeripheral(GPIOS_Pheripheral_Enable[HLCD_cfg[i].PORT], Peripheral_Enable);
            if (Loc_enuRCC_Error_Status != RCC_OK)
            {
                Loc_enuHLCD_Error_Status = HLCD_enuRCCErrorToHLCDError(Loc_enuRCC_Error_Status);
                break;
            }

            PIN_PORT_Conf_t Loc_strPIN_PORT_Conf = {
                .PORT = HLCD_cfg[i].PORT,
                .PIN_State = (PIN_LOW),
                .PIN_Speed = Low_Speed,
                .PIN_PUPD = No_pull_up_pull_down,
                .PIN_Mode = Mode_General_Purpose_Output,
                .PIN_Type = Push_Pull,
                .PIN_AF = AF0,
                .PIN = HLCD_cfg[i].PIN};

            Loc_enuGPIO_Error_Status = GPIO_enuPinInit(&Loc_strPIN_PORT_Conf);
            if (Loc_enuGPIO_Error_Status != GPIO_OK)
            {
                Loc_enuHLCD_Error_Status = HLCD_enuGPIOErrorToHLCDError(Loc_enuGPIO_Error_Status);
                break;
            }
        }
    }

    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuPINValid(Control_Data_PINs_t Copy_enuPIN)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    switch (Copy_enuPIN)
    {
    case 0 ... NUM_OF_Control_Data_PINs:
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_InvalidPIN;
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuPINCtrl(Control_Data_PINs_t Copy_enuPIN, GPIO_PIN_State_t Copy_enuState)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_enuPINValid(Copy_enuPIN);
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuGPIO_Error_Status = GPIO_enuPinWrite(HLCD_cfg[Copy_enuPIN].PORT, HLCD_cfg[Copy_enuPIN].PIN, Copy_enuState);
        if (Loc_enuGPIO_Error_Status != GPIO_OK)
        {
            Loc_enuHLCD_Error_Status = HLCD_enuGPIOErrorToHLCDError(Loc_enuGPIO_Error_Status);
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuSendCommand(u8 Copy_u8Command)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
#if BIT_MODE == _4_BIT_MODE
    switch (Copy_u8Command)
    {
    case 0b0 ... 0b1111:
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_InvalidCommand;
        break;
    }
#endif
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(RS, PIN_LOW);
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(RW, PIN_LOW);
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(E, PIN_HIGH);
    }

    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {

        for (u8 i = Data_Start_Index; i < NUM_OF_Control_Data_PINs; i++)
        {
            u8 Loc_u8TempBit = Get_Lastbit(Copy_u8Command);
            switch (Loc_u8TempBit)
            {
            case 0:
                Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(i, PIN_LOW);
                break;
            default:
                Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(i, PIN_HIGH);
                break;
            }
            if (Loc_enuHLCD_Error_Status != HLCD_OK)
            {
                break;
            }
            Copy_u8Command = Shift_Right_by_one(Copy_u8Command);
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuFunctionSet(Function_Set_Instruction_Status_t *Ref_enuFunctionSetInstructionWait)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
#if BIT_MODE == _8_BIT_MODE
    Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Function_Set_8_BIT);
    *Ref_enuFunctionSetInstructionWait = Function_Set_DONE;
#elif BIT_MODE == _4_BIT_MODE
    switch (*Ref_enuFunctionSetInstructionWait)
    {
    case Function_Set_Wait_1:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Function_Set_4_BIT_1);
        (*Ref_enuFunctionSetInstructionWait)++;
        break;
    case Function_Set_Wait_2:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Function_Set_4_BIT_2);
        (*Ref_enuFunctionSetInstructionWait)++;
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Function_Set_4_BIT_3);
        (*Ref_enuFunctionSetInstructionWait)++;
        break;
    }
#endif
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuDisplayOnOff(Display_ON_OFF_Status_t *Ref_enuDisplayOnOff)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
#if BIT_MODE == _8_BIT_MODE
    Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Display_On_Off_8_BIT);
    *Ref_enuDisplayOnOff = Display_ON_OFF_DONE;
#elif BIT_MODE == _4_BIT_MODE
    switch (*Ref_enuDisplayOnOff)
    {
    case Display_ON_OFF_Wait_1:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Display_On_Off_4_BIT_1);
        (*Ref_enuDisplayOnOff)++;
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Display_On_Off_4_BIT_2);
        (*Ref_enuDisplayOnOff)++;
        break;
    }
#endif
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuDisplayClear(Display_Clear_Status_t *Ref_enuDisplayClear)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
#if BIT_MODE == _8_BIT_MODE
    Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Display_On_Off_8_BIT);
    *Ref_enuDisplayClear = Display_Clear_DONE;
#elif BIT_MODE == _4_BIT_MODE
    switch (*Ref_enuDisplayClear)
    {
    case Display_Clear_Wait_1:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Display_On_Off_4_BIT_1);
        (*Ref_enuDisplayClear)++;
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Display_On_Off_4_BIT_2);
        (*Ref_enuDisplayClear)++;
        break;
    }
#endif
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuEntryMode(Entry_Mode_Status_t *Ref_enuEntryMode)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
#if BIT_MODE == _8_BIT_MODE
    Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Entry_Mode_8_Bit);
    *Ref_enuEntryMode = Entry_Mode_DONE;
#elif BIT_MODE == _4_BIT_MODE
    switch (*Ref_enuEntryMode)
    {
    case Display_Clear_Wait_1:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Entry_Mode_4_Bit_1);
        (*Ref_enuEntryMode)++;
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Entry_Mode_4_Bit_2);
        (*Ref_enuEntryMode)++;
        break;
    }
#endif
    return Loc_enuHLCD_Error_Status;
}

static void HLCD_Runnable(void)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    if (HLCD_InitSeq == Init_Done)
    {
    }
    else
    {
        switch (HLCD_InitSeq)
        {
        case Init_Pins:
            HLCD_enuInitPINs();
            HLCD_InitSeq++;
            break;
        case Function_Set:
            Loc_enuHLCD_Error_Status = HLCD_enuFunctionSet(&HLCD_FunctionSetInstructionStatus);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq++;
            break;
        case Function_Set_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (HLCD_FunctionSetInstructionStatus == Function_Set_DONE)
                {
                    HLCD_InitSeq++;
                }
                else
                {
                    HLCD_InitSeq--;
                }
            }
            break;
        case Display_ON_OFF:
            Loc_enuHLCD_Error_Status = HLCD_enuDisplayOnOff(&HLCD_DisplayOnOffStatus);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq++;
            break;
        case Display_ON_OFF_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (HLCD_DisplayOnOffStatus == Display_ON_OFF_DONE)
                {
                    HLCD_InitSeq++;
                }
                else
                {
                    HLCD_InitSeq--;
                }
            }
            break;
        case Display_Clear:
            Loc_enuHLCD_Error_Status = HLCD_enuDisplayClear(&HLCD_DisplayClearStatus);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq++;
            break;
        case Display_Clear_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (HLCD_DisplayClearStatus == Display_Clear_DONE)
                {
                    HLCD_InitSeq++;
                }
                else
                {
                    HLCD_InitSeq--;
                }
            }
            break;
        case Entry_Mode_Set:
            Loc_enuHLCD_Error_Status = HLCD_enuEntryMode(&HLCD_EntryModeStatus);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq++;
            break;
        case Entry_Mode_Set_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (HLCD_EntryModeStatus == Entry_Mode_DONE)
                {
                    HLCD_InitSeq++;
                }
                else
                {
                    HLCD_InitSeq--;
                }
            }
            break;
        default:
            HLCD_State = Available;
            break;
        }
    }
}

HLCD_Error_Status_t HLCD_enuInit(u8 Copy_u8Priority)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    if (HLCD_State == Busy)
    {
        Loc_enuHLCD_Error_Status = HLCD_Busy;
    }
    else
    {
        SchedRunnable.periorty = Copy_u8Priority;
        Sched_enuAddRunnable(&SchedRunnable);
        HLCD_InitSeq = Init_Pins;
        HLCD_State = Busy;
    }
    return Loc_enuHLCD_Error_Status;
}
