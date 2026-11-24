# Nama Program        : Gaji Pegawai
# Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
# Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
# Nama NPM Anggota 3  : Asma Hamidah (140810250053)
# Tanggal Pengerjaan  : 10 November 2026
# Deskripsi           : Program Sistem Parkir Gedung merupakan program berbasis Java yang digunakan untuk mengelola data parkir kendaraan, baik untuk pengguna umum maupun pegawai. Program ini mencatat identitas pengguna, jenis kendaraan, lokasi parkir, tanggal dan waktu masuk, serta durasi parkir. Biaya parkir dihitung berdasarkan jenis kendaraan, status pengguna, dan lama parkir, dengan penerapan diskon bagi pengguna umum sesuai ketentuan kunjungan. Program ini menerapkan konsep OOP, meliputi encapsulation, inheritance, polymorphism, abstraction, dan composition.


from abc import ABC, abstractmethod
from datetime import datetime, timedelta


# ==================== CLASS WAKTU ====================
class Waktu:
    def __init__(self, jam=0, menit=0, detik=0):
        self.__jam = jam
        self.__menit = menit
        self.__detik = detik

    def getJam(self):
        return self.__jam

    def getMenit(self):
        return self.__menit

    def getDetik(self):
        return self.__detik

    def inputWaktu(self):
        self.__jam = int(input("Jam   : "))
        self.__menit = int(input("Menit : "))
        self.__detik = int(input("Detik : "))

    def toSecond(self):
        return self.__jam * 3600 + self.__menit * 60 + self.__detik

    def outputWaktu(self):
        return f"{self.__jam:02d}:{self.__menit:02d}:{self.__detik:02d}"

    def valid(self):
        return (
            self.__jam >= 0
            and 0 <= self.__menit < 60
            and 0 <= self.__detik < 60
        )


# ==================== CLASS PERSON ====================
class Person:
    def __init__(self, nama, alamat):
        self.__nama = nama
        self.__alamat = alamat

    def getNama(self):
        return self.__nama

    def getAlamat(self):
        return self.__alamat

    def output(self):
        print("Nama             :", self.__nama)
        print("Alamat           :", self.__alamat)


# ==================== CLASS KENDARAAN ====================
class Kendaraan(ABC):
    def __init__(self, nomorPlat):
        self._nomorPlat = nomorPlat

    def getNomorPlat(self):
        return self._nomorPlat

    @abstractmethod
    def getTarifUmum(self):
        pass

    @abstractmethod
    def getTarifPegawai(self):
        pass

    @abstractmethod
    def getJenis(self):
        pass

    def hitungBiayaUmum(self, jam):
        return self.getTarifUmum() * jam

    def hitungBiayaPegawai(self, hari):
        return self.getTarifPegawai() * hari


# ==================== CLASS MOBIL ====================
class Mobil(Kendaraan):
    def __init__(self, nomorPlat):
        super().__init__(nomorPlat)

    def getTarifUmum(self):
        return 3000

    def getTarifPegawai(self):
        return 6000

    def getJenis(self):
        return "Mobil"


# ==================== CLASS TRUK ====================
class Truk(Kendaraan):
    def __init__(self, nomorPlat):
        super().__init__(nomorPlat)

    def getTarifUmum(self):
        return 5000

    def getTarifPegawai(self):
        return 5000

    def getJenis(self):
        return "Truk"


# ==================== CLASS MOTOR ====================
class Motor(Kendaraan):
    def __init__(self, nomorPlat):
        super().__init__(nomorPlat)

    def getTarifUmum(self):
        return 2000

    def getTarifPegawai(self):
        return 3000

    def getJenis(self):
        return "Motor"


# ==================== CLASS PARKIR ====================
class Parkir:
    def __init__(
        self, kode, person, kendaraan, pegawai, nip,
        tanggal, waktuMasuk, lamaParkir, kunjungan
    ):
        self.__kode = kode
        self.__person = person
        self.__kendaraan = kendaraan
        self.__pegawai = pegawai
        self.__nip = nip
        self.__tanggal = tanggal
        self.__waktuMasuk = waktuMasuk
        self.__lamaParkir = lamaParkir
        self.__kunjungan = kunjungan
        self.__lokasi = ""

    def setLokasi(self, lokasi):
        self.__lokasi = lokasi

    def getKendaraan(self):
        return self.__kendaraan

    def isPegawai(self):
        return self.__pegawai

    def getTanggal(self):
        return self.__tanggal

    def getKunjungan(self):
        return self.__kunjungan

    def getWaktuKeluar(self):
        masuk = datetime.strptime(
            self.__tanggal, "%Y-%m-%d"
        ).replace(
            hour=self.__waktuMasuk.getJam(),
            minute=self.__waktuMasuk.getMenit(),
            second=self.__waktuMasuk.getDetik()
        )

        keluar = masuk + timedelta(
            seconds=self.__lamaParkir.toSecond()
        )

        if keluar.second == 0:
            return keluar.strftime("%Y-%m-%d %H:%M")

        return keluar.strftime("%Y-%m-%d %H:%M:%S")

    def hitungBiaya(self):
        totalDetik = self.__lamaParkir.toSecond()

        if self.__pegawai:
            if self.__kendaraan.getJenis() == "Truk":
                jam = (totalDetik + 3599) // 3600
                biaya = self.__kendaraan.hitungBiayaUmum(jam)
            else:
                hari = (totalDetik + 86399) // 86400
                biaya = self.__kendaraan.hitungBiayaPegawai(hari)
        else:
            jam = (totalDetik + 3599) // 3600
            biaya = self.__kendaraan.hitungBiayaUmum(jam)

            if self.__kunjungan >= 2:
                biaya -= biaya * 10 // 100

        return biaya

    def output(self):
        print("\n========================================")
        print("           LAPORAN PARKIR")
        print("========================================")
        print("Kode Parkir       :", self.__kode)
        print("Lokasi Parkir     :", self.__lokasi)

        self.__person.output()

        if self.__pegawai:
            print("Status Pengguna   : Pegawai")
            print("NIP               :", self.__nip)
        else:
            print("Status Pengguna   : Umum")

        print("Jenis Kendaraan   :", self.__kendaraan.getJenis())
        print("Nomor Plat        :", self.__kendaraan.getNomorPlat())
        print("Tanggal           :", self.__tanggal)
        print("Waktu Masuk       :", self.__waktuMasuk.outputWaktu())
        print("Lama Parkir       :", self.__lamaParkir.outputWaktu())
        print("Waktu Keluar      :", self.getWaktuKeluar())
        print("Kunjungan         :", self.__kunjungan)
        print("Total Biaya       : Rp", self.hitungBiaya())
        print("========================================")


# ==================== CLASS DATAPARKIR ====================
class DataParkir:
    def __init__(self):
        self.__parkir = []
        self.__jumlah = 0

    def getParkir(self):
        return self.__parkir

    def getJumlah(self):
        return self.__jumlah

    def setParkir(self, data):
        self.__parkir = data
        self.__jumlah = len(data)

    def hitungKunjunganMinggu(self, plat, tanggal):
        total = 1
        tanggalDicari = datetime.strptime(tanggal, "%Y-%m-%d")
        awalMinggu = (
            tanggalDicari - timedelta(days=tanggalDicari.weekday())
        ).date()

        for data in self.__parkir:
            tanggalLama = datetime.strptime(
                data.getTanggal(), "%Y-%m-%d"
            )

            awalMingguLama = (
                tanggalLama - timedelta(days=tanggalLama.weekday())
            ).date()

            if (
                not data.isPegawai()
                and data.getKendaraan().getNomorPlat().lower() == plat.lower()
                and awalMingguLama == awalMinggu
            ):
                total += 1

        return total

    def output(self):
        print("\n\n========== SELURUH DATA PARKIR ==========")

        for data in self.__parkir:
            data.output()

        print("Jumlah data parkir:", self.__jumlah)


# ==================== CLASS MENU ====================
class Menu:
    # Constructor Menu
    def __init__(self):
        self.__dataParkir = DataParkir()

    # Input jenis kendaraan
    def inputKendaraan(self):
        print("\nJenis Kendaraan:")
        print("1. Mobil")
        print("2. Truk")
        print("3. Motor")

        pilihan = int(input("Pilihan: "))
        plat = input("Nomor Plat: ")

        if pilihan == 1:
            return Mobil(plat)
        elif pilihan == 2:
            return Truk(plat)
        elif pilihan == 3:
            return Motor(plat)
        else:
            print("Jenis kendaraan tidak valid.")
            return None

    # Input data parkir berdasarkan lokasi
    def inputData(self, lokasi):
        jumlah = int(input("\nJumlah data parkir: "))

        if jumlah < 1:
            print("Jumlah harus lebih dari 0.")
            return

        dataBaru = []

        for i in range(jumlah):
            print(f"\nData Parkir ke-{i + 1}")

            kode = input("Kode Parkir: ")
            nama = input("Nama: ")
            alamat = input("Alamat: ")

            print("\nPengguna (1. Umum / 2. Pegawai): ")
            pilihanPengguna = int(input("Pilihan: "))

            if pilihanPengguna not in (1, 2):
                print("Pilihan pengguna tidak valid. Data dilewati.")
                continue

            pegawai = pilihanPengguna == 2
            nip = ""

            if pegawai:
                nip = input("NIP: ")

            kendaraan = self.inputKendaraan()

            if kendaraan is None:
                print("Data dilewati.")
                continue

            tanggal = input("Tanggal (YYYY-MM-DD): ")

            print("\nWaktu Masuk")
            waktuMasuk = Waktu()
            waktuMasuk.inputWaktu()

            print("\nLama Parkir")
            lamaParkir = Waktu()
            lamaParkir.inputWaktu()

            if (
                not waktuMasuk.valid()
                or waktuMasuk.getJam() > 23
            ):
                print("Waktu masuk tidak valid. Data dilewati.")
                continue

            if not lamaParkir.valid() or lamaParkir.toSecond() < 1:
                print("Lama parkir tidak valid. Data dilewati.")
                continue

            kunjungan = 1

            if not pegawai:
                tanggalBaru = datetime.strptime(tanggal, "%Y-%m-%d")
                awalMinggu = (
                    tanggalBaru - timedelta(days=tanggalBaru.weekday())
                ).date()

                for data in dataBaru:
                    tanggalLama = datetime.strptime(
                        data.getTanggal(), "%Y-%m-%d"
                    )

                    awalMingguLama = (
                        tanggalLama - timedelta(days=tanggalLama.weekday())
                    ).date()

                    if (
                        not data.isPegawai()
                        and data.getKendaraan().getNomorPlat().lower()
                        == kendaraan.getNomorPlat().lower()
                        and awalMingguLama == awalMinggu
                    ):
                        kunjungan += 1

                kunjungan += (
                    self.__dataParkir.hitungKunjunganMinggu(
                        kendaraan.getNomorPlat(), tanggal
                    ) - 1
                )

            person = Person(nama, alamat)

            data = Parkir(
                kode, person, kendaraan, pegawai, nip,
                tanggal, waktuMasuk, lamaParkir, kunjungan
            )

            data.setLokasi(lokasi)
            dataBaru.append(data)

        gabungan = self.__dataParkir.getParkir() + dataBaru
        self.__dataParkir.setParkir(gabungan)

    # Input parkir dalam gedung
    def inputDalam(self):
        print("\n===== INPUT PARKIR DALAM GEDUNG =====")
        self.inputData("Dalam")

    # Input parkir luar gedung
    def inputLuar(self):
        print("\n===== INPUT PARKIR LUAR GEDUNG =====")
        self.inputData("Luar")

    # Menampilkan laporan parkir
    def lihatLaporan(self):
        self.__dataParkir.output()

    # Menjalankan menu utama
    def run(self):
        pilihan = 0

        while pilihan != 4:
            print("\n================================")
            print("       SISTEM PARKIR GEDUNG")
            print("================================")
            print("1. Input Parkir Dalam")
            print("2. Input Parkir Luar")
            print("3. Lihat Laporan Parkir")
            print("4. Keluar")

            pilihan = int(input("Pilihan: "))

            if pilihan == 1:
                self.inputDalam()
            elif pilihan == 2:
                self.inputLuar()
            elif pilihan == 3:
                self.lihatLaporan()
            elif pilihan == 4:
                print("Terima kasih.")
            else:
                print("Pilihan tidak valid.")


# ==================== PROGRAM UTAMA ====================
if __name__ == "__main__":
    menu = Menu()
    menu.run()


