#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "rcc.h"
#include "GPIO.h"
#include "Sched.h"

#define Number_Of_Readings 5

static void HSwitch_voidRunnable(void);
Sched_Runnable_t SchedRunnable = {.p2f = HSwitch_voidRunnable, .CyclicTime_ms = Number_Of_Readings, .first_delay = 0};

extern const HSwitch_cfg_t HSwitch_cfg[NUM_OF_Switches];

static Switch_State_t Switches_State[NUM_OF_Switches];

static Switch_State_t Prev_Switches_State[NUM_OF_Switches];
static Switch_State_t Switches_Counter[NUM_OF_Switches];

static const Peripheral_t GPIOS_Pheripheral_Enable[GPIO_Count] = {
    Peripheral_GPIOA,
    Peripheral_GPIOB,
    Peripheral_GPIOC,
    Peripheral_GPIOD,
    Peripheral_GPIOE,
    Peripheral_GPIOH};

static inline HSwitch_Error_Status_t HSwitch_enuRCCErrorToHSwitchError(RCC_Error_Status_t Copy_enuRCC_Error_Status)
{
    HSwitch_Error_Status_t Loc_enuHSwitch_Error_Status;
    switch (Copy_enuRCC_Error_Status)
    {
    case RCC_Timeout:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_Timeout;
        break;
    case RCC_InvalidParam:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_InvalidParam;
        break;
    case RCC_ClockInUse:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_ClockInUse;
        break;
    case RCC_CLKDisabled:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_CLKDisabled;
        break;
    case RCC_PLLEnabled:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_PLLEnabled;
        break;
    case RCC_InvalidPLLDivisiors:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_InvalidPLLDivisiors;
        break;
    case RCC_PLLSRCDisabled:
        Loc_enuHSwitch_Error_Status = HSwitch_RCC_PLLSRCDisabled;
        break;
    default:
        Loc_enuHSwitch_Error_Status = HSwitch_OK;
        break;
    }
    return Loc_enuHSwitch_Error_Status;
}

static inline HSwitch_Error_Status_t HSwitch_enuGPIOErrorToHSwitchError(GPIO_Error_Status_t Copy_enuGPIO_Error_Status)
{
    HSwitch_Error_Status_t Loc_enuHSwitch_Error_Status;
    switch (Copy_enuGPIO_Error_Status)
    {
    case GPIO_InvalidParam:
        Loc_enuHSwitch_Error_Status = HSwitch_GPIO_InvalidParam;
        break;
    default:
        Loc_enuHSwitch_Error_Status = HSwitch_OK;
        break;
    }
    return Loc_enuHSwitch_Error_Status;
}

HSwitch_Error_Status_t HSwitch_enuInit(u8 Copy_u8Periorty)
{
    GPIO_Error_Status_t Loc_enuGPIO_Error_Status = GPIO_OK;
    RCC_Error_Status_t Loc_enuRCC_Error_Status = RCC_OK;
    HSwitch_Error_Status_t Loc_enuHSwitch_Error_Status = HSwitch_OK;

    for (u8 i = 0; i < NUM_OF_Switches; i++)
    {
        Loc_enuRCC_Error_Status = RCC_enuCTRLPeripheral(GPIOS_Pheripheral_Enable[HSwitch_cfg[i].PORT], Peripheral_Enable);
        if (Loc_enuRCC_Error_Status != RCC_OK)
        {
            Loc_enuHSwitch_Error_Status = HSwitch_enuRCCErrorToHSwitchError(Loc_enuRCC_Error_Status);
            break;
        }

        PIN_PORT_Conf_t Loc_strPIN_PORT_Conf = {
            .PORT = HSwitch_cfg[i].PORT,
            .PIN_State = PIN_LOW,   // ignore as it's input not output
            .PIN_Speed = Low_Speed, // igonre as it's  input not output
            .PIN_PUPD = HSwitch_cfg[i].PIN_PUPD,
            .PIN_Mode = Mode_Input, // must be input
            .PIN_Type = Push_Pull,  // igonre as it's input not output
            .PIN_AF = AF0,          // must be AF0
            .PIN = HSwitch_cfg[i].PIN};

        Loc_enuGPIO_Error_Status = GPIO_enuPinInit(&Loc_strPIN_PORT_Conf);
        if (Loc_enuGPIO_Error_Status != GPIO_OK)
        {
            Loc_enuHSwitch_Error_Status = HSwitch_enuGPIOErrorToHSwitchError(Loc_enuGPIO_Error_Status);
            break;
        }
    }
    SchedRunnable.periorty = Copy_u8Periorty;
    Sched_enuAddRunnable(&SchedRunnable);

    return Loc_enuHSwitch_Error_Status;
}

HSwitch_Error_Status_t HSwitch_enuReadState(HSwitch_Switches_t Copy_enuSwitch, Switch_State_t *Ref_enuSwitchState)
{
    HSwitch_Error_Status_t Loc_enuHSwitch_Error_Status = HSwitch_OK;
    switch (Copy_enuSwitch)
    {
    case 0 ... NUM_OF_Switches - 1:
        break;
    default:
        Loc_enuHSwitch_Error_Status = HSwitch_InvalidSwitch;
        break;
    }
    if (Loc_enuHSwitch_Error_Status == HSwitch_OK && Ref_enuSwitchState == nullptr)
    {
        Loc_enuHSwitch_Error_Status = HSwitch_InvalidPtr;
    }
    *Ref_enuSwitchState = Switches_State[Copy_enuSwitch];
    return Loc_enuHSwitch_Error_Status;
}

static inline Switch_State_t HSwitch_enuGPIOReadToSwitchState(HSwitch_Switches_t Copy_enuSwitch)
{
    Switch_State_t Loc_enuSwitch_State;
    GPIO_PIN_State_t Loc_enuPINState;
    GPIO_enuPinReadInput(HSwitch_cfg[Copy_enuSwitch].PORT, HSwitch_cfg[Copy_enuSwitch].PIN, &Loc_enuPINState);
    if ((Loc_enuPINState == PIN_LOW && HSwitch_cfg[Copy_enuSwitch].Pressed_State == Pressed_Low) ||
        (Loc_enuPINState == PIN_HIGH && HSwitch_cfg[Copy_enuSwitch].Pressed_State == Pressed_High))
    {
        Loc_enuSwitch_State = Pressed;
    }
    else
    {
        Loc_enuSwitch_State = Released;
    }
    return Loc_enuSwitch_State;
}

static void HSwitch_voidRunnable(void)
{
    for (u8 i = 0; i < NUM_OF_Switches; i++)
    {
        Switch_State_t Loc_enuCurrState = HSwitch_enuGPIOReadToSwitchState(i);
        Switch_State_t Loc_enuPrevState = Prev_Switches_State[i];
        if (Loc_enuCurrState == Loc_enuPrevState)
        {
            switch (Switches_Counter[i])
            {
            case 0 ... 4:
                Switches_Counter[i]++;
                break;
            default:
                break;
            }
        }
        else
        {
            Switches_Counter[i] = 0;
        }
        Prev_Switches_State[i] = Loc_enuCurrState;

        if (Switches_Counter[i] == Number_Of_Readings)
        {
            Switches_State[i] = Loc_enuCurrState;
        }
        else
        {
            switch (Switches_State[i])
            {
            case Pressed:
                Switches_State[i] = Pre_Released;
                break;
            case Released:
                Switches_State[i] = Pre_Pressed;
                break;
            default:
                break;
            }
        }
    }
}
