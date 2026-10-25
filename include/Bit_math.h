#ifndef BIT_MATH_H
#define BIT_MATH_H

#define Set_Bit(reg, bit_no) (reg |= (1UL << bit_no))
#define Clear_Bit(reg, bit_no) (reg &= ~(1UL << bit_no))
#define Toggle_Bit(reg, bit_no) (reg ^= (1UL << bit_no))
#define Get_bit(reg, bit_no) ((reg >> bit_no) & 1UL)
#define Clear_Mask(reg, bit_mask) (reg &= ~(bit_mask))
#define Set_Mask(reg, bit_mask) (reg |= (bit_mask))
#define Get_Mask(reg,bit_mask) ( (reg & bit_mask) )

#endif