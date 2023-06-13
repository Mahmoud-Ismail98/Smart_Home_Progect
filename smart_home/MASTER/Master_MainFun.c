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
uint8 temp[2];
uint8 Temp_Value;						
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
				_delay_ms(100);
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

void SelectModePass(struct_modecnf *ps)
{
	uint8 Wrong_Tries=0;
	int pass;
	while (Wrong_Tries < ALLWED_TRIES)
	{
		SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
		GO_LOC(2,5);
		SEND_STRING(ps->ptr_mode);
		SEND_STRING(" MODE");
		GO_LOC(3,1);
		SEND_STRING("Enter Pass:");
		_delay_ms(100);
		pass = u8CheckPass(ps->PASS_ADD);
		if (pass==TRUE)
		{
			Mode=ps->mode;
			DDRC|=(1<<ps->MODE_LED_PIN);
			PORTC|=(1<<ps->MODE_LED_PIN);
			break;
		}
		else if(pass==FALSE)
		{
			Wrong_Tries++;
			SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
			GO_LOC(2,4);
			//SEND_STRING(ps->mode);
			SEND_STRING("Rong Pass");
			GO_LOC(3,4);
			SEND_STRING("TRY Again");
			_delay_ms(200);
		}
	}
	if (Wrong_Tries>=ALLWED_TRIES)
	{
		DDRC|=(1<<BLOCK_BUZ_PIN);
		PORTC |=(1<<BLOCK_BUZ_PIN);
		//PORTC|=(1<<3);
		SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
		GO_LOC(2,4);
		Wrong_Tries=0;
		SEND_STRING("blocked mode");
		GO_LOC(3,4);
		SEND_STRING("wait 20 sec");
		_delay_ms(3000);
	    PORTC&=(~(1<<BLOCK_BUZ_PIN));
	    _delay_ms(7000);
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
		_delay_ms(300);
		GO_LOC(3,12+pass_count);
		SEND_DATE('*');
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
		if (key_pressed==RET) break;				
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+ROOM1_OFFSET);	
		break;
	case ROOM2_CNFG:	
		vShowState(ROOM2_STATUS,ROOM2_CNFG);
		key_pressed=keyfind();
		if (key_pressed==RET) break;			
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+ROOM2_OFFSET);
		break;	
	case ROOM3_CNFG:
		vShowState(ROOM3_STATUS,ROOM3_CNFG);
		key_pressed=keyfind();
		if (key_pressed==RET) break;			
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+ROOM3_OFFSET);
		break;
	case TV_CNFG:
		vShowState(TV_STATUS,TV_CNFG);
		key_pressed=keyfind();
		if (key_pressed==RET) break;			
		vTurnOnOf(key_pressed,OFFSET_MESSAGE+TV_OFFSET);
		break;	
	case AIRCOND_CNFG:
		vShowState(AIR_COND_STATUS,AIRCOND_CNFG);
		key_pressed=keyfind();
		if (key_pressed==RET) break;	
		if (key_pressed=='3')  //entering control temperture of air conditioning
		{
			vSetTempMenue();
		} 
		else
		{
		   vTurnOnOf(key_pressed,OFFSET_MESSAGE+AIRCOND_OFFSET);
		}
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
	else if (Num==AIRCOND_CNFG)
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

	SPI_ui8TransmitRecive(State);	//demand the status from the slave
	_delay_ms(100);//Halt the system for the given time in (ms)	
	SPI_RESPONSE = SPI_ui8TransmitRecive(DEMAND_RESPONSE);	
	if(SPI_RESPONSE == ON_STATUS)//if the response from the slave was on status
	{
		SEND_STRING("ON");//print the status on
	}
	else if(SPI_RESPONSE == OFF_STATUS)//if the response from the slave was off status
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

void vSetTempMenue(void)
{
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically	
	SPI_ui8TransmitRecive(TEMP_STATUS);	//demand the status from the slave
	_delay_ms(100);//Halt the system for the given time in (ms)	
	//uint8 temp[2];
	//uint8 Temp_Value;
	Temp_Value = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
	temp[0]=Temp_Value/10;
	temp[1]=Temp_Value%10;	
	GO_LOC(2,1);	
	SEND_STRING("old required temp:");
	SEND_DATE(temp[0]+48);
	SEND_DATE(temp[1]+48);		
	Temp_Value=0;
	temp[0]=0;
	temp[1]=0;
	GO_LOC(3,1);
	SEND_STRING("enter new temp:");
	key_pressed=keyfind();
	temp[0]=key_pressed-48;
	SEND_DATE(key_pressed);
	_delay_ms(200);
	key_pressed=keyfind();
	temp[1]=key_pressed-48;
	SEND_DATE(key_pressed);
	_delay_ms(200);
	SPI_ui8TransmitRecive(SET_TEMPERATURE);//Send the code of set temperature
	_delay_ms(200);//Halt the system to prevent write collision
	Temp_Value=temp[0]*10+temp[1];
	SPI_ui8TransmitRecive(Temp_Value);//send the entered temperature
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically//
	SEND_STRING("Temperature Sent");//show the message
	_delay_ms(500);//Halt the system for the given time in (ms)
}