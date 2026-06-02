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

void generateAcak() {
    int n, minVal, maxVal;
    cout << "Masukkan jumlah data: ";
    cin >> n;
    cout << "Masukkan nilai minimal acak: ";
    cin >> minVal;
    cout << "Masukkan nilai maksimal acak: ";
    cin >> maxVal;
    
    dataUtama.clear();
    for (int i = 0; i < n; i++) {
        int acak = minVal + (rand() % (maxVal - minVal + 1));
        dataUtama.push_back(acak);
    }
    cout << "=> " << n << " data acak berhasil digenerate.\n";
}

void bacaDariFile() {
    string namaFile;
    cout << "Masukkan nama file (contoh: data.txt): ";
    cin >> namaFile;
    
    ifstream file(namaFile);
    if (!file.is_open()) {
        cout << "[Error] File tidak ditemukan! Buat file " << namaFile << " dulu di folder yang sama.\n";
        return;
    }
    
    dataUtama.clear();
    int nilai;
    while (file >> nilai) {
        dataUtama.push_back(nilai);
    }
    file.close();
    cout << "=> Berhasil membaca " << dataUtama.size() << " data dari file.\n";
}
