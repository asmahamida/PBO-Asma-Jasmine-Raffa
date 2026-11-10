
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
