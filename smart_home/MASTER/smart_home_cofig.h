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

#define ALLWED_TRIES  (uint8)1
#define NO_MODE 0
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

#define OWNER_LED_PORT PORTC_OUTPUTREG_ADDRESS
#define GUEST_LED_PORT PORTC_OUTPUTREG_ADDRESS
#define BLOCK_BUZ_PORT PORTC_OUTPUTREG_ADDRESS//(uint8)PORTC//(uint8)'C'

#define  OWNER_PIN		(uint8)0
#define  GUEST_PIN		(uint8)1
#define BLOCK_BUZ_PIN	(uint8)2
#define  ROOM1 (uint8)2
#define  ROOM2 (uint8)3
#define  ROOM3 (uint8)4
#define  TV (uint8)5
#define  AIR_COND (uint8)6

#define Login_status (uint16)0x20
#define ADMIN_PASS_ADD (uint16)0x21
#define Guest_PASS_ADD (uint16)0x25



#endif ///* SMART_HOME_COFIG_H_ */