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


void vEnterFirstTime(void);
void SelectModePass(char Mode_Key);
uint8 u8CheckPass(uint8 u8Mode_Add );
uint8 u8EnterRoonConfig(char Key);
void vShowState(uint8 state,char Num);
void vTurnOnOf(char key,uint8 MESSAGE);
#endif /* MASTER_MAINFUN.C_H_ */