/*
Nama Program        : Soal3_017_043_053.cpp
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 25 Oktober 2026
Deskripsi           : Program OOP Array of Object untuk mencari gaji
                      harian dan lembur pegawai berdasarkan lama kerja,
                      lengkap dengan status peringatan.
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

    static string duaDigit(int nilai) {
        return (nilai < 10 ? "0" : "") + to_string(nilai);
    }

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

    explicit Waktu(int totalDetik) {
        this->jam = totalDetik / 3600;
        this->menit = (totalDetik % 3600) / 60;
        this->detik = totalDetik % 60;
    }

    void setJam(int jam) { this->jam = jam; }
    int getJam() const { return jam; }

    void setMenit(int menit) { this->menit = menit; }
    int getMenit() const { return menit; }

    void setDetik(int detik) { this->detik = detik; }
    int getDetik() const { return detik; }

    void inputWaktu() {
        cout << "Jam           : ";
        cin >> jam;
        cout << "Menit         : ";
        cin >> menit;
        cout << "Detik         : ";
        cin >> detik;
    }

    int toSecond() const {
        return jam * 3600 + menit * 60 + detik;
    }

    int selisihWaktu(const Waktu& waktu) const {
        int selisih = waktu.toSecond() - this->toSecond();
        if (selisih < 0) {
            selisih += 24 * 3600;
        }
        return selisih;
    }

    string outputWaktu() const {
        return duaDigit(jam) + ":" + duaDigit(menit) + ":" + duaDigit(detik);
    }
};

class Person {
private:
    string nama;
    string alamat;

public:
    Person() {
        nama = "";
        alamat = "";
    }

    Person(string nama, string alamat) {
        this->nama = nama;
        this->alamat = alamat;
    }

    void setNama(string nama) { this->nama = nama; }
    string getNama() const { return nama; }

    void setAlamat(string alamat) { this->alamat = alamat; }
    string getAlamat() const { return alamat; }

    void inputPerson() {
        cout << "Nama          : ";
        getline(cin, nama);

        cout << "Alamat        : ";
        getline(cin, alamat);
    }

    string getInfo() const {
        return nama + " (" + alamat + ")";
    }

    void outputPerson() const {
        cout << "Nama          : " << nama << endl;
        cout << "Alamat        : " << alamat << endl;
    }
};

class Pegawai : public Person {
private:
    string NIP;
    int gol;
    Waktu datang;
    Waktu pulang;

public:
    Pegawai() : Person() {
        NIP = "";
        gol = 0;
        datang = Waktu();
        pulang = Waktu();
    }

    Pegawai(string NIP, string nama, string alamat, int gol, Waktu datang, Waktu pulang) : Person(nama, alamat) {
        this->NIP = NIP;
        this->gol = gol;
        this->datang = datang;
        this->pulang = pulang;
    }

    void setNIP(string NIP) { this->NIP = NIP; }
    string getNIP() const { return NIP; }

    void setGol(int gol) { this->gol = gol; }
    int getGol() const { return gol; }

    void setDatang(Waktu datang) { this->datang = datang; }
    Waktu getDatang() const { return datang; }

    void setPulang(Waktu pulang) { this->pulang = pulang; }
    Waktu getPulang() const { return pulang; }

    int lamaKerja() const {
        return datang.selisihWaktu(pulang);
    }

    int lamaLembur() const {
        int lama = lamaKerja();

        if (lama >= 28800) {
            return lama - 28800;
        } else {
            return 0;
        }
    }

    int jamLembur() const {
        return lamaLembur() / 3600;
    }

    int getGaji() const {
        switch (gol) {
            case 1: return 150000;
            case 2: return 200000;
            case 3: return 400000;
            case 4: return 500000;
            default: return 0;
        }
    }

    int getTarifLembur() const {
        switch (gol) {
            case 1: return 50000;
            case 2: return 75000;
            case 3: return 150000;
            case 4: return 200000;
            default: return 0;
        }
    }

    int getLembur() const {
        return jamLembur() * getTarifLembur();
    }

    int getTotal() const {
        return getGaji() + getLembur();
    }

    string status() const {
        if (lamaKerja() < 28800) {
            return "Peringatan";
        } else {
            return "ok";
        }
    }

    static string formatRupiah(int nilai) {
        string angka = to_string(nilai < 0 ? -nilai : nilai);
        string hasil = "";
        int hitung = 0;
        for (int i = (int)angka.length() - 1; i >= 0; i--) {
            hasil.insert(hasil.begin(), angka[i]);
            hitung++;
            if (hitung % 3 == 0 && i != 0) {
                hasil.insert(hasil.begin(), '.');
            }
        }
        return hasil;
    }

    void inputPegawai() {
        cout << "NIP           : ";
        getline(cin, NIP);

        inputPerson();

        cout << "Golongan      : ";
        cin >> gol;

        cout << "\nWaktu datang" << endl;
        datang.inputWaktu();

        cout << "\nWaktu pulang" << endl;
        pulang.inputWaktu();

        cin.ignore(1000, '\n');
    }

    void output(int no) const {
        cout << left  << setw(3)  << no << ' '
             << setw(6)  << NIP << ' '
             << setw(10) << getNama() << ' '
             << setw(10) << getAlamat() << ' '
             << setw(4)  << gol << ' '
             << setw(9)  << datang.outputWaktu() << ' '
             << setw(9)  << pulang.outputWaktu() << ' '
             << setw(9)  << Waktu(lamaKerja()).outputWaktu() << ' '
             << setw(10) << Waktu(lamaLembur()).outputWaktu() << ' '
             << right
             << setw(12) << formatRupiah(getGaji()) << ' '
             << setw(10) << formatRupiah(getLembur()) << ' '
             << setw(10) << formatRupiah(getTotal()) << "  "
             << left
             << setw(10) << status()
             << endl;
    }
};

class ArrayPegawai {
private:
    Pegawai* pegawai;
    int jumlah;

public:
    ArrayPegawai() {
        pegawai = nullptr;
        jumlah = 0;
    }

    explicit ArrayPegawai(int jumlah) {
        this->jumlah = jumlah;
        pegawai = new Pegawai[jumlah];
    }

    ArrayPegawai(const Pegawai isi[], int jumlah) {
        pegawai = nullptr;
        this->jumlah = 0;
        setPegawai(isi, jumlah);
    }

    ArrayPegawai(const ArrayPegawai& lain) {
        pegawai = nullptr;
        jumlah = 0;
        setPegawai(lain.pegawai, lain.jumlah);
    }

    ArrayPegawai& operator=(const ArrayPegawai& lain) {
        if (this != &lain) {
            setPegawai(lain.pegawai, lain.jumlah);
        }
        return *this;
    }

    ~ArrayPegawai() {
        delete[] pegawai;
    }

    void setPegawai(const Pegawai isi[], int jumlah) {
        delete[] pegawai;
        this->jumlah = jumlah;
        pegawai = new Pegawai[jumlah];

        for (int i = 0; i < jumlah; i++) {
            pegawai[i] = isi[i];
        }
    }

    void setPegawaiKe(int index, const Pegawai& p) {
        if (pegawai != nullptr && index >= 0 && index < jumlah) {
            pegawai[index] = p;
        }
    }

    Pegawai* getPegawai() const { return pegawai; }

    void setJumlah(int jumlah) { this->jumlah = jumlah; }
    int getJumlah() const { return jumlah; }

    void input() {
        int n = 0;
        while (n < 1) {
            cout << "Jumlah pegawai: ";
            cin >> n;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                n = 0;
                cout << "Input harus berupa angka!" << endl;
            } else {
                cin.ignore(1000, '\n');
                if (n < 1) {
                    cout << "Jumlah tidak valid, harap ulangi." << endl;
                }
            }
        }

        delete[] pegawai;
        this->jumlah = n;
        this->pegawai = new Pegawai[n];

        for (int i = 0; i < n; i++) {
            cout << "\nData Pegawai ke-" << (i + 1) << endl;
            pegawai[i].inputPegawai();
        }
    }

    int totalGaji() const {
        int total = 0;
        for (int i = 0; i < jumlah; i++) {
            total += pegawai[i].getTotal();
        }
        return total;
    }

    int rataRataGaji() const {
        return (int)((float)totalGaji() / jumlah + 0.5);
    }

    Pegawai gajiTertinggi() const {
        Pegawai tertinggi = pegawai[0];
        for (int i = 1; i < jumlah; i++) {
            if (pegawai[i].getTotal() > tertinggi.getTotal()) {
                tertinggi = pegawai[i];
            }
        }
        return tertinggi;
    }

    Pegawai gajiTerendah() const {
        Pegawai terendah = pegawai[0];
        for (int i = 1; i < jumlah; i++) {
            if (pegawai[i].getTotal() < terendah.getTotal()) {
                terendah = pegawai[i];
            }
        }
        return terendah;
    }

    void output() const {
        if (pegawai == nullptr || jumlah == 0) {
            cout << "Belum ada data pegawai." << endl;
            return;
        }

        string garis(125, '-');

        cout << endl;
        cout << "                                  Daftar Gaji Harian PT Informatika" << endl;
        cout << garis << endl;
        cout << left
             << setw(3)  << "No" << ' '
             << setw(6)  << "NIP" << ' '
             << setw(10) << "Nama" << ' '
             << setw(10) << "Alamat" << ' '
             << setw(4)  << "Gol" << ' '
             << setw(9)  << "Datang" << ' '
             << setw(9)  << "Pulang" << ' '
             << setw(9)  << "Lama" << ' '
             << setw(10) << "Jam Lembur" << ' '
             << right
             << setw(12) << "Gaji Harian" << ' '
             << setw(10) << "Lembur" << ' '
             << setw(10) << "Total" << "  "
             << left
             << setw(10) << "Status"
             << endl;
        cout << garis << endl;

        for (int i = 0; i < jumlah; i++) {
            pegawai[i].output(i + 1);
        }

        cout << garis << endl;

        Pegawai tertinggi = gajiTertinggi();
        Pegawai terendah = gajiTerendah();

        cout << "Rata-rata Gaji : " << Pegawai::formatRupiah(rataRataGaji()) << endl;
        cout << "Gaji Tertinggi : " << Pegawai::formatRupiah(tertinggi.getTotal()) << " (" << tertinggi.getNama() << ")" << endl;
        cout << "Gaji Terendah  : " << Pegawai::formatRupiah(terendah.getTotal()) << " (" << terendah.getNama() << ")" << endl;
    }
};

class Menu {
private:
    int pilihan;

    void Constructor() {
        cout << "--- 1. Constructor ---" << endl;
        Pegawai isi[3] = {
            Pegawai("001", "Ali", "Dago 4",   3, Waktu(8, 0, 0),  Waktu(17, 15, 10)),
            Pegawai("004", "ida", "Uber 3",   2, Waktu(8, 30, 0), Waktu(15, 0, 0)),
            Pegawai("005", "Adi", "Riung 10", 1, Waktu(7, 45, 0), Waktu(18, 50, 30))
        };
        ArrayPegawai arrayPegawai(isi, 3);
        arrayPegawai.output();
    }

    void Setter() {
        cout << "--- 2. Setter ---" << endl;
        ArrayPegawai arrayPegawai(2);

        Pegawai p1;
        p1.setNIP("010");
        p1.setNama("Budi");
        p1.setAlamat("Cihampelas");
        p1.setGol(4);
        p1.setDatang(Waktu(7, 30, 0));
        p1.setPulang(Waktu(17, 0, 0));

        Pegawai p2;
        p2.setNIP("011");
        p2.setNama("Sari");
        p2.setAlamat("Setiabudi");
        p2.setGol(2);
        p2.setDatang(Waktu(9, 0, 0));
        p2.setPulang(Waktu(15, 30, 0));

        arrayPegawai.setPegawaiKe(0, p1);
        arrayPegawai.setPegawaiKe(1, p2);
        arrayPegawai.output();
    }

    void inputDalam() {
        cout << "--- 3. Input Dalam Class ---" << endl;
        ArrayPegawai arrayPegawai;
        arrayPegawai.input();
        arrayPegawai.output();
    }

    void inputLuar() {
        cout << "--- 4. Input Luar Class ---" << endl;
        int jumlah = 0;
        while (jumlah < 1) {
            cout << "Jumlah pegawai: ";
            cin >> jumlah;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                jumlah = 0;
                cout << "Input harus berupa angka!" << endl;
            } else {
                cin.ignore(1000, '\n');
                if (jumlah < 1) {
                    cout << "Jumlah tidak valid, ulangi." << endl;
                }
            }
        }

        Pegawai* isi = new Pegawai[jumlah];

        for (int i = 0; i < jumlah; i++) {
            string nip, nama, alamat;
            int gol, jam, menit, detik;

            cout << "\nData Pegawai ke-" << (i + 1) << endl;

            cout << "NIP           : ";
            getline(cin, nip);

            cout << "Nama          : ";
            getline(cin, nama);

            cout << "Alamat        : ";
            getline(cin, alamat);

            cout << "Gol           : ";
            cin >> gol;

            cout << "\nWaktu datang" << endl;
            cout << "Jam           : ";
            cin >> jam;
            cout << "Menit         : ";
            cin >> menit;
            cout << "Detik         : ";
            cin >> detik;
            Waktu datang(jam, menit, detik);

            cout << "\nWaktu pulang" << endl;
            cout << "Jam           : ";
            cin >> jam;
            cout << "Menit         : ";
            cin >> menit;
            cout << "Detik         : ";
            cin >> detik;
            Waktu pulang(jam, menit, detik);

            cin.ignore(1000, '\n');

            isi[i] = Pegawai(nip, nama, alamat, gol, datang, pulang);
        }

        ArrayPegawai arrayPegawai;
        arrayPegawai.setPegawai(isi, jumlah);
        delete[] isi;
        arrayPegawai.output();
    }

public:
    Menu() {
        pilihan = 0;
    }

    void tampilanMenu() const {
        cout << "\n==========================================" << endl;
        cout << "     MENU PROGRAM GAJI HARIAN PEGAWAI     " << endl;
        cout << "==========================================" << endl;
        cout << "1. Constructor" << endl;
        cout << "2. Setter" << endl;
        cout << "3. Input Dalam Class" << endl;
        cout << "4. Input Luar Class" << endl;
        cout << "5. Keluar" << endl;
        cout << "------------------------------------------" << endl;
    }

    void inputPilihan() {
        cout << "Pilih Menu (1-5): ";
        cin >> pilihan;
        if (cin.eof()) {
            pilihan = 5;
        } else if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            pilihan = 0;
        } else {
            cin.ignore(1000, '\n');
        }
        cout << endl;
    }

    void run() {
        do {
            tampilanMenu();
            inputPilihan();

            switch (pilihan) {
                case 1:
                    Constructor();
                    break;
                case 2:
                    Setter();
                    break;
                case 3:
                    inputDalam();
                    break;
                case 4:
                    inputLuar();
                    break;
                case 5:
                    cout << "Selesai. Keluar dari program." << endl;
                    break;
                default:
                    cout << "Pilihan menu tidak valid! Silakan masukkan opsi 1-5." << endl;
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