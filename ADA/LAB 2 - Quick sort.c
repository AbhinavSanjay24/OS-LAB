#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j] <= pivot) {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {

        int pi = partition(arr, low, high);


        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int N;

    printf("Enter the number of elements: ");
    scanf("%d", &N);
    int *arr = (int*)malloc(N * sizeof(int));

    printf("Enter the elements:\n");
    for (int i = 0; i < N; i++) {
        arr[i]=rand()%30000;
        //scanf("%d",&arr[i]);
    }
    clock_t start = clock();
    quickSort(arr, 0, N - 1);
    clock_t end = clock();

    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array using Quick Sort: ");
    printArray(arr, N);
    printf("Time taken by Quick Sort: %f seconds\n", timeTaken);

    free(arr);
    return 0;
}
