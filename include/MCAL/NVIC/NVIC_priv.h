#ifndef NVIC_Priv_H
#define NVIC_Priv_H

#include "STD_types.h"

#define NVIC_BASE ((volatile u32*)(0xE000E100))

typedef struct
{
    u32 NVIC_ISERx[8];
    u32 reserved0[24];
    u32 NVIC_ICERx[8];
    u32 reserved1[24];
    u32 NVIC_ISPRx[8];
    u32 reserved2[24];
    u32 NVIC_ICPRx[8];
    u32 reserved3[24];
    u32 NVIC_IABRx[8];
    u32 reserved4[56];
    u8 NVIC_IPx[240];
    u32 reserved5[644];
    u32 STIR;

}NVIC_reg_t;

#define NVIC_reg ((volatile NVIC_reg_t*)(NVIC_BASE))

#define Register_Bits_Capacity 32UL
#define PriorityShift 4

#define PriorityShiftMSB(Priority) (Priority<<PriorityShift)

#define PriorityMaskAfterShiftRight (0x0FUL)


typedef enum
{
    NVIC_IRQ_R0_MIN = 0,
    NVIC_IRQ_R0_MAX = 18,
    
    NVIC_IRQ_R1_MIN = 23,
    NVIC_IRQ_R1_MAX = 38,
    
    NVIC_IRQ_R2_MIN = 40,
    NVIC_IRQ_R2_MAX = 42,
    
    NVIC_IRQ_R3_MIN = 47,
    NVIC_IRQ_R3_MAX = 47,
    
    NVIC_IRQ_R4_MIN = 49,
    NVIC_IRQ_R4_MAX = 51,
    
    NVIC_IRQ_R5_MIN = 56,
    NVIC_IRQ_R5_MAX = 60,
    
    NVIC_IRQ_R6_MIN = 67,
    NVIC_IRQ_R6_MAX = 73,
    
    NVIC_IRQ_R7_MIN = 81,
    NVIC_IRQ_R7_MAX = 81,
    
    NVIC_IRQ_R8_MIN = 84,
    NVIC_IRQ_R8_MAX = 84
} NVIC_IRQ_Range_t;

#endif