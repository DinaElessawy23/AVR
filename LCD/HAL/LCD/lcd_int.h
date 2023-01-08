/*
 * lcd_int.h
 *
 *  Created on: Jan 4, 2023
 *      Author: DINA ELESSAWY
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_


#define LCD_FUNC_SET_CMD      0b00111000  //0b001DLNFXX DL for 8-bit mode ,N=1 for 2 lines ,F=0 for 5x7
#define LCD_DSP_ON_OFF_CTRL   0b00001100  //0b00001DCB  D Diplay ON /OFF ,C cursor ,Blink Cursor
#define LCD_CLR_DSP_CMD       0b00000001
#define LCD_ENTRY_MOD_SET     0b00000110  //I/D increment=1 or decrement display write from right or left , S shift write or left
#define LCD_SET_DDRAM_ADDRESS 0b10000000
#define LCD_SET_CGRAM_ADDRESS 0b01000000
#define LCD_READ_CGRAM_DATA   0b11000000
#define LCD_DISPLAY_SHIFT_RIGHT     0b00011100  //  0b0001(S/C)(R/L)00
#define LCD_DISPLAY_SHIFT_LEFT      0b00011000  //  0b0001(S/C)(R/L)00

void LCD_vidInit(void);
void LCD_vidWriteCmd(uint8 u8CommandCopy);
void LCD_vidWriteChar(uint8 u8CharacterCopy);
void LCD_ClrDisplay();
void LCD_ShiftLeft();
void LCD_ShiftRight();
void LCD_GoToXY(uint8 row,uint8 col);
void LCD_WriteString(uint8* str);
void LCD_WriteInt(uint32 number);//123

void LCD_CreateCustomeChar(uint8 loc,uint8* custom);




#endif /* HAL_LCD_LCD_INT_H_ */
