#include<stdio.h>
int main()
{
int d,m,y,flag=1,leap=0;
printf("enter the dd-mm-yy:");
scanf("%d%d%d",&d,&m,&y);
     if((y%4==0 && y%100!=0) || y%400==0)
         leap=1;
		if(y>2020 || y<2000)
         	   flag=0;
		else
    		if(m<1 || m>12)
		   flag=0;
		else		
		if(d<1)
	             flag=0;
 				    	
	else if(m==2)
	{
	   if(d>28)
		flag=0;
 	if(d==29 && leap)
	flag= 1;
         }
 	    else if(m==4 || m==6 || m==9 || m==11)
	     {
	       if(d>30)	
		flag= 0;
	     }
	else if(d>31)
	       flag=0;
	
  if(flag==0)	
     	printf("not valid date");

   else
	printf("date is valid:%d.%d.%d",d,m,y);
return 0;
}
