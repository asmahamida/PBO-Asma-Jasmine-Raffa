/*
Nama Program        : Soal2_017_043_053.py
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 13 Oktober 2026
Deskripsi           : Program OOP untuk penjumlahan dan perkalian dua matriks.
*/

#include <iostream>
using namespace std;

class Matriks {
private:
    int* data;
    int baris;
    int kolom;

    void hapus() {
        if (data != NULL) {
            delete[] data;
            data = NULL;
        }
    }

    void buatKosong(int b, int k) {
        hapus();
        baris = b;
        kolom = k;

        data = new int[baris * kolom];

        for (int i = 0; i < baris * kolom; i++) {
            data[i] = 0;
        }
    }

public:
    Matriks() {
        data = NULL;
        baris = 0;
        kolom = 0;
    }

    Matriks(int baris, int kolom) {
        data = NULL;
        this->baris = 0;
        this->kolom = 0;
        buatKosong(baris, kolom);
    }

    Matriks(int baris, int kolom, int isi[]) {
        data = NULL;
        this->baris = 0;
        this->kolom = 0;
        setData(isi, baris, kolom);
    }

    Matriks(const Matriks& lain) {
        data = NULL;
        baris = 0;
        kolom = 0;
        *this = lain;
    }

    Matriks& operator=(const Matriks& lain) {
        if (this != &lain) {
            buatKosong(lain.baris, lain.kolom);

            for (int i = 0; i < baris * kolom; i++) {
                data[i] = lain.data[i];
            }
        }
        return *this;
    }

    ~Matriks() {
        hapus();
    }

    void setData(int isi[], int b, int k) {
        buatKosong(b, k);

        for (int i = 0; i < baris * kolom; i++) {
            data[i] = isi[i];
        }
    }

    int getBaris() {
        return baris;
    }

    int getKolom() {
        return kolom;
    }

    int getElemen(int i, int j) const {
        return data[i * kolom + j];
    }

    void setElemen(int i, int j, int nilai) {
        data[i * kolom + j] = nilai;
    }

    void input() {
        int b, k;

        cout << "Masukkan jumlah baris: ";
        cin >> b;
        while (b < 1) {
            cout << "Jumlah baris tidak valid, ulangi: ";
            cin >> b;
        }

        cout << "Masukkan jumlah kolom: ";
        cin >> k;
        while (k < 1) {
            cout << "Jumlah kolom tidak valid, ulangi: ";
            cin >> k;
        }

        buatKosong(b, k);

        for (int i = 0; i < baris; i++) {
            for (int j = 0; j < kolom; j++) {
                cout << "Data [" << i << "][" << j << "] = ";
                cin >> data[i * kolom + j];
            }
        }
    }

    void output() {
        if (data == NULL) {
            cout << "Matriks kosong!" << endl;
            return;
        }

        for (int i = 0; i < baris; i++) {
            for (int j = 0; j < kolom; j++) {
                cout << data[i * kolom + j] << "\t";
            }
            cout << endl;
        }
    }

    bool bisaDijumlah(Matriks& matriks2) {
        return baris == matriks2.baris && kolom == matriks2.kolom;
    }

    bool bisaDikali(Matriks& matriks2) {
        return kolom == matriks2.baris;
    }

    Matriks penjumlahan(Matriks& matriks2) {
        Matriks hasil(baris, kolom);

        for (int i = 0; i < baris * kolom; i++) {
            hasil.data[i] = data[i] + matriks2.data[i];
        }

        return hasil;
    }

    void penjumlahanVoid(Matriks& matriks2, Matriks& hasil) {
        hasil.buatKosong(baris, kolom);

        for (int i = 0; i < baris * kolom; i++) {
            hasil.data[i] = data[i] + matriks2.data[i];
        }
    }

    Matriks perkalian(Matriks& matriks2) {
        Matriks hasil(baris, matriks2.kolom);

        for (int i = 0; i < baris; i++) {
            for (int j = 0; j < matriks2.kolom; j++) {
                int total = 0;
                for (int k = 0; k < kolom; k++) {
                    total += data[i * kolom + k] * matriks2.data[k * matriks2.kolom + j];
                }
                hasil.setElemen(i, j, total);
            }
        }

        return hasil;
    }

    void perkalianVoid(Matriks& matriks2, Matriks& hasil) {
        hasil.buatKosong(baris, matriks2.kolom);

        for (int i = 0; i < baris; i++) {
            for (int j = 0; j < matriks2.kolom; j++) {
                int total = 0;
                for (int k = 0; k < kolom; k++) {
                    total += data[i * kolom + k] * matriks2.data[k * matriks2.kolom + j];
                }
                hasil.setElemen(i, j, total);
            }
        }
    }
};

class Menu {
private:
    int pilihan;

    void bacaMatriks(const char* nama, Matriks& m) {
        int b, k;

        cout << "Matriks " << nama << endl;
        cout << "Masukkan jumlah baris: ";
        cin >> b;
        while (b < 1) {
            cout << "Jumlah baris tidak valid, ulangi: ";
            cin >> b;
        }

        cout << "Masukkan jumlah kolom: ";
        cin >> k;
        while (k < 1) {
            cout << "Jumlah kolom tidak valid, ulangi: ";
            cin >> k;
        }

        int* isi = new int[b * k];

        for (int i = 0; i < b; i++) {
            for (int j = 0; j < k; j++) {
                cout << "Data [" << i << "][" << j << "] = ";
                cin >> isi[i * k + j];
            }
        }

        m.setData(isi, b, k);
        delete[] isi;
    }

    void proses(Matriks& matriks1, Matriks& matriks2) {
        cout << "\nMatriks 1:" << endl;
        matriks1.output();

        cout << "\nMatriks 2:" << endl;
        matriks2.output();

        if (matriks1.bisaDijumlah(matriks2)) {
            Matriks hasil1 = matriks1.penjumlahan(matriks2);
            cout << "\nHasil Penjumlahan (fungsi):" << endl;
            hasil1.output();

            Matriks hasil2;
            matriks1.penjumlahanVoid(matriks2, hasil2);
            cout << "\nHasil Penjumlahan (void):" << endl;
            hasil2.output();
        }
        else {
            cout << "\nMatriks tidak dapat dijumlahkan." << endl;
            cout << "Ordo kedua matriks harus sama." << endl;
        }

        if (matriks1.bisaDikali(matriks2)) {
            Matriks hasil3 = matriks1.perkalian(matriks2);
            cout << "\nHasil Perkalian (fungsi):" << endl;
            hasil3.output();

            Matriks hasil4;
            matriks1.perkalianVoid(matriks2, hasil4);
            cout << "\nHasil Perkalian (void):" << endl;
            hasil4.output();
        }
        else {
            cout << "\nMatriks tidak dapat dikalikan." << endl;
            cout << "Kolom matriks 1 harus sama dengan baris matriks 2." << endl;
        }
    }

public:
    void run() {
        do {
            cout << "\n==========================================" << endl;
            cout << "        MENU PROGRAM ARRAY 2 DIMENSI      " << endl;
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
                    int isiA[6] = {1, 2, 3, 4, 5, 6};
                    int isiB[6] = {7, 8, 9, 10, 11, 12};
                    Matriks matriks1(2, 3, isiA);
                    Matriks matriks2(3, 2, isiB);
                    proses(matriks1, matriks2);
                    break;
                }
                case 2: {
                    cout << "--- 2. Setter ---" << endl;
                    int isiA[4] = {2, 4, 6, 8};
                    int isiB[4] = {1, 3, 5, 7};
                    Matriks matriks1;
                    Matriks matriks2;
                    matriks1.setData(isiA, 2, 2);
                    matriks2.setData(isiB, 2, 2);
                    proses(matriks1, matriks2);
                    break;
                }
                case 3: {
                    cout << "--- 3. Input Dalam Class ---" << endl;
                    Matriks matriks1;
                    Matriks matriks2;
                    cout << "Matriks 1" << endl;
                    matriks1.input();
                    cout << "Matriks 2" << endl;
                    matriks2.input();
                    proses(matriks1, matriks2);
                    break;
                }
                case 4: {
                    cout << "--- 4. Input Luar Class ---" << endl;
                    Matriks matriks1;
                    Matriks matriks2;
                    bacaMatriks("1", matriks1);
                    bacaMatriks("2", matriks2);
                    proses(matriks1, matriks2);
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