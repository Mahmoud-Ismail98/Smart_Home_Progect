/*
 * TIMER0.h
 *
 * Created: 18/03/2020 11:18:45 م
 *  Author: MIK-PC
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "stand.h"


/*
	Function Name        : timer0_initializeCTC
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize and start the timer0 for compare match.
*/
void timer0_initializeCTC(void);

/*
	Function Name        : timer0_stop
	Function Returns     : void
	Function Arguments   : void
	Function Description : Stop timer0.
*/
void timer0_stop(void);

/*
	Function Name        : timer_initializefastpwm
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize timer0 for FastPWM mode.
*/
void timer_initializefastpwm(void);

/*
	Function Name        : LCD_vInit
	Function Returns     : void
	Function Arguments   : float64 duty
	Function Description : Set duty cycle to the given duty percentage.
*/
void change_dutycycle(float64 duty);



#endif /* TIMER0_H_ */