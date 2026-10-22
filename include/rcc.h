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

RCC_Error_Status_t RCC_enuCLKControl(CLK_Type_t Copy_enuCLKType, CLK_Status_t Copy_enuCLKStatus);


#endif