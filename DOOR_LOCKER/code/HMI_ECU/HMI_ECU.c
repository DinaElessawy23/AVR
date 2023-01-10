/*
 * HMI_ECU.c
 *
 *  Created on: Nov 2, 2021
 *      Author: Dina Elessawy
 */


#include"HMI_ECU.h"


int main()
{

	/* Initialize the LCD driver */
	LCD_init();
	Timer_setCallBack(Calculate_time,Timer0);


	/* Initialize the uart driver */
    UART_init(&UART_Config);
    LCD_clearScreen();
    	LCD_displayStringRowColumn(0,0,"DOOR LOCKER SYS");
    	LCD_displayStringRowColumn(1,4,"WELCOME");

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	_delay_ms(4000);

	//ifPassSavedORNOT();   /* to check either it's first time for the user to log in or no */

    while(1)
    {
		(*ptr_states[g_stateNum])();   /* calling functions from the array of functions */

    }


}
void create_StorePassword(void)
{
	/*
	 * 1. DISPLAY ON SCREEN A MESSAGE TO ENTER THE PASSWORD
	 * 2. ENTER IT AGAIN AND CHECK IF IT MATCHES
	 * 3. START FILLING IN THE PASSWORD FROM THE USER TO A GLOBAL ARRAY
	 * 4. SEND COMMAND TO CONTROL_ECU (PASSWORD_SEND)
	 * 5. SENDING THE PASSWORD TO THE CONTROL_ECU AND IF IT MATCHES STORE IT
	 * 6. IF IT DOESN'T MATCH DISPLAY A MESSAGE ON SCREEN
	 */
	if(g_flag==0){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"ENTER THE PASS");
		LCD_moveCursor(1,6);
		fill_Password(password);
		sendCommand(PASSWORD_SEND);
		SendPassword(password);
		g_flag=1;
	}
	if(g_flag==1)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"RE-ENTER PASS");
		LCD_moveCursor(1,6);
		fill_Password(password);
		sendCommand(PASSWORD_CONFIRMATION_SEND);
		SendPassword(password);
		g_flag=2;
	}
	if (g_flag==2)
	{
		switch(recieveCommand())
		{
		case PASSWORD_MATCH:
			g_flag=3;
			g_stateNum=1;
			break;

		case PASSWORD_NOT_MATCHED:
			Password_MISMATCH();
			g_flag=0;
			break;
		}
	}
}


void SendPassword(uint8 a_arr[])
{
	/*
	 * 1. SEND A READY COMMAND TO THE CONTROL_ECU TO SAY THAT HMI_ECI IS READY
	 * 2.WAITING UNTIL THE CONTROL_ECU SEND A READY COMMAND TOO
	 * 3.SENDING THE PASSWORD ENTERED BY THE USER FROM THE GLOBAL ARRAY
	 * 4. WAITING UNTIL THE CONTROL_ECU SENDS DONE COMMAND
	 */
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};

	for(uint8 i=0;i<PASSWORD_ARRAY_SIZE;i++)
	{
		UART_sendByte(a_arr[i]);
	}
	while(UART_recieveByte() != DONE){};
}

void sendCommand(uint8 command)
{
	/*
	 * 1. SEND A READY COMMAND TO THE CONTROL_ECU TO SAY THAT HMI_ECI IS READY
	 * 2.WAITING UNTIL THE CONTROL_ECU SEND A READY COMMAND TOO
	 * 3.SENDING A COMMAND FROM THE HMI_ECU
	 * 4. WAITING UNTIL THE CONTROL_ECU SENDS DONE COMMAND
	 */
	UART_sendByte(READY);
	while(UART_recieveByte() != READY){};
	UART_sendByte(command);
	while(UART_recieveByte() != DONE){};

}

uint8 recieveCommand(void)
{
	/*
	 * 1.WAITING UNTIL THE CONTROL_ECU SEND A READY COMMAND
	 * 2. SEND A READY COMMAND TO THE CONTROL_ECU TO SAY THAT HMI_ECI IS READY
	 * 3. RECIEVE A COMMAND FROM THE CONTROL_ECU
	 * 4. SENDING TO THE  CONTROL_ECU  DONE COMMAND
	 * 5. RETURN THE COMMAND SENT FROM THE COTROL_ECU
	 */
	while(UART_recieveByte() != READY){};
	UART_sendByte(READY);
	command=UART_recieveByte();
	UART_sendByte(DONE);
	return command;
}


void mainFucntion(void)
{
	/*
	 * 1. DISPLAY THE MAIN OPTIONS TO THE USER ON THE SCREEN
	 * 2.DEPENDING ON WHICH OPTION HE CHOSE DO IT
	 * 3.CASE'-':
	 *           REQUEST THE OLD PASSOWRD
	 *           FILL IN THE PASSWORD FROM THE USER
	 *           SEND COMMAND TO CONTROL_ECU TO CHECK IF PASSWORD MATCHES WHAT THE USER ENTERED OR NOT
	 *           IF IT MATCHES:
	 *                         GO TO STATE NUMBER 0 TO CHANGE THE PASSWORD
	 *           IF NOT:
	 *                  DISPLAY PASSWORD WRONG MESSAGE ALSO INCREMENT THE GLOBAL WRONG VARIABLE
	 *   CASE'+':
	 *            REQUEST THE OLD PASSOWRD
	 *            FILL IN THE PASSWORD FROM THE USER
	 *            SEND COMMAND TO CONTROL_ECU TO CHECK IF PASSWORD MATCHES WHAT THE USER ENTERED OR NOT
	 *            IF IT MATCHES:
	 *                          GO TO STATE NUMBER 2 TO OPEN THE DOOR
	 *            IF NOT:
	 *                   DISPLAY PASSWORD WRONG MESSAGE ALSO INCREMENT THE GLOBAL WRONG VARIABLE
	 */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+: open door");
	LCD_displayStringRowColumn(1,0,"-: change pass");
	switch(KEYPAD_getPressedKey())
	{
	case '-':
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"ENTER OLD PASS");
		LCD_moveCursor(1,6);
		_delay_ms(1500);
		fill_Password(password);
		sendCommand(CHECK_PASSWORD);
		SendPassword(password);
		switch (recieveCommand())
		{
		case PASSWORD_MATCH:
			g_flag=0;
			g_stateNum=0;
			wrong=0;
			break;
		case PASSWORD_NOT_MATCHED:
			wrongPasswordScreen();
			break;
		}
		break;
		case '+':
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"ENTER THE PASS");
			LCD_moveCursor(1,6);
			_delay_ms(1500);
			fill_Password(password);
			sendCommand(CHECK_PASSWORD);
			SendPassword(password);
			switch (recieveCommand()){
			case PASSWORD_MATCH:
				sendCommand(OPEN_DOOR);
				g_stateNum=2;
				wrong=0;
				break;
			case PASSWORD_NOT_MATCHED:
				wrongPasswordScreen();
				break;
			}
			break;
	}

}

void ifPassSavedORNOT(void)
{
	/*
	 * 1. SEND A COMMAND TO CONTROL_ECU TO CHECK IF IT HAS A SAVED PASSWORD IN EEPROM OR NOT YET
	 * 2.WAITING UNTIL THE CONTROL_ECU SEND COMMAND TOO
	 * IF YES_SAVED COMMAD:
	 *                    GO TO STATE 1 FOR THE MAIN FUNCTION
	 * IF NO_SAVED_PASSWORD:
	 *                     GO TO STATE 0 TO ENTER A NEW PASSWORD
	 */
	sendCommand(CHECK_IF_SAVED);
	switch (recieveCommand())
	{
	case YES_SAVED:
		g_stateNum=1;
		break;
	case NO_SAVED_PASSWORD:
		g_stateNum=0;
		break;

	}

}

void wrongPasswordScreen(void)
{
	/*
	 *1. DISPLAY A WRONG PASSWORD MESSAGE ON SCREEN
	 *2. INCREMENT THE GLOBAL WRONG VARIABLE
	 *3. SEND COMMANT TO THE CONTROL_ECU THAT THE USER HAS ENTERED A WRONG PASSWORD
	 *4. IF PASSWORD ENTERED IS WRONG 3 TIMES IN A ROW
	 *   IT WILL DISPLAY AN ALARM MESSAGE ON THE SCREEN
	 */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"WRONG PASSWORD!!");
	wrong++;
	sendCommand(WRONG_PASSWORD);
	if(wrong == 3)
	{
		ALERTscreen();
	}
	_delay_ms(4000);

}


void fill_Password(uint8 a_arr[])
{
	uint8 counter=0;
	key=KEYPAD_getPressedKey();/* get the pressed key number */
	while(key != '=')
	{
		key=KEYPAD_getPressedKey();
		if( ( key != '+' && key != '-' && key != '*' && key != '%' && key != '=') || (key>= 0 && key<= 9) )
		{
			if(counter < PASSWORD_ARRAY_SIZE)
			{
				a_arr[counter]=key;
				LCD_displayCharacter('*');
				counter++;
			}
		}
		_delay_ms(3000);
	}

}
void Password_MISMATCH(void)
{
	LCD_clearScreen();
	LCD_displayString("PASSWORD MISMATCH");
	_delay_ms(4000);

}



void ALERTscreen(void)
{
	LCD_clearScreen();
	Timer_init(&Timer_config);
	Timer_setCallBack( Calculate_time,Timer0);
	tick =0; /*Initially make the tick equals zero, to start from the beginning*/
	g_calc_sec_flag =0; /*Initially make the sec_flag equals zero,to start from the beginning*/

	while(g_calc_sec_flag != 60)
		{
			LCD_displayStringRowColumn(0,4,"ALERT!!!!");
			LCD_displayStringRowColumn(1,4,"THEIF!!!!");
		}
		if(g_calc_sec_flag == 60)
		{
			wrong=0;
			g_stateNum=1;
		}

}
void doorIsOpeningCloseingScreen(void)
{
	/*
	 * 1.INITIATE TIMER1 WITH THE GIVEN CONFIGURATIONS
	 * 2.SET THE CALL BACK FUNCTION
	 * 3. WHILE TIMER HASN'T FINISHED COUNTING DISPLAY DOOR IS UNLOCKING AND LOCKING  MESSAGE
	 * 4. IF TIME REACHED THE REQUIRED COUNTS
	 *    WRONG COUNTER BACK TO ZERO COUNTS ALSO GO BACK TO THE MAIN FUNCTION
	 */
	LCD_clearScreen();
	Timer_init(&Timer_config);
	Timer_setCallBack(Calculate_time,Timer0);
	tick =0; /*Initially make the tick equals zero, to start from the beginning*/
	g_calc_sec_flag =0; /*Initially make the sec_flag equals zero,to start from the beginning*/

	while(g_calc_sec_flag != 15)
	{
		LCD_displayStringRowColumn(0,0,"DOOR IS UNLOCKING..");
	}
	LCD_clearScreen();/*Clear LCD*/
	tick =0; /*Initially make the tick equals zero, to start from the beginning*/
	g_calc_sec_flag =0; /*Initially make the sec_flag equals zero, to start from the beginning*/
	/*As long as it hasn't passed 3 seconds, display on LCD this message*/
	while(g_calc_sec_flag != 3)
	{
		LCD_displayStringRowColumn(0,0,"Door is opened");
	}
	LCD_clearScreen(); /*Clear LCD*/
		tick =0; /*Initially make the tick equals zero, to start from the beginning*/
		g_calc_sec_flag =0; /*Initially make the sec_flag equals zero, to start from the beginning*/
		/*As long as it hasn't passed 15 seconds, display on LCD this message*/
		while(g_calc_sec_flag != 15)
		{
			LCD_displayStringRowColumn(0,0,"locking door");

		}
		if(g_calc_sec_flag == 15)
			{
				g_stateNum=1;
			}

}



void Calculate_time(void)
{
	tick ++; /*Every overflow increase ticks*/

	/*Once ticks become 30(according to the used prescalar),increase seconds flag and tick =0*/
	if(tick == 30)
	{
		g_calc_sec_flag ++; /*Every 30 tick, increase seconds flag*/
		tick =0; /*Put tick=0 to start counting new second*/
	}
}


