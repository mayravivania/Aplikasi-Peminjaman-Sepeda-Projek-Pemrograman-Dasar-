#ifndef SISTEMPEMINJAMANSEPEDA_H
#define SISTEMPEMINJAMANSEPEDA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class RiwayatPeminjaman {
public:
    string userName;
    time_t waktuPeminjaman;
    time_t waktuPengembalian;

    RiwayatPeminjaman(string userName, time_t waktuPeminjaman);
};

class LaporanKerusakan {
public:
    string userName;
    string deskripsi;

    LaporanKerusakan(string userName, string deskripsi);
};

class User {
public:
    string nama;
    string NiuNip;
    bool sepedaTerpinjam;

    User(string nama, string NiuNip);
};

class SistemPeminjamanSepeda {
private:
    vector<User> users;
    vector<RiwayatPeminjaman> riwayat;
    vector<LaporanKerusakan> laporanKerusakan;
    int jumlahSepeda;
    const string namaFile = "sepeda.txt";
    const string adminPassword = "projekprogdas";

public:
    SistemPeminjamanSepeda();
    void setJumlahSepeda();
    void registerUser(const string& nama, const string& NiuNip);
    void pinjamSepeda(const string& NiuNip);
    void pengembalianSepeda(const string& NiuNip);
    void laporKerusakan(const string& NiuNip);
    void lihatRiwayatPeminjaman();
    void lihatLaporanKerusakan();
};

#endif