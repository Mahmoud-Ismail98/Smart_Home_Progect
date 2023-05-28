/*
 * smart_home_cofig.h
 *
 * Created: 24/05/2023 02:46:51 م
 *  Author: mkora
 */ 


#ifndef SMART_HOME_COFIG_H_
#define SMART_HOME_COFIG_H_


#define F_CPU 1000000U
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "microconf.h"
#include <avr/interrupt.h>
#include "lcd.h"
#include "keypad.h"
#include "TIMER0.h"
#include "SPI.h"

#define TRUE  1
#define FALSE 0

#define TURN_ON	'1'
#define TURN_OFF '2'
#define RET '0'

#define	OWNER_MODE 1
#define	GUEST_MODE 2
#define	BLOCK_MODE 3

#define	ROOM1_CNFG '1'
#define	ROOM2_CNFG '2'
#define	ROOM3_CNFG '3'
#define TV_CNFG '4'
#define AIRCOND_CNFG '5'

#define	ROOM1_OFFSET	0x01
#define	ROOM2_OFFSET	0x03
#define	ROOM3_OFFSET	0x05
#define TV_OFFSET		0x07
#define AIRCOND_OFFSET  0x09

#define  OWNER_PIN 0
#define  GUEST_PIN 1
#define  ROOM1 (uint8)2
#define  ROOM2 (uint8)3
#define  ROOM3 (uint8)4
#define  TV (uint8)5
#define  AIR_COND (uint8)6

#define Login_status (uint16)0x20
#define ADMIN_PASS_ADD (uint16)0x21
#define Guest_PASS_ADD (uint16)0x25



//////////////////
//define INPUT
#define  Door_Sen      PINC0
#define  Weight_Sen    PINC1
#define  Cancal_Sw     PINC2
//define OUTPUT
#define  Motor         PINC3
#define  Heater        PINC4
#define  Lamp          PINC5
#define  Buz           PINC6


#define Buzzer_On    PORTC |=(1<<Buz)
#define Buzzer_Off   PORTC &=(~(1<<Buz))

void Turn_Buz(void);
void Starting_Program(void);
void Device_Drive(void);
void Turn_Output(void);
void Stop_Output(void);
void Start_Message(void);
void Create_Timing(void);
//void Entering_Time(uint8_t num_as_char);
uint8_t Sensors_Read(void);
void Remaning_Time(void);
void Cancling_Mode(void);
void Turn_Fan(void);
void close_Fan(void);

void Entering_Time(void);

void Reset_time(void);
void MIcrowave_Finish_task(void);
#endif /* SMART_HOME_COFIG_H_ */