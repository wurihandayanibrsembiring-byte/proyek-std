#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include <cstdlib>

#include "sorting.cpp"
#include "searching.cpp"

using namespace std;

vector<int> dataUtama;
vector<int> dataTerurut;

void inputManual() {
    int n;
    cout << "Masukkan jumlah data: ";
    cin >> n;
    dataUtama.clear();
    for (int i = 0; i < n; i++) {
        int nilai;
        cout << "Data ke-" << i + 1 << ": ";
        cin >> nilai;
        dataUtama.push_back(nilai);
    }
    cout << "=> Data berhasil disimpan secara manual.\n";
}
