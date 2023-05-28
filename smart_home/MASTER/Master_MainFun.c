/*
 * Master_MainFun.c
 *
 * Created: 28/05/2023 02:50:27 ص
 *  Author: mkora
 */ 
#include "Master_MainFun.h"

uint8 pass[4];
uint8 pass_count=0;
volatile char key_pressed;
uint8 Mode;
vEnterFirstTime()
{
			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,1);
			SEND_STRING("login for first time");
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
				_delay_ms(00);
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
			_delay_ms(100);
			pass_count++;
		}
		EEPROM_vWriteBlockToAddress(Guest_PASS_ADD,pass,4);
		EEPROM_vWriteByteToAddress(Login_status,0x00);
}

void SelectModePass(char Mode_Key)
{
int pass;
if (Mode_Key=='0')
{
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
	GO_LOC(2,1);
	SEND_STRING("OWNER mode");
	GO_LOC(3,1);
	SEND_STRING("Enter Pass:");
	_delay_ms(100);
	pass = u8CheckPass(ADMIN_PASS_ADD);
	if (pass==TRUE)
	{
		Mode=OWNER_MODE;
		DDRC|=(1<<OWNER_PIN);
		PORTC|=(1<<OWNER_PIN);
	}
	else if(pass==FALSE)
	{
		SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
		GO_LOC(2,1);
		SEND_STRING("Owner Rong Pass");
		GO_LOC(3,1);
	}
}
else if(key_pressed=='1')
{	
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
	GO_LOC(2,1);
	SEND_STRING("Guest mode");
	GO_LOC(3,1);
	SEND_STRING("Enter Pass:");
	_delay_ms(100);
	pass = u8CheckPass(Guest_PASS_ADD);
	if (pass==TRUE)
	{
		Mode=GUEST_MODE;
		DDRC|=(1<<GUEST_PIN);
		PORTC|=(1<<GUEST_PIN);
	}
	else if(pass==FALSE)
	{
		SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
		GO_LOC(2,1);
		SEND_STRING("GUEST Rong Pass");
		GO_LOC(3,1);
	}
}

}

uint8 u8CheckPass(uint8 u8Mode_Add )
{
//uint8 Mode;
	uint8 pass_count=0;
	while (pass_count<4)
	{
		key_pressed=keyfind();
		pass[pass_count]=(key_pressed);
		SEND_DATE(key_pressed);
		_delay_ms(100);
		pass_count++;
	}
	uint8 EEPROM_Pass;
	uint8 i=0;
	while(i<4)
	{
		
		EEPROM_Pass = EEPROM_ui8ReadByteFromAddress(u8Mode_Add+i);
		if (EEPROM_Pass==(pass[i]-48))
		{
			i++;
			
		}
		else
		{
			pass_count=FALSE;
			break;
		}
		if(i==3)
		{
			pass_count=TRUE;
		}
	}	
	return pass_count;	
}	

uint8 u8EnterRoonConfig(char Key)
{
	
	switch (Key)
	{
	case ROOM1_CNFG:
		vShowState(ROOM1_STATUS,ROOM1_CNFG);
		key_pressed=keyfind();
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+ROOM1_OFFSET);	
		break;
	case ROOM2_CNFG:
		vShowState(ROOM2_STATUS,ROOM2_CNFG);
		key_pressed=keyfind();
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+ROOM2_OFFSET);
		break;	
	case ROOM3_CNFG:
		vShowState(ROOM3_STATUS,ROOM3_CNFG);
		key_pressed=keyfind();
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+ROOM3_OFFSET);
		break;
	case TV_CNFG:
		vShowState(TV_STATUS,TV_CNFG);
		key_pressed=keyfind();
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+TV_OFFSET);
		break;	
	case AIRCOND_CNFG:
		vShowState(AIR_COND,AIRCOND_CNFG);
		key_pressed=keyfind();
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+AIRCOND_OFFSET);
		break;			
		
	}
	
}

void vShowState(uint8 State,char Num)
{
	uint8 SPI_RESPONSE;	
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
	GO_LOC(2,1);
	if (Num==TV_CNFG)
	{
	SEND_STRING("TV:");
	SEND_STRING(" State:");		
	}
	if (Num==AIRCOND_CNFG)
	{
		SEND_STRING("AIR_COND:");
		SEND_STRING(" State:");
	}
	else
	{
	SEND_STRING("ROOM:");
	SEND_DATE(Num);
	SEND_STRING(" State:");
	}	
	SPI_ui8TransmitRecive(State);	
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
	if (Num==AIRCOND_CNFG)
	{
		GO_LOC(4,1);
		SEND_STRING("control temp:3");

	}
		
}	

void vTurnOnOf(char key,uint8 MESSAGE)
{	
	if (key==TURN_ON)
	{
		SPI_ui8TransmitRecive(MESSAGE);
	}
	else if(key_pressed==TURN_OFF)
	{
		SPI_ui8TransmitRecive(MESSAGE+1);
	}	
	
}	