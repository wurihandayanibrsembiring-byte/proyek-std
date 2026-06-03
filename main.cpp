#include <iostream>
#include <vector>
#include <string>
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
vector<string> dataString; // Data khusus demonstrasi string

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
    cout << "2. Generate Otomatis Data Skala Besar (>1000 Data)\n";
    cout << "3. Baca dari File Teks (.txt)\n";
    cout << "Pilih metode (1-3): ";
    cin >> pil;
    
    if (pil == 1) inputManual();
    else if (pil == 2) generateAcak();
    else if (pil == 3) bacaDariFile();
    else cout << "Pilihan salah!\n";
}

// ======================================================
// MENAMPILKAN 10 DATA PERTAMA DAN TERAKHIR
// UNTUK DATA BESAR (>20 ELEMEN)
// ======================================================

void tampilkanRingkasan(const vector<int>& arr)
{
    int n = arr.size();

    cout << "\n10 Data Pertama:\n";

    for(int i = 0; i < 10 && i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n\n10 Data Terakhir:\n";

    int mulai = max(0, n - 10);

    for(int i = mulai; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n";
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
	else {
    tampilkanRingkasan(dataTerurut);
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

// ======================================================
// MEMBUAT DATA ACAK
// ======================================================

vector<int> generateRandomData(int n)
{
    vector<int> data;

    for(int i=0;i<n;i++)
    {
        data.push_back(rand()%10000);
    }

    return data;
}

// ======================================================
// MEMBUAT DATA SUDAH TERURUT
// ======================================================

vector<int> generateSortedData(int n)
{
    vector<int> data;

    for(int i=0;i<n;i++)
    {
        data.push_back(i);
    }

    return data;
}

// ======================================================
// MEMBUAT DATA TERBALIK
// ======================================================

vector<int> generateReverseData(int n)
{
    vector<int> data;

    for(int i=n;i>0;i--)
    {
        data.push_back(i);
    }

    return data;
}

// ======================================================
// MEMBUAT DATA BANYAK DUPLIKAT
// ======================================================

vector<int> generateDuplicateData(int n)
{
    vector<int> data;

    for(int i=0;i<n;i++)
    {
        data.push_back(rand()%10);
    }

    return data;
}

// ======================================================
// SHELL SORT UNTUK STRING
// ======================================================

void shellSortString(vector<string>& arr)
{
    int n = arr.size();

    for(int gap = n/2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < n; i++)
        {
            string temp = arr[i];
            int j;

            for(j = i; j >= gap && arr[j-gap] > temp; j -= gap)
            {
                arr[j] = arr[j-gap];
            }

            arr[j] = temp;
        }
    }
}

// ======================================================
// DEMO STRING
// ======================================================

void menuString()
{
    vector<string> nama =
    {
        "Wuri Handayani",
        "Fiona Hutagalung",
        "Meliana Manullang",
        "Putri Aritonang"
    };

    cout << "\n=== DEMO SHELL SORT STRING ===\n";

    cout << "\nData Sebelum Diurutkan:\n";

    for(string s : nama)
    {
    cout << s << endl;
    }

    cout << endl;

    shellSortString(nama);

    cout << "\nData Setelah Diurutkan:\n";

    for(string s : nama)
    {
    cout << s << endl;
    } 

    cout << endl;
}

void menuBenchmark()
{
    // Ukuran data 
    int ukuranData[] =
    {
        100,
        500,
        1000,
        5000,
        10000
    };

    int jumlahUkuran =
        sizeof(ukuranData) /
        sizeof(ukuranData[0]);

    ofstream csv("hasil_perbandingan.csv");

    csv << "Kondisi,N,Shell(ms),Knuth(ms),Bubble(ms)\n";

    cout << "\n================================================\n";
    cout << "BENCHMARK SHELL VS KNUTH VS BUBBLE\n";
    cout << "================================================\n";

    string kondisi[4] =
    {
        "Random",
        "Sorted",
        "Reverse",
        "Duplicate"
    };

    for(int k=0;k<4;k++)
    {
        cout << "\n========================================\n";
        cout << "KONDISI DATA : " << kondisi[k] << endl;
        cout << "========================================\n";

        for(int i=0;i<jumlahUkuran;i++)
        {
            int n = ukuranData[i];

            vector<int> data;

            if(k==0)
                data = generateRandomData(n);

            else if(k==1)
                data = generateSortedData(n);

            else if(k==2)
                data = generateReverseData(n);

            else
                data = generateDuplicateData(n);

            vector<int> shellData = data;
            vector<int> knuthData = data;
            vector<int> bubbleData = data;

            int c1,s1,c2,s2,c3,s3;

            auto start1 =
            chrono::high_resolution_clock::now();

            shellSortCore(shellData,c1,s1,false);

            auto end1 =
            chrono::high_resolution_clock::now();

            auto start2 =
            chrono::high_resolution_clock::now();

            shellSortKnuth(knuthData,c2,s2,false);

            auto end2 =
            chrono::high_resolution_clock::now();

            auto start3 =
            chrono::high_resolution_clock::now();

            bubbleSortCore(bubbleData,c3,s3);

            auto end3 =
            chrono::high_resolution_clock::now();

            chrono::duration<double,milli>
            tShell = end1-start1;

            chrono::duration<double,milli>
            tKnuth = end2-start2;

            chrono::duration<double,milli>
            tBubble = end3-start3;

            cout
            << "N = "
            << n
            << " | Shell = "
            << tShell.count()
            << " ms | Knuth = "
            << tKnuth.count()
            << " ms | Bubble = "
            << tBubble.count()
            << " ms\n";

            csv
            << kondisi[k]
            << ","
            << n
            << ","
            << tShell.count()
            << ","
            << tKnuth.count()
            << ","
            << tBubble.count()
            << "\n";
        }
    }

    csv.close();

    cout << "\nCSV berhasil dibuat.\n";
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
        cout << "5. Demo Shell Sort String\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "--------------------------------------------------\n";
        cout << "Pilih Aktivitas (0-5): ";
        cin >> pilihan;
        
        // Sistem Switch Case untuk mengarahkan pengguna sesuai nomor tombol menu yang dipilih
        switch (pilihan) {
            case 1: menuInput(); break;     // Jika ketik 1, lompat ke fungsi menuInput
            case 2: menuSorting(); break;   // Jika ketik 2, lompat ke fungsi menuSorting
            case 3: menuSearching(); break; // Jika ketik 3, lompat ke fungsi menuSearching
            case 4: menuBenchmark(); break; // Jika ketik 4, lompat ke fungsi menuBenchmark
            case 5: menuString(); break;    // Jika ketik 5, Lompat ke fungsi menuString
            case 0: cout << "Sistem dimatikan. Terima kasih!\n"; break;
            default: cout << "Menu tidak tersedia. Coba lagi.\n";
        }
    } while (pilihan != 0); // Program akan terus berputar ulang selama pengguna tidak menekan tombol 0
    return 0;
}
