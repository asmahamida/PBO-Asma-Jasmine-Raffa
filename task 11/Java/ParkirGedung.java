/*
Nama Program        : Gaji Pegawai
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 10 November 2026
Deskripsi           : Program OOP Array of Object untuk mencari gaji
                      harian dan lembur pegawai berdasarkan lama kerja,
                      lengkap dengan status peringatan.
*/

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Scanner;


class Waktu {
    private int jam;
    private int menit;
    private int detik;

    public Waktu() {
        this.jam = 0;
        this.menit = 0;
        this.detik = 0;
    }

    public Waktu(int jam, int menit, int detik) {
        this.jam = jam;
        this.menit = menit;
        this.detik = detik;
    }

    public int getJam() {
        return jam;
    }

    public int getMenit() {
        return menit;
    }

    public int getDetik() {
        return detik;
    }

    public void inputWaktu(Scanner sc) {
        System.out.print("Jam   : ");
        jam = Integer.parseInt(sc.nextLine().trim());

        System.out.print("Menit : ");
        menit = Integer.parseInt(sc.nextLine().trim());

        System.out.print("Detik : ");
        detik = Integer.parseInt(sc.nextLine().trim());
    }

    public long toSecond() {
        return (jam * 3600L) + (menit * 60L) + detik;
    }

    public void outputWaktu() {
        System.out.printf("%02d:%02d:%02d", jam, menit, detik);
    }
}

class Person {
    private String nama;
    private String alamat;

    public Person(String nama, String alamat) {
        this.nama = nama;
        this.alamat = alamat;
    }

    public String getNama() {
        return nama;
    }

    public String getAlamat() {
        return alamat;
    }

    public void output() {
        System.out.println("Nama           : " + nama);
        System.out.println("Alamat         : " + alamat);
    }
}

abstract class Kendaraan {
    protected String nomorPlat;

    public Kendaraan(String nomorPlat) {
        this.nomorPlat = nomorPlat;
    }

    public String getNomorPlat() {
        return nomorPlat;
    }

    public abstract int getTarifUmum();

    public abstract int getTarifPegawai();

    public abstract String getJenis();

    public int hitungBiayaUmum(int jam) {
        return getTarifUmum() * jam;
    }

    public int hitungBiayaPegawai(int hari) {
        return getTarifPegawai() * hari;
    }
}

class Mobil extends Kendaraan {
    public Mobil(String nomorPlat) {
        super(nomorPlat);
    }

    @Override
    public int getTarifUmum() {
        return 3000;
    }

    @Override
    public int getTarifPegawai() {
        return 6000;
    }

    @Override
    public String getJenis() {
        return "Mobil";
    }
}

class Truk extends Kendaraan {
    public Truk(String nomorPlat) {
        super(nomorPlat);
    }

    @Override
    public int getTarifUmum() {
        return 5000;
    }

    @Override
    public int getTarifPegawai() {
        return 5000;
    }

    @Override
    public String getJenis() {
        return "Truk";
    }
}

class Motor extends Kendaraan {
    public Motor(String nomorPlat) {
        super(nomorPlat);
    }

    @Override
    public int getTarifUmum() {
        return 2000;
    }

    @Override
    public int getTarifPegawai() {
        return 3000;
    }

    @Override
    public String getJenis() {
        return "Motor";
    }
}

// ==========================================
// CLASS PARKIR
// ==========================================
class Parkir {
    private String kode;
    private Person person;
    private Kendaraan kendaraan;
    private boolean pegawai;
    private String nip;

    private LocalDate tanggal;
    private Waktu waktuMasuk;
    private Waktu lamaParkir;

    private int kunjungan;
    private String lokasi;

    public Parkir(String kode, Person person,
                  Kendaraan kendaraan, boolean pegawai,
                  String nip, LocalDate tanggal,
                  Waktu waktuMasuk, Waktu lamaParkir,
                  int kunjungan) {

        this.kode = kode;
        this.person = person;
        this.kendaraan = kendaraan;
        this.pegawai = pegawai;
        this.nip = nip;
        this.tanggal = tanggal;
        this.waktuMasuk = waktuMasuk;
        this.lamaParkir = lamaParkir;
        this.kunjungan = kunjungan;
    }

    public Kendaraan getKendaraan() {
        return kendaraan;
    }

    public boolean isPegawai() {
        return pegawai;
    }

    public LocalDate getTanggal() {
        return tanggal;
    }

    public int getKunjungan() {
        return kunjungan;
    }

    public void setLokasi(String lokasi) {
        this.lokasi = lokasi;
    }

    public LocalDateTime getWaktuKeluar() {
        LocalDateTime masuk = tanggal.atTime(
            waktuMasuk.getJam(),
            waktuMasuk.getMenit(),
            waktuMasuk.getDetik()
        );

        return masuk.plusSeconds(lamaParkir.toSecond());
    }

    public int hitungBiaya() {
        long totalDetik = lamaParkir.toSecond();

        if (pegawai) {
            if (kendaraan instanceof Truk) {
                int jam = (int) Math.ceil(totalDetik / 3600.0);
                return kendaraan.hitungBiayaUmum(jam);
            }

            int hari = (int) Math.ceil(totalDetik / 86400.0);
            return kendaraan.hitungBiayaPegawai(hari);
        }

        int jam = (int) Math.ceil(totalDetik / 3600.0);
        int biaya = kendaraan.hitungBiayaUmum(jam);

        if (kunjungan >= 2) {
            biaya -= biaya * 10 / 100;
        }

        return biaya;
    }

    public void output() {
        System.out.println("\n====================================");
        System.out.println("         DATA PARKIR GEDUNG");
        System.out.println("====================================");

        System.out.println("Kode Parkir    : " + kode);
        System.out.println("Lokasi         : " + lokasi);

        person.output();

        System.out.println("Jenis Pengguna : " +
            (pegawai ? "Pegawai" : "Umum"));

        if (pegawai) {
            System.out.println("NIP            : " + nip);
        }

        System.out.println("Kendaraan      : " + kendaraan.getJenis());
        System.out.println("Nomor Plat     : " + kendaraan.getNomorPlat());
        System.out.println("Tanggal Masuk  : " + tanggal);

        System.out.print("Jam Masuk      : ");
        waktuMasuk.outputWaktu();
        System.out.println();

        System.out.print("Lama Parkir    : ");
        lamaParkir.outputWaktu();
        System.out.println();

        System.out.println("Tanggal Keluar : " +
            getWaktuKeluar().toLocalDate());

        System.out.println("Jam Keluar     : " +
            getWaktuKeluar().toLocalTime());

        if (!pegawai) {
            System.out.println("Kunjungan      : " + kunjungan);

            if (kunjungan >= 2) {
                System.out.println("Diskon         : 10%");
            }
        }

        System.out.println("Total Biaya    : Rp" + hitungBiaya());
        System.out.println("====================================");
    }
}

class DataParkir {
    private Parkir[] parkir;
    private int jumlah;

    public DataParkir() {
        parkir = new Parkir[0];
        jumlah = 0;
    }

    public Parkir[] getParkir() {
        return parkir;
    }

    public int getJumlah() {
        return jumlah;
    }

    public void setParkir(Parkir[] parkir, int jumlah) {
        this.parkir = parkir;
        this.jumlah = jumlah;
    }

    public int hitungKunjunganMinggu(String plat,
                                      LocalDate tanggal) {
        int total = 0;

        LocalDate awal = tanggal.with(DayOfWeek.MONDAY);
        LocalDate akhir = awal.plusDays(6);

        for (int i = 0; i < jumlah; i++) {
            if (parkir[i] != null &&
                !parkir[i].isPegawai() &&
                parkir[i].getKendaraan().getNomorPlat()
                    .equalsIgnoreCase(plat)) {

                LocalDate tgl = parkir[i].getTanggal();

                if (!tgl.isBefore(awal) && !tgl.isAfter(akhir)) {
                    total++;
                }
            }
        }

        return total;
    }

    public void output() {
        System.out.println("\n\n========== LAPORAN PARKIR ==========");

        if (jumlah == 0) {
            System.out.println("Belum ada data parkir.");
            return;
        }

        for (int i = 0; i < jumlah; i++) {
            if (parkir[i] != null) {
                parkir[i].output();
            }
        }

        System.out.println("\nJumlah Transaksi : " + jumlah);
        System.out.println("====================================");
    }
}

class Menu {
    private Scanner sc;
    private DataParkir dataParkir;

    public Menu() {
        sc = new Scanner(System.in);
        dataParkir = new DataParkir();
    }

    public void run() {
        System.out.println("====================================");
        System.out.println("       SISTEM PARKIR GEDUNG");
        System.out.println("====================================");

        System.out.print("Jumlah data parkir: ");
        int jumlah = Integer.parseInt(sc.nextLine().trim());

        if (jumlah < 1) {
            System.out.println("Jumlah harus lebih dari 0.");
            return;
        }

        Parkir[] isi = new Parkir[jumlah];

        for (int i = 0; i < jumlah; i++) {
            System.out.println("\nData Parkir ke-" + (i + 1));

            System.out.print("Kode parkir    : ");
            String kode = sc.nextLine().trim();

            System.out.print("Lokasi parkir (1. Dalam / 2. Luar): ");
            int pilihanLokasi = Integer.parseInt(sc.nextLine().trim());

            if (pilihanLokasi != 1 && pilihanLokasi != 2) {
                System.out.println("Lokasi tidak valid. Data dilewati.");
                continue;
            }

            String lokasi = pilihanLokasi == 2 ? "Luar" : "Dalam";

            System.out.print("Jenis pengguna (1. Umum / 2. Pegawai): ");
            int pilihanPengguna = Integer.parseInt(sc.nextLine().trim());

            if (pilihanPengguna != 1 && pilihanPengguna != 2) {
                System.out.println("Jenis pengguna tidak valid.");
                continue;
            }

            boolean pegawai = pilihanPengguna == 2;

            System.out.print("Nama           : ");
            String nama = sc.nextLine().trim();

            System.out.print("Alamat         : ");
            String alamat = sc.nextLine().trim();

            String nip = "-";

            if (pegawai) {
                System.out.print("NIP            : ");
                nip = sc.nextLine().trim();
            }

            System.out.print("Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): ");
            int jenis = Integer.parseInt(sc.nextLine().trim());

            if (jenis < 1 || jenis > 3) {
                System.out.println("Jenis kendaraan tidak valid.");
                continue;
            }

            System.out.print("Nomor plat     : ");
            String plat = sc.nextLine().trim();

            System.out.print("Tanggal parkir (YYYY-MM-DD): ");
            LocalDate tanggal = LocalDate.parse(sc.nextLine().trim());

            System.out.println("\nMasukkan waktu masuk:");
            Waktu waktuMasuk = new Waktu();
            waktuMasuk.inputWaktu(sc);

            System.out.println("\nMasukkan lama parkir:");
            Waktu lamaParkir = new Waktu();
            lamaParkir.inputWaktu(sc);

            if (waktuMasuk.getJam() < 0 ||
                waktuMasuk.getJam() > 23 ||
                waktuMasuk.getMenit() < 0 ||
                waktuMasuk.getMenit() > 59 ||
                waktuMasuk.getDetik() < 0 ||
                waktuMasuk.getDetik() > 59) {

                System.out.println("Waktu masuk tidak valid.");
                continue;
            }

            if (lamaParkir.getJam() < 0 ||
                lamaParkir.getMenit() < 0 ||
                lamaParkir.getMenit() > 59 ||
                lamaParkir.getDetik() < 0 ||
                lamaParkir.getDetik() > 59 ||
                lamaParkir.toSecond() < 1) {

                System.out.println("Durasi parkir tidak valid.");
                continue;
            }

            Kendaraan kendaraan;

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
                default:
                    continue;
            }

            Person person = new Person(nama, alamat);

            int kunjunganSebelumnya = 0;

            if (!pegawai) {
                LocalDate awal = tanggal.with(DayOfWeek.MONDAY);
                LocalDate akhir = awal.plusDays(6);

                for (int j = 0; j < i; j++) {
                    if (isi[j] != null &&
                        !isi[j].isPegawai() &&
                        isi[j].getKendaraan().getNomorPlat()
                            .equalsIgnoreCase(plat)) {

                        LocalDate tgl = isi[j].getTanggal();

                        if (!tgl.isBefore(awal) && !tgl.isAfter(akhir)) {
                            kunjunganSebelumnya++;
                        }
                    }
                }

                kunjunganSebelumnya +=
                    dataParkir.hitungKunjunganMinggu(plat, tanggal);
            }

            int kunjunganSaatIni =
                pegawai ? 0 : kunjunganSebelumnya + 1;

            isi[i] = new Parkir(
                kode, person, kendaraan, pegawai, nip,
                tanggal, waktuMasuk, lamaParkir,
                kunjunganSaatIni
            );

            isi[i].setLokasi(lokasi);
        }

        Parkir[] lama = dataParkir.getParkir();
        int jumlahLama = dataParkir.getJumlah();

        int jumlahValid = 0;

        for (Parkir p : isi) {
            if (p != null) {
                jumlahValid++;
            }
        }

        Parkir[] gabungan = new Parkir[jumlahLama + jumlahValid];

        for (int i = 0; i < jumlahLama; i++) {
            gabungan[i] = lama[i];
        }

        int indeks = jumlahLama;

        for (Parkir p : isi) {
            if (p != null) {
                gabungan[indeks] = p;
                indeks++;
            }
        }

        dataParkir.setParkir(gabungan, gabungan.length);
        dataParkir.output();
    }
}

public class ParkirGedung {
    public static void main(String[] args) {
        Menu menu = new Menu();
        menu.run();
    }
}
