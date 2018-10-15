// 1 2 4 7 11 16 23 31 ...
#include<stdio.h>
int main()
 {
int i,sum=1,n,total=0;
printf("enter the number:");
scanf("%d",&n);
for(i=0;i<n;i++)
 {
   sum=sum+i;
   total=total+sum;
   printf("%d ",sum);
 }

 printf("%d\n",total);
 }
 
