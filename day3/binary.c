#include<omp.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
void swap(int *a,int*b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}
void bubblesort(int arr[],int n)
{
	bool swapped;
	for(int i=0;i<n-1;i++)
	{
		swapped=false;
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				swap(&arr[j],&arr[j+1]);
				swapped=true;
			}
		}
		if(swapped==false)
		{
			break;
		}
	}
}
bool binary(int arr[],int high,int low,int key)
{
	while(low<=high)
	{
		int mid=low+(high-low)/2;
		if(arr[mid]==key)
		{
			return true;
		}	
		if(arr[mid]<key)
		{
			low=mid+1;
		}
		else
		{
			high=mid-1;	
		}
	}
	return false;
}
int main()
{
	double start,end;
	int arr[10000],key;
	FILE *file=fopen("numbers.txt","r");
	for(int i=0;i<10000;i++)
	{
		fscanf(file,"%d",&arr[i]);
	}
	fclose(file);
	printf("enter the number to search:");
	scanf("%d",&key);
	bubblesort(arr,10000);
	start= omp_get_wtime();
	bool test=binary(arr,10000,0,key);
	if(test==true)
		printf("number found.\n");
	else
		printf("number not found.\n");
	end= omp_get_wtime();
	printf("\nexecution time: %f\n",end-start);	
}
