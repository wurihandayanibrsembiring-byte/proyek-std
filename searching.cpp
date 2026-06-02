#include <iostream>
#include <vector>
#include <cmath> // Library wajib untuk memanggil fungsi akar kuadrat (sqrt)
using namespace std;

// FUNGSI UTAMA: Algoritma Jump Search untuk Mencari ID Pegawai
int jumpSearchCore(const vector<int>& arr, int target, int& steps) {
    int n = arr.size(); // Mengambil jumlah total data
    int step = sqrt(n); // Menentukan jarak lompatan berdasarkan akar kuadrat dari N data
    int prev = 0; // Menyimpan posisi indeks sebelum melompat
    steps = 0; // Mengosongkan hitungan langkah pencarian
    
    cout << "Langkah Lompatan (sqrt(" << n << ")) = " << step << "\n";
    
    // TAHAP 1: Melompat blok demi blok untuk mencari di blok mana angka target berada
    while (arr[min(step, n) - 1] < target) {
        steps++; // Tambah hitungan iterasi lompatan
        cout << "Iterasi " << steps << ": Lompat ke indeks " << min(step, n) - 1 << " (Nilai ID: " << arr[min(step, n) - 1] << ")\n";
        
        prev = step; // Geser batas belakang blok ke posisi lompatan sekarang
        step += sqrt(n); // Lompat lagi ke blok berikutnya
        if (prev >= n) return -1; // Jika posisi lompat melebihi ukuran data, artinya tidak ketemu
    }
    
    cout << "ID target berada di kisaran indeks " << prev << " sampai " << min(step, n) - 1 << ". Mulai pencarian linear...\n";
    
    // TAHAP 2: Melakukan Pencarian Linear (satu per satu) di dalam blok yang sudah ditemukan
    while (arr[prev] < target) {
        steps++; // Tambah hitungan langkah linear
        prev++; // Geser ke indeks berikutnya secara berurutan
        if (prev == min(step, n)) return -1; // Jika sampai batas blok belum ketemu, artinya data tidak ada
    }
    
    steps++;
    // TAHAP 3: Cek apakah angka di indeks terakhir itu sama dengan target yang dicari
    if (arr[prev] == target) return prev; // Jika cocok, kembalikan posisi indeksnya
    
    return -1; // Kembalikan -1 jika angka benar-benar tidak ditemukan
}
