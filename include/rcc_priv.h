#ifndef RCC_PRIV_H
#define RCC_PRIV_H

#include "STD_types.h"

#define TIMEOUT 100000

#define RCC_BASE ((volatile u32 *)(0x40023800UL))

typedef struct
{
    u32 RCC_CR;
    u32 RCC_PLLCFGR;
    u32 RCC_CFGR;
    u32 RCC_CIR;
    u32 RCC_AHB1RSTR;
    u32 RCC_AHB2RSTR;
    u32 Reserved_0[2];
    u32 RCC_APB1RSTR;
    u32 RCC_APB2RSTR;
    u32 Reserved_1[2];
    u32 RCC_AHB1ENR;
    u32 RCC_AHB2ENR;
    u32 Reserved_2[2];
    u32 RCC_APB1ENR;
    u32 RCC_APB2ENR;
    u32 Reserved_3[2];
    u32 RCC_AHB1LPENR;
    u32 RCC_AHB2LPENR;
    u32 Reserved_4[2];
    u32 RCC_APB1LPENR;
    u32 RCC_APB2LPENR;
    u32 Reserved_5[2];
    u32 RCC_BDCR;
    u32 RCC_CSR;
    u32 Reserved_6[2];
    u32 RCC_SSCGR;
    u32 RCC_PLLI2SCFGR;
    u32 Reserved_7;
    u32 RCC_DCKCFGR;
} RCC_reg_t;

#define RCC_reg ((volatile RCC_reg_t *)RCC_BASE)

// RCC_CR register

// bit numbers
#define RCC_CR_HSION 0
#define RCC_CR_HSIRDY 1
#define RCC_CR_HSITRIM 3
#define RCC_CR_HSICAL 8
#define RCC_CR_HSEON 16
#define RCC_CR_HSERDY 17
#define RCC_CR_HSEBYP 18
#define RCC_CR_CSSON 19
#define RCC_CR_PLLON 24
#define RCC_CR_PLLRDY 25
#define RCC_CR_PLLI2SON 26
#define RCC_CR_PLLI2SRDY 27
// bit masking
#define RCC_CR_HSITRIM_MASK (0x1FUL << RCC_CR_HSITRIM)
#define RCC_CR_HSICAL_MASK (0xFFUL << RCC_CR_HSICAL)

// RCC_CFGR register

// bit numbers
#define RCC_CFGR_SW 0
#define RCC_CFGR_SWS 2
#define RCC_CFGR_HPRE 4
#define RCC_CFGR_PPRE1 10
#define RCC_CFGR_PPRE2 13
#define RCC_CFGR_RTCPRE 16
#define RCC_CFGR_MCO1 21
#define RCC_CFGR_I2SSRC 23
#define RCC_CFGR_MCO1PRE 24
#define RCC_CFGR_MCO2PRE 27
#define RCC_CFGR_MCO2 30

// bit masking
#define RCC_CFGR_SW_MASK (0x03UL << RCC_CFGR_SW)
#define RCC_CFGR_SWS_MASK (0x03UL << RCC_CFGR_SWS)
#define RCC_CFGR_HPRE_MASK (0x0FUL << RCC_CFGR_HPRE)
#define RCC_CFGR_PPRE1_MASK (0x07UL << RCC_CFGR_PPRE1)
#define RCC_CFGR_PPRE2_MASK (0x07UL << RCC_CFGR_PPRE2)
#define RCC_CFGR_RTCPRE_MASK (0x1FUL << RCC_CFGR_RTCPRE)
#define RCC_CFGR_MCO1_MASK (0x03UL << RCC_CFGR_MCO1)
#define RCC_CFGR_MCO1PRE_MASK (0x07UL << RCC_CFGR_MCO1PRE)
#define RCC_CFGR_MCO2PRE_MASK (0x07UL << RCC_CFGR_MCO2PRE)
#define RCC_CFGR_MCO2_MASK (0x03UL << RCC_CFGR_MCO2)

//BUS_CODE_MASK
#define BUS_CODE_MASK (0x03UL << 5)
#define BUS_CODE_POS (5)


#endif