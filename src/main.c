#include "STD_types.h"
#include "rcc.h"
#include "STK.h"
#include "HLED.h"
#include "Sched.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"
#include "HLCD.h"
#include "Clock.h"
#include "Calculator.h"
#include "UART.h"

u8 ITI_Logo[8] = {
    0b10000,
    0b00000,
    0b10001,
    0b11110,
    0b10101,
    0b10101,
    0b00101,
    0b00001};
    #define Clock 0
    #define Calculator 1
    #define Mode Calculator
// int main(void)
// {
//     // #if Mode==Clock
//     // Clockenu_On(LCD_1, (u8 *)"   Hello ITI ");
//     // Clock_enuAddCustomChar(0, ITI_Logo);
//     // #elif Mode == Calculator
//     // Calculatorenu_On(LCD_1);

//     // #endif
//     // Sched_Start();
    
    


// }

#include "STD_types.h"
#include "rcc.h"
#include "GPIO.h"
#include "UART.h"
#include "NVIC.h"

u16 temp;
UART_Buffer_t bbuffer;
u8 data[5];
void tempRXcbf(void)
{
    UART_enuSendBuffer(UART1,&bbuffer);
}
void tempTXcbf(void)
{
    UART_enuReceiveBuffer(UART1,&bbuffer);
}

int main(void)
{
    RCC_enuCTRLPeripheral(Peripheral_GPIOA, Peripheral_Enable);
    RCC_enuCTRLPeripheral(Peripheral_USART1, Peripheral_Enable);
    PIN_PORT_Conf_t TX_Pin = {
        .PORT      = GPIO_PORTA,
        .PIN       = PIN9,
        .PIN_Mode  = Mode_Alternate_Function,
        .PIN_Type  = Push_Pull,
        .PIN_Speed = High_Speed,
        .PIN_PUPD  = No_pull_up_pull_down,
        .PIN_AF    = AF7,
        .PIN_State = PIN_LOW
    };

    PIN_PORT_Conf_t RX_Pin = {
        .PORT      = GPIO_PORTA,
        .PIN       = PIN10,
        .PIN_Mode  = Mode_Alternate_Function,
        .PIN_Type  = Push_Pull,
        .PIN_Speed = High_Speed,
        .PIN_PUPD  = Pull_up,
        .PIN_AF    = AF7,
        .PIN_State = PIN_LOW
    };

    GPIO_enuPinInit(&TX_Pin);
    GPIO_enuPinInit(&RX_Pin);
    UART_cfg_t Loc_strUART1Cfg = {
        .BaudRate        = 9600,
        .Parity          = No_Parity,
        .Data_Size       = _8_bit,
        .Over_Sampling   = Over_16,
        .Break           = Break_Disable,
        .Reciever        = Reciever_Enable,
        .Transmitter     = Transmitter_Enable,
        .Interrupt_Flags = UART_INTERUPT_RXNEIE,
        .Stop_bit        = _1_Stop_bit
    };

    UART_enuInit(UART1, &Loc_strUART1Cfg);

    UART_Error_Status_t Loc;
    STK_enuInit();
    //UART_enuSetRXcbf(UART1,tempRXcbf);
    bbuffer.buffer = data;
    bbuffer.size = 5;
    UART_enuSetRXcbf(UART1,tempRXcbf);
    UART_enuSetTXcbf(UART1,tempTXcbf);
    UART_enuReceiveBuffer(UART1,&bbuffer);
    NVIC_enuEnableIRQ(NVIC_IRQ_USART1);
    while (1)
    {
        
    }
}