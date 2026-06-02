#include <iostream>
#include <vector>
using namespace std;

 // Fungsi pembantu untuk mencetak semua angka di dalam array ke layar
void cetakArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

 // FUNGSI UTAMA: Algoritma Shell Sort dengan Fitur Pelacakan (Trace)
void shellSortCore(vector<int>& arr, int& comparisons, int& swaps, bool verbose) {
    int n = arr.size(); // Mengambil jumlah total data
    comparisons = 0; swaps = 0; // Mengosongkan hitungan awal nilai operasi
    
    // Perulangan untuk menentukan Jarak (Gap), dimulai dari N/2 lalu dibagi 2 terus sampai Gap = 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Jika data <= 20 dan fitur verbose aktif, cetak tahapan gap-nya
        if (verbose && n <= 20) cout << "\n-> Jarak (Gap) = " << gap << "\n";
        
        // Memulai Insertion Sort berdasarkan jarak gap yang sudah ditentukan
        for (int i = gap; i < n; i++) {
            int temp = arr[i]; // Simpan sementara data ID yang sedang dicek
            int j;
            
            // Menggeser data elemen terdahulu yang nilainya lebih besar dari data temp
            for (j = i; j >= gap; j -= gap) {
                comparisons++; // Hitung setiap kali ada proses perbandingan angka
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap]; // Geser angka ke kanan
                    swaps++; // Hitung setiap kali terjadi pergeseran/pertukaran
                } else {
                    break; // Berhenti menggeser jika posisi sudah benar
                }
            }
            arr[j] = temp; // Masukkan data temp ke posisi yang pas
            
            // Cetak kondisi barisan ID log setelah digeser (hanya jika data dikit/<=20)
            if (verbose && n <= 20) {
                cout << "   Kondisi ID Log: ";
                cetakArray(arr);
            }
        }
    }
}

// ======================================================
// SHELL SORT VARIASI KNUTH GAP SEQUENCE
// Gap menggunakan rumus:
// 1, 4, 13, 40, 121, ...
// gap = gap * 3 + 1
// ======================================================

void shellSortKnuth(vector<int>& arr,
                    int& comparisons,
                    int& swaps,
                    bool verbose)
{
    int n = arr.size();

    comparisons = 0;
    swaps = 0;

    // Membentuk gap terbesar yang masih lebih kecil dari jumlah data
    int gap = 1;

    while (gap < n / 3)
    {
        gap = gap * 3 + 1;
    }

    // Proses pengurutan menggunakan gap Knuth
    while (gap >= 1)
    {
        if (verbose && n <= 20)
        {
            cout << "\n[KNUTH GAP = " << gap << "]\n";
        }

        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap; j -= gap)
            {
                comparisons++;

                if (arr[j-gap] > temp)
                {
                    arr[j] = arr[j-gap];
                    swaps++;
                }
                else
                {
                    break;
                }
            }

            arr[j] = temp;

            if (verbose && n <= 20)
            {
                cout << "Kondisi Data : ";
                cetakArray(arr);
            }
        }

        // Mundur ke gap sebelumnya
        gap = (gap - 1) / 3;
    }
}

 // FUNGSI PEMBANDING: Algoritma Bubble Sort (Untuk Studi Kasus Menu 4)
void bubbleSortCore(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0; swaps = 0;
    // Perulangan luar untuk mengecek seluruh data
    for (int i = 0; i < n - 1; i++) {
        // Perulangan dalam untuk membandingkan angka yang berdampingan
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++; // Hitung perbandingan angka
            if (arr[j] > arr[j + 1]) {
                // Tukar posisi angka jika angka kiri lebih besar dari angka kanan
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++; // Hitung operasi pertukaran
            }
        }
    }
}
                 
                
