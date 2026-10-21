
"""
Nama Program        : Soal1_017_043_053.py
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 7 Oktober 2026
Deskripsi           : Program OOP untuk mencari nilai rata-rata,
                      nilai tertinggi, nilai terendah, dan sorting
                      dari kumpulan data bertipe array integer.
"""


class Nilai:
    def __init__(self, data=None):
        self.__data = None
        if data is not None:
            self.setData(data)

    def setData(self, data):
        self.__data = list(data)

    def getData(self):
        return self.__data

    def getJumlah(self):
        if self.__data is None:
            return 0
        return len(self.__data)

    def input(self):
        if self.__data is not None:
            pilihan = input(
                "Array sudah ada. Hapus array lama? (y/n): "
            ).lower()

            if pilihan == "n":
                print("Array batal diubah.")
                return

            if pilihan != "y":
                print("Pilihan tidak valid. Array tidak diubah.")
                return

        jumlah = int(input("Masukkan jumlah data: "))

        while jumlah < 1:
            jumlah = int(
                input("Jumlah tidak valid, masukkan ulang: ")
            )

        data = []

        for i in range(jumlah):
            nilai = int(input("Data ke-" + str(i + 1) + ": "))
            data.append(nilai)

        self.setData(data)

    def tampilData(self):
        if not self.__data:
            print("Data kosong!")
            return

        for nilai in self.__data:
            print(nilai, end=" ")
        print()

    def rataRata(self):
        total = 0

        for nilai in self.__data:
            total += nilai

        return total / len(self.__data)

    def nilaiTertinggi(self):
        maksimum = self.__data[0]

        for i in range(1, len(self.__data)):
            if self.__data[i] > maksimum:
                maksimum = self.__data[i]

        return maksimum

    def nilaiTerendah(self):
        minimum = self.__data[0]

        for i in range(1, len(self.__data)):
            if self.__data[i] < minimum:
                minimum = self.__data[i]

        return minimum

    def sortingAscending(self):
        jumlah = len(self.__data)

        for i in range(jumlah - 1):
            for j in range(jumlah - 1 - i):
                if self.__data[j] > self.__data[j + 1]:
                    temp = self.__data[j]
                    self.__data[j] = self.__data[j + 1]
                    self.__data[j + 1] = temp

    def sortingDescending(self):
        jumlah = len(self.__data)

        for i in range(jumlah - 1):
            for j in range(jumlah - 1 - i):
                if self.__data[j] < self.__data[j + 1]:
                    temp = self.__data[j]
                    self.__data[j] = self.__data[j + 1]
                    self.__data[j + 1] = temp

    def output(self):
        if not self.__data:
            print("Data kosong!")
            return

        print("Data            :", end=" ")
        self.tampilData()

        print("Rata-rata       :", self.rataRata())
        print("Nilai tertinggi :", self.nilaiTertinggi())
        print("Nilai terendah  :", self.nilaiTerendah())

        self.sortingAscending()
        print("Ascending       :", end=" ")
        self.tampilData()

        self.sortingDescending()
        print("Descending      :", end=" ")
        self.tampilData()


class Menu:
    def run(self):
        pilihan = 0

        while pilihan != 5:
            print("\n==========================================")
            print("       MENU PROGRAM ARRAY 1 DIMENSI       ")
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

                contoh = [85, 70, 92, 66, 78]
                nilai = Nilai(contoh)
                nilai.output()

            elif pilihan == 2:
                print("--- 2. Setter ---")

                nilai = Nilai()
                contoh = [50, 90, 35, 77, 61, 88]
                nilai.setData(contoh)
                nilai.output()

            elif pilihan == 3:
                print("--- 3. Input Dalam Class ---")

                nilai = Nilai()
                nilai.input()
                nilai.output()

            elif pilihan == 4:
                print("--- 4. Input Luar Class ---")

                jumlah = int(input("Masukkan jumlah data: "))

                while jumlah < 1:
                    jumlah = int(
                        input("Jumlah tidak valid, masukkan ulang: ")
                    )

                data = []

                for i in range(jumlah):
                    nilaiInput = int(
                        input("Data ke-" + str(i + 1) + ": ")
                    )
                    data.append(nilaiInput)

                nilai = Nilai()
                nilai.setData(data)
                nilai.output()

            elif pilihan == 5:
                print("Selesai. Keluar dari program.")

            else:
                print(
                    "Pilihan menu tidak valid! "
                    "Silakan masukkan opsi 1 - 5."
                )


menu = Menu()
menu.run()
