#include "HLCD.h"
#include "HLCD_cfg.h"
#include "HLCD_priv.h"
#include "rcc.h"
#include "Bit_math.h"
#include "Sched.h"
#include "Queue.h"

typedef enum
{
    Wait2_1,
    Wait2_2,
    Wait2_Done
} Two_Waits_t;

typedef enum
{
    Wait3_1,
    Wait3_2,
    Wait3_3,
    Wait3_Done
} Three_Waits_t;

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
} HLCD_enuInitSeq_t;

typedef enum
{
    Available,
    Busy
} HLCD_Busy_t;

static HLCD_Busy_t HLCD_State[LCD_Count];

HLCD_enuInitSeq_t HLCD_InitSeq[LCD_Count];

static Two_Waits_t Two_Waits[LCD_Count];
static Three_Waits_t Three_Waits[LCD_Count];

extern const LCD_Init_cfg_t LCDs_Init_Conf[LCD_Count];
extern const HLCD_PIN_cfg_t HLCD_PIN_cfg[LCD_Count][NUM_OF_Control_Data_PINs];
static void HLCD_Runnable(void);
static Sched_Runnable_t SchedRunnable[LCD_Count];

static const Peripheral_t GPIOS_Pheripheral_Enable[GPIO_Count] = {
    Peripheral_GPIOA,
    Peripheral_GPIOB,
    Peripheral_GPIOC,
    Peripheral_GPIOD,
    Peripheral_GPIOE,
    Peripheral_GPIOH};

static inline HLCD_Error_Status_t HLCD_enuValidLCDNumber(LCD_Numbers_t Copy_enuLCDNumber)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    switch (Copy_enuLCDNumber)
    {
    case 0 ... LCD_Count:
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_InvalidLCDNumber;
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_ValidBitMode(LCD_Numbers_t Copy_enuLCDNumber)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    switch (LCDs_Init_Conf[Copy_enuLCDNumber].DL)
    {
    case _8_BIT_MODE:
    case _4_BIT_MODE:
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_InvalidCFG;
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

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

static inline HLCD_Error_Status_t HLCD_enuInitPINs(LCD_Numbers_t Copy_enuLCDNumber)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_enuValidLCDNumber(Copy_enuLCDNumber);
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_ValidBitMode(Copy_enuLCDNumber);
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        for (u8 i = 0; i < NUM_OF_Control_Data_PINs; i++)
        {
            Loc_enuRCC_Error_Status = RCC_enuCTRLPeripheral(GPIOS_Pheripheral_Enable[HLCD_PIN_cfg[Copy_enuLCDNumber][i].PORT], Peripheral_Enable);
            if (Loc_enuRCC_Error_Status != RCC_OK)
            {
                Loc_enuHLCD_Error_Status = HLCD_enuRCCErrorToHLCDError(Loc_enuRCC_Error_Status);
                break;
            }

            PIN_PORT_Conf_t Loc_strPIN_PORT_Conf = {
                .PORT = HLCD_PIN_cfg[Copy_enuLCDNumber][i].PORT,
                .PIN_State = (PIN_LOW),
                .PIN_Speed = Low_Speed,
                .PIN_PUPD = No_pull_up_pull_down,
                .PIN_Mode = Mode_General_Purpose_Output,
                .PIN_Type = Push_Pull,
                .PIN_AF = AF0,
                .PIN = HLCD_PIN_cfg[Copy_enuLCDNumber][i].PIN};

            Loc_enuGPIO_Error_Status = GPIO_enuPinInit(&Loc_strPIN_PORT_Conf);
            if (Loc_enuGPIO_Error_Status != GPIO_OK)
            {
                Loc_enuHLCD_Error_Status = HLCD_enuGPIOErrorToHLCDError(Loc_enuGPIO_Error_Status);
                break;
            }
            if (i == E && !LCDs_Init_Conf[Copy_enuLCDNumber].DL)
            {
                i = D3;
            }
        }
    }

    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuPINValid(LCD_Numbers_t Copy_enuLCDNumber, Control_Data_PINs_t Copy_enuPIN)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    if (Copy_enuPIN > NUM_OF_Control_Data_PINs)
    {
        Loc_enuHLCD_Error_Status = HLCD_InvalidPIN;
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuPINCtrl(LCD_Numbers_t Copy_enuLCDNumber, Control_Data_PINs_t Copy_enuPIN, GPIO_PIN_State_t Copy_enuState)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_enuPINValid(Copy_enuLCDNumber, Copy_enuPIN);
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuGPIO_Error_Status = GPIO_enuPinWrite(HLCD_PIN_cfg[Copy_enuLCDNumber][Copy_enuPIN].PORT, HLCD_PIN_cfg[Copy_enuLCDNumber][Copy_enuPIN].PIN, Copy_enuState);
        if (Loc_enuGPIO_Error_Status != GPIO_OK)
        {
            Loc_enuHLCD_Error_Status = HLCD_enuGPIOErrorToHLCDError(Loc_enuGPIO_Error_Status);
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuValid(LCD_Numbers_t Copy_enuLCDNumber, u8 Copy_u8Command_Data)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    if (LCDs_Init_Conf[Copy_enuLCDNumber].DL == _4_BIT_MODE)
    {
        if (Copy_u8Command_Data > Full_4_bit_ones)
        {
            Loc_enuHLCD_Error_Status = HLCD_InvalidCommand;
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuSendCommand(LCD_Numbers_t Copy_enuLCDNumber, u8 Copy_u8Command)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_enuValid(Copy_enuLCDNumber, Copy_u8Command);

    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, RS, PIN_LOW);
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, RW, PIN_LOW);
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, E, PIN_HIGH);
    }

    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {

        for (u8 i = Data_Start_Index(LCDs_Init_Conf[Copy_enuLCDNumber].DL); i < NUM_OF_Control_Data_PINs; i++)
        {
            u8 Loc_u8TempBit = Get_Lastbit(Copy_u8Command);
            switch (Loc_u8TempBit)
            {
            case 0:
                Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, i, PIN_LOW);
                break;
            default:
                Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, i, PIN_HIGH);
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

static inline HLCD_Error_Status_t HLCD_enuFunctionSet(LCD_Numbers_t Copy_enuLCDNumber, Three_Waits_t *Ref_enuThree_Waits)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    u8 Loc_u8Command = Function_Set_Command(LCDs_Init_Conf[Copy_enuLCDNumber].DL, LCDs_Init_Conf[Copy_enuLCDNumber].N, LCDs_Init_Conf[Copy_enuLCDNumber].DL);
    switch (LCDs_Init_Conf[Copy_enuLCDNumber].DL)
    {
    case _8_BIT_MODE:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
        *Ref_enuThree_Waits = Wait3_Done;
        break;
    default:
        switch (*Ref_enuThree_Waits)
        {
        case Wait3_1:
        case Wait3_2:
            Loc_u8Command = Get_HigherNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuThree_Waits)++;
            break;
        default:
            Loc_u8Command = Get_LowerNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuThree_Waits)++;
            break;
        }
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuDisplayOnOff(LCD_Numbers_t Copy_enuLCDNumber, Two_Waits_t *Ref_enuTwo_Waits)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    u8 Loc_u8Command = Display_On_Off_Command(LCDs_Init_Conf[Copy_enuLCDNumber].D, LCDs_Init_Conf[Copy_enuLCDNumber].C, LCDs_Init_Conf[Copy_enuLCDNumber].B);
    switch (LCDs_Init_Conf[Copy_enuLCDNumber].DL)
    {
    case _8_BIT_MODE:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
        *Ref_enuTwo_Waits = Wait2_Done;
        break;
    default:
        switch (*Ref_enuTwo_Waits)
        {
        case Wait2_1:
            Loc_u8Command = Get_HigherNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        default:
            Loc_u8Command = Get_LowerNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuDisplayClear(LCD_Numbers_t Copy_enuLCDNumber, Two_Waits_t *Ref_enuTwo_Waits)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    u8 Loc_u8Command = Clear_Display_Command;
    switch (LCDs_Init_Conf[Copy_enuLCDNumber].DL)
    {
    case _8_BIT_MODE:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
        *Ref_enuTwo_Waits = Wait2_Done;
        break;
    default:
        switch (*Ref_enuTwo_Waits)
        {
        case Wait2_1:
            Loc_u8Command = Get_HigherNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        default:
            Loc_u8Command = Get_LowerNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuEntryMode(LCD_Numbers_t Copy_enuLCDNumber, Two_Waits_t *Ref_enuTwo_Waits)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    u8 Loc_u8Command = Entry_Mode_Command(LCDs_Init_Conf[Copy_enuLCDNumber].I_D, LCDs_Init_Conf[Copy_enuLCDNumber].S);
    switch (LCDs_Init_Conf[Copy_enuLCDNumber].DL)
    {
    case _8_BIT_MODE:
        Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
        *Ref_enuTwo_Waits = Wait2_Done;
        break;
    default:
        switch (*Ref_enuTwo_Waits)
        {
        case Wait2_1:
            Loc_u8Command = Get_HigherNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        default:
            Loc_u8Command = Get_LowerNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuSendData(LCD_Numbers_t Copy_enuLCDNumber, u8 Copy_u8Data)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_enuValid(Copy_enuLCDNumber, Copy_u8Data);

    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, RS, PIN_HIGH);
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, RW, PIN_LOW);
    }
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, E, PIN_HIGH);
    }

    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {

        for (u8 i = Data_Start_Index(LCDs_Init_Conf[Copy_enuLCDNumber].DL); i < NUM_OF_Control_Data_PINs; i++)
        {
            u8 Loc_u8TempBit = Get_Lastbit(Copy_u8Data);
            switch (Loc_u8TempBit)
            {
            case 0:
                Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, i, PIN_LOW);
                break;
            default:
                Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Copy_enuLCDNumber, i, PIN_HIGH);
                break;
            }
            if (Loc_enuHLCD_Error_Status != HLCD_OK)
            {
                break;
            }
            Copy_u8Data = Shift_Right_by_one(Copy_u8Data);
        }
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_enuSendChar(LCD_Numbers_t Copy_enuLCDNumber, u8 Copy_u8Data, Two_Waits_t *Ref_enuTwo_Waits)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    u8 Loc_u8Command = Copy_u8Data;
    switch (LCDs_Init_Conf[Copy_enuLCDNumber].DL)
    {
    case _8_BIT_MODE:
        Loc_enuHLCD_Error_Status = HLCD_enuSendData(Copy_enuLCDNumber, Loc_u8Command);
        *Ref_enuTwo_Waits = Wait2_Done;
        break;
    default:
        switch (*Ref_enuTwo_Waits)
        {
        case Wait2_1:
            Loc_u8Command = Get_HigherNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendData(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        default:
            Loc_u8Command = Get_LowerNipple(Loc_u8Command);
            Loc_enuHLCD_Error_Status = HLCD_enuSendData(Copy_enuLCDNumber, Loc_u8Command);
            (*Ref_enuTwo_Waits)++;
            break;
        }
    }
    return Loc_enuHLCD_Error_Status;
}

typedef struct
{
    LCD_Numbers_t LCD_no;
    u8 Priority;
} LCD_Periority_t;

static LCD_Periority_t LCD_Periority[LCD_Count];
static u8 LCD_CNT_for_Runnables = 0;
static u8 exisit_LCDs;

typedef enum
{
    No_req,
    Write_Cmd,
    Write_Cmd_Wait,
    Write_String,
    Write_String_Wait,
    Write_Data,
    Write_Data_Wait,
    Write_Done
} HLCD_enuDataSeq_t;

HLCD_enuDataSeq_t HLCD_DataSeq[LCD_Count];
static u8 String_Index[LCD_Count];
static u8 RequestedString[LCD_Count][16*100];
static ReuestedCMD[LCD_Count][100];
static u8 Cur_Pos[LCD_Count];

typedef enum
{
    CMD,
    Data,
    String
}Orders_t;

static Queue Orders[LCD_Count];
static Queue Data[LCD_Count];
static Queue CMD[LCD_Count];
static Queueu8ptr Strings[LCD_Count];

HLCD_Error_Status_t HLCD_enuWriteString(LCD_Numbers_t Copy_enuLCDNumber, u8 *Copy_u8String)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        Queueu8ptrPush (&Strings[Copy_enuLCDNumber], Copy_u8String);
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_ValidRow(Row_Number_t Copy_enuRow)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    switch (Copy_enuRow)
    {
    case 0 ... Row_Count - 1:
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_InvalidRow;
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

static inline HLCD_Error_Status_t HLCD_ValidCol(Col_Number_t Copy_enuCol)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    switch (Copy_enuCol)
    {
    case 0 ... Col_Count - 1:
        break;
    default:
        Loc_enuHLCD_Error_Status = HLCD_InvalidRow;
        break;
    }
    return Loc_enuHLCD_Error_Status;
}

HLCD_Error_Status_t HLCD_enuSetCursorPos(LCD_Numbers_t Copy_enuLCDNumber, Row_Number_t Copy_enuRow, Col_Number_t Copy_enuCol)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    if (HLCD_State[Copy_enuLCDNumber] != Available)
        Loc_enuHLCD_Error_Status = HLCD_Busy;
    if (Loc_enuHLCD_Error_Status == HLCD_OK && HLCD_InitSeq[Copy_enuLCDNumber] != Init_Done)
        Loc_enuHLCD_Error_Status = HLCD_LCDNotInitilized;
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        HLCD_DataSeq[Copy_enuLCDNumber] = Write_Cmd;
        Cur_Pos[Copy_enuLCDNumber] = Cursor_Position_Command(Copy_enuRow, Copy_enuCol);
        HLCD_State[Copy_enuLCDNumber] = Busy;
    }
    return Loc_enuHLCD_Error_Status;
}

static void HLCD_Runnable(void)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_OK;
    LCD_Numbers_t Loc_LCDnumber = LCD_Periority[LCD_CNT_for_Runnables].LCD_no;
    if (HLCD_InitSeq[Loc_LCDnumber] == Init_Done)
    {
        switch (HLCD_DataSeq[Loc_LCDnumber])
        {
        case Write_Cmd:
            Loc_enuHLCD_Error_Status = HLCD_enuSendCommand(Loc_LCDnumber, &Two_Waits[Loc_LCDnumber]);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                HLCD_DataSeq[Loc_LCDnumber]++;
            }
            break;
        case Write_Cmd_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Loc_LCDnumber, E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (Two_Waits[Loc_LCDnumber] == Wait2_Done)
                {
                    Two_Waits[Loc_LCDnumber] = Wait2_1;
                    HLCD_DataSeq[Loc_LCDnumber] = Write_Done;
                }
                else
                {
                    HLCD_DataSeq[Loc_LCDnumber]--;
                }
            }
            break;
        case Write_String:
            Loc_enuHLCD_Error_Status = HLCD_enuSendChar(Loc_LCDnumber, RequestedString[Loc_LCDnumber][String_Index[Loc_LCDnumber]], &Two_Waits[Loc_LCDnumber]);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                HLCD_DataSeq[Loc_LCDnumber]++;
                String_Index[Loc_LCDnumber]++;
            }
            break;
        case Write_String_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Loc_LCDnumber, E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (Two_Waits[Loc_LCDnumber] == Wait2_Done)
                {
                    Two_Waits[Loc_LCDnumber] = Wait2_1;
                    if (RequestedString[Loc_LCDnumber][String_Index[Loc_LCDnumber]] == '\0')
                    {
                        HLCD_DataSeq[Loc_LCDnumber] = Write_Done;
                    }
                    else
                    {
                        HLCD_DataSeq[Loc_LCDnumber]--;
                    }
                }
                else
                {
                    HLCD_DataSeq[Loc_LCDnumber]--;
                    String_Index[Loc_LCDnumber]--;
                }
            }
            break;
        case Write_Data:
            // Loc_enuHLCD_Error_Status = HLCD_enuSendChar(Loc_LCDnumber, 'a', &Two_Waits[Loc_LCDnumber]);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_DataSeq[Loc_LCDnumber]++;
            break;
        case Write_Data_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Loc_LCDnumber, E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (Two_Waits[Loc_LCDnumber] == Wait2_Done)
                {
                    Two_Waits[Loc_LCDnumber] = Wait2_1;
                    HLCD_DataSeq[Loc_LCDnumber]++;
                }
                else
                {
                    HLCD_DataSeq[Loc_LCDnumber]--;
                }
            }
            break;
        default:
            HLCD_State[Loc_LCDnumber] = Available;
            break;
        }
    }
    else
    {
        switch (HLCD_InitSeq[Loc_LCDnumber])
        {
        case Init_Pins:
            HLCD_enuInitPINs(Loc_LCDnumber);
            HLCD_InitSeq[Loc_LCDnumber]++;
            break;
        case Function_Set:
            Loc_enuHLCD_Error_Status = HLCD_enuFunctionSet(Loc_LCDnumber, &Three_Waits[Loc_LCDnumber]);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq[Loc_LCDnumber]++;
            break;
        case Function_Set_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Loc_LCDnumber, E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (Three_Waits[Loc_LCDnumber] == Wait3_Done)
                {
                    Three_Waits[Loc_LCDnumber] = Wait3_1;
                    HLCD_InitSeq[Loc_LCDnumber]++;
                }
                else
                {
                    HLCD_InitSeq[Loc_LCDnumber]--;
                }
            }
            break;
        case Display_ON_OFF:
            Loc_enuHLCD_Error_Status = HLCD_enuDisplayOnOff(Loc_LCDnumber, &Two_Waits[Loc_LCDnumber]);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq[Loc_LCDnumber]++;
            break;
        case Display_ON_OFF_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Loc_LCDnumber, E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (Two_Waits[Loc_LCDnumber] == Wait2_Done)
                {
                    Two_Waits[Loc_LCDnumber] = Wait2_1;
                    HLCD_InitSeq[Loc_LCDnumber]++;
                }
                else
                {
                    HLCD_InitSeq[Loc_LCDnumber]--;
                }
            }
            break;
        case Display_Clear:
            Loc_enuHLCD_Error_Status = HLCD_enuDisplayClear(Loc_LCDnumber, &Two_Waits[Loc_LCDnumber]);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq[Loc_LCDnumber]++;
            break;
        case Display_Clear_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Loc_LCDnumber, E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (Two_Waits[Loc_LCDnumber] == Wait2_Done)
                {
                    Two_Waits[Loc_LCDnumber] = Wait2_1;
                    HLCD_InitSeq[Loc_LCDnumber]++;
                }
                else
                {
                    HLCD_InitSeq[Loc_LCDnumber]--;
                }
            }
            break;
        case Entry_Mode_Set:
            Loc_enuHLCD_Error_Status = HLCD_enuEntryMode(Loc_LCDnumber, &Two_Waits[Loc_LCDnumber]);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
                HLCD_InitSeq[Loc_LCDnumber]++;
            break;
        case Entry_Mode_Set_Wait:
            Loc_enuHLCD_Error_Status = HLCD_enuPINCtrl(Loc_LCDnumber, E, PIN_LOW);
            if (Loc_enuHLCD_Error_Status == HLCD_OK)
            {
                if (Two_Waits[Loc_LCDnumber] == Wait2_Done)
                {
                    Two_Waits[Loc_LCDnumber] = Wait2_1;
                    HLCD_InitSeq[Loc_LCDnumber]++;
                    HLCD_State[Loc_LCDnumber] = Available;
                }
                else
                {
                    HLCD_InitSeq[Loc_LCDnumber]--;
                }
            }
            break;
        default:
            break;
        }
    }
    LCD_CNT_for_Runnables = (LCD_CNT_for_Runnables + 1) % exisit_LCDs;
}

static inline void swapLCDPeriorityies(u8 index1, u8 index2)
{
    LCD_Periority_t temp = LCD_Periority[index1];
    LCD_Periority[index1] = LCD_Periority[index2];
    LCD_Periority[index2] = temp;
    return;
}

static inline void OrderingLCDPeriorityArray(void)
{
    for (u8 i = exisit_LCDs; i > 0; i--)
    {
        if (LCD_Periority[i].Priority < LCD_Periority[i - 1].Priority)
        {
            swapLCDPeriorityies(i, i - 1);
        }
        else
        {
            break;
        }
    }
}

static inline u8 EnoughLCDs(void)
{
    u8 Loc_return = 0;
    if (exisit_LCDs == LCD_Count)
    {
        Loc_return = 1;
    }
    return Loc_return;
}

static inline u8 AlreadyInitilized(LCD_Numbers_t Copy_enuLCDNumber)
{
    u8 Loc_return = 0;
    for (u8 i = 0; i < exisit_LCDs; i--)
    {
        if (LCD_Periority[i].LCD_no == Copy_enuLCDNumber)
        {
            Loc_return = 1;
            break;
        }
    }
    return Loc_return;
}

static inline void settingcursorposatbegining(LCD_Numbers_t Copy_enuLCDNumber)
{
    Cur_Pos[Copy_enuLCDNumber] = Cursor_Position_Command(Row_1, Col_1);
    return;
}

HLCD_Error_Status_t HLCD_enuInit(LCD_Numbers_t Copy_enuLCDNumber, u8 Copy_u8Priority)
{
    HLCD_Error_Status_t Loc_enuHLCD_Error_Status = HLCD_enuValidLCDNumber(Copy_enuLCDNumber);
    if (Loc_enuHLCD_Error_Status == HLCD_OK && EnoughLCDs())
        Loc_enuHLCD_Error_Status = HLCD_LCDLimit;
    if (Loc_enuHLCD_Error_Status == HLCD_OK && AlreadyInitilized(Copy_enuLCDNumber))
        Loc_enuHLCD_Error_Status = HLCD_AlreadyInitilized;
    if (Loc_enuHLCD_Error_Status == HLCD_OK)
    {
        if (HLCD_State[Copy_enuLCDNumber] == Busy)
        {
            Loc_enuHLCD_Error_Status = HLCD_Busy;
        }
        else
        {

            SchedRunnable[Copy_enuLCDNumber].p2f = HLCD_Runnable;
            SchedRunnable[Copy_enuLCDNumber].CyclicTime_ms = Cylic_ms;
            SchedRunnable[Copy_enuLCDNumber].first_delay = FirstDelay_ms;
            SchedRunnable[Copy_enuLCDNumber].periorty = Copy_u8Priority;
            Sched_Error_Status_t Loc_enuSched_Error_Status = Sched_enuAddRunnable(&SchedRunnable[Copy_enuLCDNumber]);
            switch (Loc_enuSched_Error_Status)
            {
            case Sched_InvalidPeriortyNumber:
                Loc_enuHLCD_Error_Status = HLCD_Sched_InvalidPeriortyNumber;
                break;
            case Sched_PeriortyNotFree:
                Loc_enuHLCD_Error_Status = HLCD_Sched_PeriortyNotFree;
                break;
            default:
                HLCD_InitSeq[Copy_enuLCDNumber] = Init_Pins;
                HLCD_State[Copy_enuLCDNumber] = Busy;
                LCD_Periority[exisit_LCDs].LCD_no = Copy_enuLCDNumber;
                LCD_Periority[exisit_LCDs].Priority = Copy_u8Priority;
                OrderingLCDPeriorityArray();
                settingcursorposatbegining(Copy_enuLCDNumber);
                exisit_LCDs++;
                break;
            }
        }
    }
    return Loc_enuHLCD_Error_Status;
}
