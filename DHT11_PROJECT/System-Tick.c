#include"Origin.h"
#define ms 50000
#define us 50
void Systick_Delay_ms(int n) //  milliseconds delay
		 {
			   NVIC_ST_CTRL_R &=~(0x03);
		      NVIC_ST_CTRL_R |=0x04;
			    NVIC_ST_CURRENT_R=0;
		      NVIC_ST_RELOAD_R=(ms*n); 
			    NVIC_ST_CTRL_R |=0X01;
			  while( (NVIC_ST_CTRL_R & 0x00010000)==0)
					{ ;
				      }	 
		 }
		 void Systick_Delay_us(int n) //Microseconds delay
		 {
			    NVIC_ST_CTRL_R &=~(0x03);
		      NVIC_ST_CTRL_R |=0x04;
			    NVIC_ST_CURRENT_R=0;
		      NVIC_ST_RELOAD_R=(us*n);
          NVIC_ST_CTRL_R |=0X01;			 
			  while( (NVIC_ST_CTRL_R & 0x00010000)==0)
					{ ;
				      }	 
			}
		 		