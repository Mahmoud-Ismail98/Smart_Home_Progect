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
#include "smart_home_cofig.h"


uint8 pass[4];
uint8 temp[2];
uint8 Temp_Value;
uint8 pass_count=0;
volatile char key_pressed;
uint8 Mode;
#define	OWNER_MODE 0
#define	GUEST_MODE 1
int main(void)
{
	// Start_Message();
	//Device_Drive();
   // Start_Message();
   	LCD_INISTIALIZATION();
	SPI_vInitMaster();//initializes the communication protocol of SPI
   	//GO_LOC(2,1);
   	SEND_STRING("wellcome to smart");
   	_delay_ms(500);
   	GO_LOC(2,3);
   	SEND_STRING("home system");
   	//_delay_ms(3000);
   	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
   	
	
	if (EEPROM_ui8ReadByteFromAddress(Login_status)==0xFF)
	{

			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,1);
			SEND_STRING("Set Admin Pass");
			GO_LOC(3,1);
			SEND_STRING("Admin Pass:");
			


			while (pass_count<4)
			{
				key_pressed =keyfind();
				 pass[pass_count]=(key_pressed-48);
				 SEND_DATE(key_pressed);
				 _delay_ms(300);
				 pass_count++;
			}
			EEPROM_vWriteBlockToAddress(ADMIN_PASS_ADD,pass,4);
			
			//pass={0};
			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,1);
			SEND_STRING("Set Guest Pass");
			GO_LOC(3,1);
			SEND_STRING("guest Pass:");

			pass_count=0;
			while (pass_count<4)
			{
				key_pressed=keyfind();
				pass[pass_count]=(key_pressed-48);
				SEND_DATE(key_pressed);
				_delay_ms(300);
				pass_count++;
			}
			EEPROM_vWriteBlockToAddress(Guest_PASS_ADD,pass,4);
		   EEPROM_vWriteByteToAddress(Login_status,0x00);
	} 
	//else
	//{
			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,1);
			SEND_STRING("selec mode");
			GO_LOC(3,1);
			SEND_STRING("0:Owner 1:Guest");
			_delay_ms(2000);
			
			key_pressed=keyfind();
			if (key_pressed=='0')
			{
				
			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,1);
			SEND_STRING("Owner mode");
			GO_LOC(3,1);
			SEND_STRING("Enter Pass:");
			_delay_ms(2000);
			pass_count=0;
			while (pass_count<4)
			{
				key_pressed=keyfind();
				pass[pass_count]=(key_pressed);
				SEND_DATE(key_pressed);
				_delay_ms(300);
				pass_count++;
			}
			uint8 EEPROM_Pass;
			uint8 i=0;
			while(i<4)
			{
				EEPROM_Pass = EEPROM_ui8ReadByteFromAddress(ADMIN_PASS_ADD+i);
				if (EEPROM_Pass==(pass[i]-48))
				{
					i++;
					
				} 
				else
				{
					SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
					GO_LOC(2,1);
					SEND_STRING("Owner Rong Pass");
					GO_LOC(3,1);					
					break;
				}
				if (i==3)
				{
				    SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
				    GO_LOC(2,1);
				    SEND_STRING("Owner Correct Pass");
				    Mode=OWNER_MODE;
				    DDRC|=(1<<OWNER_PIN);
				    PORTC|=(1<<OWNER_PIN);
				}

			}

			} 
			else if(key_pressed=='1')
			{
				
				SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
				GO_LOC(2,1);
				SEND_STRING("Guest mode");
				GO_LOC(3,1);
				SEND_STRING("Enter Pass:");
				_delay_ms(2000);
				pass_count=0;
				while (pass_count<4)
				{
					key_pressed=keyfind();
					pass[pass_count]=(key_pressed);
					SEND_DATE(key_pressed);
					_delay_ms(300);
					pass_count++;
				}
				uint8 EEPROM_Pass;
				uint8 i=0;
				while(i<4)
				{
					EEPROM_Pass = EEPROM_ui8ReadByteFromAddress(Guest_PASS_ADD+i);
					if (EEPROM_Pass==(pass[i]-48))
					{
						i++;
						
					}
					else
					{
						SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
						GO_LOC(2,1);
						SEND_STRING("Guest Rong Pass");
						GO_LOC(3,1);
						break;
					}
					if(i==3)
					{
					SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
					GO_LOC(2,1);
					SEND_STRING("Guest Correct Pass");
					Mode=GUEST_MODE;
					DDRC|=(1<<GUEST_PIN);
					PORTC|=(1<<GUEST_PIN);
					}					
				}				
			}
			
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
	
	switch(key_pressed)
	{
		case '1':
			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,1);
			SEND_STRING("ROOM State:");
			GO_LOC(3,1);
			SEND_STRING("ON:1   OFF:2  RET:0");
			key_pressed=keyfind();
			
			if (key_pressed=='1')
			{
				DDRC|=(1<<ROOM1);
				PORTC|=(1<<ROOM1);
			} 
			else if(key_pressed=='2')
			{
				DDRC|=(1<<ROOM1);
				PORTC|=(0<<ROOM1);
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
	}						
			
			
			
			
}