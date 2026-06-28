#include <iostream>
#include <string>

using namespace std;

// Struct untuk data Tiket (Linked List)
struct Tiket {
    int idTiket;
    string namaPengguna;
    string keluhan;
    string status; // "Menunggu", "Diproses", "Selesai"
    string teknisiDitugaskan;
    Tiket* next;
};

// Struct untuk Antrean Tiket (Materi Queue dengan SLL)
struct Antrean {
    Tiket* tiketData;
    Antrean* next;
};

// Struct untuk data Teknisi (Materi Hashing)
struct Teknisi {
    string idTeknisi; // Menggunakan string/char untuk keperluan Hashing
    string namaTeknisi;
    string spesialisasi;
    bool isTersedia;
    Teknisi* next; // Untuk penanganan collision chaining di Hash Table
};

// Global Pointer / Kumpulan Head & Tail
Tiket* listTiketHead = NULL;
Tiket* listTiketTail = NULL;

Antrean* queueHead = NULL;
Antrean* queueTail = NULL;

const int HASH_TABLE_SIZE = 26; // Berdasarkan alphabet a-z
Teknisi* hashTable[HASH_TABLE_SIZE]; // Array of Pointer untuk Hash Table

int globalIdTiket = 101; // Auto increment ID Tiket

// 2. FUNGSI HASHING
int fungsiHash(string key) {
    if (key.length() == 0) return 0;
    // Mengambil huruf pertama, diubah ke lowercase, dikurangi 97
    char hurufPertama = tolower(key[0]);
    int index = hurufPertama - 97;
    
    // Validasi agar index tetap berada dalam range 0 - 25
    if (index < 0 || index >= HASH_TABLE_SIZE) {
        return 0; 
    }
    return index;
}

// 3. OPERASI FITUR MINIMAL (ADT IMPLEMENTATION)

// Fitur 3: Tambah Teknisi (Hashing Insert)
void tambahTeknisi(string id, string nama, string spesialisasi) {
    int index = fungsiHash(id);
    
    Teknisi* teknisiBaru = new Teknisi;
    teknisiBaru->idTeknisi = id;
    teknisiBaru->namaTeknisi = nama;
    teknisiBaru->spesialisasi = spesialisasi;
    teknisiBaru->isTersedia = true;
    teknisiBaru->next = NULL;

    // Jika index di Hash Table masih kosong
    if (hashTable[index] == NULL) {
        hashTable[index] = teknisiBaru;
    } else {
        // Jika ada collision, gunakan chaining (ditambahkan di akhir linked list index tsb)
        Teknisi* cur = hashTable[index];
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = teknisiBaru;
    }
    cout << "Teknisi " << nama << " berhasil didaftarkan pada indeks hash [" << index << "].\n";
}

// Fitur 4: Cari Teknisi (Hashing Search)
Teknisi* cariTeknisi(string id) {
    int index = fungsiHash(id);
    Teknisi* cur = hashTable[index];
    
    while (cur != NULL) {
        if (cur->idTeknisi == id) {
            return cur; // Teknisi ditemukan
        }
        cur = cur->next;
    }
    return NULL; // Tidak ditemukan
}

// Fitur 1: Tambah Tiket (Linked List & Enqueue ke Antrean)
void tambahTiket(string namaUser, string keluhan) {
    // 1. Simpan ke Riwayat Master Tiket
    Tiket* tiketBaru = new Tiket;
    tiketBaru->idTiket = globalIdTiket++;
    tiketBaru->namaPengguna = namaUser;
    tiketBaru->keluhan = keluhan;
    tiketBaru->status = "Menunggu";
    tiketBaru->teknisiDitugaskan = "-";
    tiketBaru->next = NULL;

    if (listTiketHead == NULL) {
        listTiketHead = tiketBaru;
        listTiketTail = tiketBaru;
    } else {
        listTiketTail->next = tiketBaru;
        listTiketTail = tiketBaru;
    }

    // 2. Masukkan ke Antrean SLL (Enqueue)
    Antrean* nodeAntreanBaru = new Antrean;
    nodeAntreanBaru->tiketData = tiketBaru;
    nodeAntreanBaru->next = NULL;

    if (queueHead == NULL) {
        queueHead = nodeAntreanBaru;
        queueTail = nodeAntreanBaru;
    } else {
        queueTail->next = nodeAntreanBaru;
        queueTail = nodeAntreanBaru;
    }
    cout << "Tiket #" << tiketBaru->idTiket << " berhasil dibuat untuk " << namaUser << " (Masuk Antrean).\n";
}

// Fitur 6: Tampilkan Status Antrean (Queue Display)
void tampilkanAntrean() {
    if (queueHead == NULL) {
        cout << "\n[Antrean Helpdesk Kosong]\n";
        return;
    }
    
    cout << "\n=== DAFTAR ANTREAN TIKET AKTIF ===\n";
    Antrean* cur = queueHead;
    int posisi = 1;
    while (cur != NULL) {
        cout << posisi << ". Tiket #" << cur->tiketData->idTiket 
             << " | Pelapor: " << cur->tiketData->namaPengguna 
             << " | Keluhan: " << cur->tiketData->keluhan 
             << " | Status: " << cur->tiketData->status << "\n";
        cur = cur->next;
        posisi++;
    }
    cout << "=========================================\n";
}

// Fitur 5: Assign Tiket ke Teknisi
void assignTiketKeTeknisi(int idTiket, string idTeknisi) {
    // Cari teknisinya di Hash Table
    Teknisi* tek = cariTeknisi(idTeknisi);
    if (tek == NULL) {
        cout << "Error: Teknisi dengan ID " << idTeknisi << " tidak ditemukan!\n";
        return;
    }
    
    // Cari tiketnya di Master Linked List
    Tiket* cur = listTiketHead;
    bool ditemukan = false;
    while (cur != NULL) {
        if (cur->idTiket == idTiket) {
            cur->teknisiDitugaskan = tek->namaTeknisi;
            cur->status = "Diproses";
            ditemukan = true;
            break;
        }
        cur = cur->next;
    }

    if (ditemukan) {
        cout << "Tiket #" << idTiket << " BERHASIL ditugaskan kepada Teknisi: " << tek->namaTeknisi << ".\n";
    } else {
        cout << "Error: Tiket #" << idTiket << " tidak ditemukan di sistem.\n";
    }
}

// Fitur 2: Proses Tiket Berikutnya (Dequeue dari Antrean)
void prosesTiketBerikutnya() {
    if (queueHead == NULL) {
        cout << "Tidak ada tiket dalam antrean untuk diproses.\n";
        return;
    }

    // Ambil data dari head antrean (Materi Dequeue)
    Antrean* del = queueHead;
    Tiket* tiketDiproses = del->tiketData;

    cout << "\n>>> MEMPROSES TIKET BERIKUTNYA <<<\n";
    cout << "ID Tiket  : #" << tiketDiproses->idTiket << "\n";
    cout << "Pelapor   : " << tiketDiproses->namaPengguna << "\n";
    cout << "Keluhan   : " << tiketDiproses->keluhan << "\n";
    
    // Jika belum di-assign teknisi, ingatkan sistem
    if (tiketDiproses->teknisiDitugaskan == "-") {
        cout << "Status    : Menunggu Teknisi (Silakan lakukan Assign Tiket terlebih dahulu).\n";
    } else {
        tiketDiproses->status = "Selesai";
        cout << "Status    : Sedang dikerjakan oleh " << tiketDiproses->teknisiDitugaskan << " -> SELESAI!\n";
    }

    // Geser head antrean (Materi Dequeue SLL)
    queueHead = queueHead->next;
    if (queueHead == NULL) {
        queueTail = NULL; // Jika antrean habis
    }
    
    delete del; // Hapus node antrean dari memori
}

// Fungsi Pembantu: Menampilkan seluruh riwayat tiket di master Linked List
void tampilkanSemuaTiket() {
    if (listTiketHead == NULL) {
        cout << "\n[Belum ada riwayat tiket di sistem]\n";
        return;
    }
    cout << "\n=== SEMUA RIWAYAT TIKET DI SISTEM (MASTER LIST) ===\n";
    Tiket* cur = listTiketHead;
    while (cur != NULL) {
        cout << "ID: #" << cur->idTiket 
             << " | User: " << cur->namaPengguna 
             << " | Keluhan: " << cur->keluhan 
             << " | Teknisi: " << cur->teknisiDitugaskan 
             << " | Status: " << cur->status << "\n";
        cur = cur->next;
    }
    cout << "===================================================\n";
}

// 4. MAIN PROGRAM / INTERFACE UTAMA
int main() {
    // Inisialisasi awal Hash Table dengan NULL (Sesuai Teori Hashing)
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    int pilihan;
    do {
        cout << "\n=========================================\n";
        cout << "     SISTEM HELPDESK TIKET IT PNJ        \n";
        cout << "=========================================\n";
        cout << "1. Tambah Tiket Baru (Keluhan User)\n";
        cout << "2. Tampilkan Antrean Aktif\n";
        cout << "3. Assign (Tugaskan) Tiket ke Teknisi\n";
        cout << "4. Proses & Selesaikan Tiket Berikutnya (Dequeue)\n";
        cout << "5. Tambah Teknisi Baru\n";
        cout << "6. Cari Teknisi (Hash Search)\n";
        cout << "7. Tampilkan Semua Riwayat Master Tiket\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "-----------------------------------------\n";
        cout << "Pilih Menu [0-7]: ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer input

        switch (pilihan) {
            case 1: {
                string nama, keluhan;
                cout << "Masukkan Nama Pengguna: ";
                getline(cin, nama);
                cout << "Masukkan Keluhan/Kerusakan Perangkat: ";
                getline(cin, keluhan);
                tambahTiket(nama, keluhan);
                break;
            }
            case 2:
                tampilkanAntrean();
                break;
            case 3: {
                int idT;
                string idTek;
                cout << "Masukkan ID Tiket yang ingin di-assign (contoh: 101): ";
                cin >> idT;
                cin.ignore();
                cout << "Masukkan ID Kode Teknisi (contoh: t1/t2/r1): ";
                getline(cin, idTek);
                assignTiketKeTeknisi(idT, idTek);
                break;
            }
            case 4:
                prosesTiketBerikutnya();
                break;
            case 5: {
                string id, nama, spesialisasi;
                cout << "Masukkan Kode ID Teknisi (Huruf kecil diawal, cth: t3): ";
                getline(cin, id);
                cout << "Masukkan Nama Teknisi: ";
                getline(cin, nama);
                cout << "Masukkan Spesialisasi Kerja: ";
                getline(cin, spesialisasi);
                tambahTeknisi(id, nama, spesialisasi);
                break;
            }
            case 6: {
                string id;
                cout << "Masukkan Kode ID Teknisi yang dicari: ";
                getline(cin, id);
                Teknisi* hasil = cariTeknisi(id);
                if (hasil != NULL) {
                    cout << "Teknisi Ditemukan pada Hash Table!\n";
                    cout << "Nama        : " << hasil->namaTeknisi << "\n";
                    cout << "Spesialisasi: " << hasil->spesialisasi << "\n";
                } else {
                    cout << "Teknisi dengan ID '" << id << "' TIDAK DITEMUKAN.\n";
                }
                break;
            }
            case 7:
                tampilkanSemuaTiket();
                break;
            case 0:
                cout << "Terima kasih! Program helpdesk ditutup.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}