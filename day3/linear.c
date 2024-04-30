#include<omp.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

bool linear(int arr[],int n,int x)
{
	for(int i=0;i<n;i++)
	{
		if(arr[i]==x)
		{
			return true;
		}
	}
	return false;
}
int main()
{
	double start,end;
	int arr[10000],x;
	FILE *file=fopen("numbers.txt","r");
	for(int i=0;i<10000;i++)
	{
		fscanf(file,"%d",&arr[i]);
	}
	fclose(file);
	printf("enter the number to search:");
	scanf("%d",&x);
	start= omp_get_wtime();
	bool test=linear(arr,10000,x);
	if(test==true)
		printf("number found.\n");
	else
		printf("number not found.\n");
	end= omp_get_wtime();
	printf("\nexecution time: %f\n",end-start);	
}
