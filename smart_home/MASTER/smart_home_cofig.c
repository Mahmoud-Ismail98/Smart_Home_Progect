/*
 * smart_home_cofig.c
 *
 * Created: 15/03/2020 02:28:02 م
 *  Author: MIK-PC
 */ 
#include "smart_home_cofig.h"

uint8_t Arr_Time[4]={0,0,0,0};
static uint8_t t=0;   //why static
volatile uint16_t Num_Total_Sec;
volatile char Date;   //to recieve date from keypad fun keyfind()

volatile uint8_t finish=1; 

volatile  uint8_t flag=1;
volatile  uint8_t flag2=0;
void Device_Drive(void)
{
	//define inputs
/*	DDRC &=(~(1<<Door_Sen));
	DDRC &=(~(1<<Weight_Sen));
	DDRC &=(~(1<<Cancal_Sw));
	//define output
	DDRC|=(1<<Motor);
	DDRC|=(1<<Heater);
	DDRC|=(1<<Lamp);
	DDRC|=(1<<Buz);*/
}


void Starting_Program(void)
{ 
	
	Device_Drive();
	Start_Message();
	Timer0_Intialization();
}

void Start_Message(void)
{   
	LCD_INISTIALIZATION();
	//GO_LOC(2,1);
	SEND_STRING("wellcome to smart");
	_delay_ms(500);
	GO_LOC(2,3);
	SEND_STRING("home system");
	//_delay_ms(3000);
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
	
	////////////////////////////	

}

void Reset_time(void)
{  
	t=0;
	 Buzzer_On;
  _delay_ms(200);
  Buzzer_Off;
	GO_LOC(2,3);
	SEND_STRING("timer canseled");
    _delay_ms(500);
	SEND_COMND(0x01); //clear lcd and curser goto loc(1.1) automatically
	SEND_STRING("timer");
	//GO_LOC(1,6);
	SEND_STRING(" 00:00 ");
	Arr_Time[0]=0;
	Arr_Time[1]=0;
	Arr_Time[2]=0;
	Arr_Time[3]=0;
	GO_LOC(1,7);
}

void Remaning_Time(void)
{
	      
		         Arr_Time[0]=(Num_Total_Sec/600);  
				 Arr_Time[1]=((Num_Total_Sec % 600)/60); 
				 Arr_Time[2]=((((Num_Total_Sec % 600)%60)/10));  
				 Arr_Time[3]=(((Num_Total_Sec % 600)%60)%10);
				      GO_LOC(2,7);    
			      SEND_DATE(Arr_Time[0]+48);
				  SEND_DATE(Arr_Time[1]+48);
				  SEND_DATE(':');
				  SEND_DATE(Arr_Time[2]+48);
				  SEND_DATE(Arr_Time[3]+48);
}
void MIcrowave_Finish_task(void)
{
	              cli();   //mask all interupt globaally
				  TCCR0=0x00;
				  flag=0;
			    GO_LOC(2,1);
			    SEND_STRING("      ");	   
		       SEND_STRING("00:00 ");
				 Stop_Output();
				  Buzzer_On;
				  _delay_ms(300);
				  Buzzer_Off;
				  SEND_COMND(0x01);
               	GO_LOC(3,1);
			    SEND_STRING("welldone");
					for (int j=0;j<=5;j++)
               	{
		          SEND_COMND(0x1C);
	             	_delay_ms(30); 
             	}
				
}

ISR(TIMER0_OVF_vect)
{
	TCNT0=165;
     Num_Total_Sec--;
	if (Num_Total_Sec !=0)
	{
		 Remaning_Time();
	}
	else
	{
		MIcrowave_Finish_task();
	}
	
}