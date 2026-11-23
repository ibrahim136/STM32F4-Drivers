#include "Calculator.h"
#include "Calculator_cfg.h"
#include "rcc.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HLCD_cfg.h"
#include "Stack.h"

#define High_Time Number_Of_Readings *Number_Of_Readings + 1
#define NUM_OF_Cols 4

static Stacku64 Calculations_s;

static u8 Matrix[NUM_OF_Rows][NUM_OF_Cols][2] = {{"1", "2", "3", "+"}, {"4", "5", "6", "-"}, {"7", "8", "9", "x"}, {"/", "0", "", "="}};

extern Row_Conf_t Row_PINs[NUM_OF_Rows];

static const Peripheral_t GPIOS_Pheripheral_Enable[GPIO_Count] = {
    Peripheral_GPIOA,
    Peripheral_GPIOB,
    Peripheral_GPIOC,
    Peripheral_GPIOD,
    Peripheral_GPIOE,
    Peripheral_GPIOH};

typedef enum
{
    Row_1_High,
    Row_2_High,
    Row_3_High,
    Row_4_High,
    Row_End_High,
} Row_High_State_t;

static void Row_voidRunnable(void);

static Sched_Runnable_t SchedRunnable = {.p2f = Row_voidRunnable, .CyclicTime_ms = High_Time, .first_delay = 100};

static inline Calculator_Error_Status_t Calculator_enuRCCErrorToCalculatorError(RCC_Error_Status_t Copy_enuRCC_Error_Status)
{
    Calculator_Error_Status_t Loc_enuCalculator_Error_Status;
    switch (Copy_enuRCC_Error_Status)
    {
    case RCC_Timeout:
        Loc_enuCalculator_Error_Status = Calculator_RCC_Timeout;
        break;
    case RCC_InvalidParam:
        Loc_enuCalculator_Error_Status = Calculator_RCC_InvalidParam;
        break;
    case RCC_ClockInUse:
        Loc_enuCalculator_Error_Status = Calculator_RCC_ClockInUse;
        break;
    case RCC_CLKDisabled:
        Loc_enuCalculator_Error_Status = Calculator_RCC_CLKDisabled;
        break;
    case RCC_PLLEnabled:
        Loc_enuCalculator_Error_Status = Calculator_RCC_PLLEnabled;
        break;
    case RCC_InvalidPLLDivisiors:
        Loc_enuCalculator_Error_Status = Calculator_RCC_InvalidPLLDivisiors;
        break;
    case RCC_PLLSRCDisabled:
        Loc_enuCalculator_Error_Status = Calculator_RCC_PLLSRCDisabled;
        break;
    default:
        Loc_enuCalculator_Error_Status = Calculator_OK;
        break;
    }
    return Loc_enuCalculator_Error_Status;
}

static inline Calculator_Error_Status_t Calculator_enuGPIOErrorToCalculatorError(GPIO_Error_Status_t Copy_enuGPIO_Error_Status)
{
    Calculator_Error_Status_t Loc_enuCalculator_Error_Status;
    switch (Copy_enuGPIO_Error_Status)
    {
    case GPIO_InvalidParam:
        Loc_enuCalculator_Error_Status = Calculator_GPIO_InvalidParam;
        break;
    default:
        Loc_enuCalculator_Error_Status = Calculator_OK;
        break;
    }
    return Loc_enuCalculator_Error_Status;
}

static inline Calculator_Error_Status_t Calculator_enuInit(u8 Copy_u8Periorty)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    Calculator_Error_Status_t Loc_enuCalculator_Error_Status = Calculator_OK;

    for (u8 i = 0; i < NUM_OF_Rows; i++)
    {
        Loc_enuRCC_Error_Status = RCC_enuCTRLPeripheral(GPIOS_Pheripheral_Enable[Row_PINs[i].PORT], Peripheral_Enable);
        if (Loc_enuRCC_Error_Status != RCC_OK)
        {
            Loc_enuCalculator_Error_Status = Calculator_enuRCCErrorToCalculatorError(Loc_enuRCC_Error_Status);
            break;
        }

        PIN_PORT_Conf_t Loc_strPIN_PORT_Conf = {
            .PORT = Row_PINs[i].PORT,
            .PIN_State = PIN_LOW,
            .PIN_Speed = Low_Speed, // igonre as it"s  input not output
            .PIN_PUPD = No_pull_up_pull_down,
            .PIN_Mode = Mode_General_Purpose_Output, // must be input
            .PIN_Type = Push_Pull,
            .PIN_AF = AF0, // must be AF0
            .PIN = Row_PINs[i].PIN};

        Loc_enuGPIO_Error_Status = GPIO_enuPinInit(&Loc_strPIN_PORT_Conf);
        if (Loc_enuGPIO_Error_Status != GPIO_OK)
        {
            Loc_enuCalculator_Error_Status = Calculator_enuGPIOErrorToCalculatorError(Loc_enuGPIO_Error_Status);
            break;
        }
    }
    SchedRunnable.periorty = Copy_u8Periorty;
    Sched_enuAddRunnable(&SchedRunnable);

    return Loc_enuCalculator_Error_Status;
}

static Row_High_State_t Row_High_State = Row_1_High;

static void Row_voidRunnable(void)
{
    if (Row_High_State == Row_End_High)
        Row_High_State = Row_1_High;
    for (u8 i = 0; i < NUM_OF_Rows; i++)
    {
        GPIO_enuPinWrite(Row_PINs[i].PORT, Row_PINs[i].PIN, PIN_LOW);
    }
    switch (Row_High_State)
    {
    case Row_1_High:
        GPIO_enuPinWrite(Row_PINs[Row_1_High].PORT, Row_PINs[Row_1_High].PIN, PIN_HIGH);
        Row_High_State++;
        break;
    case Row_2_High:
        GPIO_enuPinWrite(Row_PINs[Row_2_High].PORT, Row_PINs[Row_2_High].PIN, PIN_HIGH);
        Row_High_State++;
        break;
    case Row_3_High:
        GPIO_enuPinWrite(Row_PINs[Row_3_High].PORT, Row_PINs[Row_3_High].PIN, PIN_HIGH);
        Row_High_State++;
        break;
    default:
        GPIO_enuPinWrite(Row_PINs[Row_4_High].PORT, Row_PINs[Row_4_High].PIN, PIN_HIGH);
        Row_High_State++;
        break;
    }
}

static LCD_Numbers_t LCD_NO;

static inline Calculator_Error_Status_t Check_LCD(LCD_Numbers_t Copy_enuLCD)
{
    Calculator_Error_Status_t Loc_enuCalculator_Error_Status = Calculator_OK;
    switch (Copy_enuLCD)
    {
    case LCD_1 ... LCD_Count - 1:
        break;
    default:
        Loc_enuCalculator_Error_Status = Calculator_InvalidLCD;
        break;
    }
    return Loc_enuCalculator_Error_Status;
}

void PrintAnswer(u64 Copy_u64Answer)
{
    Stacku64 temp = CreateStacku64();
    while (Copy_u64Answer)
    {
        Stacku64Push(&temp, Copy_u64Answer % 10);
        Copy_u64Answer /= 10;
    }
    static u8 answer[17];
    for (u8 i = 0; i < 16 && IsEmptyStacku64(temp) == False_Bool; i++)
    {
        answer[i] = Stacku64Back(temp) + '0';
        answer[i + 1] = '\0';
        Stacku64Pop(&temp);
    }
    HLCD_enuWriteString(LCD_NO, answer);
}

static inline void CalculateAnswer(void)
{
    u64 res = 0;
    u64 temp1 = 0;
    u64 temp2 = 0;
    u64 operation = 0;
    u8 divided_by_zero = 0;
    while (IsEmptyStacku64(Calculations_s) == False_Bool)
    {
        temp2 = Stacku64Back(Calculations_s);
        Stacku64Pop(&Calculations_s);
        operation = Stacku64Back(Calculations_s);
        Stacku64Pop(&Calculations_s);
        temp1 = Stacku64Back(Calculations_s);
        Stacku64Pop(&Calculations_s);
        switch (operation)
        {
        case '+':
            res += temp1 + temp2;
            break;
        case '-':
            res += temp1 - temp2;
            break;
        case 'x':
            res += temp1 * temp2;
            break;
        default:
            if (temp2 == 0)
                divided_by_zero = 1;
            res += temp1 / temp2;
            break;
        }
    }
    if (divided_by_zero)
    {
        HLCD_enuWriteString(LCD_NO, "Infinite");
    }
    else
    {
        PrintAnswer(res);
    }
}

static inline void clear(void)
{
    HLCD_enuSetCursorPos(LCD_NO, Row_2, Col_1);
    HLCD_enuWriteString(LCD_NO, "                ");
    HLCD_enuSetCursorPos(LCD_NO, Row_2, Col_1);
}

void Col_voidRunnable(void)
{
    HSwitch_Switches_t i = Switch_no_1;
    Switch_State_t Loc_enuSwitchState = Unknown;
    static u8 is_cal = 0;
    for (; i < Switch_no_1 + 4; i++)
    {
        HSwitch_enuReadState(i, &Loc_enuSwitchState);
        if (Loc_enuSwitchState == Pressed)
            break;
    }
    if (Loc_enuSwitchState == Pressed)
    {
        if (Row_High_State - 1 != Row_4_OUT || i != (u8)Col_3_IN)
        {
            if (is_cal)
            {
                clear();
                is_cal = 0;
            }
            HLCD_enuWriteString(LCD_NO, Matrix[Row_High_State - 1][i]);
            u64 temp;
            switch (Matrix[Row_High_State - 1][i][0])
            {
            case '0' ... '9':
                temp = Stacku64Back(Calculations_s);
                Stacku64Pop(&Calculations_s);
                temp = temp * 10 + Matrix[Row_High_State - 1][i][0] - '0';
                Stacku64Push(&Calculations_s, temp);
                break;
            case '+':
            case '-':
            case 'x':
            case '/':
                Stacku64Push(&Calculations_s, Matrix[Row_High_State - 1][i][0]);
                Stacku64Push(&Calculations_s, 0);
                break;
            default:
                CalculateAnswer();
                is_cal = 1;
                break;
            }
        }
    }
}

Calculator_Error_Status_t Calculatorenu_On(LCD_Numbers_t Copy_enuLCD)
{
    Calculator_Error_Status_t Loc_enuCalculator_Error_Status = Calculator_OK;
    Loc_enuCalculator_Error_Status = Check_LCD(Copy_enuLCD);
    if (Loc_enuCalculator_Error_Status == Calculator_OK)
    {
        LCD_NO = Copy_enuLCD;
    }
    Calculations_s = CreateStacku64();
    Stacku64Push(&Calculations_s, 0);
    Sched_enuInit();
    HLCD_enuInit(LCD_NO, 5);
    HSwitch_enuInit(6);
    Calculator_enuInit(8);

    HLCD_enuSetCursorPos(LCD_NO, Row_1, Col_4);
    HLCD_enuWriteString(LCD_NO, "Calculator");
    HLCD_enuSetCursorPos(LCD_NO, Row_2, Col_1);

    static Sched_Runnable_t r0 = {.CyclicTime_ms = High_Time, .first_delay = 100, .p2f = Col_voidRunnable, .periorty = 7};
    Sched_enuAddRunnable(&r0);
    return Loc_enuCalculator_Error_Status;
}
