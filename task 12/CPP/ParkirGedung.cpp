/*
Nama Program        : Sistem Parkir Gedung
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 23 November 2026
Deskripsi           : Membuat sistem parkir gedung dengan algoritma queue
*/

#include <iostream>
#include <string>

using namespace std;

class Tanggal {
private:
    int tahun;
    int bulan;
    int hari;

    static bool kabisat(int y) {
        return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
    }

    static int hariDalamBulan(int y, int m) {
        static const int h[] = {31, 28, 31, 30, 31, 30,
                                31, 31, 30, 31, 30, 31};

        return (m == 2 && kabisat(y)) ? 29 : h[m - 1];
    }

    static bool angka(char c) {
        return c >= '0' && c <= '9';
    }

public:
    Tanggal() : tahun(1970), bulan(1), hari(1) {}

    Tanggal(int tahun, int bulan, int hari)
        : tahun(tahun), bulan(bulan), hari(hari) {}

    static bool parse(const string& s, Tanggal& hasil) {
        if (s.size() != 10 || s[4] != '-' || s[7] != '-') {
            return false;
        }

        for (size_t i = 0; i < s.size(); i++) {
            if (i != 4 && i != 7 && !angka(s[i])) {
                return false;
            }
        }

        int y = stoi(s.substr(0, 4));
        int m = stoi(s.substr(5, 2));
        int d = stoi(s.substr(8, 2));

        if (m < 1 || m > 12 || d < 1 || d > hariDalamBulan(y, m)) {
            return false;
        }

        hasil = Tanggal(y, m, d);
        return true;
    }

    long toDays() const {
        int y = bulan <= 2 ? tahun - 1 : tahun;
        long era = y / 400;
        long yoe = y - era * 400;
        long doy = (153 * (bulan + (bulan > 2 ? -3 : 9)) + 2) / 5 + hari - 1;
        long doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;

        return era * 146097 + doe - 719468;
    }

    long awalMinggu() const {
        long d = toDays();
        return d - (((d + 3) % 7 + 7) % 7);
    }

    Tanggal plusDays(long n) const {
        Tanggal t = *this;

        while (n-- > 0) {
            if (++t.hari > hariDalamBulan(t.tahun, t.bulan)) {
                t.hari = 1;

                if (++t.bulan > 12) {
                    t.bulan = 1;
                    t.tahun++;
                }
            }
        }

        return t;
    }

    string toString() const {
        string t = to_string(tahun);

        return string(4 - t.size(), '0') + t + "-" +
               (bulan < 10 ? "0" : "") + to_string(bulan) + "-" +
               (hari < 10 ? "0" : "") + to_string(hari);
    }
};

class Waktu {
private:
    int jam;
    int menit;
    int detik;

public:
    Waktu() : jam(0), menit(0), detik(0) {}

    Waktu(int jam, int menit, int detik)
        : jam(jam), menit(menit), detik(detik) {}

    long long toSecond() const {
        return (jam * 3600LL) + (menit * 60LL) + detik;
    }

    bool validJamMasuk() const {
        return jam >= 0 && jam <= 23 && menit >= 0 && menit <= 59 &&
               detik >= 0 && detik <= 59;
    }

    bool validDurasi() const {
        return jam >= 0 && menit >= 0 && menit <= 59 &&
               detik >= 0 && detik <= 59 && toSecond() >= 1;
    }

    string toString() const {
        return string(jam < 10 ? "0" : "") + to_string(jam) + ":" +
               (menit < 10 ? "0" : "") + to_string(menit) + ":" +
               (detik < 10 ? "0" : "") + to_string(detik);
    }
};

class Person {
private:
    string nama;
    string alamat;

public:
    Person(const string& nama, const string& alamat)
        : nama(nama), alamat(alamat) {}

    void output() const {
        cout << "Nama           : " << nama << endl;
        cout << "Alamat         : " << alamat << endl;
    }
};

class Kendaraan {
private:
    string nomorPlat;

public:
    Kendaraan(const string& nomorPlat) : nomorPlat(nomorPlat) {}

    virtual ~Kendaraan() {}

    string getNomorPlat() const {
        return nomorPlat;
    }

    virtual int getTarifUmum() const = 0;

    virtual int getTarifPegawai() const = 0;

    virtual string getJenis() const = 0;

    virtual bool pegawaiTarifHarian() const {
        return true;
    }

    int hitungBiayaUmum(int jam) const {
        return getTarifUmum() * jam;
    }

    int hitungBiayaPegawai(int hari) const {
        return getTarifPegawai() * hari;
    }
};

class Mobil : public Kendaraan {
public:
    Mobil(const string& nomorPlat) : Kendaraan(nomorPlat) {}

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

class Truk : public Kendaraan {
public:
    Truk(const string& nomorPlat) : Kendaraan(nomorPlat) {}

    int getTarifUmum() const override {
        return 5000;
    }

    int getTarifPegawai() const override {
        return 5000;
    }

    string getJenis() const override {
        return "Truk";
    }

    bool pegawaiTarifHarian() const override {
        return false;
    }
};

class Motor : public Kendaraan {
public:
    Motor(const string& nomorPlat) : Kendaraan(nomorPlat) {}

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
    Parkir(const string& kode, const Person& person,
           Kendaraan* kendaraan, bool pegawai,
           const string& nip, const Tanggal& tanggal,
           const Waktu& waktuMasuk, const Waktu& lamaParkir,
           int kunjungan, const string& lokasi)
        : kode(kode), person(person), kendaraan(kendaraan),
          pegawai(pegawai), nip(nip), tanggal(tanggal),
          waktuMasuk(waktuMasuk), lamaParkir(lamaParkir),
          kunjungan(kunjungan), lokasi(lokasi) {}

    ~Parkir() {
        delete kendaraan;
    }

    Parkir(const Parkir&) = delete;
    Parkir& operator=(const Parkir&) = delete;

    string getKode() const {
        return kode;
    }

    Kendaraan* getKendaraan() const {
        return kendaraan;
    }

    bool isPegawai() const {
        return pegawai;
    }

    Tanggal getTanggal() const {
        return tanggal;
    }

    long long totalDetikKeluar() const {
        return waktuMasuk.toSecond() + lamaParkir.toSecond();
    }

    Tanggal getTanggalKeluar() const {
        return tanggal.plusDays((long) (totalDetikKeluar() / 86400));
    }

    string getJamKeluar() const {
        long long sisa = totalDetikKeluar() % 86400;
        string s = Waktu((int) (sisa / 3600), (int) ((sisa % 3600) / 60),
                         (int) (sisa % 60)).toString();

        return sisa % 60 == 0 ? s.substr(0, 5) : s;
    }

    int hitungBiaya() const {
        long long detik = lamaParkir.toSecond();
        int jam = (int) ((detik + 3599) / 3600);

        if (pegawai) {
            if (kendaraan->pegawaiTarifHarian()) {
                return kendaraan->hitungBiayaPegawai((int) ((detik + 86399) / 86400));
            }

            return kendaraan->hitungBiayaUmum(jam);
        }

        int biaya = kendaraan->hitungBiayaUmum(jam);
        return kunjungan >= 2 ? biaya - biaya * 10 / 100 : biaya;
    }

    void output() const {
        cout << "\n====================================" << endl;
        cout << "         DATA PARKIR GEDUNG" << endl;
        cout << "====================================" << endl;

        cout << "Kode Parkir    : " << kode << endl;
        cout << "Lokasi         : " << lokasi << endl;

        person.output();

        cout << "Jenis Pengguna : " << (pegawai ? "Pegawai" : "Umum") << endl;

        if (pegawai) {
            cout << "NIP            : " << nip << endl;
        }

        cout << "Kendaraan      : " << kendaraan->getJenis() << endl;
        cout << "Nomor Plat     : " << kendaraan->getNomorPlat() << endl;
        cout << "Tanggal Masuk  : " << tanggal.toString() << endl;
        cout << "Jam Masuk      : " << waktuMasuk.toString() << endl;
        cout << "Lama Parkir    : " << lamaParkir.toString() << endl;
        cout << "Tanggal Keluar : " << getTanggalKeluar().toString() << endl;
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

class QueueParkir {
private:
    Parkir** data;
    int kapasitas;
    int front;
    int rear;
    int count;

    void perbesar() {
        Parkir** baru = new Parkir*[kapasitas * 2];

        for (int i = 0; i < count; i++) {
            baru[i] = data[(front + i) % kapasitas];
        }

        delete[] data;
        data = baru;
        kapasitas *= 2;
        front = 0;
        rear = count - 1;
    }

public:
    QueueParkir(int kapasitas = 5)
        : data(new Parkir*[kapasitas]), kapasitas(kapasitas),
          front(0), rear(-1), count(0) {}

    ~QueueParkir() {
        delete[] data;
    }

    QueueParkir(const QueueParkir&) = delete;
    QueueParkir& operator=(const QueueParkir&) = delete;

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == kapasitas;
    }

    int size() const {
        return count;
    }

    void enqueue(Parkir* p) {
        if (isFull()) {
            perbesar();
        }

        rear = (rear + 1) % kapasitas;
        data[rear] = p;
        count++;
    }

    Parkir* dequeue() {
        if (isEmpty()) {
            return nullptr;
        }

        Parkir* p = data[front];
        front = (front + 1) % kapasitas;
        count--;

        return p;
    }

    Parkir* peek() const {
        return isEmpty() ? nullptr : data[front];
    }

    Parkir* get(int index) const {
        if (index < 0 || index >= count) {
            return nullptr;
        }

        return data[(front + index) % kapasitas];
    }
};

class DataParkir {
private:
    Parkir** semua;
    int kapasitasSemua;
    int jumlah;

    QueueParkir antrean;

    int jumlahDiproses;
    long long totalPendapatan;

public:
    DataParkir()
        : semua(new Parkir*[5]), kapasitasSemua(5), jumlah(0),
          jumlahDiproses(0), totalPendapatan(0) {}

    ~DataParkir() {
        for (int i = 0; i < jumlah; i++) {
            delete semua[i];
        }

        delete[] semua;
    }

    DataParkir(const DataParkir&) = delete;
    DataParkir& operator=(const DataParkir&) = delete;

    int getJumlahAntrean() const {
        return antrean.size();
    }

    void tambah(Parkir* p) {
        if (jumlah == kapasitasSemua) {
            Parkir** baru = new Parkir*[kapasitasSemua * 2];

            for (int i = 0; i < jumlah; i++) {
                baru[i] = semua[i];
            }

            delete[] semua;
            semua = baru;
            kapasitasSemua *= 2;
        }

        semua[jumlah++] = p;
        antrean.enqueue(p);
    }

    Parkir* lihatDepan() const {
        return antrean.peek();
    }

    Parkir* proses() {
        Parkir* p = antrean.dequeue();

        if (p != nullptr) {
            totalPendapatan += p->hitungBiaya();
            jumlahDiproses++;
        }

        return p;
    }

    int hitungKunjunganMinggu(const string& plat,
                              const Tanggal& tanggal) const {
        int total = 0;
        long minggu = tanggal.awalMinggu();

        for (int i = 0; i < jumlah; i++) {
            if (!semua[i]->isPegawai() &&
                semua[i]->getKendaraan()->getNomorPlat() == plat &&
                semua[i]->getTanggal().awalMinggu() == minggu) {
                total++;
            }
        }

        return total;
    }

    void outputAntrean() const {
        cout << "\n========== ANTREAN PARKIR ==========" << endl;

        if (antrean.isEmpty()) {
            cout << "Antrean kosong." << endl;
            return;
        }

        for (int i = 0; i < antrean.size(); i++) {
            Parkir* p = antrean.get(i);

            cout << (i + 1) << ". " << p->getKode()
                 << " | " << p->getKendaraan()->getJenis()
                 << " | " << p->getKendaraan()->getNomorPlat()
                 << (i == 0 ? "  <-- terdepan" : "") << endl;
        }

        cout << "Jumlah dalam antrean : " << antrean.size() << endl;
        cout << "====================================" << endl;
    }

    void output() const {
        cout << "\n\n========== LAPORAN PARKIR ==========" << endl;

        if (jumlah == 0) {
            cout << "Belum ada data parkir." << endl;
            return;
        }

        for (int i = 0; i < jumlah; i++) {
            semua[i]->output();
        }

        cout << "\nJumlah Transaksi   : " << jumlah << endl;
        cout << "Sudah Diproses     : " << jumlahDiproses << endl;
        cout << "Masih di Antrean   : " << antrean.size() << endl;
        cout << "Total Pendapatan   : Rp" << totalPendapatan << endl;
        cout << "====================================" << endl;
    }
};

class Menu {
private:
    DataParkir dataParkir;

    int inputAngka() {
        string s;
        getline(cin, s);

        try {
            return stoi(s);
        } catch (...) {
            return -1;
        }
    }

    Waktu inputWaktu() {
        cout << "Jam   : ";
        int jam = inputAngka();

        cout << "Menit : ";
        int menit = inputAngka();

        cout << "Detik : ";
        int detik = inputAngka();

        return Waktu(jam, menit, detik);
    }

    void lihatDepan() {
        Parkir* p = dataParkir.lihatDepan();

        if (p == nullptr) {
            cout << "Antrean kosong." << endl;
            return;
        }

        cout << "\nTransaksi terdepan di antrean:" << endl;
        p->output();
    }

    void prosesDepan() {
        Parkir* p = dataParkir.proses();

        if (p == nullptr) {
            cout << "Antrean kosong, tidak ada yang diproses." << endl;
            return;
        }

        cout << "\nTransaksi berikut telah diproses (keluar antrean):" << endl;
        p->output();
        cout << "Sisa antrean: " << dataParkir.getJumlahAntrean() << endl;
    }

    void tambahData() {
        cout << "Jumlah data parkir: ";
        int jumlah = inputAngka();

        if (jumlah < 1) {
            cout << "Jumlah harus lebih dari 0." << endl;
            return;
        }

        for (int i = 0; i < jumlah; i++) {
            cout << "\nData Parkir ke-" << (i + 1) << endl;

            cout << "Kode parkir    : ";
            string kode;
            getline(cin, kode);

            cout << "Lokasi parkir (1. Dalam / 2. Luar): ";
            int pilihanLokasi = inputAngka();

            if (pilihanLokasi != 1 && pilihanLokasi != 2) {
                cout << "Lokasi tidak valid. Data dilewati." << endl;
                continue;
            }

            cout << "Jenis pengguna (1. Umum / 2. Pegawai): ";
            int pilihanPengguna = inputAngka();

            if (pilihanPengguna != 1 && pilihanPengguna != 2) {
                cout << "Jenis pengguna tidak valid." << endl;
                continue;
            }

            bool pegawai = pilihanPengguna == 2;

            cout << "Nama           : ";
            string nama;
            getline(cin, nama);

            cout << "Alamat         : ";
            string alamat;
            getline(cin, alamat);

            string nip = "-";

            if (pegawai) {
                cout << "NIP            : ";
                getline(cin, nip);
            }

            cout << "Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): ";
            int jenis = inputAngka();

            if (jenis < 1 || jenis > 3) {
                cout << "Jenis kendaraan tidak valid." << endl;
                continue;
            }

            cout << "Nomor plat     : ";
            string plat;
            getline(cin, plat);

            for (char& c : plat) {
                if (c >= 'a' && c <= 'z') {
                    c -= 32;
                }
            }

            cout << "Tanggal parkir (YYYY-MM-DD): ";
            string teksTanggal;
            getline(cin, teksTanggal);
            Tanggal tanggal;

            if (!Tanggal::parse(teksTanggal, tanggal)) {
                cout << "Format tanggal tidak valid." << endl;
                continue;
            }

            cout << "\nMasukkan waktu masuk:" << endl;
            Waktu waktuMasuk = inputWaktu();

            cout << "\nMasukkan lama parkir:" << endl;
            Waktu lamaParkir = inputWaktu();

            if (!waktuMasuk.validJamMasuk()) {
                cout << "Waktu masuk tidak valid." << endl;
                continue;
            }

            if (!lamaParkir.validDurasi()) {
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

            int kunjungan = pegawai
                ? 0
                : dataParkir.hitungKunjunganMinggu(plat, tanggal) + 1;

            dataParkir.tambah(new Parkir(
                kode, Person(nama, alamat), kendaraan, pegawai, nip,
                tanggal, waktuMasuk, lamaParkir, kunjungan,
                pilihanLokasi == 2 ? "Luar" : "Dalam"
            ));

            cout << "Data " << kode << " masuk antrean (enqueue)." << endl;
        }
    }

public:
    void run() {
        cout << "====================================" << endl;
        cout << "       SISTEM PARKIR GEDUNG" << endl;
        cout << "====================================" << endl;

        bool jalan = true;

        while (jalan) {
            cout << "\n============== MENU ==============" << endl;
            cout << "1. Tambah data parkir " << endl;
            cout << "2. Lihat antrean terdepan" << endl;
            cout << "3. Proses antrean terdepan" << endl;
            cout << "4. Tampilkan seluruh antrean" << endl;
            cout << "5. Laporan parkir" << endl;
            cout << "0. Keluar" << endl;
            cout << "Pilihan: ";

            int pilihan = inputAngka();

            if (cin.eof()) {
                break;
            }

            switch (pilihan) {
                case 1:
                    tambahData();
                    break;
                case 2:
                    lihatDepan();
                    break;
                case 3:
                    prosesDepan();
                    break;
                case 4:
                    dataParkir.outputAntrean();
                    break;
                case 5:
                    dataParkir.output();
                    break;
                case 0:
                    jalan = false;
                    cout << "Terima kasih." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        }
    }
};

int main() {
    Menu menu;
    menu.run();
    return 0;
}