#include "UART.h"
#include "UART_priv.h"
#include "Bit_math.h"

static volatile UART_reg_t *UARTS[UART_Count] = {UART1_reg, UART2_reg, UART6_reg};

static inline UART_Error_Status_t Check_UART_NO(UART_NO_t Copy_enuUART_NO)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuUART_NO)
    {
    case 0 ... UART_Count - 1:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidUART_NO;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_Parity(Parity_t Copy_enuParity)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuParity)
    {
    case No_Parity ... Odd_Parity:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidParity;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_DataSize(Data_Size_t Copy_enuData_Size)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuData_Size)
    {
    case _8_bit ... _9_bit:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidDataSize;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_OverSampling(Over_Sampling_t Copy_enuOverSampling)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuOverSampling)
    {
    case Over_16 ... Over_8:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidOverSampling;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_Break(Break_t Copy_enuBreak)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuBreak)
    {
    case Break_Disable ... Break_Enable:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidBreak;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_Reciever(Reciever_t Copy_enuReciever)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuReciever)
    {
    case Reciever_Disable ... Reciever_Enable:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidReciever;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_Transmitter(Transmitter_t Copy_enuTransmitter)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuTransmitter)
    {
    case Transmitter_Disable ... Transmitter_Enable:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidTransmitter;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_Stop(Stop_bit_t Copy_enuStopBit)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuStopBit)
    {
    case _1_Stop_bit ... _1_and_half_Stop_bit :
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidStopBit;
        break;
    }
    return Loc_enuUART_Error_Status;
}


static inline UART_Error_Status_t Checks(UART_NO_t Copy_enuUART_NO, UART_cfg_t Copy_strUART_cfg)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_UART_NO(Copy_enuUART_NO);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_Parity(Copy_strUART_cfg.Parity);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_DataSize(Copy_strUART_cfg.Data_Size);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_OverSampling(Copy_strUART_cfg.Over_Sampling);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_Break(Copy_strUART_cfg.Break);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_Reciever(Copy_strUART_cfg.Reciever);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_Transmitter(Copy_strUART_cfg.Transmitter);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_Stop(Copy_strUART_cfg.Stop_bit);
    }
    return Loc_enuUART_Error_Status;
}

UART_Error_Status_t UART_enuInit(UART_NO_t Copy_enuUART_NO, UART_cfg_t Copy_strUART_cfg)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = Checks(Copy_enuUART_NO, Copy_strUART_cfg);
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_UE);
        switch (Copy_strUART_cfg.Break)
        {
        case Break_Enable:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_SBK);
            break;
        default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_SBK);
            break;
        }
        switch(Copy_strUART_cfg.Reciever)
        {
            case Reciever_Enable:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_RE);
            break;
            default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_RE);
            break;
        }
        switch(Copy_strUART_cfg.Transmitter)
        {
            case Transmitter_Enable:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TE);
            break;
            default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TE);
            break;
        }
        switch(Copy_strUART_cfg.Parity)
        {
            case No_Parity:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PS);
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PCE);
            break;
            case Odd_Parity:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PS);
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PCE);
            default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PS);
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PCE);

            break;
        }
        switch (Copy_strUART_cfg.Data_Size)
        {
            case _8_bit:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_M);
            break;
            default:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_M);
            break;
        }
        switch(Copy_strUART_cfg.Over_Sampling)
        {
            case Over_16:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_OVER8);
            break;
            default:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_OVER8);
            break;
        }
        Clear_Mask(UARTS[Copy_enuUART_NO]->USART_CR2,USART_CR2_STOP_MASK);
        switch(Copy_strUART_cfg.Stop_bit)
        {
            case _1_Stop_bit:
            
            break;
            default:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR2, USART_CR1_OVER8);
            break;
        }

    }
    return Loc_enuUART_Error_Status;
}
