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

GPIO_Error_Status_t GPIO_enuPinWrite(GPIO_Port_t Copy_enuPORT, GPIO_PIN_Number_t COPY_enuPIN, GPIO_PIN_State_t Copy_enuState);

#endif