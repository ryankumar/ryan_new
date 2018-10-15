#include"Origin.h"
int a[40]={0},i,x=0;;
int main()
{
	PLL_init();
    portB_init();
	  
	    for(i=1;i<=4;i++)        //wait 1 "second"
        Systick_Delay_ms(250);
	           GPIO_PORTB_DATA_R &= ~0x010;
	             Systick_Delay_ms(18);    //send low for 18ms
	             GPIO_PORTB_DIR_R&=~0x010; // input
	               while((GPIO_PORTB_DATA_R &0x010)!=0);
	             Systick_Delay_us(170); // response and peripheral ready time
	         						
								for(i=0;i<40;i++)
								{
								Systick_Delay_us(54);   //54 us
								Systick_Delay_us(25);  // 26 to 28 us run
							  if( (GPIO_PORTB_DATA_R & 0x010) !=0)
								    {
											 a[i]=0x01;  // x |=1<<i;
										// if delay is 70us then bit is one 
											   Systick_Delay_us(45);   // 40us delay
											    continue;
										}
										a[i]=0x00;
										//x|=0<<i;
										//Systick_Delay_us(5);
						 }
								
											Systick_Delay_us(5);

}

											  
                      									


