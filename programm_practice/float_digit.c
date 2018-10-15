#include<stdio.h>
int main()
{
double n;
int c=0;
long int x;
printf("enter the float value:");
scanf("%lf",&n);

while(n!=(int)n)
{
n=n*10;

}
printf("%lf\n",n);

x=(long int)n;
while(x>0)
{
x=x/10;
c++;
}
printf("%d\n",c);
}
