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

// ==========================================
// CLASS MOBIL
// ==========================================
class Mobil : public Kendaraan {
public:
    Mobil(string plat) : Kendaraan(plat) {}

    int getTarifUmum() const override {
        return 3000;
    }

    int getTarifPegawai() const override {
        return 6000;
    }

    string getJenis() const override {
        return "Mobil";
    }
};

// ==========================================
// CLASS TRUK
// ==========================================
class Truk : public Kendaraan {
public:
    Truk(string plat) : Kendaraan(plat) {}

    int getTarifUmum() const override {
        return 5000;
    }

    int getTarifPegawai() const override {
        return 5000;
    }

    string getJenis() const override {
        return "Truk";
    }
};

// ==========================================
// CLASS MOTOR
// ==========================================
class Motor : public Kendaraan {
public:
    Motor(string plat) : Kendaraan(plat) {}

    int getTarifUmum() const override {
        return 2000;
    }

    int getTarifPegawai() const override {
        return 3000;
    }

    string getJenis() const override {
        return "Motor";
    }
};

// ==========================================
// FUNGSI BANTU TANGGAL
// ==========================================
bool parseTanggal(const string& teks, int& tahun, int& bulan, int& hari) {
    char tanda1, tanda2;
    stringstream ss(teks);

    if (!(ss >> tahun >> tanda1 >> bulan >> tanda2 >> hari)) {
        return false;
    }

    if (tanda1 != '-' || tanda2 != '-' ||
        bulan < 1 || bulan > 12 || hari < 1 || hari > 31) {
        return false;
    }

    tm waktu = {};
    waktu.tm_year = tahun - 1900;
    waktu.tm_mon = bulan - 1;
    waktu.tm_mday = hari;
    waktu.tm_hour = 12;
    mktime(&waktu);

    return waktu.tm_year == tahun - 1900 &&
           waktu.tm_mon == bulan - 1 &&
           waktu.tm_mday == hari;
}

string formatTanggal(int tahun, int bulan, int hari) {
    stringstream ss;
    ss << setfill('0') << setw(4) << tahun << "-"
       << setw(2) << bulan << "-"
       << setw(2) << hari;
    return ss.str();
}

string kunciMinggu(int tahun, int bulan, int hari) {
    tm waktu = {};
    waktu.tm_year = tahun - 1900;
    waktu.tm_mon = bulan - 1;
    waktu.tm_mday = hari;
    waktu.tm_hour = 12;
    mktime(&waktu);

    // tm_wday: Minggu = 0, Senin = 1, ..., Sabtu = 6.
    int mundur = (waktu.tm_wday + 6) % 7;
    waktu.tm_mday -= mundur;
    mktime(&waktu);

    return formatTanggal(
        waktu.tm_year + 1900,
        waktu.tm_mon + 1,
        waktu.tm_mday
    );
}

string tambahDetikTanggal(int tahun, int bulan, int hari,
                          int jam, int menit, int detik,
                          long long tambahanDetik,
                          string& jamKeluar) {
    tm waktu = {};
    waktu.tm_year = tahun - 1900;
    waktu.tm_mon = bulan - 1;
    waktu.tm_mday = hari;
    waktu.tm_hour = jam;
    waktu.tm_min = menit;
    waktu.tm_sec = detik;

    time_t waktuMasuk = mktime(&waktu);
    time_t waktuKeluar = waktuMasuk + tambahanDetik;

    tm* hasil = localtime(&waktuKeluar);

    stringstream ssJam;
    ssJam << setfill('0') << setw(2) << hasil->tm_hour << ":"
          << setw(2) << hasil->tm_min << ":"
          << setw(2) << hasil->tm_sec;
    jamKeluar = ssJam.str();

    return formatTanggal(
        hasil->tm_year + 1900,
        hasil->tm_mon + 1,
        hasil->tm_mday
    );
}

// ==========================================
// CLASS PARKIR
// ==========================================
class Parkir {
private:
    string kode, nip, lokasi;
    Person person;
    Kendaraan* kendaraan;
    bool pegawai;

    int tahun, bulan, hari;
    Waktu waktuMasuk, lamaParkir;
    int kunjungan;

public:
    Parkir() {
        kendaraan = nullptr;
        pegawai = false;
        tahun = bulan = hari = 0;
        kunjungan = 0;
    }

    void isiData(string k, Person p, Kendaraan* kend, bool peg,
                 string n, int th, int bl, int hr,
                 Waktu masuk, Waktu lama, int kunj, string lok) {
        kode = k;
        person = p;
        kendaraan = kend;
        pegawai = peg;
        nip = n;
        tahun = th;
        bulan = bl;
        hari = hr;
        waktuMasuk = masuk;
        lamaParkir = lama;
        kunjungan = kunj;
        lokasi = lok;
    }

    Kendaraan* getKendaraan() const {
        return kendaraan;
    }

    bool isPegawai() const {
        return pegawai;
    }

    int getTahun() const { return tahun; }
    int getBulan() const { return bulan; }
    int getHari() const { return hari; }
    int getKunjungan() const { return kunjungan; }

    bool platSama(const string& plat) const {
        return kendaraan != nullptr &&
               kendaraan->getNomorPlat() == plat;
    }

    int hitungBiaya() const {
        long long totalDetik = lamaParkir.toSecond();

        if (pegawai) {
            if (kendaraan->getJenis() == "Truk") {
                int jam = (int)ceil(totalDetik / 3600.0);
                return kendaraan->hitungBiayaUmum(jam);
            }

            int hariParkir = (int)ceil(totalDetik / 86400.0);
            return kendaraan->hitungBiayaPegawai(hariParkir);
        }

        int jam = (int)ceil(totalDetik / 3600.0);
        int biaya = kendaraan->hitungBiayaUmum(jam);

        if (kunjungan >= 2) {
            biaya -= biaya * 10 / 100;
        }

        return biaya;
    }

    void output() const {
        string jamKeluar;
        string tanggalKeluar = tambahDetikTanggal(
            tahun, bulan, hari,
            waktuMasuk.getJam(),
            waktuMasuk.getMenit(),
            waktuMasuk.getDetik(),
            lamaParkir.toSecond(),
            jamKeluar
        );

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
        cout << "Tanggal Masuk  : " << formatTanggal(tahun, bulan, hari) << endl;

        cout << "Jam Masuk      : ";
        waktuMasuk.output();
        cout << endl;

        cout << "Lama Parkir    : ";
        lamaParkir.output();
        cout << endl;

        cout << "Tanggal Keluar : " << tanggalKeluar << endl;
        cout << "Jam Keluar     : " << jamKeluar << endl;

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

// ==========================================
// CLASS DATA PARKIR
// ==========================================
class DataParkir {
private:
    Parkir data[MAKS_DATA];
    int jumlah;

public:
    DataParkir() {
        jumlah = 0;
    }

    int getJumlah() const {
        return jumlah;
    }

    Parkir getData(int indeks) const {
        return data[indeks];
    }

    int hitungKunjunganMinggu(const string& plat,
                              int tahun, int bulan, int hari) const {
        int total = 0;
        string mingguDicari = kunciMinggu(tahun, bulan, hari);

        for (int i = 0; i < jumlah; i++) {
            if (!data[i].isPegawai() && data[i].platSama(plat)) {
                string mingguData = kunciMinggu(
                    data[i].getTahun(),
                    data[i].getBulan(),
                    data[i].getHari()
                );

                if (mingguData == mingguDicari) {
                    total++;
                }
            }
        }

        return total;
    }

    void tambah(Parkir p) {
        if (jumlah < MAKS_DATA) {
            data[jumlah] = p;
            jumlah++;
        }
    }

    void output() const {
        cout << "\n\n========== LAPORAN PARKIR ==========" << endl;

        if (jumlah == 0) {
            cout << "Belum ada data parkir." << endl;
            return;
        }

        for (int i = 0; i < jumlah; i++) {
            data[i].output();
        }

        cout << "\nJumlah Transaksi : " << jumlah << endl;
        cout << "====================================" << endl;
    }
};

// ==========================================
// CLASS MENU
// ==========================================
class Menu {
private:
    DataParkir dataParkir;

    int inputInt(const string& pesan) {
        int nilai;
        cout << pesan;
        cin >> nilai;
        return nilai;
    }

public:
    void run() {
        cout << "====================================" << endl;
        cout << "       SISTEM PARKIR GEDUNG" << endl;
        cout << "====================================" << endl;

        int jumlah = inputInt("Jumlah data parkir: ");

        if (jumlah < 1) {
            cout << "Jumlah harus lebih dari 0." << endl;
            return;
        }

        if (jumlah > MAKS_DATA) {
            cout << "Maksimal data adalah " << MAKS_DATA << "." << endl;
            return;
        }

        Parkir dataBaru[MAKS_DATA];
        int jumlahValid = 0;

        for (int i = 0; i < jumlah; i++) {
            cout << "\nData Parkir ke-" << i + 1 << endl;

            string kode, nama, alamat, nip = "-", plat, tanggalInput;
            int pilihanLokasi, pilihanPengguna, jenis;
            int tahun, bulan, hari;

            cout << "Kode parkir    : ";
            cin >> ws;
            getline(cin, kode);

            pilihanLokasi = inputInt(
                "Lokasi parkir (1. Dalam / 2. Luar): "
            );

            if (pilihanLokasi != 1 && pilihanLokasi != 2) {
                cout << "Lokasi tidak valid. Data dilewati." << endl;
                continue;
            }

            pilihanPengguna = inputInt(
                "Jenis pengguna (1. Umum / 2. Pegawai): "
            );

            if (pilihanPengguna != 1 && pilihanPengguna != 2) {
                cout << "Jenis pengguna tidak valid. Data dilewati." << endl;
                continue;
            }

            bool pegawai = pilihanPengguna == 2;

            cout << "Nama           : ";
            getline(cin >> ws, nama);

            cout << "Alamat         : ";
            getline(cin, alamat);

            if (pegawai) {
                cout << "NIP            : ";
                getline(cin, nip);
            }

            jenis = inputInt(
                "Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): "
            );

            if (jenis < 1 || jenis > 3) {
                cout << "Jenis kendaraan tidak valid. Data dilewati." << endl;
                continue;
            }

            cout << "Nomor plat     : ";
            getline(cin >> ws, plat);

            cout << "Tanggal parkir (YYYY-MM-DD): ";
            getline(cin, tanggalInput);

            if (!parseTanggal(tanggalInput, tahun, bulan, hari)) {
                cout << "Tanggal tidak valid. Data dilewati." << endl;
                continue;
            }

            cout << "\nMasukkan waktu masuk:" << endl;
            int jam, menit, detik;

            jam = inputInt("Jam   : ");
            menit = inputInt("Menit : ");
            detik = inputInt("Detik : ");

            if (jam < 0 || jam > 23 ||
                menit < 0 || menit > 59 ||
                detik < 0 || detik > 59) {
                cout << "Waktu masuk tidak valid. Data dilewati." << endl;
                continue;
            }

            Waktu waktuMasuk(jam, menit, detik);

            cout << "\nMasukkan lama parkir:" << endl;

            int jamLama, menitLama, detikLama;
            jamLama = inputInt("Jam   : ");
            menitLama = inputInt("Menit : ");
            detikLama = inputInt("Detik : ");

            if (jamLama < 0 || menitLama < 0 || menitLama > 59 ||
                detikLama < 0 || detikLama > 59 ||
                (jamLama == 0 && menitLama == 0 && detikLama == 0)) {
                cout << "Durasi parkir tidak valid. Data dilewati." << endl;
                continue;
            }

            Waktu lamaParkir(jamLama, menitLama, detikLama);

            Kendaraan* kendaraan = nullptr;

            if (jenis == 1) {
                kendaraan = new Mobil(plat);
            } else if (jenis == 2) {
                kendaraan = new Truk(plat);
            } else {
                kendaraan = new Motor(plat);
            }

            int kunjunganSebelumnya = 0;

            if (!pegawai) {
                for (int j = 0; j < jumlahValid; j++) {
                    if (!dataBaru[j].isPegawai() &&
                        dataBaru[j].platSama(plat) &&
                        kunciMinggu(
                            dataBaru[j].getTahun(),
                            dataBaru[j].getBulan(),
                            dataBaru[j].getHari()
                        ) == kunciMinggu(tahun, bulan, hari)) {
                        kunjunganSebelumnya++;
                    }
                }

                kunjunganSebelumnya +=
                    dataParkir.hitungKunjunganMinggu(
                        plat, tahun, bulan, hari
                    );
            }

            int kunjunganSaatIni =
                pegawai ? 0 : kunjunganSebelumnya + 1;

            string lokasi = pilihanLokasi == 1 ? "Dalam" : "Luar";

            Parkir transaksi;
            transaksi.isiData(
                kode, Person(nama, alamat), kendaraan,
                pegawai, nip, tahun, bulan, hari,
                waktuMasuk, lamaParkir,
                kunjunganSaatIni, lokasi
            );

            dataBaru[jumlahValid] = transaksi;
            jumlahValid++;
        }

        for (int i = 0; i < jumlahValid; i++) {
            dataParkir.tambah(dataBaru[i]);
        }

        dataParkir.output();
    }
};

// ==========================================
// PROGRAM UTAMA
// ==========================================
int main() {
    Menu menu;
    menu.run();

    return 0;
}
