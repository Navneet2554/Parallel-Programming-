#include <stdio.h>
#include <time.h>

int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    FILE *file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);

    int numbers[size];
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &numbers[i]);
    }
    fclose(file);

    int target_value;
    printf("Enter the number to search: ");
    scanf("%d", &target_value);

    clock_t start_time = clock();
    int result = binarySearch(numbers, 0, size - 1, target_value);
    clock_t end_time = clock();

    if (result != -1) {
        printf("Number %d found at index %d.\n", target_value, result);
    } else {
        printf("Number %d not found.\n", target_value);
    }

    printf("Binary Search Execution Time: %f seconds\n", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);

    return 0;
}
