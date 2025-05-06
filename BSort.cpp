// #include headers
#include<iostream>
#include<omp.h>
#include<cstdlib>

using namespace std;

// Swaps elements at index i and j in the array
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Parallel Even-Odd Bubble Sort using OpenMP
void bubble_even_odd(int arr[], int size) {
    bool IsSort = false;

    while (!IsSort) {
        IsSort = true;

        #pragma omp parallel for
        for (int i = 0; i < size - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr, i, i + 1);
                IsSort = false;
            }
        }

        #pragma omp parallel for
        for (int i = 1; i < size - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr, i, i + 1);
                IsSort = false;
            }
        }
    }
}

int main() {
    int n = 5;
    int arr[5] = {44, 43, 12, 101, 34};

    bubble_even_odd(arr, n);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
