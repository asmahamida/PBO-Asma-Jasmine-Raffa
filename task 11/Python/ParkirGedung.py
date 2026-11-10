# Nama Program        : Gaji Pegawai
# Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
# Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
# Nama NPM Anggota 3  : Asma Hamidah (140810250053)
# Tanggal Pengerjaan  : 10 November 2026
# Deskripsi           : Program Sistem Parkir Gedung merupakan program berbasis Java yang digunakan untuk mengelola data parkir kendaraan, baik untuk pengguna umum maupun pegawai. Program ini mencatat identitas pengguna, jenis kendaraan, lokasi parkir, tanggal dan waktu masuk, serta durasi parkir. Biaya parkir dihitung berdasarkan jenis kendaraan, status pengguna, dan lama parkir, dengan penerapan diskon bagi pengguna umum sesuai ketentuan kunjungan. Program ini menerapkan konsep OOP, meliputi encapsulation, inheritance, polymorphism, abstraction, dan composition.

from datetime import date, datetime, timedelta
from math import ceil


# ==========================================
# CLASS WAKTU
# ==========================================
class Waktu:
    def __init__(self, jam=0, menit=0, detik=0):
        self.jam = jam
        self.menit = menit
        self.detik = detik

    def total_detik(self):
        return self.jam * 3600 + self.menit * 60 + self.detik

    def tampil(self):
        return f"{self.jam:02d}:{self.menit:02d}:{self.detik:02d}"


# ==========================================
# CLASS PERSON
# ==========================================
class Person:
    def __init__(self, nama, alamat):
        self.__nama = nama
        self.__alamat = alamat

    def output(self):
        print(f"Nama           : {self.__nama}")
        print(f"Alamat         : {self.__alamat}")


# ==========================================
# CLASS KENDARAAN (INDUK)
# ==========================================
class Kendaraan:
    def __init__(self, nomor_plat):
        self.nomor_plat = nomor_plat

    def get_tarif_umum(self):
        raise NotImplementedError

    def get_tarif_pegawai(self):
        raise NotImplementedError

    def get_jenis(self):
        raise NotImplementedError

    def hitung_biaya_umum(self, jam):
        return self.get_tarif_umum() * jam

    def hitung_biaya_pegawai(self, hari):
        return self.get_tarif_pegawai() * hari


# ==========================================
# CLASS MOBIL
# ==========================================
class Mobil(Kendaraan):
    def get_tarif_umum(self):
        return 3000

    def get_tarif_pegawai(self):
        return 6000

    def get_jenis(self):
        return "Mobil"


# ==========================================
# CLASS TRUK
# ==========================================
class Truk(Kendaraan):
    def get_tarif_umum(self):
        return 5000

    def get_tarif_pegawai(self):
        return 5000

    def get_jenis(self):
        return "Truk"


# ==========================================
# CLASS MOTOR
# ==========================================
class Motor(Kendaraan):
    def get_tarif_umum(self):
        return 2000

    def get_tarif_pegawai(self):
        return 3000

    def get_jenis(self):
        return "Motor"


# ==========================================
# CLASS PARKIR
# ==========================================
class Parkir:
    def __init__(self, kode, person, kendaraan, pegawai, nip,
                 tanggal, waktu_masuk, lama_parkir, kunjungan, lokasi):
        self.kode = kode
        self.person = person
        self.kendaraan = kendaraan
        self.pegawai = pegawai
        self.nip = nip
        self.tanggal = tanggal
        self.waktu_masuk = waktu_masuk
        self.lama_parkir = lama_parkir
        self.kunjungan = kunjungan
        self.lokasi = lokasi

    def waktu_keluar(self):
        masuk = datetime.combine(
            self.tanggal,
            datetime.min.time()
        ) + timedelta(seconds=(
            self.waktu_masuk.total_detik() + self.lama_parkir.total_detik()
        ))
        return masuk

    def hitung_biaya(self):
        total_detik = self.lama_parkir.total_detik()

        if self.pegawai:
            if isinstance(self.kendaraan, Truk):
                jam = ceil(total_detik / 3600)
                return self.kendaraan.hitung_biaya_umum(jam)

            hari = ceil(total_detik / 86400)
            return self.kendaraan.hitung_biaya_pegawai(hari)

        jam = ceil(total_detik / 3600)
        biaya = self.kendaraan.hitung_biaya_umum(jam)

        if self.kunjungan >= 2:
            biaya -= biaya * 10 // 100

        return biaya

    def output(self):
        keluar = self.waktu_keluar()

        print("\n====================================")
        print("         DATA PARKIR GEDUNG")
        print("====================================")
        print(f"Kode Parkir    : {self.kode}")
        print(f"Lokasi         : {self.lokasi}")
        self.person.output()
        print(f"Jenis Pengguna : {'Pegawai' if self.pegawai else 'Umum'}")

        if self.pegawai:
            print(f"NIP            : {self.nip}")

        print(f"Kendaraan      : {self.kendaraan.get_jenis()}")
        print(f"Nomor Plat     : {self.kendaraan.nomor_plat}")
        print(f"Tanggal Masuk  : {self.tanggal}")
        print(f"Jam Masuk      : {self.waktu_masuk.tampil()}")
        print(f"Lama Parkir    : {self.lama_parkir.tampil()}")
        print(f"Tanggal Keluar : {keluar.date()}")
        print(f"Jam Keluar     : {keluar.strftime('%H:%M:%S')}")

        if not self.pegawai:
            print(f"Kunjungan      : {self.kunjungan}")
            if self.kunjungan >= 2:
                print("Diskon         : 10%")

        print(f"Total Biaya    : Rp{self.hitung_biaya():,}".replace(",", "."))
        print("====================================")


# ==========================================
# CLASS DATA PARKIR
# ==========================================
class DataParkir:
    def __init__(self):
        self.parkir = []

    def hitung_kunjungan_minggu(self, plat, tanggal):
        awal_minggu = tanggal - timedelta(days=tanggal.weekday())
        akhir_minggu = awal_minggu + timedelta(days=6)

        total = 0
        for data in self.parkir:
            if (not data.pegawai
                    and data.kendaraan.nomor_plat.lower() == plat.lower()
                    and awal_minggu <= data.tanggal <= akhir_minggu):
                total += 1
        return total

    def output(self):
        print("\n\n========== LAPORAN PARKIR ==========")
        if not self.parkir:
            print("Belum ada data parkir.")
            return

        for data in self.parkir:
            data.output()

        print(f"\nJumlah Transaksi : {len(self.parkir)}")
        print("====================================")


# ==========================================
# CLASS MENU
# ==========================================
class Menu:
    def __init__(self):
        self.data_parkir = DataParkir()

    @staticmethod
    def input_int(pesan):
        return int(input(pesan).strip())

    @staticmethod
    def input_waktu(judul):
        print(f"\nMasukkan {judul}:")
        jam = Menu.input_int("Jam   : ")
        menit = Menu.input_int("Menit : ")
        detik = Menu.input_int("Detik : ")
        return Waktu(jam, menit, detik)

    @staticmethod
    def validasi_waktu(waktu, waktu_masuk=False):
        if waktu.jam < 0 or waktu.menit < 0 or waktu.detik < 0:
            return False
        if waktu.menit > 59 or waktu.detik > 59:
            return False
        if waktu_masuk and waktu.jam > 23:
            return False
        return waktu.total_detik() > 0 if not waktu_masuk else True

    def run(self):
        print("====================================")
        print("       SISTEM PARKIR GEDUNG")
        print("====================================")

        jumlah = self.input_int("Jumlah data parkir: ")
        if jumlah < 1:
            print("Jumlah harus lebih dari 0.")
            return

        data_baru = []

        for i in range(jumlah):
            print(f"\nData Parkir ke-{i + 1}")

            kode = input("Kode parkir    : ").strip()

            pilihan_lokasi = self.input_int(
                "Lokasi parkir (1. Dalam / 2. Luar): "
            )
            if pilihan_lokasi not in (1, 2):
                print("Lokasi tidak valid. Data dilewati.")
                continue
            lokasi = "Dalam" if pilihan_lokasi == 1 else "Luar"

            pilihan_pengguna = self.input_int(
                "Jenis pengguna (1. Umum / 2. Pegawai): "
            )
            if pilihan_pengguna not in (1, 2):
                print("Jenis pengguna tidak valid. Data dilewati.")
                continue
            pegawai = pilihan_pengguna == 2

            nama = input("Nama           : ").strip()
            alamat = input("Alamat         : ").strip()
            nip = input("NIP            : ").strip() if pegawai else "-"

            jenis = self.input_int(
                "Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): "
            )
            if jenis not in (1, 2, 3):
                print("Jenis kendaraan tidak valid. Data dilewati.")
                continue

            plat = input("Nomor plat     : ").strip()

            try:
                tanggal = date.fromisoformat(
                    input("Tanggal parkir (YYYY-MM-DD): ").strip()
                )
            except ValueError:
                print("Format tanggal tidak valid. Data dilewati.")
                continue

            waktu_masuk = self.input_waktu("waktu masuk")
            lama_parkir = self.input_waktu("lama parkir")

            if not self.validasi_waktu(waktu_masuk, True):
                print("Waktu masuk tidak valid. Data dilewati.")
                continue

            if not self.validasi_waktu(lama_parkir):
                print("Durasi parkir tidak valid. Data dilewati.")
                continue

            if jenis == 1:
                kendaraan = Mobil(plat)
            elif jenis == 2:
                kendaraan = Truk(plat)
            else:
                kendaraan = Motor(plat)

            kunjungan_sebelumnya = 0
            if not pegawai:
                awal_minggu = tanggal - timedelta(days=tanggal.weekday())
                akhir_minggu = awal_minggu + timedelta(days=6)

                for data in data_baru:
                    if (not data.pegawai
                            and data.kendaraan.nomor_plat.lower() == plat.lower()
                            and awal_minggu <= data.tanggal <= akhir_minggu):
                        kunjungan_sebelumnya += 1

                kunjungan_sebelumnya += (
                    self.data_parkir.hitung_kunjungan_minggu(plat, tanggal)
                )

            kunjungan_saat_ini = (
                0 if pegawai else kunjungan_sebelumnya + 1
            )

            transaksi = Parkir(
                kode, Person(nama, alamat), kendaraan, pegawai, nip,
                tanggal, waktu_masuk, lama_parkir,
                kunjungan_saat_ini, lokasi
            )
            data_baru.append(transaksi)

        self.data_parkir.parkir.extend(data_baru)
        self.data_parkir.output()


# ==========================================
# PROGRAM UTAMA
# ==========================================
if __name__ == "__main__":
    menu = Menu()
    menu.run()
