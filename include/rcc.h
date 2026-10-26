#ifndef RCC_H
#define RCC_H

typedef enum
{
    RCC_OK,
    RCC_Timeout,
    RCC_InvalidParam,
    RCC_ClockInUse,
    RCC_CLKDisabled
} RCC_Error_Status_t;

typedef enum
{
    CLK_Enable,
    CLK_Disable,
    UNDEFINED
} CLK_Status_t;

typedef enum
{
    HSI,
    HSE,
    PLL,
    Not_applicable
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
{ // BUS CODE
    AHB1_BUS = 0UL << 5,
    AHB2_BUS = 1UL << 5,
    APB1_BUS = 2UL << 5,
    APB2_BUS = 3UL << 5,

} Peripheral_Bus_t;

typedef enum // peripherals with their bus code
{
    // AHB1 peripheral clock enable register
    Peripheral_GPIOA = (AHB1_BUS | 0),
    Peripheral_GPIOB = (AHB1_BUS | 1),
    Peripheral_GPIOC = (AHB1_BUS | 2),
    Peripheral_GPIOD = (AHB1_BUS | 3),
    Peripheral_GPIOE = (AHB1_BUS | 4),
    Peripheral_GPIOH = (AHB1_BUS | 7),
    Peripheral_CRC = (AHB1_BUS | 12),
    Peripheral_DMA1 = (AHB1_BUS | 21),
    Peripheral_DMA2 = (AHB1_BUS | 22),

    // AHB2 peripheral clock enable register
    Peripheral_OTGFS = (AHB2_BUS | 0),

    // APB1 peripheral clock enable register
    Peripheral_TIM2 = (APB1_BUS | 0),
    Peripheral_TIM3 = (APB1_BUS | 1),
    Peripheral_TIM4 = (APB1_BUS | 2),
    Peripheral_TIM5 = (APB1_BUS | 3),
    Peripheral_WWDG = (APB1_BUS | 11),
    Peripheral_SPI2 = (APB1_BUS | 14),
    Peripheral_SPI3 = (APB1_BUS | 15),
    Peripheral_USART2 = (APB1_BUS | 17),
    Peripheral_I2C1 = (APB1_BUS | 21),
    Peripheral_I2C2 = (APB1_BUS | 22),
    Peripheral_I2C3 = (APB1_BUS | 23),
    Peripheral_PWR = (APB1_BUS | 28),

    // APB2 peripheral clock enable register
    Peripheral_TIM1 = (APB2_BUS | 0),
    Peripheral_USART1 = (APB2_BUS | 4),
    Peripheral_USART6 = (APB2_BUS | 5),
    Peripheral_ADC1 = (APB2_BUS | 8),
    Peripheral_SDIO = (APB2_BUS | 11),
    Peripheral_SPI1 = (APB2_BUS | 12),
    Peripheral_SPI4 = (APB2_BUS | 13),
    Peripheral_SYSCFG = (APB2_BUS | 14),
    Peripheral_TIM9 = (APB2_BUS | 16),
    Peripheral_TIM10 = (APB2_BUS | 17),
    Peripheral_TIM11 = (APB2_BUS | 18),

} Peripheral_t;

typedef enum
{
    Peripheral_Enable,
    Peripheral_Disable
} Peripheral_State_t;

typedef struct
{
    u8 M;
    u16 N;
    u8 P;
    u8 SRC;
    u8 Q;

} PLL_Config_t;

RCC_Error_Status_t RCC_enuCLKControl(CLK_Type_t Copy_enuCLKType, CLK_Status_t Copy_enuCLKStatus);
RCC_Error_Status_t RCC_enuSelectSysCLK(CLK_Type_t Copy_enuCLKType);
RCC_Error_Status_t RCC_enuSetBusPrescaler(BUS_Type_t Copy_enuBus, Prescaler_t Copy_enuPrescaler);
RCC_Error_Status_t RCC_enuCTRLPeripheral(Peripheral_t Copy_enuPeripheral, Peripheral_State_t Copy_enuPeripheralState);
RCC_Error_Status_t RCC_enuConfigurePLL(PLL_Config_t *Copy_strPLLConfig);
CLK_Type_t RCC_enuGetSysCLK();
#endif