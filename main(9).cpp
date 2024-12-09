#include "SistemPeminjamanSepeda.h"

int main() {
    SistemPeminjamanSepeda system;

    int choice;
    do {
        cout << "\n--- Sistem Peminjaman Sepeda ---\n";
        cout << "1. Admin: Atur Sepeda\n";
        cout << "2. Admin: Lihat Riwayat Peminjaman\n";
        cout << "3. Admin: Lihat Laporan Kerusakan\n";
        cout << "4. Registrasi Pengguna\n";
        cout << "5. Pinjam Sepeda\n";
        cout << "6. Kembalikan Sepeda\n";
        cout << "7. Laporkan Kerusakan Sepeda\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu: ";
        cin >> choice;

        string nama, NiuNip;
        switch (choice) {
        case 1:
            system.setJumlahSepeda();
            break;
        case 2:
            system.lihatRiwayatPeminjaman();
            break;
        case 3:
            system.lihatLaporanKerusakan();
            break;
        case 4:
            cout << "Masukkan Nama: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan NIU/NIP: ";
            cin >> NiuNip;
            system.registerUser(nama, NiuNip);
            break;
        case 5:
            cout << "Masukkan NIU/NIP: ";
            cin >> NiuNip;
            system.pinjamSepeda(NiuNip);
            break;
        case 6:
            cout << "Masukkan NIU/NIP: ";
            cin >> NiuNip;
            system.pengembalianSepeda(NiuNip);
            break;
        case 7:
            cout << "Masukkan NIU/NIP: ";
            cin >> NiuNip;
            system.laporKerusakan(NiuNip);
            break;
        case 8:
            cout << "Terima kasih telah menggunakan sistem ini.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (choice != 8);

    return 0;
}