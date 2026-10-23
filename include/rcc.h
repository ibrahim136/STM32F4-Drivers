#ifndef RCC_H
#define RCC_H

typedef enum{
    RCC_OK,
    RCC_Timeout,
    RCC_InvalidParam
}RCC_Error_Status_t;

typedef enum{
    CLK_Enable,
    CLK_Disable
}CLK_Status_t;

typedef enum{
    HSI,
    HSE,
    PLL
}CLK_Type_t;

typedef enum{
    AHB,
    APB1,
    APB2
}BUS_Type_t;

typedef enum{
    Prescaler0=0x00UL,
    Prescaler2=0x00UL,
    Prescaler4=0x01UL,
    Prescaler8=0x02UL,
    Prescaler16=0x03UL,
    Prescaler64=0x04UL,
    Prescaler128=0x05UL,
    Prescaler256=0x06UL,
    Prescaler512=0x07UL,

}Prescaler_t;

RCC_Error_Status_t RCC_enuCLKControl(CLK_Type_t Copy_enuCLKType, CLK_Status_t Copy_enuCLKStatus);
RCC_Error_Status_t RCC_enuSelectSysCLK(CLK_Type_t Copy_enuCLKType);
RCC_Error_Status_t RCC_enuSetBusPrescaler(BUS_Type_t Copy_enuBus, Prescaler_t Copy_enuPrescaler);

#endif