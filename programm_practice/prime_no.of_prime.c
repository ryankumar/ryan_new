//wap for finding the number of prime numbers in a number.ex:i/p 12745 o/p:3prime number

#include<stdio.h>
int main()
{

int n,flag, c=0,i,rem,a=0;
printf("enter the number");
scanf("%d",&n);
       while(n>0)
       {
	   rem=n%10;
	 i=2;
       flag=1; 
   	  while(rem==1) 
	  {
	    flag=0;
	    break;
	  }
	   while(i<rem)
		{
		if(rem%i==0)
		flag=0;
		i++;
		}
	    if(flag==0)
		a=1;
		else 
	        c++;
	       n=n/10;
       	    
	}


	
	printf("%d\n",c);
}
