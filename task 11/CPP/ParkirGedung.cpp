
            cout << "Alamat         : ";
            getline(cin, alamat);

            if (pegawai) {
                cout << "NIP            : ";
                getline(cin, nip);
            }

            jenis = inputInt(
                "Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): "
            );

            if (jenis < 1 || jenis > 3) {
                cout << "Jenis kendaraan tidak valid. Data dilewati." << endl;
                continue;
            }

            cout << "Nomor plat     : ";
            getline(cin >> ws, plat);

            cout << "Tanggal parkir (YYYY-MM-DD): ";
            getline(cin, tanggalInput);

            if (!parseTanggal(tanggalInput, tahun, bulan, hari)) {
                cout << "Tanggal tidak valid. Data dilewati." << endl;
                continue;
            }

            cout << "\nMasukkan waktu masuk:" << endl;
            int jam, menit, detik;

            jam = inputInt("Jam   : ");
            menit = inputInt("Menit : ");
            detik = inputInt("Detik : ");

            if (jam < 0 || jam > 23 ||
                menit < 0 || menit > 59 ||
                detik < 0 || detik > 59) {
                cout << "Waktu masuk tidak valid. Data dilewati." << endl;
                continue;
            }

            Waktu waktuMasuk(jam, menit, detik);

            cout << "\nMasukkan lama parkir:" << endl;

            int jamLama, menitLama, detikLama;
            jamLama = inputInt("Jam   : ");
            menitLama = inputInt("Menit : ");
            detikLama = inputInt("Detik : ");

            if (jamLama < 0 || menitLama < 0 || menitLama > 59 ||
                detikLama < 0 || detikLama > 59 ||
                (jamLama == 0 && menitLama == 0 && detikLama == 0)) {
                cout << "Durasi parkir tidak valid. Data dilewati." << endl;
                continue;
            }

            Waktu lamaParkir(jamLama, menitLama, detikLama);

            Kendaraan* kendaraan = nullptr;

            if (jenis == 1) {
                kendaraan = new Mobil(plat);
            } else if (jenis == 2) {
                kendaraan = new Truk(plat);
            } else {
                kendaraan = new Motor(plat);
            }

            int kunjunganSebelumnya = 0;

            if (!pegawai) {
                for (int j = 0; j < jumlahValid; j++) {
                    if (!dataBaru[j].isPegawai() &&
                        dataBaru[j].platSama(plat) &&
                        kunciMinggu(
                            dataBaru[j].getTahun(),
                            dataBaru[j].getBulan(),
                            dataBaru[j].getHari()
                        ) == kunciMinggu(tahun, bulan, hari)) {
                        kunjunganSebelumnya++;
                    }
                }

                kunjunganSebelumnya +=
                    dataParkir.hitungKunjunganMinggu(
                        plat, tahun, bulan, hari
                    );
            }

            int kunjunganSaatIni =
                pegawai ? 0 : kunjunganSebelumnya + 1;

            string lokasi = pilihanLokasi == 1 ? "Dalam" : "Luar";

            Parkir transaksi;
            transaksi.isiData(
                kode, Person(nama, alamat), kendaraan,
                pegawai, nip, tahun, bulan, hari,
                waktuMasuk, lamaParkir,
                kunjunganSaatIni, lokasi
            );

            dataBaru[jumlahValid] = transaksi;
            jumlahValid++;
        }

        for (int i = 0; i < jumlahValid; i++) {
            dataParkir.tambah(dataBaru[i]);
        }

        dataParkir.output();
    }
};

// ==========================================
// PROGRAM UTAMA
// ==========================================
int main() {
    Menu menu;
    menu.run();

    return 0;
}
