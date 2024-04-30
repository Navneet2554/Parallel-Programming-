#include <stdio.h>
#include <time.h>

int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
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
    int result = linearSearch(numbers, size, target_value);
    clock_t end_time = clock();

    if (result != -1) {
        printf("Number %d found at index %d.\n", target_value, result);
    } else {
        printf("Number %d not found.\n", target_value);
    }

    printf("Linear Search Execution Time: %f seconds\n", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);

    return 0;
}
