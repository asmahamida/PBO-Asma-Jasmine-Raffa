"""
Nama Program        : Soal3_017_043_053.py
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 13 Oktober 2026
Deskripsi           : Program OOP Array of Object untuk menghitung
                      gaji harian dan lembur pegawai berdasarkan
                      lama kerja.
"""

class Waktu:
    def __init__(self, jam=0, menit=0, detik=0):
        self._jam = jam
        self._menit = menit
        self._detik = detik

    @classmethod
    def dari_detik(cls, total_detik):
        return cls(total_detik // 3600, (total_detik % 3600) // 60, total_detik % 60)

    def set_jam(self, jam):
        self._jam = jam

    def get_jam(self):
        return self._jam

    def set_menit(self, menit):
        self._menit = menit

    def get_menit(self):
        return self._menit

    def set_detik(self, detik):
        self._detik = detik

    def get_detik(self):
        return self._detik

    def input_waktu(self):
        self._jam = int(input("Jam           : ").strip())
        self._menit = int(input("Menit         : ").strip())
        self._detik = int(input("Detik         : ").strip())

    def to_second(self):
        return self._jam * 3600 + self._menit * 60 + self._detik

    def selisih_waktu(self, waktu):
        selisih = waktu.to_second() - self.to_second()
        if selisih < 0:
            selisih += 24 * 3600
        return selisih

    def output_waktu(self):
        return f"{self._jam:02d}:{self._menit:02d}:{self._detik:02d}"

class Pegawai:
    def __init__(self, nip="", nama="", gol=0, datang=None, pulang=None):
        self._nip = nip
        self._nama = nama
        self._gol = gol
        self._datang = datang if datang is not None else Waktu()
        self._pulang = pulang if pulang is not None else Waktu()

    def set_nip(self, nip):
        self._nip = nip

    def get_nip(self):
        return self._nip

    def set_nama(self, nama):
        self._nama = nama

    def get_nama(self):
        return self._nama

    def set_gol(self, gol):
        self._gol = gol

    def get_gol(self):
        return self._gol

    def set_datang(self, datang):
        self._datang = datang

    def get_datang(self):
        return self._datang

    def set_pulang(self, pulang):
        self._pulang = pulang

    def get_pulang(self):
        return self._pulang

    def lama_kerja(self):
        return self._datang.selisih_waktu(self._pulang)

    def lama_lembur(self):
        lama = self.lama_kerja()
        if lama >= 28800:
            return lama - 28800
        else:
            return 0

    def jam_lembur(self):
        return self.lama_lembur() // 3600

    def get_gaji(self):
        daftar = {1: 150000, 2: 200000, 3: 400000, 4: 500000}
        return daftar.get(self._gol, 0)

    def get_tarif_lembur(self):
        daftar = {1: 50000, 2: 75000, 3: 150000, 4: 200000}
        return daftar.get(self._gol, 0)

    def get_lembur(self):
        return self.jam_lembur() * self.get_tarif_lembur()

    def get_total(self):
        return self.get_gaji() + self.get_lembur()

    def status(self):
        if self.lama_kerja() < 28800:
            return "Peringatan"
        else:
            return "Oke"

    @staticmethod
    def format_rupiah(nilai):
        return f"{abs(nilai):,}".replace(",", ".")

    def input_pegawai(self):
        self._nip = input("NIP           : ").strip()
        self._nama = input("Nama          : ").strip()
        self._gol = int(input("Golongan      : ").strip())

        print("\nWaktu datang")
        self._datang.input_waktu()

        print("\nWaktu pulang")
        self._pulang.input_waktu()

    def output(self, no):
        lama = Waktu.dari_detik(self.lama_kerja()).output_waktu()
        lembur_waktu = Waktu.dari_detik(self.lama_lembur()).output_waktu()
        print(f"{no:<3} {self._nip:<6} {self._nama:<10} {self._gol:<4} "
              f"{self._datang.output_waktu():<9} {self._pulang.output_waktu():<9} "
              f"{lama:<9} {lembur_waktu:<10} "
              f"{Pegawai.format_rupiah(self.get_gaji()):>12} "
              f"{Pegawai.format_rupiah(self.get_lembur()):>10} "
              f"{Pegawai.format_rupiah(self.get_total()):>10}  "
              f"{self.status():<10}")

class ArrayPegawai:
    def __init__(self, jumlah=0, isi=None):
        if isi is not None:
            self._pegawai = list(isi)
            self._jumlah = len(isi)
        elif jumlah > 0:
            self._pegawai = [Pegawai() for _ in range(jumlah)]
            self._jumlah = jumlah
        else:
            self._pegawai = []
            self._jumlah = 0

    def set_pegawai(self, isi, jumlah):
        self._jumlah = jumlah
        self._pegawai = list(isi[:jumlah])

    def set_pegawai_ke(self, index, p):
        if 0 <= index < self._jumlah:
            self._pegawai[index] = p

    def get_pegawai(self):
        return self._pegawai

    def set_jumlah(self, jumlah):
        self._jumlah = jumlah

    def get_jumlah(self):
        return self._jumlah

    def input(self):
        n = 0
        while n < 1:
            try:
                n = int(input("Jumlah pegawai: ").strip())
                if n < 1:
                    print("Jumlah tidak valid, harap ulangi.")
            except ValueError:
                print("Input harus berupa angka!")

        self._jumlah = n
        self._pegawai = []

        for i in range(n):
            print(f"\nData Pegawai ke-{i + 1}")
            p = Pegawai()
            p.input_pegawai()
            self._pegawai.append(p)

    def total_gaji(self):
        total = 0
        for p in self._pegawai:
            total += p.get_total()
        return total

    def output(self):
        if self._jumlah == 0:
            print("Belum ada data pegawai.")
            return

        garis = "-" * 114

        print()
        print("                              Daftar Gaji Harian PT Informatika")
        print(garis)
        print(f"{'No':<3} {'NIP':<6} {'Nama':<10} {'Gol':<4} {'Datang':<9} "
              f"{'Pulang':<9} {'Lama':<9} {'Jam Lembur':<10} "
              f"{'Gaji Harian':>12} {'Lembur':>10} {'Total':>10}  {'Status':<10}")
        print(garis)

        for i in range(self._jumlah):
            self._pegawai[i].output(i + 1)

        print(garis)

class Menu:
    def __init__(self):
        self._pilihan = 0

    def tampilan_menu(self):
        print("\n==========================================")
        print("     MENU PROGRAM GAJI HARIAN PEGAWAI     ")
        print("==========================================")
        print("1. Constructor")
        print("2. Setter")
        print("3. Input Dalam Class")
        print("4. Input Luar Class")
        print("5. Keluar")
        print("------------------------------------------")

    def input_pilihan(self):
        try:
            self._pilihan = int(input("Pilih Menu (1-5): ").strip())
        except ValueError:
            self._pilihan = 0
        except EOFError:
            self._pilihan = 5
        print()

    def run(self):
        while True:
            self.tampilan_menu()
            self.input_pilihan()

            if self._pilihan == 1:
                self.menu_constructor()
            elif self._pilihan == 2:
                self.menu_setter()
            elif self._pilihan == 3:
                self.input_dalam()
            elif self._pilihan == 4:
                self.input_luar()
            elif self._pilihan == 5:
                print("Selesai. Keluar dari program.")
                break
            else:
                print("Pilihan menu tidak valid! Silakan masukkan opsi 1-5.")

    def menu_constructor(self):
        print("--- 1. Constructor ---")
        isi = [
            Pegawai("001", "Ali", 3, Waktu(8, 0, 0), Waktu(17, 15, 10)),
            Pegawai("004", "ida", 2, Waktu(8, 30, 0), Waktu(15, 0, 0)),
            Pegawai("005", "Adi", 1, Waktu(7, 45, 0), Waktu(18, 50, 30)),
        ]
        array_pegawai = ArrayPegawai(isi=isi)
        array_pegawai.output()

    def menu_setter(self):
        print("--- 2. Setter ---")
        array_pegawai = ArrayPegawai(jumlah=2)

        p1 = Pegawai()
        p1.set_nip("010")
        p1.set_nama("Budi")
        p1.set_gol(4)
        p1.set_datang(Waktu(7, 30, 0))
        p1.set_pulang(Waktu(17, 0, 0))

        p2 = Pegawai()
        p2.set_nip("011")
        p2.set_nama("Sari")
        p2.set_gol(2)
        p2.set_datang(Waktu(9, 0, 0))
        p2.set_pulang(Waktu(15, 30, 0))

        array_pegawai.set_pegawai_ke(0, p1)
        array_pegawai.set_pegawai_ke(1, p2)
        array_pegawai.output()

    def input_dalam(self):
        print("--- 3. Input Dalam Class ---")
        array_pegawai = ArrayPegawai()
        try:
            array_pegawai.input()
            array_pegawai.output()
        except ValueError:
            print("Input harus berupa angka! Kembali ke menu.")

    def input_luar(self):
        print("--- 4. Input Luar Class ---")
        try:
            jumlah = 0
            while jumlah < 1:
                jumlah = int(input("Jumlah pegawai: ").strip())
                if jumlah < 1:
                    print("Jumlah tidak valid, ulangi.")

            isi = []

            for i in range(jumlah):
                print(f"\nData Pegawai ke-{i + 1}")

                nip = input("NIP           : ").strip()
                nama = input("Nama          : ").strip()
                gol = int(input("Gol           : ").strip())

                print("\nWaktu datang")
                jam_datang = int(input("Jam           : ").strip())
                menit_datang = int(input("Menit         : ").strip())
                detik_datang = int(input("Detik         : ").strip())
                datang = Waktu(jam_datang, menit_datang, detik_datang)

                print("\nWaktu pulang")
                jam_pulang = int(input("Jam           : ").strip())
                menit_pulang = int(input("Menit         : ").strip())
                detik_pulang = int(input("Detik         : ").strip())
                pulang = Waktu(jam_pulang, menit_pulang, detik_pulang)

                p = Pegawai()
                p.set_nip(nip)
                p.set_nama(nama)
                p.set_gol(gol)
                p.set_datang(datang)
                p.set_pulang(pulang)
                isi.append(p)

            array_pegawai = ArrayPegawai()
            array_pegawai.set_pegawai(isi, jumlah)
            array_pegawai.output()
        except ValueError:
            print("Format input salah! Kembali ke menu.")

if __name__ == "__main__":
    menu = Menu()
    menu.run()