#include "UART.h"
#include "UART_priv.h"
#include "Bit_math.h"
#include "rcc.h"

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
    case _1_Stop_bit ... _1_and_half_Stop_bit:
        break;
    default:
        Loc_enuUART_Error_Status = UART_InvalidStopBit;
        break;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_BaudRate(u32 Copy_enuBaudRate)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Copy_enuBaudRate)
    {
    case 0:
        Loc_enuUART_Error_Status = UART_InvalidZeroBaudRate;
        break;
    default:
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
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_BaudRate(Copy_strUART_cfg.BaudRate);
    }
    if (Loc_enuUART_Error_Status == UART_OK && (Copy_strUART_cfg.Interrupt_Flags & ~(Interrupt_MASK)))
    {
        Loc_enuUART_Error_Status = UART_InvalidInterruptFlags;
    }
    return Loc_enuUART_Error_Status;
}

UART_Error_Status_t UART_enuInit(UART_NO_t Copy_enuUART_NO, UART_cfg_t *Copy_strUART_cfg)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    if (Copy_strUART_cfg == nullptr)
    {
        Loc_enuUART_Error_Status = UART_InvalidPtr;
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Checks(Copy_enuUART_NO, *Copy_strUART_cfg);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_UE);
        switch (Copy_strUART_cfg->Data_Size)
        {
        case _8_bit:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_M);
            break;
        default:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_M);
            break;
        }
        Clear_Mask(UARTS[Copy_enuUART_NO]->USART_CR2, USART_CR2_STOP_MASK);
        u32 Loc_u32StopMaskToSet = Masking_Value(Copy_strUART_cfg->Stop_bit, USART_CR2_STOP);
        Set_Mask(UARTS[Copy_enuUART_NO]->USART_CR2, Loc_u32StopMaskToSet);

        u64 Loc_u64UARTfclk;
        switch (Copy_enuUART_NO)
        {
        case UART1:
            RCC_enuGetPeripheralCLK(Peripheral_USART1, &Loc_u64UARTfclk);
            break;
        case UART2:
            RCC_enuGetPeripheralCLK(Peripheral_USART2, &Loc_u64UARTfclk);
            break;
        default:
            RCC_enuGetPeripheralCLK(Peripheral_USART6, &Loc_u64UARTfclk);
            break;
        }

        u32 Loc_BaudDiv1000 = BaudDiv1000(Loc_u64UARTfclk, Copy_strUART_cfg->Over_Sampling, Copy_strUART_cfg->BaudRate);
        u16 Loc_u16DIV_Mantissa = BaudDivMantissa(Loc_BaudDiv1000);
        u8 Loc_u8Fraction = BaudDivFraction(Loc_BaudDiv1000, Copy_strUART_cfg->Over_Sampling);
        Check_Fraction(Loc_u16DIV_Mantissa, Loc_u8Fraction, Copy_strUART_cfg->Over_Sampling);

        u16 Loc_16USART_BRR = Masking_Value(Loc_u16DIV_Mantissa, USART_BRR_DIV_Mantissa);
        Set_Mask(Loc_16USART_BRR, Loc_u8Fraction);
        Clear_Mask(UARTS[Copy_enuUART_NO]->USART_BRR, USART_BRR_DIV_Mantissa_MASK);
        Clear_Mask(UARTS[Copy_enuUART_NO]->USART_BRR, USART_BRR_DIV_Fraction_MASK);
        Set_Mask(UARTS[Copy_enuUART_NO]->USART_BRR, Loc_16USART_BRR);

        switch (Copy_strUART_cfg->Parity)
        {
        case No_Parity:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PS);
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PCE);
            break;
        case Odd_Parity:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PS);
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PCE);
            break;
        default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PS);
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_PCE);
            break;
        }

        switch (Copy_strUART_cfg->Over_Sampling)
        {
        case Over_16:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_OVER8);
            break;
        default:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_OVER8);
            break;
        }

        Clear_Mask(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_Interrups);
        Clear_Mask(UARTS[Copy_enuUART_NO]->USART_CR2, Shift_32(USART_CR2_Interrups));
        Clear_Mask(UARTS[Copy_enuUART_NO]->USART_CR3, Shift_32_16(USART_CR3_Interrups));
        Set_Mask(UARTS[Copy_enuUART_NO]->USART_CR1, Get_Mask(Copy_strUART_cfg->Interrupt_Flags, USART_CR1_Interrups));
        Set_Mask(UARTS[Copy_enuUART_NO]->USART_CR2, Shift_32(Get_Mask(Copy_strUART_cfg->Interrupt_Flags, USART_CR2_Interrups)));
        Set_Mask(UARTS[Copy_enuUART_NO]->USART_CR3, Shift_32_16(Get_Mask(Copy_strUART_cfg->Interrupt_Flags, USART_CR3_Interrups)));

        switch (Copy_strUART_cfg->Transmitter)
        {
        case Transmitter_Enable:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TE);
            break;
        default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TE);
            break;
        }

        switch (Copy_strUART_cfg->Reciever)
        {
        case Reciever_Enable:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_RE);
            break;
        default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_RE);
            break;
        }
        switch (Copy_strUART_cfg->Break)
        {
        case Break_Enable:
            Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_SBK);
            break;
        default:
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_SBK);
            break;
        }
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_Busy(UART_NO_t Copy_enuUART_NO)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    if (Get_bit(UARTS[Copy_enuUART_NO]->USART_SR, USART_SR_TXE) != 1)
    {
        Loc_enuUART_Error_Status = UART_Busy;
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_Data(UART_NO_t Copy_enuUART_NO, u16 Copy_u16Data)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    switch (Get_bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_M))
    {
    case _8_bit:
        if (Copy_u16Data > 0xFF)
            Loc_enuUART_Error_Status = UART_InvalidDataSize;
        break;
    default:
        if (Copy_u16Data > 0x1FF)
            Loc_enuUART_Error_Status = UART_InvalidDataSize;
        break;
    }
    return Loc_enuUART_Error_Status;
}

UART_Error_Status_t UART_enuSendByte(UART_NO_t Copy_enuUART_NO, u16 Copy_u16Byte)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = Check_UART_NO(Copy_enuUART_NO);
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_Busy(Copy_enuUART_NO);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_Data(Copy_enuUART_NO, Copy_u16Byte);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        UARTS[Copy_enuUART_NO]->USART_DR = Copy_u16Byte;
        Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TXEIE);
    }
    return Loc_enuUART_Error_Status;
}

static inline UART_Error_Status_t Check_RXE(UART_NO_t Copy_enuUART_NO)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    if (Get_bit(UARTS[Copy_enuUART_NO]->USART_SR, USART_SR_RXNE) == 0)
    {
        Loc_enuUART_Error_Status = UART_NO_DATA;
    }
    return Loc_enuUART_Error_Status;
}

UART_Error_Status_t UART_enuReceiveByte(UART_NO_t Copy_enuUART_NO, u16 *Ref_u16Byte)
{

    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    if (Ref_u16Byte == nullptr)
    {
        Loc_enuUART_Error_Status = UART_InvalidPtr;
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_UART_NO(Copy_enuUART_NO);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_RXE(Copy_enuUART_NO);
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        *Ref_u16Byte = UARTS[Copy_enuUART_NO]->USART_DR;
    }
    return Loc_enuUART_Error_Status;
}

static ptrtofun TXcbf[UART_Count];
static ptrtofun RXcbf[UART_Count];

UART_Error_Status_t UART_enuSetTXcbf(UART_NO_t Copy_enuUART_NO, ptrtofun Ref_cbf)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = Check_UART_NO(Copy_enuUART_NO);
    if (Loc_enuUART_Error_Status == UART_OK && Ref_cbf == nullptr)
    {
        Loc_enuUART_Error_Status = UART_Invalidcbf;
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        TXcbf[Copy_enuUART_NO] = Ref_cbf;
    }
    return Loc_enuUART_Error_Status;
}

UART_Error_Status_t UART_enuSetRXcbf(UART_NO_t Copy_enuUART_NO, ptrtofun Ref_cbf)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = Check_UART_NO(Copy_enuUART_NO);
    if (Loc_enuUART_Error_Status == UART_OK && Ref_cbf == nullptr)
    {
        Loc_enuUART_Error_Status = UART_Invalidcbf;
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        RXcbf[Copy_enuUART_NO] = Ref_cbf;
    }
    return Loc_enuUART_Error_Status;
}

typedef enum
{
    Idle,
    Busy
} UART_State_t;

static UART_State_t TX_UART_States[UART_Count];
static UART_State_t RX_UART_States[UART_Count];

static u64 TX_Index[UART_Count];
static u64 RX_Index[UART_Count];

static UART_Buffer_t TX_Buffer[UART_Count];
static UART_Buffer_t *RX_Buffer[UART_Count];

static inline UART_Error_Status_t Check_TXState(UART_NO_t Copy_enuUART_NO)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    if (TX_UART_States[Copy_enuUART_NO] == Busy)
    {
        Loc_enuUART_Error_Status = UART_Busy;
    }
    return Loc_enuUART_Error_Status;
}
static inline UART_Error_Status_t Check_RXState(UART_NO_t Copy_enuUART_NO)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = UART_OK;
    if (RX_UART_States[Copy_enuUART_NO] == Busy)
    {
        Loc_enuUART_Error_Status = UART_Busy;
    }
    return Loc_enuUART_Error_Status;
}

UART_Error_Status_t UART_enuSendBuffer(UART_NO_t Copy_enuUART_NO, UART_Buffer_t *Ref_strBuffer)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = Check_UART_NO(Copy_enuUART_NO);
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_TXState(Copy_enuUART_NO);
    }
    if (Loc_enuUART_Error_Status == UART_OK && Ref_strBuffer == nullptr)
    {
        Loc_enuUART_Error_Status = UART_InvalidPtr;
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        TX_Buffer[Copy_enuUART_NO] = *Ref_strBuffer;
        TX_Index[Copy_enuUART_NO] = 0;
        UARTS[Copy_enuUART_NO]->USART_DR = Ref_strBuffer->buffer[0];
        TX_Index[Copy_enuUART_NO]++;
        Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TXEIE);
        TX_UART_States[Copy_enuUART_NO] = Busy;
    }
    return Loc_enuUART_Error_Status;
}

UART_Error_Status_t UART_enuReceiveBuffer(UART_NO_t Copy_enuUART_NO, UART_Buffer_t *Ref_strBuffer)
{
    UART_Error_Status_t Loc_enuUART_Error_Status = Check_UART_NO(Copy_enuUART_NO);
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        Loc_enuUART_Error_Status = Check_RXState(Copy_enuUART_NO);
    }
    if (Loc_enuUART_Error_Status == UART_OK && Ref_strBuffer == nullptr)
    {
        Loc_enuUART_Error_Status = UART_InvalidPtr;
    }
    if (Loc_enuUART_Error_Status == UART_OK)
    {
        RX_Index[Copy_enuUART_NO] = 0;
        RX_Buffer[Copy_enuUART_NO] = Ref_strBuffer;
        RX_UART_States[Copy_enuUART_NO] = Busy;
        Set_Bit(UARTS[Copy_enuUART_NO]->USART_CR1,USART_CR1_RXNEIE);
    }
    return Loc_enuUART_Error_Status;
}

static inline void USART_IRQHandler(UART_NO_t Copy_enuUART_NO)
{
    if (Get_bit(UARTS[Copy_enuUART_NO]->USART_SR, USART_SR_TXE) && Get_bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TXEIE))
    {
        if (TX_UART_States[Copy_enuUART_NO] == Busy)
        {
            if (TX_Index[Copy_enuUART_NO] < TX_Buffer[Copy_enuUART_NO].size)
            {
                UARTS[Copy_enuUART_NO]->USART_DR = TX_Buffer[Copy_enuUART_NO].buffer[TX_Index[Copy_enuUART_NO]];
                TX_Index[Copy_enuUART_NO]++;
            }
            if (TX_Index[Copy_enuUART_NO] == TX_Buffer[Copy_enuUART_NO].size)
            {
                TX_Index[Copy_enuUART_NO] = 0;
                TX_UART_States[Copy_enuUART_NO] = Idle;
                Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TXEIE);
                if (TXcbf[Copy_enuUART_NO] != nullptr)
                    TXcbf[Copy_enuUART_NO]();
            }
        }
        else
        {
            Clear_Bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_TXEIE);
            if (TXcbf[Copy_enuUART_NO] != nullptr)
            {
                TXcbf[Copy_enuUART_NO]();
            }
        }
    }
    if (Get_bit(UARTS[Copy_enuUART_NO]->USART_SR, USART_SR_RXNE) && Get_bit(UARTS[Copy_enuUART_NO]->USART_CR1, USART_CR1_RXNEIE))
    {
        if (RX_UART_States[Copy_enuUART_NO] == Busy)
        {
            if (RX_Index[Copy_enuUART_NO] < RX_Buffer[Copy_enuUART_NO]->size)
            {
                RX_Buffer[Copy_enuUART_NO]->buffer[RX_Index[Copy_enuUART_NO]] = UARTS[Copy_enuUART_NO]->USART_DR;
                RX_Index[Copy_enuUART_NO]++;
            }
            if (RX_Index[Copy_enuUART_NO] == RX_Buffer[Copy_enuUART_NO]->size)
            {
                RX_Index[Copy_enuUART_NO] =0;
                RX_UART_States[Copy_enuUART_NO] = Idle;
                if (RXcbf[Copy_enuUART_NO] != nullptr) RXcbf[Copy_enuUART_NO]();
            }
        }
        else
        {
            if (RXcbf[Copy_enuUART_NO] != nullptr)
            {
                RXcbf[Copy_enuUART_NO]();
            }
        }
    }
}

void USART1_IRQHandler(void)
{
    USART_IRQHandler(UART1);
}
void USART2_IRQHandler(void)
{
    USART_IRQHandler(UART2);
}
void USART6_IRQHandler(void)
{
    USART_IRQHandler(UART6);
}
