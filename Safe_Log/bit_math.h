/*
 * bit_math.h
 *
 *  Created on: Dec 9, 2022
 *      Author: DINA ELESSAWY
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(Reg, BIT_NO) Reg |= (1<<BIT_NO)
#define CLR_BIT(Reg, BIT_NO) Reg &= ~(1<<BIT_NO)
#define TOGGLE_BIT(Reg, BIT_NO) Reg ^= (1<<BIT_NO)
#define GET_BIT(Reg, BIT_NO) ((Reg >>BIT_NO) & 1)

#endif /* BIT_MATH_H_ */
