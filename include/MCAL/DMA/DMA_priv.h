#ifndef DMA_Priv_H
#define DMA_Priv_H
#include "STD_types.h"

typedef struct {
    u32 DMA_LISR;
    u32 DMA_HISR;
    u32 DMA_LIFCR;
    u32 DMA_HIFCR;
    u32 DMA_S0CR;
    u32 DMA_S0NDTR;
    u32 DMA_S0PAR;
    u32 DMA_S0M0AR;
    u32 DMA_S0M1AR;
    u32 DMA_S0FCR;
    u32 DMA_S1CR;
    u32 DMA_S1NDTR;

    u32 DMA_S1PAR;
    u32 DMA_S1M0AR;
    u32 DMA_S1M1AR;
    u32 DMA_S1FCR;
    u32 DMA_S2CR;
    u32 DMA_S2NDTR;
    u32 DMA_S2PAR;
    u32 DMA_S2M0AR;
    u32 DMA_S2M1AR;
    u32 DMA_S2FCR;
    u32 DMA_S3CR;
    u32 DMA_S3NDTR;
    u32 DMA_S3PAR;
    u32 DMA_S3M0AR;

    u32 DMA_S3M1AR;
    u32 DMA_S3FCR;
    u32 DMA_S4CR;
    u32 DMA_S4NDTR;
    u32 DMA_S4PAR;
    u32 DMA_S4M0AR;
    u32 DMA_S4M1AR;
    u32 DMA_S4FCR;
    u32 DMA_S5CR;
    u32 DMA_S5NDTR;
    u32 DMA_S5PAR;
    u32 DMA_S5M0AR;
    u32 DMA_S5M1AR;
    u32 DMA_S5FCR;
    u32 DMA_S6CR;
    u32 DMA_S6NDTR;
    u32 DMA_S6PAR;

    u32 DMA_S6M0AR;
    u32 DMA_S6M1AR;
    u32 DMA_S6FCR;
    u32 DMA_S7CR;
    u32 DMA_S7NDTR;
    u32 DMA_S7PAR;
    u32 DMA_S7M0AR;
    u32 DMA_S7M1AR;
    u32 DMA_S7FCR;

}DMA_reg_t;

#define DMA1_BASE ((volatile u32*) 0x40026000)
#define DMA2_BASE ((volatile u32*) 0x40026400)

#define DMA1_reg ((volatile DMA_reg_t*)DMA1_BASE)
#define DMA2_reg ((volatile DMA_reg_t*)DMA2_BASE)




#endif