/*
 * main.c
 *
 *  Created on: Jan 4, 2023
 *      Author: DINA ELESSAWY
 */
#include "../SERVE/std_types.h"
#include "../HAL/LCD/lcd_int.h"
#include "util/delay.h"
void main(void)
{
uint8 Character1[8] = {
		0b00000,
		0b00000,
		0b00001,
		0b00001,
		0b00001,
		0b11111,
		0b00000,
		0b00000};
uint8 Character2[8] =
{
		0b10000,
		0b00000,
		0b10001,
		0b10001,
		0b10001,
		0b11111,
		0b00000,
		0b00110
};
/*uint8 Character3[8]={
		0b10000,
		0b00000,
		0b10000,
		0b10000,
		0b10000,
		0b11111,
		0b00000,
		0b00000
};*/
uint8 Character3[8] =
{
0b10000,
0b10000,
0b10000,
0b10000,
0b10000,
0b11111,
0b00000,
0b00000
};
/* Custom char set for alphanumeric LCD Module */
		//unsigned char Character2[8] = { 0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F };
		//unsigned char Character3[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00 };
		//unsigned char Character4[8] = { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01 };
		//unsigned char Character5[8] = { 0x01, 0x03, 0x05, 0x09, 0x09, 0x0B, 0x1B, 0x18 };
		//unsigned char Character6[8] = { 0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04 };
		//unsigned char Character7[8] = { 0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00 };
		unsigned char Character4[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };
	LCD_vidInit();


	LCD_CreateCustomeChar(0,Character1);
	LCD_CreateCustomeChar(1,Character2);
	LCD_CreateCustomeChar(2,Character3);
	LCD_CreateCustomeChar(3,Character4);
	//LCD_CreateCustomeChar(Character5);
	//LCD_CreateCustomeChar(Character6);
	//LCD_CreateCustomeChar(Character7);
	//LCD_CreateCustomeChar(Character8);
		LCD_GoToXY(1,9);
		LCD_vidWriteCmd(0b00000100);//Entry mode decrease
	LCD_vidWriteChar(0);
	LCD_vidWriteChar(1);
	LCD_vidWriteChar(2);
	LCD_vidWriteChar(3);

	LCD_GoToXY(2,6);
	LCD_vidWriteCmd(0b00000110);//Entry mode increase
	LCD_WriteString("Dina");
	LCD_GoToXY(2,10);
	LCD_vidWriteChar(3);


	while(1)
	{
		LCD_ShiftRight();
		_delay_ms(200);




	}
}
