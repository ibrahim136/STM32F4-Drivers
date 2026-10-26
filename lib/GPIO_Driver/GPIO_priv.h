#ifndef GPIO_Priv_H
#define GPIO_Priv_H

#include "STD_types.h"

#define TIMEOUT 100000

#define GPIOA_BASE ((volatile u32 *)(0x40020000UL))
#define GPIOB_BASE ((volatile u32 *)(0x40020400UL))
#define GPIOC_BASE ((volatile u32 *)(0x40020800UL))
#define GPIOD_BASE ((volatile u32 *)(0x40020C00UL))
#define GPIOE_BASE ((volatile u32 *)(0x40021000UL))
#define GPIOH_BASE ((volatile u32 *)(0x40021C00UL))

typedef struct
{
    u32 GPIO_MODER;
    u32 GPIO_OTYPER;
    u32 GPIO_OSPEEDR;
    u32 GPIO_PUPDR;
    u32 GPIO_IDR;
    u32 GPIO_ODR;
    u32 GPIO_BSRR;
    u32 GPIO_LCKR;
    u32 GPIO_AFRL;
    u32 GPIO_AFRH;

} GPIO_reg_t;

//PORTS BASE Addresses 

#define GPIOA ((volatile GPIO_reg_t *)GPIOA_BASE)
#define GPIOB ((volatile GPIO_reg_t *)GPIOB_BASE)
#define GPIOC ((volatile GPIO_reg_t *)GPIOC_BASE)
#define GPIOD ((volatile GPIO_reg_t *)GPIOD_BASE)
#define GPIOE ((volatile GPIO_reg_t *)GPIOE_BASE)
#define GPIOH ((volatile GPIO_reg_t *)GPIOH_BASE)

#define BR(bit) (bit+16)
#define BS(bit) (bit+0)


#endif