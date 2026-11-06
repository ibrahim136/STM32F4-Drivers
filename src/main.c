#include "rcc.h"
#include "GPIO.h"
#include "HLED_cfg.h"
#include "HLED.h"
#include "SysTick.h"

typedef struct mode
{
    u8 on;
    u8 off;
} mode;

mode modes[11] = {
    {100, 0},
    {90, 10},
    {80, 20},
    {70, 30},
    {60, 40},
    {50, 50},
    {40, 60},
    {30, 70},
    {20, 80},
    {10, 90},
    {0, 100}

};

void PWM_voidManual(HLED_LEDS_t LED, u8 Select_mode)
{
    HLED_enuTurnOn(LED);
    STK_voidDelay_us(modes[Select_mode].on);
    HLED_enuTurnOff(LED);
    STK_voidDelay_us(modes[Select_mode].off);
}

u8 level = 0;

// int main()
// {

//     HLED_enuInit();
//     RCC_enuCTRLPeripheral(Peripheral_GPIOB, Peripheral_Enable);
//     PIN_PORT_Conf_t PORTB_conf = {.PORT = GPIO_PORTB, .PIN_State = PIN_LOW, .PIN_Speed = Low_Speed, .PIN_PUPD = Pull_down, .PIN_Mode = Mode_Input, .PIN_Type = Push_Pull, .PIN_AF = AF0};
//     GPIO_enuPORTInit(&PORTB_conf);
//     u8 counter = 0;

//     while (1)
//     {
//         PWM_voidManual(counter,level);
//         GPIO_PIN_State_t PIN0B_State;
//         GPIO_enuPinReadInput(GPIO_PORTB, PIN0, &PIN0B_State);
//         if (PIN0B_State == PIN_HIGH)
//         {
//             //STK_voidDelay_ms(10);
//             GPIO_enuPinReadInput(GPIO_PORTB, PIN0, &PIN0B_State);
//             if (PIN0B_State == PIN_HIGH)
//             {
//                 counter = (counter + 1) % 8;
//             }
//         }
//         GPIO_PIN_State_t PIN1B_State;
//         GPIO_enuPinReadInput(GPIO_PORTB, PIN1, &PIN1B_State);
//         if (PIN1B_State == PIN_HIGH)
//         {
//             //STK_voidDelay_ms(10);
//             GPIO_enuPinReadInput(GPIO_PORTB, PIN1, &PIN1B_State);
//             if (PIN1B_State == PIN_HIGH)
//             {
//                 level = level >7 ? level : level+1;
//             }
//         }
//         PWM_voidManual(counter,5);
//     }
// }

int main(void)
{
    RCC_enuCTRLPeripheral(Peripheral_GPIOA, Peripheral_Enable);
    HLED_enuInit();
    HLED_enuTurnOff(PINA0);
    while (1)
    {
        STK_voidDelay_ms(1000);
        HLED_enuTurnOn(PINA0);
        STK_voidDelay_ms(1000);
        HLED_enuTurnOff(PINA0);
    }
}