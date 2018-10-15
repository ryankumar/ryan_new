#include<stdio.h>
#include<stdlib.h>

int main()
{
	int r,c,tr,tc,Rr=0,Rc=0;
	int i,j,k,l,m,n,sum=0,sum1=0;
	int rem1,rem2,rem3,rem4;
	printf("Enter the number of row and column \n");
	scanf("%d%d",&m,&n);
	r=m;
	c=n;
	 int **ptr1=(int **) malloc(m * sizeof(int *));
	 for(i=0;i<m;i++)
                    ptr1[i]=(int *) malloc(n * sizeof(int));
	 
	printf("enter elements for m * n  matrix:\n");
	  for(i=0;i<m;i++)
	  {
		  for(j=0;j<n;j++)
		  {
			  scanf("%d",&ptr1[i][j]);
		  }
	  }

	tr= r%3;
	tc= c%3;
	
	if(tr!=0)
	{
		Rr=(3-tr);
		r +=Rr;
	}
	if(tc!=0)
	{
		Rc=3-tc;
		c +=Rc;
	}	
	
	int **ptr=(int **) malloc(r * sizeof(int *));
	for(i=0;i<r;i++)
		ptr[i]=(int *) malloc(c * sizeof(int));

	
 	for(i=0;i<r;i++)
	{
	   
		for(j=0;j<c;j++)

		{
			if(tr!=0 && tc==0)
			{
				rem1= r-Rr;
				if(i<rem1)
					ptr[i][j]=ptr1[i][j];
				else
					ptr[i][j]=1;
			}
			else if(tr==0 && tc!=0)
			{
				rem2=c-Rc;
				if(j<rem2)
					ptr[i][j]=ptr1[i][j];
				else
					ptr[i][j]=1;
			}


			else if(tr!=0 && tc!=0)
			{
				rem3=r-Rr;
				rem4=c-Rc;
				if(i<rem3 && j<rem4)
					ptr[i][j]=ptr1[i][j];
				else if(i>=rem3 || j>=rem4)
					ptr[i][j]=1;
			}
				

	        }
	}

	printf("\n*******************entered matrix***************************\n");
		
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%d  ",ptr[i][j]);
		}
		printf("\n");
	}

	printf("\n************matrixes in 3*3 format*****************\n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%d\t", ptr[i][j]);
			
			if((j+1)%3==0 && (j+1)<c)
				printf("\t\t");
		}
		
		if((i+1)%3==0)
		{
			printf("\n\n");
		}
		else
			printf("\n");
	}
	
	printf("\n*************sum of diagonal is M * N matrix is ***************\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j || (j==n-(i+1)))
				sum=sum+ptr1[i][j];
			 
		}
	}
	printf("sum :%d\n",sum);
	
	printf("\n****************** sum of 3*3 matrices *******************\n");
	for(i=0;i<r; )
	{
		for(j=0;j<c; )
		{
			for(k=i;k<(3+i);k++)
			{
				for(l=j;l<(3+j);l++)
				{
					sum1=sum1+ptr[k][l];
				}
			}
			printf("sum of 1st matrix is :%d\n ",sum1);
			sum1=0;
			j=j+3;
		}
	       i=i+3;
	}

	for(i=0;i<m;i++)
	free(ptr1[i]);
	free(ptr1);
	
	for(i=0;i<r;i++)
	free(ptr[i]);
	free(ptr);	
	return 0;


}


