#ifndef UART_H
#define UART_H

#include "STD_types.h"

typedef void(*ptrtofun)(void);

#define UART_INTERUPT_IDLEIE (1ULL<< 4)
#define UART_INTERUPT_RXNEIE (1ULL<< 5)
#define UART_INTERUPT_PEIE (1ULL<< 8)

#define UART_INTERUPT_LBDIE (1ULL<< 6 +32)


#define UART_INTERUPT_EIE (1ULL<< 0 +32+16)
#define UART_INTERUPT_CTSIE (1ULL<< 10 +32+16)







typedef enum
{
    UART_OK,
    UART_InvalidParam,
    UART_InvalidUART_NO,
    UART_InvalidParity,
    UART_InvalidDataSize,
    UART_InvalidOverSampling,
    UART_InvalidBreak,
    UART_InvalidReciever,
    UART_InvalidTransmitter,
    UART_InvalidStopBit,
    UART_InvalidZeroBaudRate,
    UART_InvalidPtr,
    UART_InvalidInterruptFlags,

    UART_Busy,
    UART_NO_DATA,
    UART_Invalidcbf

} UART_Error_Status_t;

typedef enum
{
    UART1,
    UART2,
    UART6,
    UART_Count
} UART_NO_t;

typedef enum
{
    No_Parity,
    Even_Parity,
    Odd_Parity
} Parity_t;

typedef enum
{
    _8_bit,
    _9_bit
} Data_Size_t; // Size includes Parity bit if enabled

typedef enum
{
    Over_16,
    Over_8
} Over_Sampling_t;

typedef enum
{
    Break_Disable,
    Break_Enable
} Break_t;

typedef enum
{
    Reciever_Disable,
    Reciever_Enable
} Reciever_t;

typedef enum
{
    Transmitter_Disable,
    Transmitter_Enable
} Transmitter_t;

typedef enum
{
    _1_Stop_bit,
    _Half_Stop_bit,
    _2_Stop_bit,
    _1_and_half_Stop_bit,
}Stop_bit_t;

typedef struct
{
    u32 BaudRate;
    Parity_t Parity;
    Data_Size_t Data_Size;
    Over_Sampling_t Over_Sampling;
    Break_t Break;
    Reciever_t Reciever;
    Transmitter_t Transmitter;
    u64 Interrupt_Flags;
    Stop_bit_t Stop_bit;
} UART_cfg_t;

typedef struct
{
    u8 * buffer;
    u64 size;

}UART_Buffer_t;

UART_Error_Status_t UART_enuInit(UART_NO_t Copy_enuUART_NO, UART_cfg_t* Copy_strUART_cfg);
UART_Error_Status_t UART_enuSendByte(UART_NO_t Copy_enuUART_NO, u16 Copy_u16Byte);
UART_Error_Status_t UART_enuReceiveByte(UART_NO_t Copy_enuUART_NO, u16* Ref_u16Byte);
UART_Error_Status_t UART_enuSetTXcbf(UART_NO_t Copy_enuUART_NO,ptrtofun Ref_cbf);
UART_Error_Status_t UART_enuSetRXcbf(UART_NO_t Copy_enuUART_NO,ptrtofun Ref_cbf);

UART_Error_Status_t UART_enuSendBuffer(UART_NO_t Copy_enuUART_NO,UART_Buffer_t * Ref_strBuffer);
UART_Error_Status_t UART_enuReceiveBuffer(UART_NO_t Copy_enuUART_NO,UART_Buffer_t * Ref_strBuffer);

#endif