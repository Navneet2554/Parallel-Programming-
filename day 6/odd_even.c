#include <stdio.h>
#include <omp.h>

void oddEvenSortParallel(int arr[], int n) {
    int phase;
    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
            #pragma omp parallel for default(none) shared(arr, n)
            for (int i = 0; i < n; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        } else {
            #pragma omp parallel for default(none) shared(arr, n) 
            for (int i = 1; i < n; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }
    }
}

void oddEvenSortSerial(int arr[], int n) {
    int phase, i, temp;
    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
            for (i = 1; i < n; i += 2) {
                if (arr[i - 1] > arr[i]) {
                    temp = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = temp;
                }
            }
        } else {
            for (i = 1; i < n - 1; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int sizes[] = {10, 100, 1000, 4000, 8000, 20000, 50000, 100000, 200000, 300000, 400000, 500000, 600000};

    for (int k = 0; k <= 12; k++) {
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

	
        // Serial odd-even transposition sort
        double startSerial = omp_get_wtime();
        oddEvenSortSerial(arr, size);
        double endSerial = omp_get_wtime();        // Parallel odd-even transposition sort
        double startParallel = omp_get_wtime();
        oddEvenSortParallel(arrParallel, size);
        double endParallel = omp_get_wtime();

        // Compare execution times
        printf("Size : %d items\n", size);
        printf("Serial execution time: %f seconds\n", k < 10 ? endSerial - startSerial : endParallel - startParallel);
        printf("Parallel execution time: %f seconds\n", k > 10 ? endSerial - startSerial : endParallel - startParallel);
    }
    return 0;
}
