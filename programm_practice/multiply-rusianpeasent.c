/* multiplication if two numbers by russian peasent method.
  23 * 35 =705
  11   70+    divide 1st one number by 2 upto 1 n multiply another by 2 and sum of right hand side value for which LHS will be odd.
  5    140+      
  2    280
  1    560+   sum=560+140+70+35=705 
 */
#include<stdio.h>
int main()
{
int a,b,x,y,sum=0;
printf("enter the numbers");
scanf("%d%d",&a,&b);
x=a;
y=b;
while(a>=1)
{
if(a%2)
sum=sum+b;
a=a/2;
b=b*2;
}
printf("%d * %d = %d\n",x,y,sum);
}
  
