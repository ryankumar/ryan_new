#include<stdio.h>
int armstrong(int);
 int main()
  {
    int arm,i,c=0;
	for(i=100;i<=999;i++)
	 {
          arm= armstrong(i);
	    if(arm==i)
              {
		printf("armstrong number is : %d\n",arm);
		 c++;
	      }
	    
          }	    
	printf("number of armstrng is:%d ",c);
     return 0;
  }
   int armstrong(int i)
      {
	int power(int,int);
	int sum=0,rem;
	while(i>0)
	 {
	   rem=i%10;
	   sum+=power(rem,3);
	   i/=10;
         }
	return sum;
     }
 int power(int r,int x)
    {
       return r*r*r;
    }
