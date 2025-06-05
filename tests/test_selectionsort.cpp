#include <iostream>
#include <cassert>
using namespace std;

// Simple selection sort implementation
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int least = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[least]) {
                least = j;
            }
        }
        swap(arr[i], arr[least]);
    }
}

int main() {
    int numbers[] = {5, 2, 3, 8, 1};
    int expected[] = {1, 2, 3, 5, 8};
    int tam = sizeof(numbers) / sizeof(numbers[0]);

    selectionSort(numbers, tam);

    for (int i = 0; i < tam; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < tam; ++i) {
        assert(numbers[i] == expected[i]);
    }
    return 0;
}

/*
To compile and run this test:

    g++ tests/test_selectionsort.cpp -o tests/test_selectionsort.out
    ./tests/test_selectionsort.out
*/
