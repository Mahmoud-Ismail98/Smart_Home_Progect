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

	#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
	#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))
	#define TOGEL_BIT(REG,BIT) (REG^=(1<<BIT))
	#define IS_BIT_SET(REG,BIT) (REG&(1<<BIT))
	#define IS_BIT_CLEAR(REG,BIT) (!(REG&(1<<BIT)))	



#endif /* STAND_H_ */