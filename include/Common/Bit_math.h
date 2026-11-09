#ifndef BIT_MATH_H
#define BIT_MATH_H

#define Set_Bit(reg, bit_no) (reg |= (1UL << bit_no))
#define Clear_Bit(reg, bit_no) (reg &= ~(1UL << bit_no))
#define Toggle_Bit(reg, bit_no) (reg ^= (1UL << bit_no))
#define Get_bit(reg, bit_no) ((reg >> bit_no) & 1UL)
#define Clear_Mask(reg, bit_mask) (reg &= ~(bit_mask))
#define Set_Mask(reg, bit_mask) (reg |= (bit_mask))
#define Get_Mask(reg, bit_mask) ((reg & bit_mask))
#define Shift_Right(reg,pos) (reg>>pos)
#define Shift_Left(reg,pos) (reg<<pos)
#define Get_Mask_Value(reg, bit_pos) Shift_Right(reg,bit_pos)
#define Masking_Value(value, pos) Shift_Left(value,pos)
#define Masking_bit(pos) (1UL << pos)
#define Double_pos(pos) (pos * 2)
#define Quad_pos(pos) (pos * 4)
#define Clear_reg(reg) (reg=0)

#endif