#ifndef RCC_H
#define RCC_H

typedef enum
{
    RCC_OK,
    RCC_Timeout,
    RCC_InvalidParam
} RCC_Error_Status_t;

typedef enum
{
    CLK_Enable,
    CLK_Disable
} CLK_Status_t;

typedef enum
{
    HSI,
    HSE,
    PLL
} CLK_Type_t;

typedef enum
{
    AHB,
    APB1,
    APB2
} BUS_Type_t;

typedef enum
{
    AHB_PRE_1 = 0x00UL,
    AHB_PRE_2 = 0x08UL,
    AHB_PRE_4 = 0x09UL,
    AHB_PRE_8 = 0x0AUL,
    AHB_PRE_16 = 0x0BUL,
    AHB_PRE_64 = 0x0CUL,
    AHB_PRE_128 = 0x0DUL,
    AHB_PRE_256 = 0x0EUL,
    AHB_PRE_512 = 0x0FUL,

    APB1_PRE_1 = 0x00UL,
    APB1_PRE_2 = 0x04UL,
    APB1_PRE_4 = 0x05UL,
    APB1_PRE_8 = 0x06UL,
    APB1_PRE_16 = 0x07UL,

    APB2_PRE_1 = 0x00UL,
    APB2_PRE_2 = 0x04UL,
    APB2_PRE_4 = 0x05UL,
    APB2_PRE_8 = 0x06UL,
    APB2_PRE_16 = 0x07UL,

} Prescaler_t;

typedef enum
{
    // AHB1 peripheral clock enable register
    Peripheral_GPIOA = 0,
    Peripheral_GPIOB = 1,
    Peripheral_GPIOC = 2,
    Peripheral_GPIOD = 3,
    Peripheral_GPIOE = 4,
    Peripheral_GPIOH = 7,
    Peripheral_CRC = 12,
    Peripheral_DMA1 = 21,
    Peripheral_DMA2 = 22,

    // AHB2 peripheral clock enable register
    Peripheral_OTGFS = 0,

    // APB1 peripheral clock enable register
    Peripheral_TIM2 = 0,
    Peripheral_TIM3 = 1,
    Peripheral_TIM4 = 2,
    Peripheral_TIM5 = 3,
    Peripheral_WWDG = 11,
    Peripheral_SPI2 = 14,
    Peripheral_SPI3 = 15,
    Peripheral_USART2 = 17,
    Peripheral_I2C1 = 21,
    Peripheral_I2C2 = 22,
    Peripheral_I2C3 = 23,
    Peripheral_PWR = 28,

    // APB2 peripheral clock enable register
    Peripheral_TIM1 = 0,
    Peripheral_USART1 = 4,
    Peripheral_USART6 = 5,
    Peripheral_ADC1 = 8,
    Peripheral_SDIO = 11,
    Peripheral_SPI1 = 12,
    Peripheral_SPI4 = 13,
    Peripheral_SYSCFG = 14,
    Peripheral_TIM9 = 16,
    Peripheral_TIM10 = 17,
    Peripheral_TIM11 = 18,

} Peripherals_t;

RCC_Error_Status_t RCC_enuCLKControl(CLK_Type_t Copy_enuCLKType, CLK_Status_t Copy_enuCLKStatus);
RCC_Error_Status_t RCC_enuSelectSysCLK(CLK_Type_t Copy_enuCLKType);
RCC_Error_Status_t RCC_enuSetBusPrescaler(BUS_Type_t Copy_enuBus, Prescaler_t Copy_enuPrescaler);

#endif