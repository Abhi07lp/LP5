#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

void merge(int arr[], int l, int m, int r);
void mergeSortP(int arr[], int l, int r);
void mergeSort(int arr[], int l, int r);

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);

        merge(arr, l, mid, r);
    }
}

void mergeSortP(int arr[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSortP(arr, l, mid);
            }
            #pragma omp section
            {
                mergeSortP(arr, mid + 1, r);
            }
        }
        merge(arr, l, mid, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* left = new int[n1];
    int* right = new int[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}


int main() {
    const int n = 1000;
    int a[n];
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 10000;
    }

    auto start_time = high_resolution_clock::now();
    mergeSort(a, 0, n - 1);
    auto end_time = high_resolution_clock::now();

    cout << "Sequential Merge Sort Result: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\nTime taken: " << duration_cast<microseconds>(end_time - start_time).count() << " seconds\n";

    // Time for parallel merge sort
    auto start_timeP = high_resolution_clock::now();
    mergeSortP(a, 0, n - 1);
    auto end_timeP = high_resolution_clock::now();

    cout << "Parallel Merge Sort Result: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\nTime taken: " << duration_cast<microseconds>(end_timeP - start_timeP).count() << " seconds\n";

    return 0;
}
