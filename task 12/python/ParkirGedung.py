# Nama Program        : Sistem Parkir Gedung
# Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
# Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
# Nama NPM Anggota 3  : Asma Hamidah (140810250053)
# Tanggal Pengerjaan  : 23 November 2026
# Deskripsi           : Membuat sistem parkir gedung dengan algoritma queue

from abc import ABC, abstractmethod
from datetime import date, timedelta


class Tanggal:
    def __init__(self, tahun, bulan, hari):
        self.__tanggal = date(tahun, bulan, hari)

    @staticmethod
    def parse(teks):
        if len(teks) != 10 or teks[4] != "-" or teks[7] != "-":
            return None

        if not (teks[:4] + teks[5:7] + teks[8:]).isdigit():
            return None

        try:
            return Tanggal(int(teks[:4]), int(teks[5:7]), int(teks[8:]))
        except ValueError:
            return None

    def awal_minggu(self):
        return self.__tanggal.toordinal() - self.__tanggal.weekday()

    def plus_days(self, n):
        baru = self.__tanggal + timedelta(days=n)
        return Tanggal(baru.year, baru.month, baru.day)

    def __str__(self):
        return self.__tanggal.isoformat()


class Waktu:
    def __init__(self, jam=0, menit=0, detik=0):
        self.__jam = jam
        self.__menit = menit
        self.__detik = detik

    def to_second(self):
        return self.__jam * 3600 + self.__menit * 60 + self.__detik

    def valid_jam_masuk(self):
        return (0 <= self.__jam <= 23 and 0 <= self.__menit <= 59
                and 0 <= self.__detik <= 59)

    def valid_durasi(self):
        return (self.__jam >= 0 and 0 <= self.__menit <= 59
                and 0 <= self.__detik <= 59 and self.to_second() >= 1)

    def __str__(self):
        return f"{self.__jam:02d}:{self.__menit:02d}:{self.__detik:02d}"


class Person:
    def __init__(self, nama, alamat):
        self.__nama = nama
        self.__alamat = alamat

    def output(self):
        print(f"Nama           : {self.__nama}")
        print(f"Alamat         : {self.__alamat}")


class Kendaraan(ABC):
    def __init__(self, nomor_plat):
        self.__nomor_plat = nomor_plat

    def get_nomor_plat(self):
        return self.__nomor_plat

    @abstractmethod
    def get_tarif_umum(self):
        pass

    @abstractmethod
    def get_tarif_pegawai(self):
        pass

    @abstractmethod
    def get_jenis(self):
        pass

    def pegawai_tarif_harian(self):
        return True

    def hitung_biaya_umum(self, jam):
        return self.get_tarif_umum() * jam

    def hitung_biaya_pegawai(self, hari):
        return self.get_tarif_pegawai() * hari


class Mobil(Kendaraan):
    def get_tarif_umum(self):
        return 3000

    def get_tarif_pegawai(self):
        return 6000

    def get_jenis(self):
        return "Mobil"


class Truk(Kendaraan):
    def get_tarif_umum(self):
        return 5000

    def get_tarif_pegawai(self):
        return 5000

    def get_jenis(self):
        return "Truk"

    def pegawai_tarif_harian(self):
        return False


class Motor(Kendaraan):
    def get_tarif_umum(self):
        return 2000

    def get_tarif_pegawai(self):
        return 3000

    def get_jenis(self):
        return "Motor"


class Parkir:
    def __init__(self, kode, person, kendaraan, pegawai, nip,
                 tanggal, waktu_masuk, lama_parkir, kunjungan, lokasi):
        self.__kode = kode
        self.__person = person
        self.__kendaraan = kendaraan
        self.__pegawai = pegawai
        self.__nip = nip
        self.__tanggal = tanggal
        self.__waktu_masuk = waktu_masuk
        self.__lama_parkir = lama_parkir
        self.__kunjungan = kunjungan
        self.__lokasi = lokasi

    def get_kode(self):
        return self.__kode

    def get_kendaraan(self):
        return self.__kendaraan

    def is_pegawai(self):
        return self.__pegawai

    def get_tanggal(self):
        return self.__tanggal

    def total_detik_keluar(self):
        return self.__waktu_masuk.to_second() + self.__lama_parkir.to_second()

    def get_tanggal_keluar(self):
        return self.__tanggal.plus_days(self.total_detik_keluar() // 86400)

    def get_jam_keluar(self):
        sisa = self.total_detik_keluar() % 86400
        teks = str(Waktu(sisa // 3600, (sisa % 3600) // 60, sisa % 60))

        return teks[:5] if sisa % 60 == 0 else teks

    def hitung_biaya(self):
        detik = self.__lama_parkir.to_second()
        jam = (detik + 3599) // 3600

        if self.__pegawai:
            if self.__kendaraan.pegawai_tarif_harian():
                hari = (detik + 86399) // 86400
                return self.__kendaraan.hitung_biaya_pegawai(hari)

            return self.__kendaraan.hitung_biaya_umum(jam)

        biaya = self.__kendaraan.hitung_biaya_umum(jam)
        return biaya - biaya * 10 // 100 if self.__kunjungan >= 2 else biaya

    def output(self):
        print("\n====================================")
        print("         DATA PARKIR GEDUNG")
        print("====================================")

        print(f"Kode Parkir    : {self.__kode}")
        print(f"Lokasi         : {self.__lokasi}")

        self.__person.output()

        print(f"Jenis Pengguna : {'Pegawai' if self.__pegawai else 'Umum'}")

        if self.__pegawai:
            print(f"NIP            : {self.__nip}")

        print(f"Kendaraan      : {self.__kendaraan.get_jenis()}")
        print(f"Nomor Plat     : {self.__kendaraan.get_nomor_plat()}")
        print(f"Tanggal Masuk  : {self.__tanggal}")
        print(f"Jam Masuk      : {self.__waktu_masuk}")
        print(f"Lama Parkir    : {self.__lama_parkir}")
        print(f"Tanggal Keluar : {self.get_tanggal_keluar()}")
        print(f"Jam Keluar     : {self.get_jam_keluar()}")

        if not self.__pegawai:
            print(f"Kunjungan      : {self.__kunjungan}")

            if self.__kunjungan >= 2:
                print("Diskon         : 10%")

        print(f"Total Biaya    : Rp{self.hitung_biaya()}")
        print("====================================")


class QueueParkir:
    def __init__(self, kapasitas=5):
        self.__data = [None] * kapasitas
        self.__kapasitas = kapasitas
        self.__front = 0
        self.__rear = -1
        self.__count = 0

    def __perbesar(self):
        baru = [None] * (self.__kapasitas * 2)

        for i in range(self.__count):
            baru[i] = self.__data[(self.__front + i) % self.__kapasitas]

        self.__data = baru
        self.__kapasitas *= 2
        self.__front = 0
        self.__rear = self.__count - 1

    def is_empty(self):
        return self.__count == 0

    def is_full(self):
        return self.__count == self.__kapasitas

    def size(self):
        return self.__count

    def enqueue(self, p):
        if self.is_full():
            self.__perbesar()

        self.__rear = (self.__rear + 1) % self.__kapasitas
        self.__data[self.__rear] = p
        self.__count += 1

    def dequeue(self):
        if self.is_empty():
            return None

        p = self.__data[self.__front]
        self.__data[self.__front] = None
        self.__front = (self.__front + 1) % self.__kapasitas
        self.__count -= 1

        return p

    def peek(self):
        return None if self.is_empty() else self.__data[self.__front]

    def get(self, index):
        if index < 0 or index >= self.__count:
            return None

        return self.__data[(self.__front + index) % self.__kapasitas]


class DataParkir:
    def __init__(self):
        self.__semua = []
        self.__antrean = QueueParkir()
        self.__jumlah_diproses = 0
        self.__total_pendapatan = 0

    def get_jumlah_antrean(self):
        return self.__antrean.size()

    def tambah(self, p):
        self.__semua.append(p)
        self.__antrean.enqueue(p)

    def lihat_depan(self):
        return self.__antrean.peek()

    def proses(self):
        p = self.__antrean.dequeue()

        if p is not None:
            self.__total_pendapatan += p.hitung_biaya()
            self.__jumlah_diproses += 1

        return p

    def hitung_kunjungan_minggu(self, plat, tanggal):
        total = 0
        minggu = tanggal.awal_minggu()

        for p in self.__semua:
            if (not p.is_pegawai()
                    and p.get_kendaraan().get_nomor_plat() == plat
                    and p.get_tanggal().awal_minggu() == minggu):
                total += 1

        return total

    def output_antrean(self):
        print("\n========== ANTREAN PARKIR ==========")

        if self.__antrean.is_empty():
            print("Antrean kosong.")
            return

        for i in range(self.__antrean.size()):
            p = self.__antrean.get(i)
            penanda = "  <-- terdepan" if i == 0 else ""

            print(f"{i + 1}. {p.get_kode()} | {p.get_kendaraan().get_jenis()}"
                  f" | {p.get_kendaraan().get_nomor_plat()}{penanda}")

        print(f"Jumlah dalam antrean : {self.__antrean.size()}")
        print("====================================")

    def output(self):
        print("\n\n========== LAPORAN PARKIR ==========")

        if not self.__semua:
            print("Belum ada data parkir.")
            return

        for p in self.__semua:
            p.output()

        print(f"\nJumlah Transaksi   : {len(self.__semua)}")
        print(f"Sudah Diproses     : {self.__jumlah_diproses}")
        print(f"Masih di Antrean   : {self.__antrean.size()}")
        print(f"Total Pendapatan   : Rp{self.__total_pendapatan}")
        print("====================================")


class Menu:
    def __init__(self):
        self.__data_parkir = DataParkir()

    def __input_angka(self):
        try:
            return int(input())
        except ValueError:
            return -1

    def __input_waktu(self):
        print("Jam   : ", end="")
        jam = self.__input_angka()

        print("Menit : ", end="")
        menit = self.__input_angka()

        print("Detik : ", end="")
        detik = self.__input_angka()

        return Waktu(jam, menit, detik)

    def __lihat_depan(self):
        p = self.__data_parkir.lihat_depan()

        if p is None:
            print("Antrean kosong.")
            return

        print("\nTransaksi terdepan di antrean:")
        p.output()

    def __proses_depan(self):
        p = self.__data_parkir.proses()

        if p is None:
            print("Antrean kosong, tidak ada yang diproses.")
            return

        print("\nTransaksi berikut telah diproses (keluar antrean):")
        p.output()
        print(f"Sisa antrean: {self.__data_parkir.get_jumlah_antrean()}")

    def __tambah_data(self):
        print("Jumlah data parkir: ", end="")
        jumlah = self.__input_angka()

        if jumlah < 1:
            print("Jumlah harus lebih dari 0.")
            return

        for i in range(jumlah):
            print(f"\nData Parkir ke-{i + 1}")

            print("Kode parkir    : ", end="")
            kode = input().strip()

            print("Lokasi parkir (1. Dalam / 2. Luar): ", end="")
            pilihan_lokasi = self.__input_angka()

            if pilihan_lokasi not in (1, 2):
                print("Lokasi tidak valid. Data dilewati.")
                continue

            print("Jenis pengguna (1. Umum / 2. Pegawai): ", end="")
            pilihan_pengguna = self.__input_angka()

            if pilihan_pengguna not in (1, 2):
                print("Jenis pengguna tidak valid.")
                continue

            pegawai = pilihan_pengguna == 2

            print("Nama           : ", end="")
            nama = input().strip()

            print("Alamat         : ", end="")
            alamat = input().strip()

            nip = "-"

            if pegawai:
                print("NIP            : ", end="")
                nip = input().strip()

            print("Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): ", end="")
            jenis = self.__input_angka()

            if jenis not in (1, 2, 3):
                print("Jenis kendaraan tidak valid.")
                continue

            print("Nomor plat     : ", end="")
            plat = input().strip().upper()

            print("Tanggal parkir (YYYY-MM-DD): ", end="")
            tanggal = Tanggal.parse(input().strip())

            if tanggal is None:
                print("Format tanggal tidak valid.")
                continue

            print("\nMasukkan waktu masuk:")
            waktu_masuk = self.__input_waktu()

            print("\nMasukkan lama parkir:")
            lama_parkir = self.__input_waktu()

            if not waktu_masuk.valid_jam_masuk():
                print("Waktu masuk tidak valid.")
                continue

            if not lama_parkir.valid_durasi():
                print("Durasi parkir tidak valid.")
                continue

            kendaraan = {1: Mobil, 2: Truk, 3: Motor}[jenis](plat)

            kunjungan = 0

            if not pegawai:
                kunjungan = self.__data_parkir.hitung_kunjungan_minggu(
                    plat, tanggal) + 1

            self.__data_parkir.tambah(Parkir(
                kode, Person(nama, alamat), kendaraan, pegawai, nip,
                tanggal, waktu_masuk, lama_parkir, kunjungan,
                "Luar" if pilihan_lokasi == 2 else "Dalam"
            ))

            print(f"Data {kode} masuk antrean (enqueue).")

    def run(self):
        print("====================================")
        print("       SISTEM PARKIR GEDUNG")
        print("====================================")

        jalan = True

        while jalan:
            print("\n============== MENU ==============")
            print("1. Tambah data parkir ")
            print("2. Lihat antrean terdepan")
            print("3. Proses antrean terdepan")
            print("4. Tampilkan seluruh antrean")
            print("5. Laporan parkir")
            print("0. Keluar")
            print("Pilihan: ", end="")

            pilihan = self.__input_angka()

            if pilihan == 1:
                self.__tambah_data()
            elif pilihan == 2:
                self.__lihat_depan()
            elif pilihan == 3:
                self.__proses_depan()
            elif pilihan == 4:
                self.__data_parkir.output_antrean()
            elif pilihan == 5:
                self.__data_parkir.output()
            elif pilihan == 0:
                jalan = False
                print("Terima kasih.")
            else:
                print("Pilihan tidak valid.")


if __name__ == "__main__":
    try:
        Menu().run()
    except EOFError:
        pass