#include<stdio.h>
int main()
{
	int a,b,mul=0;
	scanf("%d%d",&a,&b);
	while(b>0)
	{
		if(b & 0x01)
			mul=mul+a;
		a=a<<1;
		b=b>>1;
	}
	printf("%d\n",mul);

}
