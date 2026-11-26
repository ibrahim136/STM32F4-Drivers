#ifndef UART_Priv_H
#define UART_Priv_H
#include "STD_types.h"

#define UART1_BASE ((volatile u32 *)((0x40011000UL)))
#define UART2_BASE ((volatile u32 *)((0x40004400UL)))
#define UART6_BASE ((volatile u32 *)((0x40011400UL)))

typedef struct
{
    u32 USART_SR;
    u32 USART_DR;
    u32 USART_BRR;
    u32 USART_CR1;
    u32 USART_CR2;
    u32 USART_CR3;
    u32 USART_GTPR;
} UART_reg_t;

#define UART1_reg ((volatile UART_reg_t *)UART1_BASE)
#define UART2_reg ((volatile UART_reg_t *)UART2_BASE)
#define UART6_reg ((volatile UART_reg_t *)UART6_BASE)

// USART_SR bit positions
#define USART_SR_PE 0
#define USART_SR_FE 1
#define USART_SR_NF 2
#define USART_SR_ORE 3
#define USART_SR_IDLE 4
#define USART_SR_RXNE 5
#define USART_SR_TC 6
#define USART_SR_TXE 7
#define USART_SR_LBD 8
#define USART_SR_CTS 9

// USART_BRR bit positions
#define USART_BRR_DIV_Fraction 0
#define USART_BRR_DIV_Mantissa 4

// USART_BRR MASKS
#define USART_BRR_DIV_Fraction_MASK (0xF << USART_BRR_DIV_Fraction)
#define USART_BRR_DIV_Mantissa_MASK (0xFFF << USART_BRR_DIV_Mantissa)

// USART_CR1 bit positions
#define USART_CR1_SBK 0
#define USART_CR1_RWU 1
#define USART_CR1_RE 2
#define USART_CR1_TE 3
#define USART_CR1_IDLEIE 4
#define USART_CR1_RXNEIE 5
#define USART_CR1_TCIE 6
#define USART_CR1_TXEIE 7
#define USART_CR1_PEIE 8
#define USART_CR1_PS 9
#define USART_CR1_PCE 10
#define USART_CR1_WAKE 11
#define USART_CR1_M 12
#define USART_CR1_UE 13
#define USART_CR1_OVER8 15

// USART_CR2  bit positions
#define USART_CR2_ADD 0
#define USART_CR2_LBDL 5
#define USART_CR2_LBDIE 6
#define USART_CR2_LBCL 8
#define USART_CR2_CPHA 9
#define USART_CR2_CPOL 10
#define USART_CR2_CLKEN 11
#define USART_CR2_STOP 12
#define USART_CR2_LINEN 14

// USART_CR2 MASKS
#define USART_CR2_ADD_MASK (0xF << USART_CR2_ADD)
#define USART_CR2_STOP_MASK (0x3 << USART_CR2_STOP)

// USART_CR3 bit positions
#define USART_CR3_EIE 0
#define USART_CR3_IREN 1
#define USART_CR3_IRLP 2
#define USART_CR3_HDSEL 3
#define USART_CR3_NACK 4
#define USART_CR3_SCEN 5
#define USART_CR3_DMAR 6
#define USART_CR3_DMAT 7
#define USART_CR3_RTSE 8
#define USART_CR3_CTSE 9
#define USART_CR3_CTSIE 10
#define USART_CR3_ONEBIT 11

// USART_GTPR bit positions
#define USART_GTPR_PSC 0
#define USART_GTPR_GT 8

// USART_GTPR MASKS
#define USART_GTPR_PSC_MASK (0xFF << USART_GTPR_PSC)
#define USART_GTPR_GT_MASK (0xFF << USART_GTPR_GT)

// BaudDiv equation

#define BaudDiv1000(fclk, over8, BaudRate) ((fclk) * 1000 / (8 * (2 - (over8)) * (BaudRate)))

#define BaudDivMantissa(BaudDiv1000) ((BaudDiv1000) / (1000))
#define ApproximateAfterDiv10(number) ((((number) % 10) > 4) ? (((number) / 10) + 1) : (((number) / 10)))
#define BaudDivFraction(BaudDiv1000, over8) (((over8) == 1) ? ApproximateAfterDiv10((BaudDiv1000) % 1000 * 8 / 100) : ApproximateAfterDiv10((BaudDiv1000) % 1000 * 16 / 100))

#define Check_Fraction(BaudDivMantissa, BaudDivFraction, over8)                            \
    if (((over8) == 1 && BaudDivFraction == 8) || ((over8) == 0 && BaudDivFraction == 16)) \
    {                                                                                      \
        BaudDivMantissa++;                                                                 \
        BaudDivFraction = 0;                                                               \
    }

#define Interrupt_MASK (UART_INTERUPT_IDLEIE | UART_INTERUPT_RXNEIE | UART_INTERUPT_PEIE | UART_INTERUPT_LBDIE | UART_INTERUPT_EIE | UART_INTERUPT_CTSIE)
#define USART_CR1_Interrups (UART_INTERUPT_IDLEIE | UART_INTERUPT_RXNEIE | UART_INTERUPT_PEIE)
#define USART_CR2_Interrups (UART_INTERUPT_LBDIE)
#define USART_CR3_Interrups (UART_INTERUPT_EIE | UART_INTERUPT_CTSIE)

#define Shift_32(reg) Shift_Right(reg,32)
#define Shift_32_16(reg) Shift_Right(reg,(32+16))



#endif