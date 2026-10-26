/*
Nama Program        : Soal1_017_043_053.cpp
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 13 Oktober 2026
Deskripsi           : Program OOP untuk mencari nilai rata-rata,
                      nilai tertinggi, nilai terendah, dan sorting
                      dari kumpulan data bertipe array integer.
*/

#include <iostream>
using namespace std;

class Nilai {
private:
    int *data;
    int jumlah;

public:
    Nilai() {
        data = NULL;
        jumlah = 0;
    }

    Nilai(int isi[], int n) {
        data = NULL;
        jumlah = 0;
        setData(isi, n);
    }

    ~Nilai() {
        if (data != NULL) {
            delete[] data;
        }
    }

    void setData(int isi[], int n) {
        if (data != NULL) {
            delete[] data;
        }
        jumlah = n;
        data = new int[jumlah];
        for (int i = 0; i < jumlah; i++) {
            data[i] = isi[i];
        }
    }

    int* getData() {
        return data;
    }

    void setJumlah(int jumlah) {
        this->jumlah = jumlah;
    }

    int getJumlah() {
        return jumlah;
    }

    void input() {
        int pilihan;

        if (data != NULL) {
            cout << "Array sudah ada. Hapus array lama? (1 = ya, 0 = tidak): ";
            cin >> pilihan;

            if (pilihan == 0) {
                cout << "Array batal diubah." << endl;
                return;
            }

            delete[] data;
            data = NULL;
        }

        cout << "Masukkan jumlah data: ";
        cin >> jumlah;

        data = new int[jumlah];

        for (int i = 0; i < jumlah; i++) {
            cout << "Data ke-" << i + 1 << ": ";
            cin >> data[i];
        }
    }

    void tampilData() {
        for (int i = 0; i < jumlah; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    double rataRata() {
        int total = 0;

        for (int i = 0; i < jumlah; i++) {
            total += data[i];
        }

        return (double) total / jumlah;
    }

    int nilaiTertinggi() {
        int max = data[0];

        for (int i = 1; i < jumlah; i++) {
            if (data[i] > max) {
                max = data[i];
            }
        }

        return max;
    }

    int nilaiTerendah() {
        int min = data[0];

        for (int i = 1; i < jumlah; i++) {
            if (data[i] < min) {
                min = data[i];
            }
        }

        return min;
    }

    void sortingAscending() {
        int temp;

        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = 0; j < jumlah - 1 - i; j++) {
                if (data[j] > data[j + 1]) {
                    temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    void sortingDescending() {
        int temp;

        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = 0; j < jumlah - 1 - i; j++) {
                if (data[j] < data[j + 1]) {
                    temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    void output() {
        if (data == NULL || jumlah <= 0) {
            cout << "Data kosong!" << endl;
            return;
        }

        cout << "Data            : ";
        tampilData();

        cout << "Rata-rata       : " << rataRata() << endl;
        cout << "Nilai tertinggi : " << nilaiTertinggi() << endl;
        cout << "Nilai terendah  : " << nilaiTerendah() << endl;

        sortingAscending();
        cout << "Ascending       : ";
        tampilData();

        sortingDescending();
        cout << "Descending      : ";
        tampilData();
    }
};

class Menu {
private:
    int pilihan;

public:
    void run() {
        do {
            cout << "\n==========================================" << endl;
            cout << "        MENU PROGRAM ARRAY 1 DIMENSI      " << endl;
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
                    int contoh[5] = {85, 70, 92, 66, 78};
                    Nilai nilai1(contoh, 5);
                    nilai1.output();
                    break;
                }
                case 2: {
                    cout << "--- 2. Setter ---" << endl;
                    int contoh[6] = {50, 90, 35, 77, 61, 88};
                    Nilai nilai2;
                    nilai2.setData(contoh, 6);
                    nilai2.output();
                    break;
                }
                case 3: {
                    cout << "--- 3. Input Dalam Class ---" << endl;
                    Nilai nilai3;
                    nilai3.input();
                    nilai3.output();
                    break;
                }
                case 4: {
                    cout << "--- 4. Input Luar Class ---" << endl;
                    int jumlah;
                    cout << "Masukkan jumlah data: ";
                    cin >> jumlah;

                    int *isi = new int[jumlah];
                    for (int i = 0; i < jumlah; i++) {
                        cout << "Data ke-" << i + 1 << ": ";
                        cin >> isi[i];
                    }

                    Nilai nilai4;
                    nilai4.setData(isi, jumlah);
                    delete[] isi;
                    nilai4.output();
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

//ini branch asma