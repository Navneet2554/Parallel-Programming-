#include <stdio.h>
#include <omp.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortParallel(int arr[], int low, int high) {
    if (low < high) {
        int pi;

        #pragma omp parallel
        {
            #pragma omp single
            pi = partition(arr, low, high);

            #pragma omp task
            quickSortParallel(arr, low, pi - 1);

            #pragma omp task
            quickSortParallel(arr, pi + 1, high);
        }
    }
}

void quickSortSerial(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSortSerial(arr, low, pi - 1);
        quickSortSerial(arr, pi + 1, high);
    }
}

int main() {
    int sizes[] = {10, 100, 1000, 4000, 8000};

    for (int k = 0; k < sizeof(sizes)/sizeof(int); k++) {
        int size = sizes[k];
        int arr[size];
        int arrParallel[size];

        // Initialize your array with data
        FILE *fp, *fp1;
        fp = fopen("number.txt", "r");
        fp1 = fopen("number.txt", "r");
        for (int i = 0; i < size; i++) {
            fscanf(fp, "%d\t", &arr[i]);
            fscanf(fp1, "%d\t", &arrParallel[i]);
        }

        // Serial quicksort
        double startSerial = omp_get_wtime();
        quickSortSerial(arr, 0, size - 1);
        double endSerial = omp_get_wtime();

        // Parallel quicksort
        double startParallel = omp_get_wtime();
        quickSortParallel(arrParallel, 0, size - 1);
        double endParallel = omp_get_wtime();

        // Compare execution times
        printf("Size : %d items\n", size);
        printf("Serial execution time: %f seconds\n", k < 10 ? endSerial - startSerial : endParallel - startParallel);
        printf("Parallel execution time: %f seconds\n", k > 10 ? endSerial - startSerial : endParallel - startParallel);
    }
    return 0;
}
