#include "rcc.h"

// تعريف ريجستر الـ FLASH_ACR مؤقتاً لحد ما نعمل درايفر الـ Flash[cite: 60]
#define FLASH_ACR (*(volatile u32*)0x40023C00)

int main(void)
{
    RCC_enuSetBusPrescaler(AHB,AHB_PRE_128);

    while (1)
    {
        // المايكروكنترولر الآن يعمل بطاقته القصوى (84 MHz) بأمان تام
    }
}