/*
 * stand.h
 *
 * Created: 26/08/2018 02:34:13 م
 *  Author: Ali Abdelhady
 */ 


#ifndef STAND_H_
#define STAND_H_

		typedef unsigned char uint8;
		typedef signed char sint8;
		typedef unsigned short uint16;
		typedef signed short sint16;
		typedef unsigned long uint32;
		typedef signed long sint32;
		typedef unsigned long long uint64;
		typedef signed long long sint64;
		typedef float float32;
		typedef double float64;



	#define REGISTER_SIZE 8
	#define SET_BIT(reg,bit)    reg|=(1<<bit)
	#define CLR_BIT(reg,bit)    reg&=(~(1<<bit))
	#define TOG_BIT(reg,bit)    reg^=(1<<bit)
	#define Read_bIT(reg,bit)    (reg&(1<<bit))>>bit
	#define IS_BIT_SET(reg,bit)  (reg&(1<<bit))>>bit
	#define IS_BIT_CLR(reg,bit)  !((reg&(1<<bit))>>bit)
	#define ROR(reg,num)         reg=(reg<<(REGISTER_SIZE-num))|(reg>>(num))
	#define ROL(reg,num)        reg= (reg>>(REGISTER_SIZE-num))|(reg<<(num))



#endif /* STAND_H_ */