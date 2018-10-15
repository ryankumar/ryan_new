#include<stdio.h>
int main()
{
int i,sum,term;
for(i=1,sum=0,term=1;i<=10;i++)
{
sum=sum+term;
term=term+i;
}
printf("%d ",sum);



}
