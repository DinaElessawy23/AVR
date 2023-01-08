/*
 * lcd_src.c
 *
 *  Created on: Jan 4, 2023
 *      Author: DINA ELESSAWY
 */
#include "../../SERVE/std_types.h"
#include "../../MCAL/DIO/dio_int.h"
#include "lcd_cfg.h"
#include "lcd_int.h"
#include "util/delay.h"


void LCD_vidInit(void)
{
  DIO_u8SetPortDir(LCD_DATA_PORT,FULL_OUTPUT);//Data pins
  DIO_u8SetPinDir(LCD_RS_PORT,LCD_RS_PIN,OUTPUT);//RS
  DIO_u8SetPinDir(LCD_RW_PORT,LCD_RW_PIN,OUTPUT);//RW
  DIO_u8SetPinDir(LCD_E_PORT,LCD_E_PIN,OUTPUT);//E
  _delay_ms(40);//wait more than 30 ms after power is on
  LCD_vidWriteCmd(LCD_FUNC_SET_CMD);
  _delay_ms(1);
  LCD_vidWriteCmd(LCD_DSP_ON_OFF_CTRL);
  _delay_ms(1);
  LCD_vidWriteCmd(LCD_CLR_DSP_CMD);
  _delay_ms(3);
  LCD_vidWriteCmd(LCD_ENTRY_MOD_SET);


}
void LCD_vidWriteCmd(uint8 u8CommandCopy)
{
  DIO_u8SetPinVal(LCD_RS_PORT,LCD_RS_PIN,LOW); //Command
  DIO_u8SetPinVal(LCD_RW_PORT,LCD_RW_PIN,LOW); //TO Write command
  DIO_u8SetPortVal(LCD_DATA_PORT,u8CommandCopy);
  DIO_u8SetPinVal(LCD_E_PORT,LCD_E_PIN,HIGH);
  _delay_ms(2);
  DIO_u8SetPinVal(LCD_E_PORT,LCD_E_PIN,LOW);


}
void LCD_vidWriteChar(uint8 u8CharacterCopy)
{
	  DIO_u8SetPinVal(LCD_RS_PORT,LCD_RS_PIN,HIGH); //Command
	  DIO_u8SetPinVal(LCD_RW_PORT,LCD_RW_PIN,LOW); //TO Write command
	  DIO_u8SetPortVal(LCD_DATA_PORT,u8CharacterCopy);
	  DIO_u8SetPinVal(LCD_E_PORT,LCD_E_PIN,HIGH);
	  _delay_ms(2);
	  DIO_u8SetPinVal(LCD_E_PORT,LCD_E_PIN,LOW);
}

void LCD_WriteString(uint8* str)
{
	while((*str)!='\0')
	{
		LCD_vidWriteChar(*str);
		str++;
	}
}

void LCD_WriteInt(uint32 number)
{
	uint8* str;
	uint8 rem;
	uint8 len;
	uint32 n=number;
	if(n==0)
	{
		LCD_vidWriteChar('0');
	}
	else
	{
	while(n !=0)
	{
		len++;
		n/=10;
	}
	for(int i=0;i<len;i++)
	{
		rem=number%10;
		number/=10;
		str[len-(i+1)]=rem+'0';// to be ASCII as LCD accept only ascii num+48 ,num+'0'
		//LCD_vidWriteChar(rem+48);
	}
	str[len]='\0';

	LCD_WriteString(str);}
}

void LCD_ClrDisplay()
{
	LCD_vidWriteCmd(LCD_CLR_DSP_CMD);
}

void LCD_GoToXY(uint8 row,uint8 col)
{
	uint8 DDRAM_AC;
	switch(row)
	{
	case 1:
		DDRAM_AC=col;
		break;
	case 2:
		DDRAM_AC=col+0x40;
		break;
	}
	LCD_vidWriteCmd(DDRAM_AC |LCD_SET_DDRAM_ADDRESS);
}

void LCD_ShiftLeft()
{
	LCD_vidWriteCmd(LCD_DISPLAY_SHIFT_LEFT);
}

void LCD_ShiftRight()
{
	LCD_vidWriteCmd(LCD_DISPLAY_SHIFT_RIGHT);
}

void LCD_CreateCustomeChar(uint8 loc,uint8* custom)
{
	LCD_vidWriteCmd(LCD_SET_CGRAM_ADDRESS+(loc*8));

	for(uint8 i=0;i<8;i++)
	{
	LCD_vidWriteChar(custom[i]);
	}
}
