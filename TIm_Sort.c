#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_RUN 4

void insertionSort(int arr[], int left, int right) {
    int i, key, j;
    for (i = left + 1; i <= right; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;

    int* leftArr = (int*)malloc(len1 * sizeof(int));
    int* rightArr = (int*)malloc(len2 * sizeof(int));

    memcpy(leftArr, &arr[left], len1 * sizeof(int));
    memcpy(rightArr, &arr[mid + 1], len2 * sizeof(int));

    int i = 0, j = 0, k = left;

    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

void timSort(int arr[], int n) {
    for (int i = 0; i < n; i += MIN_RUN) {
        insertionSort(arr, i, (i + MIN_RUN - 1) < (n - 1) ? (i + MIN_RUN - 1) : (n - 1));
        printf("Sorting tahap 1: ");
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }

    for (int size = MIN_RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1) < (n - 1) ? (left + 2 * size - 1) : (n - 1);
            merge(arr, left, mid, right);
            printf("Sorting tahap 2: ");
            for (int j = 0; j < n; j++) {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }
    }
}

int main() {
    int data[] = {77, 33, 44, 11, 88, 22, 66, 55};
    int size = sizeof(data) / sizeof(data[0]);

    printf("Data awal: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    timSort(data, size);

    printf("Data setelah diurutkan: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
