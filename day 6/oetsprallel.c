#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void oddEvenTranspositionSort(int arr[], int n) {
    int sorted = 0;

    while (!sorted) {
        sorted = 1;

        // Odd phase
        #pragma omp parallel for shared(arr, n)
        for (int i = 1; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                sorted = 0;
            }
        }

        // Even phase
        #pragma omp parallel for shared(arr, n)
        for (int i = 0; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                sorted = 0;
            }
        }
    }
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    double start_time = omp_get_wtime();
    oddEvenTranspositionSort(arr, n);
    double end_time = omp_get_wtime();

    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nParallel Execution Time: %f seconds\n", end_time - start_time);

    return 0;
}