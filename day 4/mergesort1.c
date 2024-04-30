#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < leftSize)
        arr[k++] = left[i++];

    while (j < rightSize)
        arr[k++] = right[j++];
}

void mergeSort(int arr[], int size) {
    if (size <= 1)
        return;

    int mid = size / 2;
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((size - mid) * sizeof(int));

    for (int i = 0; i < mid; i++)
        left[i] = arr[i];

    for (int i = mid; i < size; i++)
        right[i - mid] = arr[i];

    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);

    free(left);
    free(right);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    FILE *file;
    int arr[100], size = 0, number;
    double start,end;
    // Read numbers from the file
    file = fopen("num.txt", "r");
    if (file == NULL) {
        printf("File not found.\n");
        return 0;
    }

    while (fscanf(file, "%d", &number) != EOF) {
        arr[size] = number;
        size++;
    }

    fclose(file);
    start = omp_get_wtime();
    // Perform merge sort
    mergeSort(arr, size);

    end = omp_get_wtime();
    // Rewrite sorted numbers back to the file
    file = fopen("num.txt", "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 0;
    }

    for (int i = 0; i < size; i++)
        fprintf(file, "%d ", arr[i]);

    fclose(file);

    // Print the sorted array
    printf("Sorted Array:\n");
    printArray(arr, size);
    printf("Execution Time: %f seconds", end - start);
    return 0;
}
