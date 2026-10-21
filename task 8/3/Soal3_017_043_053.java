/*
Nama Program        : Soal3_017_043_053.java
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 7 Oktober 2026
Deskripsi           : Program OOP Array of Object untuk menghitung
                      gaji harian dan lembur pegawai berdasarkan
                      lama kerja.
*/

import java.util.Scanner;

class Waktu {
    private int jam;
    private int menit;
    private int detik;

    public Waktu() {
        jam = 0;
        menit = 0;
        detik = 0;
    }

    public Waktu(int jam, int menit, int detik) {
        this.jam = jam;
        this.menit = menit;
        this.detik = detik;
    }

    public void setJam(int jam) {
        this.jam = jam;
    }

    public int getJam() {
        return jam;
    }

    public void setMenit(int menit) {
        this.menit = menit;
    }

    public int getMenit() {
        return menit;
    }

    public void setDetik(int detik) {
        this.detik = detik;
    }

    public int getDetik() {
        return detik;
    }

    public void input(Scanner sc) {
        jam = Integer.parseInt(sc.nextLine());
        menit = Integer.parseInt(sc.nextLine());
        detik = Integer.parseInt(sc.nextLine());
    }

    public int keDetik() {
        return jam * 3600 + menit * 60 + detik;
    }

    public int selisihDetik(Waktu waktu) {
        return waktu.keDetik() - this.keDetik();
    }

    public String output() {
        return String.format("%02d:%02d:%02d", jam, menit, detik);
    }
}

class Pegawai {
    private String NIP;
    private String nama;
    private int gol;
    private Waktu datang;
    private Waktu pulang;
    private Waktu lamaKerja;
    private Waktu jamLembur;
    private int gajiHarian;
    private int lembur;
    private int total;
    private String statusPeringatan;

    public Pegawai() {
        NIP = "";
        nama = "";
        gol = 0;
        datang = new Waktu();
        pulang = new Waktu();
        lamaKerja = new Waktu();
        jamLembur = new Waktu();
        gajiHarian = 0;
        lembur = 0;
        total = 0;
        statusPeringatan = "";
    }

    public Pegawai(String NIP, String nama, int gol) {
        this.NIP = NIP;
        this.nama = nama;
        this.gol = gol;
        datang = new Waktu();
        pulang = new Waktu();
        lamaKerja = new Waktu();
        jamLembur = new Waktu();
        gajiHarian = 0;
        lembur = 0;
        total = 0;
        statusPeringatan = "";
    }

    public void setNIP(String NIP) {
        this.NIP = NIP;
    }

    public String getNIP() {
        return NIP;
    }

    public void setNama(String nama) {
        this.nama = nama;
    }

    public String getNama() {
        return nama;
    }

    public void setGol(int gol) {
        this.gol = gol;
    }

    public int getGol() {
        return gol;
    }

    public void setDatang(Waktu datang) {
        this.datang = datang;
    }

    public Waktu getDatang() {
        return datang;
    }

    public void setPulang(Waktu pulang) {
        this.pulang = pulang;
    }

    public Waktu getPulang() {
        return pulang;
    }

    public void setLamaKerja(Waktu lamaKerja) {
        this.lamaKerja = lamaKerja;
    }

    public Waktu getLamaKerja() {
        return lamaKerja;
    }

    public void setJamLembur(Waktu jamLembur) {
        this.jamLembur = jamLembur;
    }

    public Waktu getJamLembur() {
        return jamLembur;
    }

    public void setGajiHarian(int gajiHarian) {
        this.gajiHarian = gajiHarian;
    }

    public int getGajiHarian() {
        return gajiHarian;
    }

    public void setLembur(int lembur) {
        this.lembur = lembur;
    }

    public int getLembur() {
        return lembur;
    }

    public void setTotal(int total) {
        this.total = total;
    }

    public int getTotal() {
        return total;
    }

    public void setStatusPeringatan(String statusPeringatan) {
        this.statusPeringatan = statusPeringatan;
    }

    public String getStatusPeringatan() {
        return statusPeringatan;
    }

    public void input(Scanner sc) {
        System.out.print("NIP: ");
        NIP = sc.nextLine();

        System.out.print("Nama: ");
        nama = sc.nextLine();

        System.out.print("Golongan: ");
        gol = Integer.parseInt(sc.nextLine());

        System.out.print("Jam datang: ");
        datang.setJam(Integer.parseInt(sc.nextLine()));
        System.out.print("Menit datang: ");
        datang.setMenit(Integer.parseInt(sc.nextLine()));
        System.out.print("Detik datang: ");
        datang.setDetik(Integer.parseInt(sc.nextLine()));

        System.out.print("Jam pulang: ");
        pulang.setJam(Integer.parseInt(sc.nextLine()));
        System.out.print("Menit pulang: ");
        pulang.setMenit(Integer.parseInt(sc.nextLine()));
        System.out.print("Detik pulang: ");
        pulang.setDetik(Integer.parseInt(sc.nextLine()));
    }

    public void proses() {
        int durasiDetik = datang.selisihDetik(pulang);

        int totalJam = durasiDetik / 3600;
        int sisaDetik = durasiDetik % 3600;
        int totalMenit = sisaDetik / 60;
        int totalDetik = sisaDetik % 60;

        lamaKerja = new Waktu(totalJam, totalMenit, totalDetik);

        int gaji = 0;
        int tarifLembur = 0;

        switch (gol) {
            case 1:
                gaji = 150000;
                tarifLembur = 50000;
                break;
            case 2:
                gaji = 200000;
                tarifLembur = 75000;
                break;
            case 3:
                gaji = 400000;
                tarifLembur = 150000;
                break;
            case 4:
                gaji = 500000;
                tarifLembur = 200000;
                break;
        }

        gajiHarian = gaji;

        if (durasiDetik < 8 * 3600) {
            statusPeringatan = "Peringatan";
            jamLembur = new Waktu(0, 0, 0);
            lembur = 0;
        } else {
            statusPeringatan = "ok";

            int lemburDetik = durasiDetik - 8 * 3600;
            int lemburJam = lemburDetik / 3600;

            jamLembur = new Waktu(
                lemburJam,
                (lemburDetik % 3600) / 60,
                lemburDetik % 60
            );

            lembur = lemburJam * tarifLembur;
        }

        total = gajiHarian + lembur;
    }

    public void output() {
        System.out.printf(
            "%-4s %-8s %-15s %-5d %-10s %-10s %-10s %-10s %,10d %,10d %,10d %-12s%n",
            "",
            NIP,
            nama,
            gol,
            datang.output(),
            pulang.output(),
            lamaKerja.output(),
            jamLembur.output(),
            gajiHarian,
            lembur,
            total,
            statusPeringatan
        );
    }
}

class ArrayPegawai {
    private Pegawai[] pegawai;
    private int jumlah;

    public ArrayPegawai() {
        pegawai = null;
        jumlah = 0;
    }

    public ArrayPegawai(int jumlah) {
        this.jumlah = jumlah;
        pegawai = new Pegawai[jumlah];

        for (int i = 0; i < jumlah; i++) {
            pegawai[i] = new Pegawai();
        }
    }

    public void setPegawai(Pegawai[] pegawai) {
        this.pegawai = pegawai;
    }

    public Pegawai[] getPegawai() {
        return pegawai;
    }

    public void setJumlah(int jumlah) {
        this.jumlah = jumlah;
    }

    public int getJumlah() {
        return jumlah;
    }

    public void input(Scanner sc) {
        System.out.print("Jumlah pegawai: ");
        jumlah = Integer.parseInt(sc.nextLine());

        pegawai = new Pegawai[jumlah];

        for (int i = 0; i < jumlah; i++) {
            System.out.println("\nData Pegawai ke-" + (i + 1));
            pegawai[i] = new Pegawai();
            pegawai[i].input(sc);
        }
    }

    public void proses() {
        for (int i = 0; i < jumlah; i++) {
            pegawai[i].proses();
        }
    }

    public void output() {
        System.out.println("\n                 Daftar Gaji Harian PT Informatika");
        System.out.println("---------------------------------------------------------------------------------------------------------------");
        System.out.printf(
            "%-4s %-8s %-15s %-5s %-10s %-10s %-10s %-10s %10s %10s %10s %-12s%n",
            "No", "NIP", "Nama", "Gol", "Datang", "Pulang",
            "Lama", "Jam Lembur", "Gaji Harian", "Lembur", "Total", "Status"
        );
        System.out.println("---------------------------------------------------------------------------------------------------------------");

        for (int i = 0; i < jumlah; i++) {
            System.out.printf("%-4d", i + 1);
            pegawai[i].output();
        }
    }
}

class Menu {
    private Scanner sc;

    public Menu(Scanner sc) {
        this.sc = sc;
    }

    public int tampilMenu() {
        System.out.println("\n===== MENU =====");
        System.out.println("1. Input Data Pegawai");
        System.out.println("2. Proses Gaji");
        System.out.println("3. Tampilkan Output");
        System.out.println("4. Keluar");
        System.out.print("Pilih menu: ");

        return Integer.parseInt(sc.nextLine());
    }

    public void jalankan(ArrayPegawai arrayPegawai) {
        int pilihan = 0;

        while (pilihan != 4) {
            pilihan = tampilMenu();

            switch (pilihan) {
                case 1:
                    arrayPegawai.input(sc);
                    break;
                case 2:
                    if (arrayPegawai.getPegawai() == null) {
                        System.out.println("Data pegawai belum dibuat.");
                    } else {
                        arrayPegawai.proses();
                        System.out.println("Data gaji berhasil diproses.");
                    }
                    break;
                case 3:
                    if (arrayPegawai.getPegawai() == null) {
                        System.out.println("Data pegawai belum dibuat.");
                    } else {
                        arrayPegawai.output();
                    }
                    break;
                case 4:
                    System.out.println("Program selesai.");
                    break;
                default:
                    System.out.println("Menu tidak tersedia.");
            }
        }
    }
}

public class Soal3_017_043_053 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayPegawai arrayPegawai = new ArrayPegawai();
        Menu menu = new Menu(sc);

        menu.jalankan(arrayPegawai);

        sc.close();
    }
}
