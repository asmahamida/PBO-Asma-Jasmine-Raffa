
# Nama Program        : Soal2_017_043_053.py
# Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
# Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
# Nama NPM Anggota 3  : Asma Hamidah (140810250053)
# Tanggal Pengerjaan  : 7 Oktober 2026
# Deskripsi           : Program OOP untuk penjumlahan dan
#                       perkalian dua matriks.


class Matriks:
    def __init__(self, baris=0, kolom=0, data=None):
        self.baris = baris
        self.kolom = kolom
        self.data = []

        if data is not None:
            self.setData(data)
        elif baris > 0 and kolom > 0:
            self.data = [
                [0 for j in range(kolom)]
                for i in range(baris)
            ]

    def setData(self, data):
        self.data = [baris[:] for baris in data]
        self.baris = len(self.data)

        if self.baris > 0:
            self.kolom = len(self.data[0])
        else:
            self.kolom = 0

    def getData(self):
        return self.data

    def setBaris(self, baris):
        self.baris = baris

    def getBaris(self):
        return self.baris

    def setKolom(self, kolom):
        self.kolom = kolom

    def getKolom(self):
        return self.kolom

    def input(self):
        baris = int(input("Masukkan jumlah baris: "))
        kolom = int(input("Masukkan jumlah kolom: "))

        while baris < 1 or kolom < 1:
            print("Jumlah baris dan kolom harus lebih dari 0.")
            baris = int(input("Masukkan jumlah baris: "))
            kolom = int(input("Masukkan jumlah kolom: "))

        data = []

        print("Masukkan elemen matriks:")

        for i in range(baris):
            barisData = []

            for j in range(kolom):
                elemen = int(
                    input(
                        "Data [" + str(i) + "][" + str(j) + "] = "
                    )
                )
                barisData.append(elemen)

            data.append(barisData)

        self.setData(data)

    def output(self):
        if not self.data:
            print("Matriks kosong!")
            return

        for i in range(self.baris):
            for j in range(self.kolom):
                print(self.data[i][j], end="\t")
            print()

    def penjumlahan(self, matriks2):
        hasil = Matriks(self.baris, self.kolom)

        for i in range(self.baris):
            for j in range(self.kolom):
                hasil.data[i][j] = (
                    self.data[i][j] + matriks2.data[i][j]
                )

        return hasil

    def penjumlahanVoid(self, matriks2, hasil):
        for i in range(self.baris):
            for j in range(self.kolom):
                hasil.data[i][j] = (
                    self.data[i][j] + matriks2.data[i][j]
                )

    def perkalian(self, matriks2):
        hasil = Matriks(self.baris, matriks2.kolom)

        for i in range(self.baris):
            for j in range(matriks2.kolom):
                for k in range(self.kolom):
                    hasil.data[i][j] += (
                        self.data[i][k] * matriks2.data[k][j]
                    )

        return hasil

    def perkalianVoid(self, matriks2, hasil):
        for i in range(self.baris):
            for j in range(matriks2.kolom):
                hasil.data[i][j] = 0

                for k in range(self.kolom):
                    hasil.data[i][j] += (
                        self.data[i][k] * matriks2.data[k][j]
                    )


class Menu:
    def inputLuar(self):
        baris = int(input("Masukkan jumlah baris: "))
        kolom = int(input("Masukkan jumlah kolom: "))

        while baris < 1 or kolom < 1:
            print("Jumlah baris dan kolom harus lebih dari 0.")
            baris = int(input("Masukkan jumlah baris: "))
            kolom = int(input("Masukkan jumlah kolom: "))

        data = []

        print("Masukkan elemen matriks:")

        for i in range(baris):
            barisData = []

            for j in range(kolom):
                elemen = int(
                    input(
                        "Data [" + str(i) + "][" + str(j) + "] = "
                    )
                )
                barisData.append(elemen)

            data.append(barisData)

        matriks = Matriks()
        matriks.setData(data)

        return matriks

    def tampilkanMatriks(self, matriks1, matriks2):
        print("\nMatriks 1:")
        matriks1.output()

        print("\nMatriks 2:")
        matriks2.output()

    def operasi(self, matriks1, matriks2):
        pilihanOperasi = int(
            input(
                "\nPilih operasi (1 = Penjumlahan, "
                "2 = Perkalian): "
            )
        )

        if pilihanOperasi == 1:
            if (
                matriks1.getBaris() != matriks2.getBaris()
                or matriks1.getKolom() != matriks2.getKolom()
            ):
                print("Matriks tidak dapat dijumlahkan.")
                print("Ordo kedua matriks harus sama.")
            else:
                hasil = matriks1.penjumlahan(matriks2)
                self.tampilkanMatriks(matriks1, matriks2)

                print("\nHasil Penjumlahan:")
                hasil.output()

        elif pilihanOperasi == 2:
            if matriks1.getKolom() != matriks2.getBaris():
                print("Matriks tidak dapat dikalikan.")
                print(
                    "Kolom matriks 1 harus sama dengan "
                    "baris matriks 2."
                )
            else:
                hasil = matriks1.perkalian(matriks2)
                self.tampilkanMatriks(matriks1, matriks2)

                print("\nHasil Perkalian:")
                hasil.output()

        else:
            print("Pilihan operasi tidak tersedia.")

    def run(self):
        pilihan = 0

        while pilihan != 5:
            print("\n==========================================")
            print("         MENU PROGRAM MATRIKS             ")
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

                data1 = [
                    [1, 2],
                    [3, 4]
                ]

                data2 = [
                    [5, 6],
                    [7, 8]
                ]

                matriks1 = Matriks(data=data1)
                matriks2 = Matriks(data=data2)

                self.operasi(matriks1, matriks2)

            elif pilihan == 2:
                print("--- 2. Setter ---")

                matriks1 = Matriks()
                matriks2 = Matriks()

                data1 = [
                    [1, 2],
                    [3, 4]
                ]

                data2 = [
                    [5, 6],
                    [7, 8]
                ]

                matriks1.setData(data1)
                matriks2.setData(data2)

                self.operasi(matriks1, matriks2)

            elif pilihan == 3:
                print("--- 3. Input Dalam Class ---")

                matriks1 = Matriks()
                matriks2 = Matriks()

                print("\n=== Matriks 1 ===")
                matriks1.input()

                print("\n=== Matriks 2 ===")
                matriks2.input()

                self.operasi(matriks1, matriks2)

            elif pilihan == 4:
                print("--- 4. Input Luar Class ---")

                print("\n=== Matriks 1 ===")
                matriks1 = self.inputLuar()

                print("\n=== Matriks 2 ===")
                matriks2 = self.inputLuar()

                self.operasi(matriks1, matriks2)

            elif pilihan == 5:
                print("Selesai. Keluar dari program.")

            else:
                print(
                    "Pilihan menu tidak valid! "
                    "Silakan masukkan opsi 1 - 5."
                )


menu = Menu()
menu.run()
