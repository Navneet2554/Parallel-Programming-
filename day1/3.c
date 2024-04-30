#include<stdio.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-1; j++) {
			if (arr[j] < arr[j+1]) {
				swap(&arr[j], &arr[j +1]);
			}
		}
	}
}

int main() {
	FILE *file = fopen("numbers.txt", "r");
	if (file == NULL) {
		printf("Error opening the file.\n");
		return 1;
	}

	int n = 10000;
	int numbers[n];

	for(int i = 0; i < n; i++) {
		fscanf(file, "%d", &numbers[i]);
	}
	fclose(file);

	bubbleSort(numbers, n);

	for(int i =0; i<n; i++){
		printf(" %d ", numbers[i]);
	}

	return 0;
}

