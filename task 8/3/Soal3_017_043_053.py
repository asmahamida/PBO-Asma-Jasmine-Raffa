
"""
Nama Program        : Soal3_017_043_053.py
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 7 Oktober 2026
Deskripsi           : Program OOP Array of Object untuk menghitung
                      gaji harian dan lembur pegawai berdasarkan
                      lama kerja.
"""


class Waktu:
    def __init__(self, jam=0, menit=0, detik=0):
        self.__jam = jam
        self.__menit = menit
        self.__detik = detik

    def setJam(self, jam):
        self.__jam = jam

    def getJam(self):
        return self.__jam

    def setMenit(self, menit):
        self.__menit = menit

    def getMenit(self):
        return self.__menit

    def setDetik(self, detik):
        self.__detik = detik

    def getDetik(self):
        return self.__detik

    def input(self):
        self.__jam = int(input("Jam: "))
        self.__menit = int(input("Menit: "))
        self.__detik = int(input("Detik: "))

    def keDetik(self):
        return self.__jam * 3600 + self.__menit * 60 + self.__detik

    def selisihDetik(self, waktu):
        return waktu.keDetik() - self.keDetik()

    def output(self):
        return f"{self.__jam:02d}:{self.__menit:02d}:{self.__detik:02d}"


class Pegawai:
    def __init__(
        self, NIP="", nama="", gol=0,
        datang=None, pulang=None
    ):
        self.__NIP = NIP
        self.__nama = nama
        self.__gol = gol
        self.__datang = datang if datang is not None else Waktu()
        self.__pulang = pulang if pulang is not None else Waktu()
        self.__lamaKerja = Waktu()
        self.__jamLembur = Waktu()
        self.__gajiHarian = 0
        self.__lembur = 0
        self.__total = 0
        self.__statusPeringatan = ""

    def setNIP(self, NIP):
        self.__NIP = NIP

    def getNIP(self):
        return self.__NIP

    def setNama(self, nama):
        self.__nama = nama

    def getNama(self):
        return self.__nama

    def setGol(self, gol):
        self.__gol = gol

    def getGol(self):
        return self.__gol

    def setDatang(self, datang):
        self.__datang = datang

    def getDatang(self):
        return self.__datang

    def setPulang(self, pulang):
        self.__pulang = pulang

    def getPulang(self):
        return self.__pulang

    def setLamaKerja(self, lamaKerja):
        self.__lamaKerja = lamaKerja

    def getLamaKerja(self):
        return self.__lamaKerja

    def setJamLembur(self, jamLembur):
        self.__jamLembur = jamLembur

    def getJamLembur(self):
        return self.__jamLembur

    def setGajiHarian(self, gajiHarian):
        self.__gajiHarian = gajiHarian

    def getGajiHarian(self):
        return self.__gajiHarian

    def setLembur(self, lembur):
        self.__lembur = lembur

    def getLembur(self):
        return self.__lembur

    def setTotal(self, total):
        self.__total = total

    def getTotal(self):
        return self.__total

    def setStatusPeringatan(self, statusPeringatan):
        self.__statusPeringatan = statusPeringatan

    def getStatusPeringatan(self):
        return self.__statusPeringatan

    def input(self):
        self.__NIP = input("NIP: ")
        self.__nama = input("Nama: ")
        self.__gol = int(input("Golongan (1-4): "))

        print("Waktu datang")
        self.__datang.input()

        print("Waktu pulang")
        self.__pulang.input()

    def proses(self):
        durasiDetik = self.__datang.selisihDetik(self.__pulang)

        if durasiDetik < 0:
            print("Waktu pulang tidak boleh lebih awal dari waktu datang.")
            self.__lamaKerja = Waktu()
            self.__jamLembur = Waktu()
            self.__gajiHarian = 0
            self.__lembur = 0
            self.__total = 0
            self.__statusPeringatan = "Data tidak valid"
            return

        totalJam = durasiDetik // 3600
        sisaDetik = durasiDetik % 3600
        totalMenit = sisaDetik // 60
        totalDetik = sisaDetik % 60

        self.__lamaKerja = Waktu(
            totalJam, totalMenit, totalDetik
        )

        if self.__gol == 1:
            gaji = 150000
            tarifLembur = 50000
        elif self.__gol == 2:
            gaji = 200000
            tarifLembur = 75000
        elif self.__gol == 3:
            gaji = 400000
            tarifLembur = 150000
        elif self.__gol == 4:
            gaji = 500000
            tarifLembur = 200000
        else:
            gaji = 0
            tarifLembur = 0

        self.__gajiHarian = gaji

        if self.__gol not in (1, 2, 3, 4):
            self.__statusPeringatan = "Gol tidak valid"
            self.__jamLembur = Waktu()
            self.__lembur = 0
        elif durasiDetik < 8 * 3600:
            self.__statusPeringatan = "Peringatan"
            self.__jamLembur = Waktu()
            self.__lembur = 0
        else:
            self.__statusPeringatan = "ok"

            lemburDetik = durasiDetik - 8 * 3600
            lemburJam = lemburDetik // 3600

            self.__jamLembur = Waktu(
                lemburJam,
                (lemburDetik % 3600) // 60,
                lemburDetik % 60
            )

            self.__lembur = lemburJam * tarifLembur

        self.__total = self.__gajiHarian + self.__lembur

    def output(self, nomor):
        print(
            f"| {nomor:<3} "
            f"| {self.__NIP:<8} "
            f"| {self.__nama:<16} "
            f"| {self.__gol:<3} "
            f"| {self.__datang.output():<8} "
            f"| {self.__pulang.output():<8} "
            f"| {self.__lamaKerja.output():<8} "
            f"| {self.__jamLembur.output():<10} "
            f"| {self.__gajiHarian:>12,} "
            f"| {self.__lembur:>10,} "
            f"| {self.__total:>12,} "
            f"| {self.__statusPeringatan:<14} |"
        )


class ArrayPegawai:
    def __init__(self, pegawai=None, jumlah=None):
        self.__pegawai = []

        if pegawai is not None:
            self.setPegawai(pegawai)
        elif jumlah is not None:
            for i in range(jumlah):
                self.__pegawai.append(Pegawai())

    def setPegawai(self, pegawai):
        self.__pegawai = list(pegawai)

    def getPegawai(self):
        return self.__pegawai

    def setPegawaiKe(self, indeks, pegawai):
        self.__pegawai[indeks] = pegawai

    def setJumlah(self, jumlah):
        while jumlah < 1:
            jumlah = int(
                input("Jumlah tidak valid, masukkan ulang: ")
            )

        self.__pegawai = [
            Pegawai() for i in range(jumlah)
        ]

    def getJumlah(self):
        return len(self.__pegawai)

    def input(self):
        jumlah = int(input("Jumlah pegawai: "))

        while jumlah < 1:
            jumlah = int(
                input("Jumlah tidak valid, masukkan ulang: ")
            )

        self.__pegawai = []

        for i in range(jumlah):
            print("\nData Pegawai ke-" + str(i + 1))
            pegawai = Pegawai()
            pegawai.input()
            self.__pegawai.append(pegawai)

    def proses(self):
        for pegawai in self.__pegawai:
            pegawai.proses()

    def output(self):
        if len(self.__pegawai) == 0:
            print("Data pegawai kosong!")
            return

        print("\n                 DAFTAR GAJI HARIAN PT INFORMATIKA")
        print("+-----+----------+------------------+-----+----------+----------+----------+------------+--------------+------------+--------------+----------------+")
        print("| No  | NIP      | Nama             | Gol | Datang   | Pulang   | Lama     | Jam Lembur | Gaji Harian  | Lembur     | Total        | Status         |")
        print("+-----+----------+------------------+-----+----------+----------+----------+------------+--------------+------------+--------------+----------------+")

        for i in range(len(self.__pegawai)):
            self.__pegawai[i].output(i + 1)

        print("+-----+----------+------------------+-----+----------+----------+----------+------------+--------------+------------+--------------+----------------+")


class Menu:
    def tampilkan(self, arrayPegawai):
        arrayPegawai.proses()
        arrayPegawai.output()

    def inputLuar(self):
        jumlah = int(input("Jumlah pegawai: "))

        while jumlah < 1:
            jumlah = int(
                input("Jumlah tidak valid, masukkan ulang: ")
            )

        isi = []

        for i in range(jumlah):
            print("\nData Pegawai ke-" + str(i + 1))

            nip = input("NIP: ")
            nama = input("Nama: ")
            gol = int(input("Golongan (1-4): "))

            print("Waktu datang")
            datang = Waktu()
            datang.input()

            print("Waktu pulang")
            pulang = Waktu()
            pulang.input()

            pegawai = Pegawai()
            pegawai.setNIP(nip)
            pegawai.setNama(nama)
            pegawai.setGol(gol)
            pegawai.setDatang(datang)
            pegawai.setPulang(pulang)

            isi.append(pegawai)

        arrayPegawai = ArrayPegawai()
        arrayPegawai.setPegawai(isi)

        return arrayPegawai

    def run(self):
        pilihan = 0

        while pilihan != 5:
            print("\n==========================================")
            print("     MENU PROGRAM GAJI HARIAN PEGAWAI    ")
            print("==========================================")
            print("1. Constructor")
            print("2. Setter")
            print("3. Input Dalam Class")
            print("4. Input Luar Class")
            print("5. Keluar")
            print("------------------------------------------")

            pilihan = int(input("Pilih Menu (1-5): "))
            print()

            if pilihan == 1:
                print("--- 1. Constructor ---")

                isi = [
                    Pegawai(
                        "001", "Ali", 3,
                        Waktu(8, 0, 0),
                        Waktu(17, 15, 10)
                    ),
                    Pegawai(
                        "004", "Ida", 2,
                        Waktu(8, 30, 0),
                        Waktu(15, 0, 0)
                    ),
                    Pegawai(
                        "005", "Adi", 1,
                        Waktu(7, 45, 0),
                        Waktu(18, 50, 30)
                    )
                ]

                arrayPegawai = ArrayPegawai(isi)
                self.tampilkan(arrayPegawai)

            elif pilihan == 2:
                print("--- 2. Setter ---")

                arrayPegawai = ArrayPegawai( jumlah=2 )

                p1 = Pegawai()
                p1.setNIP("010")
                p1.setNama("Budi")
                p1.setGol(4)
                p1.setDatang(Waktu(7, 30, 0))
                p1.setPulang(Waktu(17, 0, 0))

                p2 = Pegawai()
                p2.setNIP("011")
                p2.setNama("Sari")
                p2.setGol(2)
                p2.setDatang(Waktu(9, 0, 0))
                p2.setPulang(Waktu(15, 30, 0))

                arrayPegawai.setPegawaiKe(0, p1)
                arrayPegawai.setPegawaiKe(1, p2)

                self.tampilkan(arrayPegawai)

            elif pilihan == 3:
                print("--- 3. Input Dalam Class ---")

                arrayPegawai = ArrayPegawai()
                arrayPegawai.input()
                self.tampilkan(arrayPegawai)

            elif pilihan == 4:
                print("--- 4. Input Luar Class ---")

                arrayPegawai = self.inputLuar()
                self.tampilkan(arrayPegawai)

            elif pilihan == 5:
                print("Selesai. Keluar dari program.")

            else:
                print(
                    "Pilihan menu tidak valid! "
                    "Silakan masukkan opsi 1 - 5."
                )


menu = Menu()
menu.run()
