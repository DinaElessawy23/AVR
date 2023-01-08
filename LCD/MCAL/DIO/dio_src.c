/*
 * dio_src.c
 *
 *  Created on: Dec 16, 2022
 *      Author: DINA ELESSAWY
 */


#include  "../../SERVE/std_types.h"//../out doi ../ outMCAL ctrl+space
#include  "../../SERVE/bit_math.h"
#include  "DIO_REG.h"
#include  "dio_int.h"

uint8 DIO_u8SetPortDir(uint8 u8PortIdCopy , uint8  u8DirCopy )
{
	uint8 errStatus = E_OK;
	switch(u8PortIdCopy)
	{
	case PORT_A :DDRA_REG = u8DirCopy ; break;
	case PORT_B :DDRB_REG = u8DirCopy ; break;
	case PORT_C :DDRC_REG = u8DirCopy ; break;
	case PORT_D :DDRD_REG = u8DirCopy ; break;
	default : errStatus = E_NOK       ; break;
	}
	return errStatus;
}

uint8 DIO_u8SetPortVal(uint8 u8PortIdCopy , uint8  u8ValCopy )
{
	uint8 errStatus = E_OK;
	switch(u8PortIdCopy)
		{
		case PORT_A :PORTA_REG = u8ValCopy ; break;
		case PORT_B :PORTB_REG = u8ValCopy ; break;
		case PORT_C :PORTC_REG = u8ValCopy ; break;
		case PORT_D :PORTD_REG = u8ValCopy ; break;
		default : errStatus = E_NOK        ; break;
		}
	return errStatus;

}

uint8 DIO_u8GetPortVal(uint8 u8PortIdCopy , uint8 * u8pValCopy )
{
	uint8 errStatus = E_OK;
	switch(u8PortIdCopy)
			{
			case PORT_A :* u8pValCopy = PINA_REG ; break;
			case PORT_B :* u8pValCopy = PINB_REG ; break;
			case PORT_C :* u8pValCopy = PINC_REG ; break;
			case PORT_D :* u8pValCopy = PIND_REG ; break;
			default : errStatus = E_NOK        ; break;
			}
	return errStatus;
}

uint8 DIO_u8SetPinDir(uint8 u8PortIdCopy , uint8 u8PinIdCopy , uint8  u8DirCopy )
{
	uint8 errStatus = E_OK;
	if(u8PinIdCopy>=PIN_0 && u8PinIdCopy<=PIN_7)
	{
		if(u8DirCopy==INPUT)
		{
			switch(u8PortIdCopy)
					{
					case PORT_A :CLR_BIT(DDRA_REG,u8PinIdCopy) ; break;
					case PORT_B :CLR_BIT(DDRB_REG,u8PinIdCopy) ; break;
					case PORT_C :CLR_BIT(DDRC_REG,u8PinIdCopy) ; break;
					case PORT_D :CLR_BIT(DDRD_REG,u8PinIdCopy) ; break;
					default : errStatus = E_NOK        ; break;
					}
		}
		else if(u8DirCopy==OUTPUT)
		{
			switch(u8PortIdCopy)
					{
					case PORT_A :SET_BIT(DDRA_REG,u8PinIdCopy) ; break;
					case PORT_B :SET_BIT(DDRB_REG,u8PinIdCopy) ; break;
					case PORT_C :SET_BIT(DDRC_REG,u8PinIdCopy) ; break;
					case PORT_D :SET_BIT(DDRD_REG,u8PinIdCopy) ; break;
					default : errStatus = E_NOK        ; break;
					}

		}
		else
		{
			errStatus = E_NOK;
		}

	}
	else
	{
		errStatus = E_NOK;
	}

	return errStatus;
}

uint8 DIO_u8SetPinVal(uint8 u8PortIdCopy , uint8 u8PinIdCopy , uint8  u8ValCopy )
{
	uint8 errStatus = E_OK;
	if(u8PinIdCopy>=PIN_0 && u8PinIdCopy<=PIN_7)
	{
		if(u8ValCopy==LOW)
		{
			switch(u8PortIdCopy)
					{
					case PORT_A :CLR_BIT(PORTA_REG,u8PinIdCopy) ; break;
					case PORT_B :CLR_BIT(PORTB_REG,u8PinIdCopy) ; break;
					case PORT_C :CLR_BIT(PORTC_REG,u8PinIdCopy) ; break;
					case PORT_D :CLR_BIT(PORTD_REG,u8PinIdCopy) ; break;
					default : errStatus = E_NOK        ; break;
					}
		}
		else if(u8ValCopy==HIGH)
		{
			switch(u8PortIdCopy)
					{
					case PORT_A :SET_BIT(PORTA_REG,u8PinIdCopy) ; break;
					case PORT_B :SET_BIT(PORTB_REG,u8PinIdCopy) ; break;
					case PORT_C :SET_BIT(PORTC_REG,u8PinIdCopy) ; break;
					case PORT_D :SET_BIT(PORTD_REG,u8PinIdCopy) ; break;
					default : errStatus = E_NOK        ; break;
					}

		}
		else
		{
			errStatus = E_NOK;
		}

	}
	else
	{
		errStatus = E_NOK;
	}

	return errStatus;

}

uint8 DIO_u8GetPinVal(uint8 u8PortIdCopy , uint8 u8PinIdCopy , uint8 * u8pValCopy )
{
	uint8 errStatus = E_OK;
	if(u8PinIdCopy>=PIN_0 && u8PinIdCopy<=PIN_7)
		{
		switch(u8PortIdCopy)
				{
				case PORT_A :* u8pValCopy=GET_BIT(PINA_REG,u8PinIdCopy) ; break;
				case PORT_B :* u8pValCopy=GET_BIT(PINB_REG,u8PinIdCopy); break;
				case PORT_C :* u8pValCopy=GET_BIT(PINC_REG,u8PinIdCopy); break;
				case PORT_D :* u8pValCopy=GET_BIT(PIND_REG,u8PinIdCopy); break;
				default : errStatus = E_NOK        ; break;
				}
		}
	else
		{
			errStatus = E_NOK;
		}
	return errStatus;
}
