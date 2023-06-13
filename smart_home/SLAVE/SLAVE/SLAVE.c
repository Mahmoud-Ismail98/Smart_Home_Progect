/*
 * SLAVE.c
 *
 * Created: 26/05/2023 12:38:00 ص
 *  Author: mkora
 */ 


#include <avr/io.h>
#include "SPI.h"
#include "STD_MESSAGES.h"
#include "GPIO.h"
#include "LED.h"
#include "ADC_driver.h"
#include "TIMER0.h"
#include "SLAVE_CONFIG.h"



	
uint8 SPI_RESPONSE;
volatile uint8 counter=0;
volatile uint8 required_temperature=24;  //default temp
volatile uint16	Temp_SensRead=0;
//uint8 AIR_COND_POS=OFF_STATUS;
int main(void)
{
	ADC_vinit();//initialize the ADC of the micro controller
//	timer0_initializeCTC();//Initialize the timer zero of the micro controller
	SPI_vInitSlave();//initialize the SPI as a slave
	

	LED_vInit(ROOM1_PORT,ROOM1_PIN);
	LED_vInit(ROOM2_PORT,ROOM2_PIN);
	LED_vInit(ROOM3_PORT,ROOM3_PIN);
	LED_vInit(TV_PORT,TV_PIN);
	LED_vInit(AIR_COND_PORT,AIR_COND_PIN);

		
    while(1)
    {
		SPI_RESPONSE=SPI_ui8TransmitRecive(DEFAULT_ACK);
		switch (SPI_RESPONSE)
		{
		case ROOM1_STATUS:
		if (LED_u8ReadStatus(ROOM1_PORT,ROOM1_PIN)==0)//if the led turned off
		{
			SPI_RESPONSE=OFF_STATUS;  
		} 
		else if(LED_u8ReadStatus(ROOM1_PORT,ROOM1_PIN)==1)//IF THE LED TURNED ON
		{
			SPI_RESPONSE=ON_STATUS;
		}		
		
		SPI_ui8TransmitRecive(SPI_RESPONSE);	
			break;
			
		case ROOM2_STATUS:
		if (LED_u8ReadStatus(ROOM2_PORT,ROOM2_PIN)==0)//if the led turned off
		{
			SPI_RESPONSE=OFF_STATUS;
		}
		else if(LED_u8ReadStatus(ROOM2_PORT,ROOM2_PIN)==1)//IF THE LED TURNED ON
		{
			SPI_RESPONSE=ON_STATUS;
		}
		
		SPI_ui8TransmitRecive(SPI_RESPONSE);
		break;	
		
		case ROOM3_STATUS:
		if (LED_u8ReadStatus(ROOM3_PORT,ROOM3_PIN)==0)//if the led turned off
		{
			SPI_RESPONSE=OFF_STATUS;
		}
		else if(LED_u8ReadStatus(ROOM3_PORT,ROOM3_PIN)==1)//IF THE LED TURNED ON
		{
			SPI_RESPONSE=ON_STATUS;
		}
		
		SPI_ui8TransmitRecive(SPI_RESPONSE);
		break;	
		case AIR_COND_STATUS:
		if (LED_u8ReadStatus(AIR_COND_PORT,AIR_COND_PIN)==0)//if the led is turned off
		{
			SPI_RESPONSE = OFF_STATUS;//set the response as off status
		}
		else if (LED_u8ReadStatus(AIR_COND_PORT,AIR_COND_PIN)==1)//if the led is turned on
		{
			SPI_RESPONSE = ON_STATUS;//set the response as on status
		}
		SPI_ui8TransmitRecive(SPI_RESPONSE);//response to the transmitter with the status
		break;
		case TEMP_STATUS:

			SPI_RESPONSE = required_temperature;
			SPI_ui8TransmitRecive(SPI_RESPONSE);//response to the transmitter with the status
		break;
		case TV_STATUS:
		if (LED_u8ReadStatus(TV_PORT,TV_PIN)==0)//if the led is turned off
		{
			SPI_RESPONSE = OFF_STATUS;//set the response as off status
		}
		else if (LED_u8ReadStatus(TV_PORT,TV_PIN)==1)//if the led is turned on
		{
			SPI_RESPONSE = ON_STATUS;//set the response as on status
		}
		SPI_ui8TransmitRecive(SPI_RESPONSE);//response to the transmitter with the status
		break;//break the switch case
			
		/*********************************   TURN ON COMMANDS ********************************/
		case ROOM1_TURN_ON:
		LED_vTurnOn(ROOM1_PORT,ROOM1_PIN);//turn on the led of room 1
		break;//break the switch case
		case ROOM2_TURN_ON:
		LED_vTurnOn(ROOM1_PORT,ROOM2_PIN);//turn on the led of room 2
		break;//break the switch case
		case ROOM3_TURN_ON:
		LED_vTurnOn(ROOM3_PORT,ROOM3_PIN);//turn on the led of room 3
		break;//break the switch case
		case AIR_COND_TURN_ON:
		timer0_initializeCTC();		
		//LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);//turn on the led of air conditioning
		break;//break the switch case
		case TV_TURN_ON:
		LED_vTurnOn(TV_PORT,TV_PIN);//turn on the led of the TV
		break;//break the switch case
			
		/*********************************   TURN OFF COMMANDS ********************************/
		case ROOM1_TURN_OFF:
		LED_vTurnOff(ROOM1_PORT,ROOM1_PIN);//turn off the led of room 1
		break;//break the switch case
		case ROOM2_TURN_OFF:
		LED_vTurnOff(ROOM2_PORT,ROOM2_PIN);//turn off the led of room 2
		break;//break the switch case
		case ROOM3_TURN_OFF:
		LED_vTurnOff(ROOM3_PORT,ROOM3_PIN);//turn off the led of room 3
		break;//break the switch case
		case AIR_COND_TURN_OFF:
		timer0_stop();
		LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);//turn off the led of air conditioning
		break;//break the switch case
		case TV_TURN_OFF:
		LED_vTurnOff(TV_PORT,TV_PIN);//turn off the led of the TV
		break;//break the switch case
		
		/*********************************   Set temperature   ********************************/
		case SET_TEMPERATURE:
		required_temperature = SPI_ui8TransmitRecive(DEFAULT_ACK);//get the temperature from the master and store the temperature in required temperature
		break;//break the switch case		
		
		
        //TODO:: Please write your application code 
		 }
	  }
}

ISR(TIMER0_COMP_vect)
{
	counter++;//count the ticks of the timer zero
	if(counter>=10)//do that code every 10 ticks
	{	
		counter=0;
	Temp_SensRead =(0.25*ADC_u16Read());
	if (Temp_SensRead<required_temperature)
	{
		LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);
	}
	else if (Temp_SensRead>required_temperature)
	{
		LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);
	}
	}	
}