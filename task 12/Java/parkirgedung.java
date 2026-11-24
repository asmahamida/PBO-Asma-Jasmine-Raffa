/*
Nama Program        : Sistem Parkir Gedung
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 23 November 2026
Deskripsi           : Membuat program Sistem Parkir Gedung menggunakan algoritma queue
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

    public String getKode() {
        return kode;
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

class QueueParkir {
    private Parkir[] data;
    private int front;
    private int rear;
    private int count;

    public QueueParkir(int kapasitas) {
        data = new Parkir[kapasitas];
        front = 0;
        rear = -1;
        count = 0;
    }

    public boolean isEmpty() {
        return count == 0;
    }

    public boolean isFull() {
        return count == data.length;
    }

    public int size() {
        return count;
    }

    private void perbesar() {
        Parkir[] baru = new Parkir[data.length * 2];

        for (int i = 0; i < count; i++) {
            baru[i] = data[(front + i) % data.length];
        }

        data = baru;
        front = 0;
        rear = count - 1;
    }

    public void enqueue(Parkir p) {
        if (isFull()) {
            perbesar();
        }

        rear = (rear + 1) % data.length;
        data[rear] = p;
        count++;
    }

    public Parkir dequeue() {
        if (isEmpty()) {
            return null;
        }

        Parkir p = data[front];
        data[front] = null;
        front = (front + 1) % data.length;
        count--;

        return p;
    }

    public Parkir peek() {
        if (isEmpty()) {
            return null;
        }

        return data[front];
    }

    public Parkir get(int index) {
        if (index < 0 || index >= count) {
            return null;
        }

        return data[(front + index) % data.length];
    }
}

class DataParkir {

    private Parkir[] semua;
    private int jumlah;

    private QueueParkir antrean;

    private int jumlahDiproses;
    private long totalPendapatan;

    public DataParkir() {
        semua = new Parkir[5];
        jumlah = 0;
        antrean = new QueueParkir(5);
        jumlahDiproses = 0;
        totalPendapatan = 0;
    }

    public int getJumlah() {
        return jumlah;
    }

    public int getJumlahAntrean() {
        return antrean.size();
    }

    public void tambah(Parkir p) {
        if (jumlah == semua.length) {
            Parkir[] baru = new Parkir[semua.length * 2];

            for (int i = 0; i < jumlah; i++) {
                baru[i] = semua[i];
            }

            semua = baru;
        }

        semua[jumlah] = p;
        jumlah++;

        antrean.enqueue(p);
    }

    public Parkir lihatDepan() {
        return antrean.peek();
    }

    public Parkir proses() {
        Parkir p = antrean.dequeue();

        if (p != null) {
            totalPendapatan += p.hitungBiaya();
            jumlahDiproses++;
        }

        return p;
    }

    public int hitungKunjunganMinggu(
        String plat, LocalDate tanggal
    ) {
        int total = 0;

        LocalDate awal = tanggal.with(DayOfWeek.MONDAY);
        LocalDate akhir = awal.plusDays(6);

        for (int i = 0; i < jumlah; i++) {
            if (semua[i] != null &&
                !semua[i].isPegawai() &&
                semua[i].getKendaraan().getNomorPlat()
                    .equalsIgnoreCase(plat)) {

                LocalDate tgl = semua[i].getTanggal();

                if (!tgl.isBefore(awal) && !tgl.isAfter(akhir)) {
                    total++;
                }
            }
        }

        return total;
    }

    public void outputAntrean() {
        System.out.println("\n========== ANTREAN PARKIR ==========");

        if (antrean.isEmpty()) {
            System.out.println("Antrean kosong.");
            return;
        }

        for (int i = 0; i < antrean.size(); i++) {
            Parkir p = antrean.get(i);

            System.out.println((i + 1) + ". " + p.getKode()
                + " | " + p.getKendaraan().getJenis()
                + " | " + p.getKendaraan().getNomorPlat()
                + (i == 0 ? "  <-- terdepan" : ""));
        }

        System.out.println("Jumlah dalam antrean : " + antrean.size());
        System.out.println("====================================");
    }

    public void output() {
        System.out.println("\n\n========== LAPORAN PARKIR ==========");

        if (jumlah == 0) {
            System.out.println("Belum ada data parkir.");
            return;
        }

        for (int i = 0; i < jumlah; i++) {
            if (semua[i] != null) {
                semua[i].output();
            }
        }

        System.out.println("\nJumlah Transaksi   : " + jumlah);
        System.out.println("Sudah Diproses     : " + jumlahDiproses);
        System.out.println("Masih di Antrean   : " + antrean.size());
        System.out.println("Total Pendapatan   : Rp" + totalPendapatan);
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

    private int bacaPilihan() {
        try {
            return Integer.parseInt(sc.nextLine().trim());
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    public void run() {
        System.out.println("====================================");
        System.out.println("       SISTEM PARKIR GEDUNG");
        System.out.println("====================================");

        boolean jalan = true;

        while (jalan) {
            System.out.println("\n============== MENU ==============");
            System.out.println("1. Tambah data parkir");
            System.out.println("2. Lihat antrean terdepan");
            System.out.println("3. Proses antrean terdepan");
            System.out.println("4. Tampilkan seluruh antrean");
            System.out.println("5. Laporan parkir");
            System.out.println("0. Keluar");
            System.out.print("Pilihan: ");

            int pilihan = bacaPilihan();

            switch (pilihan) {
                case 1:
                    tambahData();
                    break;
                case 2:
                    lihatDepan();
                    break;
                case 3:
                    prosesDepan();
                    break;
                case 4:
                    dataParkir.outputAntrean();
                    break;
                case 5:
                    dataParkir.output();
                    break;
                case 0:
                    jalan = false;
                    System.out.println("Terima kasih.");
                    break;
                default:
                    System.out.println("Pilihan tidak valid.");
            }
        }
    }

    private void lihatDepan() {
        Parkir p = dataParkir.lihatDepan();

        if (p == null) {
            System.out.println("Antrean kosong.");
            return;
        }

        System.out.println("\nTransaksi terdepan di antrean:");
        p.output();
    }

    private void prosesDepan() {
        Parkir p = dataParkir.proses();

        if (p == null) {
            System.out.println("Antrean kosong, tidak ada yang diproses.");
            return;
        }

        System.out.println("\nTransaksi berikut telah diproses (keluar antrean):");
        p.output();
        System.out.println("Sisa antrean: " + dataParkir.getJumlahAntrean());
    }

    private void tambahData() {
        System.out.print("Jumlah data parkir: ");
        int jumlah = Integer.parseInt(sc.nextLine().trim());

        if (jumlah < 1) {
            System.out.println("Jumlah harus lebih dari 0.");
            return;
        }

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

            System.out.print(
                "Jenis kendaraan (1. Mobil / 2. Truk / 3. Motor): "
            );
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

            int kunjunganSaatIni = 0;

            if (!pegawai) {
                kunjunganSaatIni =
                    dataParkir.hitungKunjunganMinggu(plat, tanggal) + 1;
            }

            Parkir baru = new Parkir(
                kode, person, kendaraan, pegawai, nip,
                tanggal, waktuMasuk, lamaParkir,
                kunjunganSaatIni
            );

            baru.setLokasi(lokasi);

            dataParkir.tambah(baru);
            System.out.println("Data " + kode
                + " masuk antrean (enqueue).");
        }
    }
}

public class parkirgedung {
    public static void main(String[] args) {
        Menu menu = new Menu();
        menu.run();
    }
}