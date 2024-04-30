#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main()
{
	int arr[10] = {2,3,8,1,7,6,4,5,9,0};
	printf("original array:\n");
	for(int i=0;i<10;i++){
		printf("%d",arr[i]);
		printf("\n");
	}
	quickSort(arr,0,9);

        printf("sorted array:\n");
        for(int i=0;i<10;i++){
                printf("%d",arr[i]);
		printf("\n");
        }
	return 0;
}
