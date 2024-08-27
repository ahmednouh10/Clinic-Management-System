//Guard
#ifndef bit_math
#define bit_math

//SET certain bit
#define SET_BIT(value,bit_num) value |= (1<<bit_num)

//CLEAR certain bit
#define CLR_BIT(value,bit_num) value &= (~(1<<bit_num))

//TOGGLE certain bit
#define TOG_BIT(value,bit_num) value ^= (1<<bit_num)

//READ certain bit
#define READ_BIT(value,bit_num) ( (value>>bit_num) & 1 )

#endif