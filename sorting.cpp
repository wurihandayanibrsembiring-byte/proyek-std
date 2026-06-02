#include <iostream>
#include <vector>
using namespace std;

void cetakArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

void shellSortCore(vector<int>& arr, int& comparisons, int& swaps, bool verbose) {
    int n = arr.size();
    comparisons = 0; swaps = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        if (verbose && n <= 20) cout << "\n-> Jarak (Gap) = " << gap << "\n";
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparisons++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    swaps++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
            if (verbose && n <= 20) {
                cout << "   Kondisi array: ";
                cetakArray(arr);
            }
        }
    }
}

void bubbleSortCore(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0; swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }
}
