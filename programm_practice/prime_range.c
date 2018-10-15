//finding the prime numbers from a range of numbers.

#include<stdio.h>
int main()
{
int m=2,n,i,a=1;
printf("enter the ending numbers");
scanf("%d",&n);
	while(m<n)
	{
	     i=2;   
	 	while(i<m)
		{
		  if(m%i==0)
		    a=0; // 'a' takes as a temp. variable for not prime number
		  i++;
		}

	      
       	    if(a!=0)
		printf("prime numbers are:%d\n",m);
	m++;
	a=1;	
	
	}

return 0;
}
