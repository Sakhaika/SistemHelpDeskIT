# 🛠️ Sistem Helpdesk Tiket IT (PNJ)

Aplikasi console (CLI) sederhana berbasis **C++** untuk mengelola tiket keluhan IT — dibuat sebagai studi kasus implementasi struktur data: **Linked List**, **Queue (SLL)**, dan **Hash Table (chaining)**.

## 📌 Fitur

| # | Fitur | Struktur Data |
|---|-------|----------------|
| 1 | Tambah tiket baru (keluhan user) | Linked List + Queue (enqueue) |
| 2 | Tampilkan antrean tiket aktif | Queue |
| 3 | Assign tiket ke teknisi | Hash Table (search) + Linked List |
| 4 | Proses & selesaikan tiket berikutnya | Queue (dequeue) |
| 5 | Tambah teknisi baru | Hash Table (insert + chaining) |
| 6 | Cari teknisi by ID | Hash Table (search) |
| 7 | Tampilkan seluruh riwayat tiket | Linked List (traversal) |
| 0 | Keluar aplikasi | - |

## 🧠 Struktur Data yang Digunakan

- **`Tiket` (Linked List)** — menyimpan seluruh riwayat tiket (master data): id, nama pengguna, keluhan, status, dan teknisi yang ditugaskan.
- **`Antrean` (Singly Linked List sebagai Queue)** — antrean FIFO tiket yang belum diproses, dengan operasi enqueue (tambah tiket) dan dequeue (proses tiket).
- **`Teknisi` (Hash Table + Chaining)** — data teknisi disimpan di array hash berukuran 26 (berdasarkan huruf awal ID), dengan collision resolution memakai chaining (linked list per index).

## 📂 Struktur File

```
SistemHelpDeskIT/
├── SistemHelpDeskSakha.cpp   # Source code utama
├── .vscode/
│   └── tasks.json            # Konfigurasi build task VS Code
└── README.md
```

## ⚙️ Cara Menjalankan

### Opsi 1 — g++ langsung
```bash
g++ SistemHelpDeskSakha.cpp -o SistemHelpDeskIT
./SistemHelpDeskIT        # Linux/Mac
SistemHelpDeskIT.exe      # Windows
```

### Opsi 2 — VS Code
Buka folder ini di VS Code (sudah ada `tasks.json`), lalu jalankan build task bawaan (`Ctrl+Shift+B`) diikuti menjalankan file hasil kompilasi.

## ▶️ Contoh Alur Pemakaian

1. Pilih **5** untuk mendaftarkan teknisi (contoh: ID `t1`, nama, spesialisasi).
2. Pilih **1** untuk membuat tiket baru dari keluhan user (otomatis masuk antrean).
3. Pilih **2** untuk melihat antrean tiket yang masih aktif.
4. Pilih **3** untuk assign tiket ke teknisi berdasarkan ID teknisi.
5. Pilih **4** untuk memproses & menyelesaikan tiket paling depan di antrean.
6. Pilih **7** kapan saja untuk melihat seluruh riwayat tiket di sistem.

## 📝 Catatan

- ID tiket dibuat otomatis (auto-increment, mulai dari `101`).
- Fungsi hash memakai huruf pertama dari ID teknisi (case-insensitive), sehingga disarankan ID teknisi diawali huruf a–z.
- Tiket yang belum di-assign teknisi tetap bisa diproses (opsi 4), namun statusnya akan tetap "Menunggu Teknisi" sampai di-assign.

## 👤 Author

Dibuat oleh [Sakhaika](https://github.com/Sakhaika) sebagai tugas/latihan mata kuliah Struktur Data.
