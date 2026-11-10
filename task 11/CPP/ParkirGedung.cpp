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
#include <vector>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <sstream>
#include <limits>

using namespace std;

// ==================== CLASS WAKTU ====================

class Waktu {
private:
    int jam, menit, detik;

public:
    Waktu() : jam(0), menit(0), detik(0) {}

    Waktu(int jam, int menit, int detik)
        : jam(jam), menit(menit), detik(detik) {}

    int getJam() const { return jam; }
    int getMenit() const { return menit; }
    int getDetik() const { return detik; }

    void inputWaktu() {
        cout << "Jam   : ";
        cin >> jam;

        cout << "Menit : ";
        cin >> menit;

        cout << "Detik : ";
        cin >> detik;
    }

    long long toSecond() const {
        return jam * 3600LL + menit * 60LL + detik;
    }

    void outputWaktu() const {
        cout << setfill('0')
             << setw(2) << jam << ":"
             << setw(2) << menit << ":"
             << setw(2) << detik
             << setfill(' ');
    }
};

// ==================== FUNGSI TANGGAL ====================

struct Tanggal {
    int tahun, bulan, hari;

    static Tanggal input(const string& teks) {
        Tanggal t;
        sscanf(teks.c_str(), "%d-%d-%d",
               &t.tahun, &t.bulan, &t.hari);
        return t;
    }

    tm toTM() const {
        tm waktu = {};
        waktu.tm_year = tahun - 1900;
        waktu.tm_mon = bulan - 1;
        waktu.tm_mday = hari;
        waktu.tm_isdst = -1;
        mktime(&waktu);
        return waktu;
    }

    string toString() const {
        ostringstream out;
        out << setfill('0')
            << setw(4) << tahun << "-"
            << setw(2) << bulan << "-"
            << setw(2) << hari;
        return out.str();
    }

    Tanggal tambahDetik(long long detik) const {
        tm waktu = toTM();
        time_t waktuMasuk = mktime(&waktu);
        waktuMasuk += detik;

        tm* hasil = localtime(&waktuMasuk);

        return {
            hasil->tm_year + 1900,
            hasil->tm_mon + 1,
            hasil->tm_mday
        };
    }

    string minggu() const {
        tm waktu = toTM();

        // Menentukan hari Senin dalam minggu yang sama.
        int mundur = (waktu.tm_wday + 6) % 7;
        waktu.tm_mday -= mundur;

        mktime(&waktu);

        ostringstream out;
        out << setw(4) << setfill('0')
            << waktu.tm_year + 1900 << "-"
            << setw(2) << waktu.tm_mon + 1 << "-"
            << setw(2) << waktu.tm_mday;

        return out.str();
    }
};

// ==================== CLASS PERSON ====================

class Person {
private:
    string nama, alamat;

public:
    Person(string nama, string alamat)
        : nama(nama), alamat(alamat) {}

    string getNama() const { return nama; }
    string getAlamat() const { return alamat; }

    void output() const {
        cout << "Nama           : " << nama << endl;
        cout << "Alamat         : " << alamat << endl;
    }
};

// ==================== CLASS KENDARAAN ====================

class Kendaraan {
protected:
    string nomorPlat;

public:
    Kendaraan(string nomorPlat) : nomorPlat(nomorPlat) {}

    virtual int getTarifUmum() const = 0;
    virtual int getTarifPegawai() const = 0;
    virtual string getJenis() const = 0;

    string getNomorPlat() const {
        return nomorPlat;
    }

    int hitungBiayaUmum(int jam) const {
        return getTarifUmum() * jam;
    }

    int hitungBiayaPegawai(int hari) const {
        return getTarifPegawai() * hari;
    }

    virtual ~Kendaraan() {}
};

class Mobil : public Kendaraan {
public:
    Mobil(string plat) : Kendaraan(plat) {}

    int getTarifUmum() const override { return 3000; }
    int getTarifPegawai() const override { return 6000; }
    string getJenis() const override { return "Mobil"; }
};

class Truk : public Kendaraan {
public:
    Truk(string plat) : Kendaraan(plat) {}

    int getTarifUmum() const override { return 5000; }
    int getTarifPegawai() const override { return 5000; }
    string getJenis() const override { return "Truk"; }
};

class Motor : public Kendaraan {
public:
    Motor(string plat) : Kendaraan(plat) {}

    int getTarifUmum() const override { return 2000; }
    int getTarifPegawai() const override { return 3000; }
    string getJenis() const override { return "Motor"; }
};

// ==================== CLASS PARKIR ====================

class Parkir {
private:
    string kode;
    Person person;
    Kendaraan* kendaraan;
    bool pegawai;
    string nip;

    Tanggal tanggal;
    Waktu waktuMasuk;
    Waktu lamaParkir;

    int kunjungan;
    string lokasi;

public:
    Parkir(string kode, Person person,
           Kendaraan* kendaraan, bool pegawai,
           string nip, Tanggal tanggal,
           Waktu waktuMasuk, Waktu lamaParkir,
           int kunjungan, string lokasi)
        : kode(kode), person(person),
          kendaraan(kendaraan), pegawai(pegawai),
          nip(nip), tanggal(tanggal),
          waktuMasuk(waktuMasuk),
          lamaParkir(lamaParkir),
          kunjungan(kunjungan), lokasi(lokasi) {}

    Kendaraan* getKendaraan() const {
        return kendaraan;
    }

    bool isPegawai() const {
        return pegawai;
    }

    Tanggal getTanggal() const {
        return tanggal;
    }

    int getKunjungan() const {
        return kunjungan;
    }

    Tanggal getTanggalKeluar() const {
        long long total = waktuMasuk.toSecond()
                        + lamaParkir.toSecond();

        return tanggal.tambahDetik(total);
    }

    string getJamKeluar() const {
        long long total = waktuMasuk.toSecond()
                        + lamaParkir.toSecond();

        int jam = (total / 3600) % 24;
        int menit = (total / 60) % 60;
        int detik = total % 60;

        ostringstream out;
        out << setfill('0')
            << setw(2) << jam << ":"
            << setw(2) << menit;

        if (detik != 0) {
            out << ":" << setw(2) << detik;
        }

        return out.str();
    }

    int hitungBiaya() const {
        long long totalDetik = lamaParkir.toSecond();

        if (pegawai) {
            if (dynamic_cast<Truk*>(kendaraan) != nullptr) {
                int jam = ceil(totalDetik / 3600.0);
                return kendaraan->hitungBiayaUmum(jam);
            }

            int hari = ceil(totalDetik / 86400.0);
            return kendaraan->hitungBiayaPegawai(hari);
        }

        int jam = ceil(totalDetik / 3600.0);
        int biaya = kendaraan->hitungBiayaUmum(jam);

        if (kunjungan >= 2) {
            biaya -= biaya * 10 / 100;
        }

        return biaya;
    }

    void output() const {
        cout << "\n====================================" << endl;
        cout << "         DATA PARKIR GEDUNG" << endl;
        cout << "====================================" << endl;

        cout << "Kode Parkir    : " << kode << endl;
        cout << "Lokasi         : " << lokasi << endl;

        person.output();

        cout << "Jenis Pengguna : "
             << (pegawai ? "Pegawai" : "Umum") << endl;

        if (pegawai) {
            cout << "NIP            : " << nip << endl;
        }

        cout << "Kendaraan      : " << kendaraan->getJenis() << endl;
        cout << "Nomor Plat     : " << kendaraan->getNomorPlat() << endl;
        cout << "Tanggal Masuk  : " << tanggal.toString() << endl;

        cout << "Jam Masuk      : ";
        waktuMasuk.outputWaktu();
        cout << endl;

        cout << "Lama Parkir    : ";
        lamaParkir.outputWaktu();
        cout << endl;

        cout << "Tanggal Keluar : "
             << getTanggalKeluar().toString() << endl;

        cout << "Jam Keluar     : " << getJamKeluar() << endl;

        if (!pegawai) {
            cout << "Kunjungan      : " << kunjungan << endl;

            if (kunjungan >= 2) {
                cout << "Diskon         : 10%" << endl;
            }
        }

        cout << "Total Biaya    : Rp" << hitungBiaya() << endl;
        cout << "====================================" << endl;
    }
};

// ==================== CLASS DATA PARKIR ====================

class DataParkir {
private:
    vector<Parkir*> parkir;

public:
    int hitungKunjunganMinggu(string plat,
                              Tanggal tanggal) const {
        int total = 0;

        for (Parkir* p : parkir) {
            if (p != nullptr &&
                !p->isPegawai() &&
                p->getKendaraan()->getNomorPlat() == plat) {

                if (p->getTanggal().minggu() == tanggal.minggu()) {
                    total++;
                }
            }
        }

        return total;
    }

    void tambah(Parkir* p) {
        parkir.push_back(p);
    }

    void output() const {
        cout << "\n\n========== LAPORAN PARKIR ==========" << endl;

        if (parkir.empty()) {
            cout << "Belum ada data parkir." << endl;
            return;
        }

        for (Parkir* p : parkir) {
            if (p != nullptr) {
                p->output();
            }
        }

        cout << "\nJumlah Transaksi : " << parkir.size() << endl;
        cout << "====================================" << endl;
    }
};

// ==================== CLASS MENU ====================

class Menu {
private:
    DataParkir dataParkir;

public:
    void run() {
        cout << "====================================" << endl;
        cout << "       SISTEM PARKIR GEDUNG" << endl;
        cout << "====================================" << endl;

        int jumlah;

        cout << "Jumlah data parkir: ";
        cin >> jumlah;

        if (jumlah < 1) {
            cout << "Jumlah harus lebih dari 0." << endl;
            return;
        }

        for (int i = 0; i < jumlah; i++) {
            cout << "\nData Parkir ke-" << i + 1 << endl;

            string kode;
            cout << "Kode parkir    : ";
            cin >> ws;
            getline(cin, kode);

            int pilihanLokasi;
            cout << "Lokasi parkir (1. Dalam / 2. Luar): ";
            cin >> pilihanLokasi;

            if (pilihanLokasi != 1 && pilihanLokasi != 2) {
                cout << "Lokasi tidak valid. Data dilewati." << endl;
                continue;
            }

            string lokasi = pilihanLokasi == 2 ? "Luar" : "Dalam";

            int pilihanPengguna;
            cout << "Jenis pengguna (1. Umum / 2. Pegawai): ";
            cin >> pilihanPengguna;

            if (pilihanPengguna != 1 && pilihanPengguna != 2) {
                cout << "Jenis pengguna tidak valid." << endl;
                continue;
            }

            bool pegawai = pilihanPengguna == 2;

            string nama, alamat, nip = "-";

            cout << "Nama           : ";
            cin >> ws;
            getline(cin, nama);

            cout << "Alamat         : ";
            getline(cin, alamat);

            if (pegawai) {
                cout << "NIP            : ";
                getline(cin, nip);
            }

            int jenis;
            cout << "Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): ";
            cin >> jenis;

            if (jenis < 1 || jenis > 3) {
                cout << "Jenis kendaraan tidak valid." << endl;
                continue;
            }

            string plat;
            cout << "Nomor plat     : ";
            cin >> ws;
            getline(cin, plat);

            string teksTanggal;
            cout << "Tanggal parkir (YYYY-MM-DD): ";
            getline(cin, teksTanggal);

            Tanggal tanggal = Tanggal::input(teksTanggal);

            cout << "\nMasukkan waktu masuk:" << endl;
            Waktu waktuMasuk;
            waktuMasuk.inputWaktu();

            cout << "\nMasukkan lama parkir:" << endl;
            Waktu lamaParkir;
            lamaParkir.inputWaktu();

            if (waktuMasuk.getJam() < 0 ||
                waktuMasuk.getJam() > 23 ||
                waktuMasuk.getMenit() < 0 ||
                waktuMasuk.getMenit() > 59 ||
                waktuMasuk.getDetik() < 0 ||
                waktuMasuk.getDetik() > 59) {

                cout << "Waktu masuk tidak valid." << endl;
                continue;
            }

            if (lamaParkir.getJam() < 0 ||
                lamaParkir.getMenit() < 0 ||
                lamaParkir.getMenit() > 59 ||
                lamaParkir.getDetik() < 0 ||
                lamaParkir.getDetik() > 59 ||
                lamaParkir.toSecond() < 1) {

                cout << "Durasi parkir tidak valid." << endl;
                continue;
            }

            Kendaraan* kendaraan = nullptr;

            switch (jenis) {
                case 1:
                    kendaraan = new Mobil(plat);
                    break;
                case 2:
                    kendaraan = new Truk(plat);
                    break;
                case 3:
                    kendaraan = new Motor(plat);
                    break;
            }

            Person person(nama, alamat);

            int kunjunganSebelumnya = 0;

            if (!pegawai) {
                kunjunganSebelumnya =
                    dataParkir.hitungKunjunganMinggu(plat, tanggal);
            }

            int kunjunganSaatIni =
                pegawai ? 0 : kunjunganSebelumnya + 1;

            Parkir* data = new Parkir(
                kode, person, kendaraan, pegawai, nip,
                tanggal, waktuMasuk, lamaParkir,
                kunjunganSaatIni, lokasi
            );

            dataParkir.tambah(data);
        }

        dataParkir.output();
    }
};

// ==================== MAIN PROGRAM ====================

int main() {
    Menu menu;
    menu.run();

    return 0;
}

