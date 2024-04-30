#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define MAX_SIZE 10000

int linear_search(int arr[],int n,int key){
	for(int i=0;i<n;i++){
		if(arr[i]==key){
			return i;
		}
	}
	return -1;
}

void bubble_sort(int arr[],int n){
	int temp;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

int binary_search(int arr[],int low,int high,int key){
	while(low<high){
		int mid=(low+high)/2;
		if(arr[mid]==key){
			return mid;
		}
		else if(arr[mid]<key){
			low=mid+1;
		}
		else{
			high=mid-1;
		}
	}
	return -1;
}

int main(){

	//opening num.txt file
	FILE *inputfile=fopen("num.txt","r");

	// Checking if file is open
	if(inputfile==NULL){
		perror("Error in file opening\n");
		return 1;
	}

	// Variables Declaration
	double linear_start,linear_end,binary_start,binary_end;
	int arr[MAX_SIZE],count,key;
	int linear_result,binary_result;


	// Taking input from the file
	count =0;
	while(fscanf(inputfile,"%d",&arr[count])==1){
		count++;
	}

	//Taking user input
	printf("Enter the number to be search : ");
	scanf("%d",&key);

	bubble_sort(arr,count);

	// Run the search program

	#pragma omp parallel
	{
	linear_start=omp_get_wtime();
	linear_result=linear_search(arr,count,key);
	linear_end=omp_get_wtime();

	binary_start=omp_get_wtime();
	binary_result=binary_search(arr,0,count-1,key);
	binary_end=omp_get_wtime();
	}

	// checking the return value
	if(linear_result==-1){
		printf("Key not found in linear\n");
	}
	else if(linear_result!=-1){
		printf("Key found in linear index : %d\n",linear_result);
	}
	if(binary_result==-1){
		printf("Key not found in binary\n");
	}
	else if(binary_result!=-1){
		printf("Key found in binary index : %d\n",binary_result);
	}

	// Execution time
	printf("Execution time for linear Search is : %f\n",linear_end-linear_start);
	printf("Execution time for binary Search is : %f\n",binary_end-binary_start);

	return 0;
}
