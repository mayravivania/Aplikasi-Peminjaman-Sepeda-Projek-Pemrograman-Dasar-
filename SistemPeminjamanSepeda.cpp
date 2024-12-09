#include "SistemPeminjamanSepeda.h"

RiwayatPeminjaman::RiwayatPeminjaman(string userName, time_t waktuPeminjaman)
    : userName(userName), waktuPeminjaman(waktuPeminjaman), waktuPengembalian(0) {}

LaporanKerusakan::LaporanKerusakan(string userName, string deskripsi)
    : userName(userName), deskripsi(deskripsi) {}

User::User(string nama, string NiuNip)
    : nama(nama), NiuNip(NiuNip), sepedaTerpinjam(false) {}

SistemPeminjamanSepeda::SistemPeminjamanSepeda() {
    ifstream file(namaFile);
    if (file.is_open()) {
        file >> jumlahSepeda;
        file.close();
        cout << "Data sepeda berhasil dimuat. Total: " << jumlahSepeda << endl;
    } else {
        jumlahSepeda = 0;
        cout << "Gagal memuat data sepeda. Pastikan file " << namaFile << " tersedia.\n";
    }
}

void SistemPeminjamanSepeda::setJumlahSepeda() {
    string inputPassword;
    cout << "Masukkan kata sandi admin: ";
    cin >> inputPassword;
    if (inputPassword != adminPassword) {
        cout << "Kata sandi salah! Akses ditolak.\n";
        return;
    }

    cout << "Masukkan jumlah total sepeda baru: ";
    cin >> jumlahSepeda;

    ofstream file(namaFile);
    if (file.is_open()) {
        file << jumlahSepeda;
        file.close();
        cout << "Jumlah sepeda berhasil diperbarui.\n";
    } else {
        cout << "Gagal membuka file.\n";
    }
}

void SistemPeminjamanSepeda::registerUser(const string& nama, const string& NiuNip) {
    users.push_back(User(nama, NiuNip));
    cout << "User " << nama << " berhasil terdaftar!\n";
}

void SistemPeminjamanSepeda::pinjamSepeda(const string& NiuNip) {
    for (auto& user : users) {
        if (user.NiuNip == NiuNip) {
            if (user.sepedaTerpinjam) {
                cout << "Anda sudah meminjam sepeda!\n";
                return;
            }
            if (jumlahSepeda > 0) {
                jumlahSepeda--;
                user.sepedaTerpinjam = true;
                time_t waktuSekarang = time(nullptr);
                riwayat.emplace_back(user.nama, waktuSekarang);
                cout << "Sepeda berhasil dipinjam oleh " << user.nama << " pada " << ctime(&waktuSekarang);
                return;
            } else {
                cout << "Maaf, tidak ada sepeda yang tersedia.\n";
            }
        }
    }
    cout << "Pengguna tidak ditemukan.\n";
}

void SistemPeminjamanSepeda::pengembalianSepeda(const string& NiuNip) {
    for (auto& user : users) {
        if (user.NiuNip == NiuNip) {
            if (!user.sepedaTerpinjam) {
                cout << "Anda tidak memiliki sepeda untuk dikembalikan.\n";
                return;
            }
            jumlahSepeda++;
            user.sepedaTerpinjam = false;
            time_t waktuSekarang = time(nullptr);
            for (auto& riwayatPeminjaman : riwayat) {
                if (riwayatPeminjaman.userName == user.nama && riwayatPeminjaman.waktuPengembalian == 0) {
                    riwayatPeminjaman.waktuPengembalian = waktuSekarang;
                    cout << "Sepeda berhasil dikembalikan oleh " << user.nama << " pada " << ctime(&waktuSekarang);
                    return;
                }
            }
        }
    }
    cout << "Pengguna tidak ditemukan.\n";
}

void SistemPeminjamanSepeda::laporKerusakan(const string& NiuNip) {
    for (auto& user : users) {
        if (user.NiuNip == NiuNip) {
            if (!user.sepedaTerpinjam) {
                cout << "Anda tidak meminjam sepeda.\n";
                return;
            }
            string deskripsi;
            cout << "Masukkan deskripsi kerusakan: ";
            cin.ignore();
            getline(cin, deskripsi);
            laporanKerusakan.emplace_back(user.nama, deskripsi);
            cout << "Laporan kerusakan berhasil dibuat oleh " << user.nama << ".\n";
            return;
        }
    }
    cout << "Pengguna tidak ditemukan.\n";
}

void SistemPeminjamanSepeda::lihatRiwayatPeminjaman() {
    string inputPassword;
    cout << "Masukkan kata sandi admin: ";
    cin >> inputPassword;
    if (inputPassword != adminPassword) {
        cout << "Kata sandi salah! Akses ditolak.\n";
        return;
    }

    cout << "=== Riwayat Peminjaman ===\n";
    for (const auto& riwayatPeminjaman : riwayat) {
        cout << "Nama: " << riwayatPeminjaman.userName
             << ", Waktu Pinjam: " << ctime(&riwayatPeminjaman.waktuPeminjaman);
        if (riwayatPeminjaman.waktuPengembalian != 0) {
            cout << "Waktu Kembali: " << ctime(&riwayatPeminjaman.waktuPengembalian);
        } else {
            cout << "Status: Belum Dikembalikan\n";
        }
    }
}

void SistemPeminjamanSepeda::lihatLaporanKerusakan() {
    string inputPassword;
    cout << "Masukkan kata sandi admin: ";
    cin >> inputPassword;
    if (inputPassword != adminPassword) {
        cout << "Kata sandi salah! Akses ditolak.\n";
        return;
    }

    cout << "=== Laporan Kerusakan ===\n";
    for (const auto& laporan : laporanKerusakan) {
        cout << "Pelapor: " << laporan.userName
             << ", Kerusakan: " << laporan.deskripsi << endl;
    }
}