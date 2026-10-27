#ifndef GPIO_H
#define GPIO_H

typedef enum
{
    GPIO_OK,
    GPIO_Timeout,
    GPIO_InvalidParam
} GPIO_Error_Status_t;

typedef enum
{
    GPIO_PORTA,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    GPIO_PORTH,
    GPIO_Count
} GPIO_Port_t;

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15,
    PIN_COUNT
} GPIO_PIN_Number_t;

typedef enum
{
    PIN_LOW,
    PIN_HIGH
} GPIO_PIN_State_t;

typedef enum{
    Low_Speed,
    Medium_Speed,
    High_Speed,
    Very_High_Speed,
    Speed_Count
}GPIO_PIN_Speed_t;

typedef enum{
    No_pull_up_pull_down,
    Pull_up,
    Pull_down,
    PUPD_Count
}GPIO_PIN_PUPD_t;

typedef enum{
    Mode_Input,
    Mode_General_Purpose_Output,
    Mode_Alternate_Function,
    Mode_Analog,
    Mode_Count
}GPIO_PIN_Moder_t;

typedef enum{
    Push_Pull,
    Open_Drain,
    Type_Count
}GPIO_PIN_Output_Type_t;

typedef enum{
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15,
    AF_Count
}GPIO_PIN_Alernative_Func_t;

GPIO_Error_Status_t GPIO_enuPinWrite(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_State_t Copy_enuState);
GPIO_Error_Status_t GPIO_enuPinRead(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_State_t* Ref_enuState);
GPIO_Error_Status_t GPIO_enuPORTWrite(GPIO_Port_t Copy_enuPORT, u16 Copy_u16PORTState);
GPIO_Error_Status_t GPIO_enuPORTRead(GPIO_Port_t Copy_enuPORT, u16 * Copy_u16PORTState);
GPIO_Error_Status_t GPIO_enuCfgSpeed(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN,GPIO_PIN_Speed_t Copy_enuPINSpeed);
GPIO_Error_Status_t GPIO_enuCfgPINPUPD(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN,GPIO_PIN_PUPD_t Copy_enuPINPUPD);
GPIO_Error_Status_t GPIO_enuCfgPINMode(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_Moder_t Copy_enuPINMODE);
GPIO_Error_Status_t GPIO_enuCfgPINOutType(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_Output_Type_t Copy_enuPINOutType);
GPIO_Error_Status_t GPIO_enuCfgPINAlternativeFunc(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t Copy_enuPIN, GPIO_PIN_Alernative_Func_t Copy_enuPINAF);

#endif