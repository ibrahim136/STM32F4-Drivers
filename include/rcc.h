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
    AHB_PRE_1=0x00UL,
    AHB_PRE_2=0x08UL,
    AHB_PRE_4=0x09UL,
    AHB_PRE_8=0x0AUL,
    AHB_PRE_16=0x0BUL,
    AHB_PRE_64=0x0CUL,
    AHB_PRE_128=0x0DUL,
    AHB_PRE_256=0x0EUL,
    AHB_PRE_512=0x0FUL,

    APB1_PRE_1=0x00UL,
    APB1_PRE_2=0x04UL,
    APB1_PRE_4=0x05UL,
    APB1_PRE_8=0x06UL,
    APB1_PRE_16=0x07UL,

    APB2_PRE_1=0x00UL,
    APB2_PRE_2=0x04UL,
    APB2_PRE_4=0x05UL,
    APB2_PRE_8=0x06UL,
    APB2_PRE_16=0x07UL,
    

}Prescaler_t;

RCC_Error_Status_t RCC_enuCLKControl(CLK_Type_t Copy_enuCLKType, CLK_Status_t Copy_enuCLKStatus);
RCC_Error_Status_t RCC_enuSelectSysCLK(CLK_Type_t Copy_enuCLKType);
RCC_Error_Status_t RCC_enuSetBusPrescaler(BUS_Type_t Copy_enuBus, Prescaler_t Copy_enuPrescaler);

#endif