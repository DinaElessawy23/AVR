/*
 * dio_int.h
 *
 *  Created on: Dec 16, 2022
 *      Author: DINA ELESSAWY
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

/*---------------------------------MACROS----------------------------------*/
#define PORT_A    0
#define PORT_B    1
#define PORT_C    2
#define PORT_D    3

#define PIN_0     0
#define PIN_1     1
#define PIN_2     2
#define PIN_3     3
#define PIN_4     4
#define PIN_5     5
#define PIN_6     6
#define PIN_7     7

#define INPUT      0
#define OUTPUT     1

#define FULL_INPUT  0x00
#define FULL_OUTPUT 0xff

#define LOW       0
#define HIGH      1

#define PUE       1//PULL UP ENABLE

#define E_OK      0
#define E_NOK     1
/*---------------------------functions prototypes--------------------------*/
/*
 * Function:DIO_u8SetPortDir
 * description:function to set the full port direction
 * input param:
 *             u8PortIdCopy -> PORT ID From(PORT_A : PORT_D)
 *             u8DirCopy    -> The full port direction ex:0xff "full o/p"
 * return: err_status -> (E_OK , E_NOK)
 *
 */

/*if the user want to use all the port at one time*/
uint8 DIO_u8SetPortDir(uint8 u8PortIdCopy , uint8  u8DirCopy );
uint8 DIO_u8SetPortVal(uint8 u8PortIdCopy , uint8  u8ValCopy );
uint8 DIO_u8GetPortVal(uint8 u8PortIdCopy , uint8 * u8pValCopy );//ptr to return value by ref as we reserved the main return for error status
/*if the user want to use only one pin from the port */
uint8 DIO_u8SetPinDir(uint8 u8PortIdCopy , uint8 u8PinIdCopy , uint8  u8DirCopy );
uint8 DIO_u8SetPinVal(uint8 u8PortIdCopy , uint8 u8PinIdCopy , uint8  u8ValCopy );
uint8 DIO_u8GetPinVal(uint8 u8PortIdCopy , uint8 u8PinIdCopy , uint8 * u8pValCopy );


#endif /* DIO_INT_H_ */
