/*
 * STD_MACROS.h
 *
 * Created: 8/5/2023 10:45:06 PM
 *  Author: AHMED LOTFY
 */

#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#define REG_SIZE 8
#define SET_BIT(reg, bit) (reg |= (1 << bit))
#define CLR_BIT(reg, bit) reg &= ~(1 << bit)
#define TOG_BIT(reg, bit) reg ^= (1 << bit)
#define READ_BIT(reg, bit) (reg & (1 << bit)) >> bit
#define IS_BIT_SET(reg, bit) (reg & (1 << bit)) >> bit
#define IS_BIT_CLR(reg, bit) !((reg & (1 << bit)) >> bit)
#define ROR(reg, num) reg = (reg >> num) | (reg << REG_SIZE - num)
#define ROL(reg, num) reg = (reg << num) | (reg >> REG_SIZE - num)

typedef unsigned char u8_t;
typedef unsigned short int u16_t;
typedef unsigned long int u32_t;

typedef signed char s8_t;
typedef signed short int s16_t;
typedef signed long int s32_t;

typedef float f32_t;
typedef double f64_t;

#endif /* STD_MACROS_H_ */