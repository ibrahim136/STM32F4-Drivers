#include "NVIC.h"
#include "NVIC_priv.h"
#include "Bit_math.h"

static inline NVIC_Error_Status_t NVIC_enuCheckIQRn(NVIC_IRQ_t Copy_enuIRQn)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_OK;
    switch (Copy_enuIRQn)
    {
    case NVIC_IRQ_R0_MIN ... NVIC_IRQ_R0_MAX:
    case NVIC_IRQ_R1_MIN ... NVIC_IRQ_R1_MAX:
    case NVIC_IRQ_R2_MIN ... NVIC_IRQ_R2_MAX:
    case NVIC_IRQ_R3_MIN ... NVIC_IRQ_R3_MAX:
    case NVIC_IRQ_R4_MIN ... NVIC_IRQ_R4_MAX:
    case NVIC_IRQ_R5_MIN ... NVIC_IRQ_R5_MAX:
    case NVIC_IRQ_R6_MIN ... NVIC_IRQ_R6_MAX:
    case NVIC_IRQ_R7_MIN ... NVIC_IRQ_R7_MAX:
    case NVIC_IRQ_R8_MIN ... NVIC_IRQ_R8_MAX:
        break;
    default:
        Loc_enuNVIC_Error_Status = NVIC_InvalidIRQn;
        break;
    }
    return Loc_enuNVIC_Error_Status;
}

static inline NVIC_Error_Status_t NVIC_enuCheckPriority(Priority_t Copy_enuPriority)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_OK;
    switch (Copy_enuPriority)
    {
    case Priority0 ... Priority_count-1:
        break;
    default:
    Loc_enuNVIC_Error_Status = NVIC_InvalidPriority;
        break;
    }
    return Loc_enuNVIC_Error_Status;
}

static inline NVIC_Error_Status_t NVIC_enuChecku8Pointer(u8 * Copy_u8Pointer)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_OK;
    if (!Copy_u8Pointer)
    {
        Loc_enuNVIC_Error_Status = NVIC_InvalidPtr;
    }
    return Loc_enuNVIC_Error_Status;
}
static inline NVIC_Error_Status_t NVIC_enuCheckPriorityPointer(Priority_t* Copy_enuPriority)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_OK;
    if (!Copy_enuPriority)
    {
        Loc_enuNVIC_Error_Status = NVIC_InvalidPtr;
    }
    return Loc_enuNVIC_Error_Status;
}



static inline u8 Get_u8RegisterIndex(NVIC_IRQ_t Copy_enuIRQn)
{
    return Copy_enuIRQn/ Register_Bits_Capacity;
}

static inline u8 Get_u8BitPos(NVIC_IRQ_t Copy_enuIRQn)
{
    return Copy_enuIRQn % Register_Bits_Capacity;
}


NVIC_Error_Status_t NVIC_enuEnableIRQ(NVIC_IRQ_t Copy_enuIRQn)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_enuCheckIQRn(Copy_enuIRQn);
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        u8 Reg_Index = Get_u8RegisterIndex(Copy_enuIRQn);
        u8 Bit_Pos = Get_u8BitPos(Copy_enuIRQn);
        NVIC_reg->NVIC_ISERx[Reg_Index] = Masking_bit(Bit_Pos);
    }
    return Loc_enuNVIC_Error_Status;
}

NVIC_Error_Status_t NVIC_enuDisableIRQ(NVIC_IRQ_t Copy_enuIRQn)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_enuCheckIQRn(Copy_enuIRQn);
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        u8 Reg_Index = Get_u8RegisterIndex(Copy_enuIRQn);
        u8 Bit_Pos = Get_u8BitPos(Copy_enuIRQn);
        NVIC_reg->NVIC_ICERx[Reg_Index] = Masking_bit(Bit_Pos);
    }
    return Loc_enuNVIC_Error_Status;
}

NVIC_Error_Status_t NVIC_enuSetPendingIRQ(NVIC_IRQ_t Copy_enuIRQn)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_enuCheckIQRn(Copy_enuIRQn);
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        u8 Reg_Index = Get_u8RegisterIndex(Copy_enuIRQn);
        u8 Bit_Pos = Get_u8BitPos(Copy_enuIRQn);
        NVIC_reg->NVIC_ISPRx[Reg_Index] = Masking_bit(Bit_Pos);
    }
    return Loc_enuNVIC_Error_Status;
}

NVIC_Error_Status_t NVIC_enuClearPendingIRQ(NVIC_IRQ_t Copy_enuIRQn)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_enuCheckIQRn(Copy_enuIRQn);
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        u8 Reg_Index = Get_u8RegisterIndex(Copy_enuIRQn);
        u8 Bit_Pos = Get_u8BitPos(Copy_enuIRQn);
        NVIC_reg->NVIC_ICPRx[Reg_Index] = Masking_bit(Bit_Pos);
    }
    return Loc_enuNVIC_Error_Status;
}

NVIC_Error_Status_t NVIC_enuGetPendingIRQ(NVIC_IRQ_t Copy_enuIRQn,u8 * Copy_u8PendingStatus)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_enuCheckIQRn(Copy_enuIRQn);
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        Loc_enuNVIC_Error_Status = NVIC_enuChecku8Pointer(Copy_u8PendingStatus);
    }
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        u8 Reg_Index = Get_u8RegisterIndex(Copy_enuIRQn);
        u8 Bit_Pos = Get_u8BitPos(Copy_enuIRQn);
        *Copy_u8PendingStatus = Get_bit(NVIC_reg->NVIC_ICPRx[Reg_Index],Bit_Pos);
    }
    return Loc_enuNVIC_Error_Status;

}

NVIC_Error_Status_t  NVIC_enuSetPriority(NVIC_IRQ_t Copy_enuIRQn, Priority_t Copy_enuPriority)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_enuCheckIQRn(Copy_enuIRQn);
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        Loc_enuNVIC_Error_Status = NVIC_enuCheckPriority(Copy_enuPriority);
    }
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        NVIC_reg->NVIC_IPx[Copy_enuIRQn] = PriorityShiftMSB(Copy_enuPriority);
    }
    return Loc_enuNVIC_Error_Status;
}

NVIC_Error_Status_t  NVIC_enuGetPriority(NVIC_IRQ_t Copy_enuIRQn, Priority_t* Copy_enuPriority)
{
    NVIC_Error_Status_t Loc_enuNVIC_Error_Status = NVIC_enuCheckIQRn(Copy_enuIRQn);
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {
        Loc_enuNVIC_Error_Status = NVIC_enuCheckPriorityPointer(Copy_enuPriority);
    }
    if (Loc_enuNVIC_Error_Status == NVIC_OK)
    {

        *Copy_enuPriority = (Priority_t)Get_Mask( Shift_Right(NVIC_reg->NVIC_IPx[Copy_enuIRQn],PriorityShift) , PriorityMaskAfterShiftRight);
    }
    return Loc_enuNVIC_Error_Status;
}





