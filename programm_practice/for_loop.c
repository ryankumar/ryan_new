/* 5 4 3 2 1 
   5 4 3 2 
   5 4 3 
   5 4 
   5 
*/


#include<stdio.h>
int main()
{
 int i,j,n;
scanf("\n%d",&n);

for(i=1 ;i<=n ; i++)
{
   for(j=n;j>=i;j--)
 printf("%d ",j);
 printf("\n");
}
}
