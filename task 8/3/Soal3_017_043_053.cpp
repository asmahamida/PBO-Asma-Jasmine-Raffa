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
using namespace std;

int panjangTeks(const char* s) {
    int n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

void salinTeks(char tujuan[], const char* sumber, int kapasitas) {
    int i = 0;
    while (sumber[i] != '\0' && i < kapasitas - 1) {
        tujuan[i] = sumber[i];
        i++;
    }
    tujuan[i] = '\0';
}

void cetakKolom(const char* teks, int lebar) {
    cout << teks;
    for (int i = panjangTeks(teks); i < lebar; i++) {
        cout << " ";
    }
}

void angkaKeTeks(int angka, bool pakaiTitik, char hasil[]) {
    char balik[20];
    int n = 0;

    if (angka == 0) {
        balik[n] = '0';
        n++;
    }

    while (angka > 0) {
        if (pakaiTitik && n > 0 && n % 4 == 3) {
            balik[n] = '.';
            n++;
        }
        balik[n] = '0' + angka % 10;
        n++;
        angka /= 10;
    }

    for (int i = 0; i < n; i++) {
        hasil[i] = balik[n - 1 - i];
    }
    hasil[n] = '\0';
}

void cetakAngkaKolom(int angka, bool pakaiTitik, int lebar) {
    char teks[20];
    angkaKeTeks(angka, pakaiTitik, teks);
    cetakKolom(teks, lebar);
}

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

    void setJam(int jam) {
        this->jam = jam;
    }

    int getJam() {
        return jam;
    }

    void setMenit(int menit) {
        this->menit = menit;
    }

    int getMenit() {
        return menit;
    }

    void setDetik(int detik) {
        this->detik = detik;
    }

    int getDetik() {
        return detik;
    }

    void input(const char* label) {
        cout << "Waktu " << label << " (jam menit detik): ";
        cin >> jam;
        cin >> menit;
        cin >> detik;
    }

    int keDetik() {
        return jam * 3600 + menit * 60 + detik;
    }

    int selisihDetik(Waktu waktu) {
        int selisih = waktu.keDetik() - this->keDetik();

        if (selisih < 0) {
            selisih += 86400;
        }

        return selisih;
    }

    void output(int lebar) {
        char hasil[10];

        hasil[0] = '0' + (jam / 10) % 10;
        hasil[1] = '0' + jam % 10;
        hasil[2] = ':';
        hasil[3] = '0' + (menit / 10) % 10;
        hasil[4] = '0' + menit % 10;
        hasil[5] = ':';
        hasil[6] = '0' + (detik / 10) % 10;
        hasil[7] = '0' + detik % 10;
        hasil[8] = '\0';

        cetakKolom(hasil, lebar);
    }
};

class Pegawai {
private:
    char NIP[20];
    char nama[50];
    int gol;
    Waktu datang;
    Waktu pulang;
    Waktu lamaKerja;
    Waktu jamLembur;
    int gajiHarian;
    int lembur;
    int total;
    const char* statusPeringatan;

public:
    Pegawai() {
        NIP[0] = '\0';
        nama[0] = '\0';
        gol = 0;
        datang = Waktu();
        pulang = Waktu();
        lamaKerja = Waktu();
        jamLembur = Waktu();
        gajiHarian = 0;
        lembur = 0;
        total = 0;
        statusPeringatan = "";
    }

    Pegawai(const char* NIP, const char* nama, int gol, Waktu datang, Waktu pulang) {
        salinTeks(this->NIP, NIP, 20);
        salinTeks(this->nama, nama, 50);
        this->gol = gol;
        this->datang = datang;
        this->pulang = pulang;
        lamaKerja = Waktu();
        jamLembur = Waktu();
        gajiHarian = 0;
        lembur = 0;
        total = 0;
        statusPeringatan = "";
    }

    void setNIP(const char* NIP) {
        salinTeks(this->NIP, NIP, 20);
    }

    const char* getNIP() {
        return NIP;
    }

    void setNama(const char* nama) {
        salinTeks(this->nama, nama, 50);
    }

    const char* getNama() {
        return nama;
    }

    void setGol(int gol) {
        this->gol = gol;
    }

    int getGol() {
        return gol;
    }

    void setDatang(Waktu datang) {
        this->datang = datang;
    }

    Waktu getDatang() {
        return datang;
    }

    void setPulang(Waktu pulang) {
        this->pulang = pulang;
    }

    Waktu getPulang() {
        return pulang;
    }

    void setLamaKerja(Waktu lamaKerja) {
        this->lamaKerja = lamaKerja;
    }

    Waktu getLamaKerja() {
        return lamaKerja;
    }

    void setJamLembur(Waktu jamLembur) {
        this->jamLembur = jamLembur;
    }

    Waktu getJamLembur() {
        return jamLembur;
    }

    void setGajiHarian(int gajiHarian) {
        this->gajiHarian = gajiHarian;
    }

    int getGajiHarian() {
        return gajiHarian;
    }

    void setLembur(int lembur) {
        this->lembur = lembur;
    }

    int getLembur() {
        return lembur;
    }

    void setTotal(int total) {
        this->total = total;
    }

    int getTotal() {
        return total;
    }

    void setStatusPeringatan(const char* statusPeringatan) {
        this->statusPeringatan = statusPeringatan;
    }

    const char* getStatusPeringatan() {
        return statusPeringatan;
    }

    void input() {
        cin.ignore(1000, '\n');

        cout << "NIP   : ";
        cin.getline(NIP, 20);

        cout << "Nama  : ";
        cin.getline(nama, 50);

        cout << "Gol   : ";
        cin >> gol;

        datang.input("datang");
        pulang.input("pulang");
    }

    void proses() {
        int durasiDetik = datang.selisihDetik(pulang);

        int totalJam = durasiDetik / 3600;
        int sisaDetik = durasiDetik % 3600;
        int totalMenit = sisaDetik / 60;
        int totalDetik = sisaDetik % 60;

        lamaKerja = Waktu(totalJam, totalMenit, totalDetik);

        int gaji = 0;
        int tarifLembur = 0;

        switch (gol) {
            case 1:
                gaji = 150000;
                tarifLembur = 50000;
                break;
            case 2:
                gaji = 200000;
                tarifLembur = 75000;
                break;
            case 3:
                gaji = 400000;
                tarifLembur = 150000;
                break;
            case 4:
                gaji = 500000;
                tarifLembur = 200000;
                break;
        }

        gajiHarian = gaji;

        if (durasiDetik < 8 * 3600) {
            statusPeringatan = "Peringatan";
            jamLembur = Waktu(0, 0, 0);
            lembur = 0;
        } else {
            statusPeringatan = "ok";

            int lemburDetik = durasiDetik - 8 * 3600;
            int lemburJam = lemburDetik / 3600;

            jamLembur = Waktu(
                lemburJam,
                (lemburDetik % 3600) / 60,
                lemburDetik % 60
            );

            lembur = lemburJam * tarifLembur;
        }

        total = gajiHarian + lembur;
    }

    void output(int nomor) {
        cetakAngkaKolom(nomor, false, 4);
        cetakKolom(NIP, 8);
        cetakKolom(nama, 15);
        cetakAngkaKolom(gol, false, 5);
        datang.output(10);
        pulang.output(10);
        lamaKerja.output(10);
        jamLembur.output(12);
        cetakAngkaKolom(gajiHarian, true, 13);
        cetakAngkaKolom(lembur, true, 10);
        cetakAngkaKolom(total, true, 10);
        cout << statusPeringatan << endl;
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
            pegawai[i].input();
        }
    }

    void proses() {
        for (int i = 0; i < jumlah; i++) {
            pegawai[i].proses();
        }
    }

    void output() {
        if (pegawai == NULL || jumlah == 0) {
            cout << "Data pegawai kosong!" << endl;
            return;
        }

        cout << endl;
        for (int i = 0; i < 40; i++) {
            cout << " ";
        }
        cout << "Daftar Gaji Harian PT Informatika" << endl;
        garis();

        cetakKolom("No", 4);
        cetakKolom("NIP", 8);
        cetakKolom("Nama", 15);
        cetakKolom("Gol", 5);
        cetakKolom("Datang", 10);
        cetakKolom("Pulang", 10);
        cetakKolom("Lama", 10);
        cetakKolom("Jam Lembur", 12);
        cetakKolom("Gaji Harian", 13);
        cetakKolom("Lembur", 10);
        cetakKolom("Total", 10);
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
        arrayPegawai.proses();
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
                        char nip[20];
                        char nama[50];
                        int gol, jam, menit, detik;

                        cout << "\nData Pegawai ke-" << i + 1 << endl;
                        cin.ignore(1000, '\n');

                        cout << "NIP   : ";
                        cin.getline(nip, 20);

                        cout << "Nama  : ";
                        cin.getline(nama, 50);

                        cout << "Gol   : ";
                        cin >> gol;

                        isi[i].setNIP(nip);
                        isi[i].setNama(nama);
                        isi[i].setGol(gol);

                        cout << "Waktu datang (jam menit detik): ";
                        cin >> jam >> menit >> detik;
                        isi[i].setDatang(Waktu(jam, menit, detik));

                        cout << "Waktu pulang (jam menit detik): ";
                        cin >> jam >> menit >> detik;
                        isi[i].setPulang(Waktu(jam, menit, detik));
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