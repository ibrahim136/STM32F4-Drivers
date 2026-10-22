#ifndef BIT_MATH_H
#define BIT_MATH_H

#define Set_Bit(reg,bit_no) (reg |= (1<<bit_no))
#define Clear_Bit(reg,bit_no) (reg &= ~(1<<bit_no))
#define Toggle_Bit(reg,bit_no) (reg ^= (1<<bit_no))
#define Get_bit(reg,bit_no) ( (reg>>bit_no) & 1UL )


#endif