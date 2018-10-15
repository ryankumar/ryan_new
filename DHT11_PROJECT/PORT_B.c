#include"Origin.h"
void portB_init(void)
	 {
           SYSCTL_RCGCGPIO|=(0x1<<1);
				    while(1)
						{
							if((SYSCTL_PRGPIO&0x02)!=0)
								    break;
						}
						GPIO_PORTB_PCTL_R &=~0x0f0;
						GPIO_PORTB_DEN_R |=0x010;
						GPIO_PORTB_AFSEL_R &=~(0x010);
						GPIO_PORTB_AMSEL_R &=~(0x010);	
						//GPIO_PORTB_PUR_R |=0x010;
						GPIO_PORTB_DATA_R |= 0x010;
					  GPIO_PORTB_DIR_R |=0x010;		
		}
	 
		
						