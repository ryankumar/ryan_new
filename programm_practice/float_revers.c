#include<stdio.h>
#include<float.h>
int main()
{
 double n,rev=0;

  int c=0,c1=0,m,c2=0;
 printf("enter the number:");
 scanf("%lf",&n);
 while(n!=(int)n)
  {
    n=n*10;
    c++;
  }
       m=n;
  	while(m>0)
	{
	  rev=rev*10+m%10;
	   c1++;
	  m/=10;
	}
	    while(c2!=c1-c)
	    {
 	      rev/=10;
	        c2++;
	    }
       printf("reverse number is:%lf\n",rev);
return 0;
}
      
