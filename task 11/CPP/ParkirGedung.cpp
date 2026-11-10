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
#include <memory>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

// ==================== CLASS WAKTU ====================
class Waktu {
private:
    int jam, menit, detik;

public:
    Waktu() {
        jam = 0;
        menit = 0;
        detik = 0;
    }

    Waktu(int jam, int menit, int detik) {
        this->jam = jam;
        this->menit = menit;
        this->detik = detik;
    }

    int getJam() { return jam; }
    int getMenit() { return menit; }
    int getDetik() { return detik; }

    void inputWaktu() {
        cout << "Jam   : ";
        cin >> jam;
        cout << "Menit : ";
        cin >> menit;
        cout << "Detik : ";
        cin >> detik;
    }

    int toSecond() {
        return jam * 3600 + menit * 60 + detik;
    }

    void outputWaktu() {
        cout << setfill('0') << setw(2) << jam << ":"
             << setw(2) << menit << ":"
             << setw(2) << detik << setfill(' ');
    }

    bool valid() {
        return jam >= 0 && menit >= 0 && menit < 60
               && detik >= 0 && detik < 60;
    }
};

// ==================== CLASS PERSON ====================
class Person {
private:
    string nama, alamat;

public:
    Person(string nama, string alamat) {
        this->nama = nama;
        this->alamat = alamat;
    }

    string getNama() { return nama; }
    string getAlamat() { return alamat; }

    void output() {
        cout << "Nama             : " << nama << endl;
        cout << "Alamat           : " << alamat << endl;
    }
};

// ==================== CLASS KENDARAAN ====================
class Kendaraan {
protected:
    string nomorPlat;

public:
    Kendaraan(string nomorPlat) {
        this->nomorPlat = nomorPlat;
    }

    virtual ~Kendaraan() {}

    string getNomorPlat() {
        return nomorPlat;
    }

    virtual int getTarifUmum() = 0;
    virtual int getTarifPegawai() = 0;
    virtual string getJenis() = 0;

    int hitungBiayaUmum(int jam) {
        return getTarifUmum() * jam;
    }

    int hitungBiayaPegawai(int hari) {
        return getTarifPegawai() * hari;
    }
};

// ==================== CLASS MOBIL ====================
class Mobil : public Kendaraan {
public:
    Mobil(string nomorPlat) : Kendaraan(nomorPlat) {}

    int getTarifUmum() override { return 3000; }
    int getTarifPegawai() override { return 6000; }
    string getJenis() override { return "Mobil"; }
};

// ==================== CLASS TRUK ====================
class Truk : public Kendaraan {
public:
    Truk(string nomorPlat) : Kendaraan(nomorPlat) {}

    int getTarifUmum() override { return 5000; }
    int getTarifPegawai() override { return 5000; }
    string getJenis() override { return "Truk"; }
};

// ==================== CLASS MOTOR ====================
class Motor : public Kendaraan {
public:
    Motor(string nomorPlat) : Kendaraan(nomorPlat) {}

    int getTarifUmum() override { return 2000; }
    int getTarifPegawai() override { return 3000; }
    string getJenis() override { return "Motor"; }
};

// ==================== FUNGSI BANTU TANGGAL ====================
tm ubahTanggal(string tanggal) {
    tm waktu = {};
    int tahun, bulan, hari;
    sscanf(tanggal.c_str(), "%d-%d-%d", &tahun, &bulan, &hari);

    waktu.tm_year = tahun - 1900;
    waktu.tm_mon = bulan - 1;
    waktu.tm_mday = hari;
    waktu.tm_isdst = -1;
    mktime(&waktu);

    return waktu;
}

string tanggalKeluar(string tanggal, Waktu masuk, Waktu durasi) {
    tm waktu = ubahTanggal(tanggal);

    waktu.tm_hour = masuk.getJam();
    waktu.tm_min = masuk.getMenit();
    waktu.tm_sec = masuk.getDetik() + durasi.toSecond();

    mktime(&waktu);

    stringstream hasil;
    hasil << setfill('0')
          << setw(4) << waktu.tm_year + 1900 << "-"
          << setw(2) << waktu.tm_mon + 1 << "-"
          << setw(2) << waktu.tm_mday << " ";

    int jam = waktu.tm_hour;
    int menit = waktu.tm_min;
    int detik = waktu.tm_sec;

    hasil << setw(2) << jam << ":" << setw(2) << menit;
    if (detik != 0) {
        hasil << ":" << setw(2) << detik;
    }

    return hasil.str();
}

int mingguKe(string tanggal) {
    tm waktu = ubahTanggal(tanggal);
    return waktu.tm_yday - ((waktu.tm_wday + 6) % 7);
}

// ==================== CLASS PARKIR ====================
class Parkir {
private:
    string kode;
    Person person;
    shared_ptr<Kendaraan> kendaraan;
    bool pegawai;
    string nip;
    string tanggal;
    Waktu waktuMasuk;
    Waktu lamaParkir;
    int kunjungan;
    string lokasi;

public:
    Parkir(string kode, Person person,
           shared_ptr<Kendaraan> kendaraan,
           bool pegawai, string nip, string tanggal,
           Waktu waktuMasuk, Waktu lamaParkir,
           int kunjungan)
        : kode(kode), person(person), kendaraan(kendaraan),
          pegawai(pegawai), nip(nip), tanggal(tanggal),
          waktuMasuk(waktuMasuk), lamaParkir(lamaParkir),
          kunjungan(kunjungan), lokasi("") {}

    void setLokasi(string lokasi) {
        this->lokasi = lokasi;
    }

    shared_ptr<Kendaraan> getKendaraan() {
        return kendaraan;
    }

    bool isPegawai() { return pegawai; }
    string getTanggal() { return tanggal; }
    int getKunjungan() { return kunjungan; }

    string getWaktuKeluar() {
        return tanggalKeluar(tanggal, waktuMasuk, lamaParkir);
    }

    int hitungBiaya() {
        int biaya;
        int totalDetik = lamaParkir.toSecond();

        if (pegawai) {
            if (kendaraan->getJenis() == "Truk") {
                int jam = (totalDetik + 3599) / 3600;
                biaya = kendaraan->hitungBiayaUmum(jam);
            } else {
                int hari = (totalDetik + 86399) / 86400;
                biaya = kendaraan->hitungBiayaPegawai(hari);
            }
        } else {
            int jam = (totalDetik + 3599) / 3600;
            biaya = kendaraan->hitungBiayaUmum(jam);

            if (kunjungan >= 2) {
                biaya -= biaya * 10 / 100;
            }
        }

        return biaya;
    }

    void output() {
        cout << "\n========================================\n";
        cout << "           LAPORAN PARKIR\n";
        cout << "========================================\n";
        cout << "Kode Parkir       : " << kode << endl;
        cout << "Lokasi Parkir     : " << lokasi << endl;
        person.output();

        if (pegawai) {
            cout << "Status Pengguna   : Pegawai\n";
            cout << "NIP               : " << nip << endl;
        } else {
            cout << "Status Pengguna   : Umum\n";
        }

        cout << "Jenis Kendaraan   : " << kendaraan->getJenis() << endl;
        cout << "Nomor Plat        : " << kendaraan->getNomorPlat() << endl;
        cout << "Tanggal           : " << tanggal << endl;
        cout << "Waktu Masuk       : ";
        waktuMasuk.outputWaktu();
        cout << endl;
        cout << "Lama Parkir       : ";
        lamaParkir.outputWaktu();
        cout << endl;
        cout << "Waktu Keluar      : " << getWaktuKeluar() << endl;
        cout << "Kunjungan         : " << kunjungan << endl;
        cout << "Total Biaya       : Rp" << hitungBiaya() << endl;
        cout << "========================================\n";
    }
};

// ==================== CLASS DATAPARKIR ====================
class DataParkir {
private:
    vector<Parkir> parkir;
    int jumlah;

public:
    DataParkir() {
        jumlah = 0;
    }

    vector<Parkir> getParkir() {
        return parkir;
    }

    int getJumlah() {
        return jumlah;
    }

    void setParkir(vector<Parkir> data) {
        parkir = data;
        jumlah = data.size();
    }

    int hitungKunjunganMinggu(string plat, string tanggal) {
        int total = 1;
        tm tanggalDicari = ubahTanggal(tanggal);
        int mingguDicari = mingguKe(tanggal);

        for (int i = 0; i < jumlah; i++) {
            string platLama = parkir[i].getKendaraan()->getNomorPlat();
            string platBaru = plat;

            transform(platLama.begin(), platLama.end(),
                      platLama.begin(), ::tolower);
            transform(platBaru.begin(), platBaru.end(),
                      platBaru.begin(), ::tolower);

            if (!parkir[i].isPegawai() &&
                platLama == platBaru) {
                tm tanggalLama = ubahTanggal(parkir[i].getTanggal());

                if (tanggalLama.tm_year == tanggalDicari.tm_year &&
                    mingguKe(parkir[i].getTanggal()) == mingguDicari) {
                    total++;
                }
            }
        }

        return total;
    }

    void output() {
        cout << "\n\n========== SELURUH DATA PARKIR ==========\n";

        for (int i = 0; i < jumlah; i++) {
            parkir[i].output();
        }

        cout << "Jumlah data parkir: " << jumlah << endl;
    }
};

// ==================== CLASS MENU ====================
class Menu {
private:
    DataParkir dataParkir;

    shared_ptr<Kendaraan> inputKendaraan() {
        int pilihan;
        cout << "\nJenis Kendaraan:\n";
        cout << "1. Mobil\n";
        cout << "2. Truk\n";
        cout << "3. Motor\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        string plat;
        cout << "Nomor Plat: ";
        cin >> ws;
        getline(cin, plat);

        switch (pilihan) {
            case 1: return make_shared<Mobil>(plat);
            case 2: return make_shared<Truk>(plat);
            case 3: return make_shared<Motor>(plat);
            default:
                cout << "Jenis kendaraan tidak valid.\n";
                return nullptr;
        }
    }

    void inputData(string lokasi) {
        int jumlahInput;
        cout << "\nJumlah data parkir: ";
        cin >> jumlahInput;

        if (jumlahInput < 1) {
            cout << "Jumlah harus lebih dari 0.\n";
            return;
        }

        vector<Parkir> dataBaru;

        for (int i = 0; i < jumlahInput; i++) {
            cout << "\nData Parkir ke-" << i + 1 << endl;

            string kode, nama, alamat, nip, tanggal;
            int pilihanPengguna;

            cout << "Kode Parkir: ";
            cin >> ws;
            getline(cin, kode);

            cout << "Nama: ";
            getline(cin, nama);

            cout << "Alamat: ";
            getline(cin, alamat);

            cout << "Pengguna (1. Umum / 2. Pegawai): ";
            cin >> pilihanPengguna;

            if (pilihanPengguna != 1 && pilihanPengguna != 2) {
                cout << "Pilihan pengguna tidak valid. Data dilewati.\n";
                continue;
            }

            bool pegawai = pilihanPengguna == 2;
            nip = "";

            if (pegawai) {
                cout << "NIP: ";
                cin >> ws;
                getline(cin, nip);
            }

            shared_ptr<Kendaraan> kendaraan = inputKendaraan();

            if (kendaraan == nullptr) {
                cout << "Data dilewati.\n";
                continue;
            }

            cout << "Tanggal (YYYY-MM-DD): ";
            cin >> tanggal;

            Waktu waktuMasuk, lamaParkir;

            cout << "\nWaktu Masuk\n";
            waktuMasuk.inputWaktu();

            cout << "\nLama Parkir\n";
            lamaParkir.inputWaktu();

            if (!waktuMasuk.valid() ||
                waktuMasuk.getJam() > 23 ||
                waktuMasuk.getMenit() > 59 ||
                waktuMasuk.getDetik() > 59) {
                cout << "Waktu masuk tidak valid. Data dilewati.\n";
                continue;
            }

            if (!lamaParkir.valid() ||
                lamaParkir.getJam() < 0 ||
                lamaParkir.toSecond() < 1) {
                cout << "Lama parkir tidak valid. Data dilewati.\n";
                continue;
            }

            int kunjungan = 1;

            if (!pegawai) {
                string plat = kendaraan->getNomorPlat();

                for (int j = 0; j < (int)dataBaru.size(); j++) {
                    string platLama =
                        dataBaru[j].getKendaraan()->getNomorPlat();

                    transform(plat.begin(), plat.end(),
                              plat.begin(), ::tolower);
                    transform(platLama.begin(), platLama.end(),
                              platLama.begin(), ::tolower);

                    if (!dataBaru[j].isPegawai() &&
                        plat == platLama &&
                        dataBaru[j].getTanggal().substr(0, 4) ==
                        tanggal.substr(0, 4) &&
                        mingguKe(dataBaru[j].getTanggal()) ==
                        mingguKe(tanggal)) {
                        kunjungan++;
                    }
                }

                kunjungan += dataParkir.hitungKunjunganMinggu(
                    kendaraan->getNomorPlat(), tanggal) - 1;
            }

            Person person(nama, alamat);

            Parkir data(kode, person, kendaraan, pegawai,
                        nip, tanggal, waktuMasuk,
                        lamaParkir, kunjungan);

            data.setLokasi(lokasi);
            dataBaru.push_back(data);
        }

        vector<Parkir> gabungan = dataParkir.getParkir();
        gabungan.insert(gabungan.end(), dataBaru.begin(), dataBaru.end());

        dataParkir.setParkir(gabungan);
    }

public:
    // Constructor Menu
    Menu() {
        dataParkir = DataParkir();
    }

    // Input parkir dalam gedung
    void inputDalam() {
        cout << "\n===== INPUT PARKIR DALAM GEDUNG =====\n";
        inputData("Dalam");
    }

    // Input parkir luar gedung
    void inputLuar() {
        cout << "\n===== INPUT PARKIR LUAR GEDUNG =====\n";
        inputData("Luar");
    }

    // Menampilkan laporan parkir
    void lihatLaporan() {
        dataParkir.output();
    }

    // Menjalankan menu utama
    void run() {
        int pilihan;

        do {
            cout << "\n================================\n";
            cout << "       SISTEM PARKIR GEDUNG\n";
            cout << "================================\n";
            cout << "1. Input Parkir Dalam\n";
            cout << "2. Input Parkir Luar\n";
            cout << "3. Lihat Laporan Parkir\n";
            cout << "4. Keluar\n";
            cout << "Pilihan: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1:
                    inputDalam();
                    break;
                case 2:
                    inputLuar();
                    break;
                case 3:
                    lihatLaporan();
                    break;
                case 4:
                    cout << "Terima kasih.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 4);
    }
};

// ==================== MAIN ====================
int main() {
    Menu menu;
    menu.run();
    return 0;
}

