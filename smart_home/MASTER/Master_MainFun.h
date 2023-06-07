/*
 * Master_MainFun.h
 *
 * Created: 28/05/2023 02:51:11 ص
 *  Author: mkora
 */ 


#ifndef MASTER_MAINFUN.C_H_
#define MASTER_MAINFUN.C_H_


#include <avr/io.h>
#include "keypad.h"
#include "lcd.h"
#include "EEPROM.h"
#include "STD_MESSAGES.h"
#include "smart_home_cofig.h"

typedef struct{
	char *ptr_mode;
	uint8 mode;
	uint16 PASS_ADD;
	uint8 *MODE_LED_PORT;
	uint8 MODE_LED_PIN;
	
	}struct_modecnf;
void vEnterFirstTime(void);
void SelectModePass(struct_modecnf *ps);
uint8 u8CheckPass(uint8 u8Mode_Add );
uint8 u8EnterRoonConfig(char Key);
void vShowState(uint8 state,char Num);
void vTurnOnOf(char key,uint8 MESSAGE);
void vSetTempMenue(void);
#endif /* MASTER_MAINFUN.C_H_ */