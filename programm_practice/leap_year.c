#include<stdio.h>
int main()
{
 int yr;
printf("enter the year:");
scanf("%d",&yr);
if((yr%4==0 && yr%100!=0) || (yr%400==0))
printf("this is a leap year\n");
else
printf("this is not a leap year\n");
return 0;


}
