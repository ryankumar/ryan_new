#include<stdio.h>
#include<float.h>
#include<limits.h>
int main()
{
 printf("float max value:%e\n",FLT_MAX);
        printf("float min value:%e\n",FLT_MIN);

        printf("double max value:%le\n",DBL_MAX);
        printf("double min value:%le\n",DBL_MIN);

        printf("long double max:%Le\n",LDBL_MAX);
        printf("long double min:%Le\n",LDBL_MIN);

        printf("float radix value:%d\n",FLT_RADIX);

}
