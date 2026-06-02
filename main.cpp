#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>   // Library wajib untuk menghitung waktu eksekusi (milidetik)
#include <fstream>  // Library wajib untuk membaca dan menulis file luar (.txt & .csv)
#include <cstdlib>

// Menyambungkan potongan file modular (sorting & searching) ke dalam file menu utama ini
#include "sorting.cpp"
#include "searching.cpp"

using namespace std;

// Variabel Global untuk menyimpan data di memori program
vector<int> dataUtama;   // Tempat menyimpan data mentah awal
vector<int> dataTerurut; // Tempat menyimpan data hasil urutan Shell Sort

// Menu 1 - Opsi 1: Mengetik angka ID satu per satu secara manual
void inputManual() {
    int n;
    cout << "Masukkan jumlah ID Log Pegawai: ";
    cin >> n;
    dataUtama.clear();
    for (int i = 0; i < n; i++) {
        int nilai;
        cout << "ID Pegawai ke-" << i + 1 << ": ";
        cin >> nilai;
        dataUtama.push_back(nilai); // Memasukkan angka ke dalam vector dataUtama
    }
    cout << "=> Data ID Log berhasil disimpan secara manual.\n";
}

// Menu 1 - Opsi 2: Membuat data acak skala besar otomatis (Syarat Studi Kasus >1000 data)
void generateAcak() {
    int n, minVal, maxVal;
    cout << "Masukkan jumlah data ID Log otomatis (Saran: 1000): ";
    cin >> n;
    cout << "Masukkan batas minimal angka ID: ";
    cin >> minVal;
    cout << "Masukkan batas maksimal angka ID: ";
    cin >> maxVal;
    
    dataUtama.clear();
    for (int i = 0; i < n; i++) {
        // Mengacak angka dengan batas minimal dan maksimal yang ditentukan pengguna
        int acak = minVal + (rand() % (maxVal - minVal + 1));
        dataUtama.push_back(acak);
    }
    cout << "=> " << n << " Data log pegawai berhasil dibuat secara acak oleh sistem.\n";
}

// Menu 1 - Opsi 3: Membaca kumpulan angka dari file teks luar (data.txt)
void bacaDariFile() {
    string namaFile;
    cout << "Masukkan nama file teks (contoh: data.txt): ";
    cin >> namaFile;
    
    ifstream file(namaFile); // Membuka file sesuai inputan nama
    if (!file.is_open()) {
        cout << "[Error] File tidak ditemukan! Buat file " << namaFile << " dulu di folder yang sama.\n";
        return;
    }
    
    dataUtama.clear();
    int nilai;
    while (file >> nilai) {
        dataUtama.push_back(nilai); // Membaca angka satu per satu sampai isi file habis
    }
    file.close(); // Menutup file setelah selesai dibaca
    cout << "=> Berhasil membaca " << dataUtama.size() << " data ID Log dari file.\n";
}

// Fungsi pengatur tampilan utama Menu 1
void menuInput() {
    int pil;
    cout << "\n=== MENU 1: INPUT DATA LOG SERVER ===\n";
    cout << "1. Input Manual ID Pegawai\n";
    cout << "2. Generate Otomatis Data Skala Besar (Sesuai Syarat Dosen >1000 Data)\n";
    cout << "3. Baca dari File Teks (.txt)\n";
    cout << "Pilih metode (1-3): ";
    cin >> pil;
    
    if (pil == 1) inputManual();
    else if (pil == 2) generateAcak();
    else if (pil == 3) bacaDariFile();
    else cout << "Pilihan salah!\n";
}

