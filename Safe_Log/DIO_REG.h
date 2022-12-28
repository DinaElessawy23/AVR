/*
 * DIO_REG.h
 *
 *  Created on: Dec 9, 2022
 *      Author: DINA ELESSAWY
 */

#ifndef DIO_REG_H_
#define DIO_REG_H_

#define DDRA_REG     *( (volatile uint8 *) 0X3A)
#define DDRB_REG     *( (volatile uint8 *) 0X37)
#define DDRC_REG     *( (volatile uint8 *) 0X34)
#define DDRD_REG     *( (volatile uint8 *) 0X31)
#define PORTA_REG    *( (volatile uint8 *) 0X3B)
#define PORTB_REG    *( (volatile uint8 *) 0X38)
#define PORTC_REG    *( (volatile uint8 *) 0X35)
#define PORTD_REG    *( (volatile uint8 *) 0X32)
#define PINA_REG     *( (volatile uint8 *) 0X39)
#define PINB_REG     *( (volatile uint8 *) 0X36)
#define PINC_REG     *( (volatile uint8 *) 0X33)
#define PIND_REG     *( (volatile uint8 *) 0X30)




#endif /* DIO_REG_H_ */
