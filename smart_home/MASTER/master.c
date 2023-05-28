/*
 * AVRGCC1.c
 *
 * Created: 24/05/2022 02:17:15 م
 *  Author: MIK-PC
 */ 

#include <avr/io.h>
#include "keypad.h"
#include "lcd.h"
#include "EEPROM.h"
#include "STD_MESSAGES.h"
#include "smart_home_cofig.h"
#include "Master_MainFun.h"

uint8 pass[4];
uint8 temp[2];
uint8 Temp_Value;
extern uint8 pass_count;
extern volatile char key_pressed;
uint8 Mode;
uint8 SPI_RESPONSE;

int main(void)
{
   	LCD_INISTIALIZATION();
	SPI_vInitMaster();//initializes the communication protocol of SPI
	
   	SEND_STRING("wellcome to smart");
   	_delay_ms(500);
   	GO_LOC(2,3);
   	SEND_STRING("home system");

	if (EEPROM_ui8ReadByteFromAddress(Login_status)==0xFF)
	{		
		vEnterFirstTime();
	} 

	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
	GO_LOC(2,1);
	SEND_STRING("selec mode");
	GO_LOC(3,1);
	SEND_STRING("0:Owner 1:Guest");
	_delay_ms(2000);				
	key_pressed=keyfind();
	SelectModePass(key_pressed);
			
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
	GO_LOC(1,1);
	SEND_STRING("1:ROOM1 2:ROOM2");
	GO_LOC(2,1);
	SEND_STRING("3:ROOM3 4:ROOM4");	
	if (Mode==OWNER_MODE)
	{
			GO_LOC(3,1);
			SEND_STRING("5:TV 6:AIR_Condition");
	}
	key_pressed=keyfind();
	
	u8EnterRoonConfig(key_pressed);	
//	key_pressed=keyfind();
	

	//break;	
	/*switch(key_pressed)
	{
		case '1':
			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,1);
			SEND_STRING("ROOM State:");
			SPI_ui8TransmitRecive(ROOM1_STATUS);
			SPI_RESPONSE = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
			if(SPI_RESPONSE == ON_STATUS)//if the response from the slave was on status
			{
				SEND_STRING("ON");//print the status on
			}
			else//if the response from the slave was off status
			{
				SEND_STRING("OFF");//print the status off
			}			
			GO_LOC(3,1);
			SEND_STRING("ON:1   OFF:2  RET:0");
			key_pressed=keyfind();
			
			if (key_pressed=='1')
			{
				SPI_ui8TransmitRecive(ROOM1_TURN_ON);
			} 
			else if(key_pressed=='2')
			{
				SPI_ui8TransmitRecive(ROOM1_TURN_OFF);
			}
			else if(key_pressed=='0')
			{
			}
		break;	
		
				case '2':
				SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
				GO_LOC(2,1);
				SEND_STRING("ROOM State:");
				GO_LOC(3,1);
				SEND_STRING("ON:1   OFF:2  RET:0");
				key_pressed=keyfind();
				
				if (key_pressed=='1')
				{
					DDRC|=(1<<ROOM2);
					PORTC|=(1<<ROOM2);
				}
				else if(key_pressed=='2')
				{
					DDRC|=(1<<ROOM2);
					PORTC|=(0<<ROOM2);
				}
				else if(key_pressed=='0')
				{
				}
				break;	
				//air condition
				case '6':
				SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
				GO_LOC(2,1);
				SEND_STRING("Air cond State:");
				GO_LOC(3,1);
				SEND_STRING("ON:1   OFF:2  RET:0");
				GO_LOC(4,1);
				SEND_STRING("3:Set Temp");				
				key_pressed=keyfind();
				
				if (key_pressed=='1')
				{
					DDRC|=(1<<AIR_COND);
					PORTC|=(1<<AIR_COND);
				}
				else if(key_pressed=='2')
				{
					DDRC|=(1<<AIR_COND);
					PORTC|=(0<<AIR_COND);
				}
				else if(key_pressed=='3')
				{
				SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
				GO_LOC(2,1);
				SEND_STRING("enter temp:");
				key_pressed=keyfind();
				temp[0]=key_pressed;
				SEND_DATE(key_pressed);
				_delay_ms(200);
				key_pressed=keyfind();
				temp[1]=key_pressed;
				SEND_DATE(key_pressed);
				_delay_ms(200);	
				Temp_Value=temp[0]*10+temp[1];				
				}
				break;				
	}	*/					
			
			
			
			
}