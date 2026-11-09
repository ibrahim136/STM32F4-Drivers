#ifndef NVIC_H
#define NVIC_H

#include "STD_types.h"

typedef enum
{
    NVIC_OK,
    NVIC_InvalidIRQn,
    NVIC_InvalidPriority,
    NVIC_InvalidPtr
} NVIC_Error_Status_t;

typedef enum{
    Priority0 = 0,
    Priority1 = 1,
    Priority2 = 2,
    Priority3 = 3,
    Priority4 = 4,
    Priority5 = 5,
    Priority6 = 6,
    Priority7 = 7,
    Priority8 = 8,
    Priority9 = 9,
    Priority10 = 10,
    Priority11 = 11,
    Priority12 = 12,
    Priority13 = 13,
    Priority14 = 14,
    Priority15 = 15,
    Priority_count
}Priority_t;

typedef enum
{
    NVIC_IRQ_WWDG = 0,
    NVIC_IRQ_EXTI16 = 1,
    NVIC_IRQ_PVD = 1,
    NVIC_IRQ_EXTI21 = 2,
    NVIC_IRQ_TAMP_STAMP = 2,
    NVIC_IRQ_EXTI22 = 3,
    NVIC_IRQ_RTC_WKUP = 3,
    NVIC_IRQ_FLASH = 4,
    NVIC_IRQ_RCC = 5,
    NVIC_IRQ_EXTI0 = 6,
    NVIC_IRQ_EXTI1 = 7,
    NVIC_IRQ_EXTI2 = 8,
    NVIC_IRQ_EXTI3 = 9,
    NVIC_IRQ_EXTI4 = 10,
    NVIC_IRQ_DMA1_Stream0 = 11,
    NVIC_IRQ_DMA1_Stream1 = 12,
    NVIC_IRQ_DMA1_Stream2 = 13,
    NVIC_IRQ_DMA1_Stream3 = 14,
    NVIC_IRQ_DMA1_Stream4 = 15,
    NVIC_IRQ_DMA1_Stream5 = 16,
    NVIC_IRQ_DMA1_Stream6 = 17,
    NVIC_IRQ_ADC = 18,
    NVIC_IRQ_EXTI9_5 = 23,
    NVIC_IRQ_TIM1_BRK_TIM9 = 24,
    NVIC_IRQ_TIM1_UP_TIM10 = 25,
    NVIC_IRQ_TIM1_TRG_COM_TIM11 = 26,
    NVIC_IRQ_TIM1_CC = 27,
    NVIC_IRQ_TIM2 = 28,
    NVIC_IRQ_TIM3 = 29,
    NVIC_IRQ_TIM4 = 30,
    NVIC_IRQ_I2C1_EV = 31,
    NVIC_IRQ_I2C1_ER = 32,
    NVIC_IRQ_I2C2_EV = 33,
    NVIC_IRQ_I2C2_ER = 34,
    NVIC_IRQ_SPI1 = 35,
    NVIC_IRQ_SPI2 = 36,
    NVIC_IRQ_USART1 = 37,
    NVIC_IRQ_USART2 = 38,
    NVIC_IRQ_EXTI15_10 = 40,
    NVIC_IRQ_EXTI17 = 41,
    NVIC_IRQ_RTC_Alarm = 41,
    NVIC_IRQ_EXTI18 = 42,
    NVIC_IRQ_OTG_FS_WKUP = 42,
    NVIC_IRQ_DMA1_Stream7 = 47,
    NVIC_IRQ_SDIO = 49,
    NVIC_IRQ_TIM5 = 50,
    NVIC_IRQ_SPI3 = 51,
    NVIC_IRQ_DMA2_Stream0 = 56,
    NVIC_IRQ_DMA2_Stream1 = 57,
    NVIC_IRQ_DMA2_Stream2 = 58,
    NVIC_IRQ_DMA2_Stream3 = 59,
    NVIC_IRQ_DMA2_Stream4 = 60,
    NVIC_IRQ_OTG_FS = 67,
    NVIC_IRQ_DMA2_Stream5 = 68,
    NVIC_IRQ_DMA2_Stream6 = 69,
    NVIC_IRQ_DMA2_Stream7 = 70,
    NVIC_IRQ_USART6 = 71,
    NVIC_IRQ_I2C3_EV = 72,
    NVIC_IRQ_I2C3_ER = 73,
    NVIC_IRQ_FPU = 81,
    NVIC_IRQ_SPI4 = 84
} NVIC_IRQ_t;

NVIC_Error_Status_t NVIC_enuEnableIRQ(NVIC_IRQ_t Copy_enuIRQn);
NVIC_Error_Status_t NVIC_enuDisableIRQ(NVIC_IRQ_t Copy_enuIRQn);
NVIC_Error_Status_t NVIC_enuSetPendingIRQ(NVIC_IRQ_t Copy_enuIRQn);
NVIC_Error_Status_t NVIC_enuClearPendingIRQ(NVIC_IRQ_t Copy_enuIRQn);
NVIC_Error_Status_t NVIC_enuGetPendingIRQ(NVIC_IRQ_t Copy_enuIRQn,u8 * Copy_u8PendingStatus);
NVIC_Error_Status_t  NVIC_enuSetPriority(NVIC_IRQ_t Copy_enuIRQn, Priority_t Copy_enuPriority);
NVIC_Error_Status_t  NVIC_enuGetPriority(NVIC_IRQ_t Copy_enuIRQn, Priority_t* Copy_enuPriority);

#endif