/*
Nama Program        : Gaji Pegawai
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 10 November 2026
Deskripsi           : Program Sistem Parkir Gedung merupakan program berbasis Java yang digunakan untuk mengelola data parkir kendaraan, baik untuk pengguna umum maupun pegawai. Program ini mencatat identitas pengguna, jenis kendaraan, lokasi parkir, tanggal dan waktu masuk, serta durasi parkir. Biaya parkir dihitung berdasarkan jenis kendaraan, status pengguna, dan lama parkir, dengan penerapan diskon bagi pengguna umum sesuai ketentuan kunjungan. Program ini menerapkan konsep OOP, meliputi encapsulation, inheritance, polymorphism, abstraction, dan composition.
*/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

const int MAKS_DATA = 1000;

// ==========================================
// CLASS WAKTU
// ==========================================
class Waktu {
private:
    int jam, menit, detik;

public:
    Waktu() {
        jam = 0;
        menit = 0;
        detik = 0;
    }

    Waktu(int j, int m, int d) {
        jam = j;
        menit = m;
        detik = d;
    }

    int getJam() const { return jam; }
    int getMenit() const { return menit; }
    int getDetik() const { return detik; }

    long long toSecond() const {
        return jam * 3600LL + menit * 60LL + detik;
    }

    void output() const {
        cout << setfill('0') << setw(2) << jam << ":"
             << setw(2) << menit << ":"
             << setw(2) << detik << setfill(' ');
    }
};

// ==========================================
// CLASS PERSON
// ==========================================
class Person {
private:
    string nama, alamat;

public:
    Person() {}

    Person(string n, string a) {
        nama = n;
        alamat = a;
    }

    void output() const {
        cout << "Nama           : " << nama << endl;
        cout << "Alamat         : " << alamat << endl;
    }
};

// ==========================================
// CLASS KENDARAAN (INDUK)
// ==========================================
class Kendaraan {
protected:
    string nomorPlat;

public:
    Kendaraan(string plat) {
        nomorPlat = plat;
    }

    virtual ~Kendaraan() {}

    string getNomorPlat() const {
        return nomorPlat;
    }

    virtual int getTarifUmum() const = 0;
    virtual int getTarifPegawai() const = 0;
    virtual string getJenis() const = 0;

    int hitungBiayaUmum(int jam) const {
        return getTarifUmum() * jam;
    }

    int hitungBiayaPegawai(int hari) const {
        return getTarifPegawai() * hari;
    }
};