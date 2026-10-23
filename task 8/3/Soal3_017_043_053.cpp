/*
Nama Program        : Soal3_017_043_053.cpp
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 13 Oktober 2026
Deskripsi           : Program OOP Array of Object untuk menghitung
                      gaji harian dan lembur pegawai berdasarkan
                      lama kerja.
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Waktu {
private:
    int jam;
    int menit;
    int detik;

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

    void setJam(int jam) { this->jam = jam; }
    int getJam() { return jam; }

    void setMenit(int menit) { this->menit = menit; }
    int getMenit() { return menit; }

    void setDetik(int detik) { this->detik = detik; }
    int getDetik() { return detik; }

    void input(string label) {
        cout << "Waktu " << label << " (jam menit detik): ";
        cin >> jam >> menit >> detik;
    }

    int keDetik() {
        return jam * 3600 + menit * 60 + detik;
    }

    // BARU: membuat objek Waktu dari total detik
    static Waktu dariDetik(int total) {
        return Waktu(total / 3600, (total % 3600) / 60, total % 60);
    }

    int selisihDetik(Waktu waktu) {
        int selisih = waktu.keDetik() - this->keDetik();
        if (selisih < 0) {
            selisih += 86400;
        }
        return selisih;
    }

    void output(int lebar) {
        cout << right << setfill('0') << setw(2) << jam << ":"
             << setw(2) << menit << ":"
             << setw(2) << detik << setfill(' ')
             << setw(lebar - 8) << "";
    }
};


class Pegawai {
private:
    string NIP;
    string nama;
    int gol;
    Waktu datang;
    Waktu pulang;

public:
    // ===== Constructor =====
    Pegawai() {
        NIP = "";
        nama = "";
        gol = 0;
    }

    Pegawai(string NIP, string nama, int gol, Waktu datang, Waktu pulang) {
        this->NIP = NIP;
        this->nama = nama;
        this->gol = gol;
        this->datang = datang;
        this->pulang = pulang;
    }

    // ===== Setter & Getter =====
    void setNIP(string NIP) { this->NIP = NIP; }
    string getNIP() { return NIP; }

    void setNama(string nama) { this->nama = nama; }
    string getNama() { return nama; }

    void setGol(int gol) { this->gol = gol; }
    int getGol() { return gol; }

    void setDatang(Waktu datang) { this->datang = datang; }
    Waktu getDatang() { return datang; }

    void setPulang(Waktu pulang) { this->pulang = pulang; }
    Waktu getPulang() { return pulang; }

    // ===== INPUT (semua atribut dibaca di sini) =====
    void input() {
        cout << "NIP   : ";
        getline(cin, NIP);
        cout << "Nama  : ";
        getline(cin, nama);
        cout << "Gol   : ";
        cin >> gol;
        while (gol < 1 || gol > 4) {
            cout << "Gol harus 1 - 4, ulangi: ";
            cin >> gol;
        }
        datang.input("datang");
        pulang.input("pulang");
    }

    int hitungDurasiDetik() {
        return datang.selisihDetik(pulang);
    }

    Waktu hitungLamaKerja() {
        return Waktu::dariDetik(hitungDurasiDetik());
    }

    int hitungGajiHarian() {
        switch (gol) {
            case 1: return 150000;
            case 2: return 200000;
            case 3: return 400000;
            case 4: return 500000;
        }
        return 0;
    }

    int hitungTarifLembur() {
        switch (gol) {
            case 1: return 50000;
            case 2: return 75000;
            case 3: return 150000;
            case 4: return 200000;
        }
        return 0;
    }

    Waktu hitungKelebihanWaktu() {
        int durasi = hitungDurasiDetik();
        if (durasi < 8 * 3600) {
            return Waktu(0, 0, 0);
        }
        return Waktu::dariDetik(durasi - 8 * 3600);
    }

    int hitungJamLembur() {
        return hitungKelebihanWaktu().getJam();
    }

    int hitungLembur() {
        return hitungJamLembur() * hitungTarifLembur();
    }

    int hitungTotal() {
        return hitungGajiHarian() + hitungLembur();
    }

    string hitungStatus() {
        if (hitungDurasiDetik() < 8 * 3600) {
            return "Peringatan";
        }
        return "ok";
    }

    // ===== OUTPUT =====
    void output(int nomor) {
        cout << left << setw(4) << nomor;
        cout << left << setw(8) << NIP;
        cout << left << setw(15) << nama;
        cout << left << setw(5) << gol;
        datang.output(10);
        pulang.output(10);
        hitungLamaKerja().output(10);
        hitungKelebihanWaktu().output(12);
        cout << left << setw(13) << hitungGajiHarian();
        cout << left << setw(10) << hitungLembur();
        cout << left << setw(10) << hitungTotal();
        cout << hitungStatus() << endl;
    }
};

class ArrayPegawai {
private:
    Pegawai *pegawai;
    int jumlah;

    ArrayPegawai(const ArrayPegawai& lain);
    ArrayPegawai& operator=(const ArrayPegawai& lain);

    void garis() {
        for (int i = 0; i < 117; i++) {
            cout << "-";
        }
        cout << endl;
    }

public:
    ArrayPegawai() {
        pegawai = NULL;
        jumlah = 0;
    }

    ArrayPegawai(int jumlah) {
        this->jumlah = jumlah;
        pegawai = new Pegawai[jumlah];
    }

    ArrayPegawai(Pegawai isi[], int n) {
        pegawai = NULL;
        jumlah = 0;
        setPegawai(isi, n);
    }

    ~ArrayPegawai() {
        if (pegawai != NULL) {
            delete[] pegawai;
        }
    }

    void setPegawai(Pegawai isi[], int n) {
        if (pegawai != NULL) {
            delete[] pegawai;
        }
        jumlah = n;
        pegawai = new Pegawai[jumlah];

        for (int i = 0; i < jumlah; i++) {
            pegawai[i] = isi[i];
        }
    }

    void setPegawaiKe(int indeks, Pegawai p) {
        pegawai[indeks] = p;
    }

    Pegawai* getPegawai() {
        return pegawai;
    }

    void setJumlah(int jumlah) {
        this->jumlah = jumlah;
    }

    int getJumlah() {
        return jumlah;
    }

    void input() {
        if (pegawai != NULL) {
            delete[] pegawai;
            pegawai = NULL;
        }

        cout << "Jumlah pegawai: ";
        cin >> jumlah;
        while (jumlah < 1) {
            cout << "Jumlah tidak valid, ulangi: ";
            cin >> jumlah;
        }

        pegawai = new Pegawai[jumlah];

        for (int i = 0; i < jumlah; i++) {
            cout << "\nData Pegawai ke-" << i + 1 << endl;
            cin.ignore(1000, '\n');
            pegawai[i].input();      // cukup input(), hasil dihitung saat output
        }
    }

    void output() {
        if (pegawai == NULL || jumlah == 0) {
            cout << "Data pegawai kosong!" << endl;
            return;
        }

        cout << endl;
        cout << setw(40) << "" << "Daftar Gaji Harian PT Informatika" << endl;
        garis();

        cout << left << setw(4) << "No";
        cout << left << setw(8) << "NIP";
        cout << left << setw(15) << "Nama";
        cout << left << setw(5) << "Gol";
        cout << left << setw(10) << "Datang";
        cout << left << setw(10) << "Pulang";
        cout << left << setw(10) << "Lama";
        cout << left << setw(12) << "Jam Lembur";
        cout << left << setw(13) << "Gaji Harian";
        cout << left << setw(10) << "Lembur";
        cout << left << setw(10) << "Total";
        cout << "Status" << endl;

        garis();

        for (int i = 0; i < jumlah; i++) {
            pegawai[i].output(i + 1);
        }

        garis();
    }
};

class Menu {
private:
    int pilihan;

    void tampilkan(ArrayPegawai &arrayPegawai) {
        arrayPegawai.output();
    }

public:
    void run() {
        do {
            cout << "\n==========================================" << endl;
            cout << "     MENU PROGRAM GAJI HARIAN PEGAWAI     " << endl;
            cout << "==========================================" << endl;
            cout << "1. Constructor" << endl;
            cout << "2. Setter" << endl;
            cout << "3. Input Dalam Class" << endl;
            cout << "4. Input Luar Class" << endl;
            cout << "5. Keluar" << endl;
            cout << "------------------------------------------" << endl;
            cout << "Pilih Menu (1-5): ";
            cin >> pilihan;
            cout << endl;

            switch (pilihan) {
                case 1: {
                    cout << "--- 1. Constructor ---" << endl;
                    // Semua 5 atribut langsung diisi lewat constructor
                    Pegawai isi[3] = {
                        Pegawai("001", "Ali", 3, Waktu(8, 0, 0), Waktu(17, 15, 10)),
                        Pegawai("004", "ida", 2, Waktu(8, 30, 0), Waktu(15, 0, 0)),
                        Pegawai("005", "Adi", 1, Waktu(7, 45, 0), Waktu(18, 50, 30))
                    };
                    ArrayPegawai arrayPegawai(isi, 3);
                    tampilkan(arrayPegawai);
                    break;
                }
                case 2: {
                    cout << "--- 2. Setter ---" << endl;
                    ArrayPegawai arrayPegawai(2);

                    // Atribut diisi satu per satu lewat setter
                    Pegawai p1;
                    p1.setNIP("010");
                    p1.setNama("Budi");
                    p1.setGol(4);
                    p1.setDatang(Waktu(7, 30, 0));
                    p1.setPulang(Waktu(17, 0, 0));

                    Pegawai p2;
                    p2.setNIP("011");
                    p2.setNama("Sari");
                    p2.setGol(2);
                    p2.setDatang(Waktu(9, 0, 0));
                    p2.setPulang(Waktu(15, 30, 0));

                    arrayPegawai.setPegawaiKe(0, p1);
                    arrayPegawai.setPegawaiKe(1, p2);
                    tampilkan(arrayPegawai);
                    break;
                }
                case 3: {
                    cout << "--- 3. Input Dalam Class ---" << endl;
                    ArrayPegawai arrayPegawai;
                    arrayPegawai.input();
                    tampilkan(arrayPegawai);
                    break;
                }
                case 4: {
                    cout << "--- 4. Input Luar Class ---" << endl;
                    int jumlah;

                    cout << "Jumlah pegawai: ";
                    cin >> jumlah;
                    while (jumlah < 1) {
                        cout << "Jumlah tidak valid, ulangi: ";
                        cin >> jumlah;
                    }

                    Pegawai *isi = new Pegawai[jumlah];

                    for (int i = 0; i < jumlah; i++) {
                        string nip, nama;
                        int gol, jam, menit, detik;

                        cout << "\nData Pegawai ke-" << i + 1 << endl;
                        cin.ignore(1000, '\n');

                        cout << "NIP   : ";
                        getline(cin, nip);

                        cout << "Nama  : ";
                        getline(cin, nama);

                        cout << "Gol   : ";
                        cin >> gol;

                        cout << "Waktu datang (jam menit detik): ";
                        cin >> jam >> menit >> detik;
                        Waktu datang(jam, menit, detik);

                        cout << "Waktu pulang (jam menit detik): ";
                        cin >> jam >> menit >> detik;
                        Waktu pulang(jam, menit, detik);

                        isi[i] = Pegawai(nip, nama, gol, datang, pulang);
                    }

                    ArrayPegawai arrayPegawai;
                    arrayPegawai.setPegawai(isi, jumlah);
                    delete[] isi;
                    tampilkan(arrayPegawai);
                    break;
                }
                case 5:
                    cout << "Selesai. Keluar dari program." << endl;
                    break;
                default:
                    cout << "Pilihan menu tidak valid! Silakan masukkan opsi 1 - 5." << endl;
                    break;
            }
        } while (pilihan != 5);
    }
};

int main() {
    Menu menu;
    menu.run();
    return 0;
}