// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];
	for (i = 0; i < n1; i++) 
	{
		L[i] = arr[l + i]; 
	}
	for (j = 0; j < n2; j++) 
	{
		R[j] = arr[m + 1 + j]; 
	}
	
	i = 0; 
	j = 0;  
	k = l; 
	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else 
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 
	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 
 
void mergeSort(int arr[], int l, int r) 
{ 
	if (l < r) 
	{ 
		int m = l + (r - l) / 2;
		#pragma omp parallel sections
		{
			#pragma omp section  
			{
				mergeSort(arr, l, m); 
			}
			#pragma omp section
			{
				mergeSort(arr, m + 1, r); 
			}
		}
		merge(arr, l, m, r);
	} 
} 

void printArray(int A[], int size) 
{ 
	int i; 
	for (i = 0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
} 

int main() 
{ 
	float start = omp_get_wtime();
	FILE *myfile;
	myfile = fopen("num.txt", "r");
	int n = 20000;
	int arr[n],temp;
	
	if(myfile == NULL)
	{
		printf("File is n ot found\n!!");
		exit(0);
	}
	
	for(int i = 0; i < n; i++)
	{
		fscanf(myfile, "%d", &arr[i]);
	} 
	
	printf(" The array is: ");
	printArray(arr, sizeof(arr)/sizeof(arr[0])); 

	mergeSort(arr, 0, sizeof(arr)/sizeof(arr[0]) -1);

	printf("\nSorted array is: "); 
	printArray(arr, sizeof(arr)/sizeof(arr[0]));
	
	fclose(myfile);
	
	float end = omp_get_wtime();
	printf("\nTotal Execution time required is: %f", end - start);	
	return 0; 
}