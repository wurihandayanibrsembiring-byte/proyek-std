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

// Menu 2: Menjalankan Fungsi Pengurutan Shell Sort
void menuSorting() {
    if (dataUtama.empty()) {
        cout << "[Peringatan] Data log kosong! Silakan isi data dulu di Menu 1.\n";
        return;
    }
    dataTerurut = dataUtama; // Menyalin data utama ke dataTerurut agar data asli tidak rusak
    int comps = 0, swps = 0;
    
    cout << "\n=== MENU 2: PROSES PENGURUTAN (SHELL SORT) ===\n";
    if (dataTerurut.size() <= 20) {
        cout << "Data ID Sebelum diurutkan:\n";
        cetakArray(dataTerurut);
    } else {
        cout << "=> Memproses " << dataTerurut.size() << " data log pegawai...\n";
    }
    
    // Mencatat waktu mulai eksekusi algoritma
    auto start = chrono::high_resolution_clock::now();
    shellSortCore(dataTerurut, comps, swps, true); // Panggil fungsi inti Shell Sort
    // Mencatat waktu selesai eksekusi algoritma
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> elapsed = end - start; // Hitung selisih waktu (Durasi)
    
    if (dataTerurut.size() <= 20) {
        cout << "\nData ID Setelah diurutkan (Rapi):\n";
        cetakArray(dataTerurut);
    }
    cout << "------------------------------------------------------\n";
    cout << "Hasil Analisis Performa Shell Sort:\n";
    cout << "Waktu Eksekusi                   : " << elapsed.count() << " milidetik\n";
    cout << "Jumlah Operasi Perbandingan (Comp) : " << comps << " kali\n";
    cout << "Jumlah Operasi Pertukaran (Swap)  : " << swps << " kali\n";
}

// Menu 3: Menjalankan Fungsi Pencarian Jump Search
void menuSearching() {
    if (dataTerurut.empty()) {
        cout << "[Peringatan] Data belum terurut! Jalankan Shell Sort dulu di Menu 2.\n";
        return;
    }
    int target, steps = 0;
    cout << "\n=== MENU 3: PENCARIAN DIREKTORI PEGAWAI (JUMP SEARCH) ===\n";
    cout << "Masukkan nomor ID Pegawai yang ingin dicari lognya: ";
    cin >> target;
    
    // Menghitung waktu mulai proses pencarian
    auto start = chrono::high_resolution_clock::now();
    int hasilIndeks = jumpSearchCore(dataTerurut, target, steps); // Panggil fungsi inti Jump Search
    // Menghitung waktu selesai proses pencarian
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> elapsed = end - start;
    
    // Cek hasil, jika indeks bukan -1 artinya angka sukses ditemukan
    if (hasilIndeks != -1) {
        cout << "=> HASIL: Pegawai dengan ID " << target << " AKTIF, ditemukan pada indeks ke-[" << hasilIndeks << "]\n";
    } else {
        cout << "=> HASIL: Pegawai dengan ID " << target << " TIDAK DITEMUKAN dalam log hari ini.\n";
    }
    cout << "Waktu Proses Pencarian : " << elapsed.count() << " milidetik\n";
    cout << "Jumlah Langkah Lompatan : " << steps << " kali iterasi\n";
}

// Menu 4: Menguji Skala Besar & Mengekspor Hasil Eksperimen Studi Kasus ke File CSV
void menuBenchmark() {
    int ukuranData[] = {100, 500, 1000, 2000}; // Ukuran dataset pengujian sesuai instruksi
    int nUkuran = sizeof(ukuranData) / sizeof(ukuranData[0]);
    
    // Menyiapkan teks judul tabel untuk isi file Microsoft Excel (.csv) nanti
    string csvContent = "Ukuran Data,Waktu Shell (ms),Comp Shell,Swap Shell,Waktu Bubble (ms),Comp Bubble,Swap Bubble\n";
    
    cout << "\n=== MENU 4: BENCHMARK STUDI KASUS (DATA REALISTIS 100 - 2000 DATA) ===\n";
    cout << "Menguji efisiensi Shell Sort vs Bubble Sort berdasarkan jumlah baris data...\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    cout << "N Data\t| Shell (ms)\t| Comp Shell\t| Bubble (ms)\t| Comp Bubble\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    
    // Perulangan untuk menguji data skala 100 sampai 2000 satu per satu
    for (int i = 0; i < nUkuran; i++) {
        int n = ukuranData[i];
        vector<int> dataUjiShell, dataUjiBubble;
        
        // Membuat data tiruan dalam jumlah besar secara otomatis
        for (int j = 0; j < n; j++) {
            int val = rand() % 10000;
            dataUjiShell.push_back(val);
            dataUjiBubble.push_back(val);
        }
        
        int compShell, swapShell, compBubble, swapBubble;
        
        // 1. Menguji Kecepatan Shell Sort
        auto s1 = chrono::high_resolution_clock::now();
        shellSortCore(dataUjiShell, compShell, swapShell, false);
        auto e1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tShell = e1 - s1;
        
        // 2. Menguji Kecepatan Bubble Sort (Sebagai Pemandig Performa)
        auto s2 = chrono::high_resolution_clock::now();
        bubbleSortCore(dataUjiBubble, compBubble, swapBubble);
        auto e2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tBubble = e2 - s2;
        
        // Cetak hasil perbandingan ke layar monitor
        cout << n << "\t| " << tShell.count() << "\t| " << compShell << "\t\t| " << tBubble.count() << "\t| " << compBubble << "\n";
        
        // Menyimpan angka baris data hasil uji coba ke dalam variabel string Excel
        csvContent += to_string(n) + "," + to_string(tShell.count()) + "," + to_string(compShell) + "," + to_string(swapShell) + "," +
                      to_string(tBubble.count()) + "," + to_string(compBubble) + "," + to_string(swapBubble) + "\n";
    }
    cout << "-----------------------------------------------------------------------------------------\n";
    
    // TAHAP EKSPOR: Membuat dan menyimpan data angka di atas menjadi file nyata 'hasil_perbandingan.csv'
    ofstream fileKeluar("hasil_perbandingan.csv");
    fileKeluar << csvContent;
    fileKeluar.close(); // Tutup file setelah sukses ditulis
    cout << "=> BERHASIL: Hasil pengujian skala besar otomatis disimpan ke 'hasil_perbandingan.csv' untuk grafik laporan!\n";
}

// Fungsi utama pengendali alur aplikasi (Fungsi yang pertama kali dijalankan komputer)
int main() {
    int pilihan;
    do {
        // Menampilkan antarmuka Menu Utama Aplikasi di layar console
        cout << "\n==================================================\n";
        cout << "      SISTEM MANAJEMEN LOG SERVER PEGAWAI         \n";
        cout << "      ALGORITMA: SHELL SORT & JUMP SEARCH         \n";
        cout << "==================================================\n";
        cout << "1. Input / Generate Data ID Log\n";
        cout << "2. Jalankan Shell Sort (Urutkan ID + Trace Langkah)\n";
        cout << "3. Jalankan Jump Search (Cari Posisi ID Pegawai)\n";
        cout << "4. Jalankan Eksperimen Benchmark Skala Besar (>1000 Data)\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "--------------------------------------------------\n";
        cout << "Pilih Aktivitas (0-4): ";
        cin >> pilihan;
        
        // Sistem Switch Case untuk mengarahkan pengguna sesuai nomor tombol menu yang dipilih
        switch (pilihan) {
            case 1: menuInput(); break;     // Jika ketik 1, lompat ke fungsi menuInput
            case 2: menuSorting(); break;   // Jika ketik 2, lompat ke fungsi menuSorting
            case 3: menuSearching(); break; // Jika ketik 3, lompat ke fungsi menuSearching
            case 4: menuBenchmark(); break; // Jika ketik 4, lompat ke fungsi menuBenchmark
            case 0: cout << "Sistem dimatikan. Terima kasih!\n"; break;
            default: cout << "Menu tidak tersedia. Coba lagi.\n";
        }
    } while (pilihan != 0); // Program akan terus berputar ulang selama pengguna tidak menekan tombol 0
    return 0;
}
