/*
Nama Program        : Soal3_017_043_053.cpp
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 25 Oktober 2026
Deskripsi           : Program OOP Array of Object untuk mencari gaji
                      harian dan lembur pegawai berdasarkan lama kerja,
                      lengkap dengan status peringatan.
*/

import java.util.Scanner;

class Waktu {
    private int jam;
    private int menit;
    private int detik;

    public Waktu(){
        jam = 0;
        menit = 0;
        detik = 0;
    }

    public Waktu(int jam, int menit, int detik){
        this.jam = jam;
        this.menit = menit;
        this.detik = detik;
    }

    public Waktu(int totalDetik){
        this.jam = totalDetik / 3600;
        this.menit = (totalDetik % 3600) / 60;
        this.detik = totalDetik % 60;
    }

    public void setJam(int jam){
        this.jam = jam;
    }

    public int getJam(){
        return jam;
    }

    public void setMenit(int menit){
        this.menit = menit;
    }

    public int getMenit(){
        return menit;
    }

    public void setDetik(int detik){
        this.detik = detik;
    }

    public int getDetik(){
        return detik;
    }

    public void inputWaktu(Scanner sc){
        System.out.print("Jam           : ");
        jam = Integer.parseInt(sc.nextLine().trim());
        System.out.print("Menit         : ");
        menit = Integer.parseInt(sc.nextLine().trim());
        System.out.print("Detik         : ");
        detik = Integer.parseInt(sc.nextLine().trim());
    }

    public int toSecond(){
        return jam * 3600 + menit * 60 + detik;
    }

    public int selisihWaktu(Waktu waktu){
        int selisih = waktu.toSecond() - this.toSecond();
        if (selisih < 0){
            selisih += 24 * 3600;
        }
        return selisih;
    }

    public String outputWaktu(){
        return String.format("%02d:%02d:%02d", jam, menit, detik);
    }
}

class Person {
    private String nama;
    private String alamat;

    public Person(){
        nama = "";
        alamat = "";
    }

    public Person(String nama, String alamat){
        this.nama = nama;
        this.alamat = alamat;
    }

    public void setNama(String nama) {
        this.nama = nama;
    }

    public String getNama() {
        return nama;
    }

    public void setAlamat(String alamat) {
        this.alamat = alamat;
    }

    public String getAlamat() {
        return alamat;
    }

    public void inputPerson(Scanner sc){
        System.out.print("Nama          : ");
        nama = sc.nextLine().trim();

        System.out.print("Alamat        : ");
        alamat = sc.nextLine().trim();
    }

    public String getInfo(){
        return nama + " (" + alamat + ")";
    }

    public void outputPerson(){
        System.out.println("Nama          : " + nama);
        System.out.println("Alamat        : " + alamat);
    }
}

class Pegawai extends Person {
    private String NIP;
    private int gol;
    private Waktu datang;
    private Waktu pulang;

    public Pegawai(){
        super();
        NIP = "";
        gol = 0;
        datang = new Waktu();
        pulang = new Waktu();
    }

    public Pegawai(String NIP, String nama, String alamat, int gol, Waktu datang, Waktu pulang){
        super(nama, alamat);
        this.NIP = NIP;
        this.gol = gol;
        this.datang = datang;
        this.pulang = pulang;
    }

    public void setNIP(String NIP) {
        this.NIP = NIP;
    }

    public String getNIP() {
        return NIP;
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

    
    public int lamaKerja(){
        return datang.selisihWaktu(pulang);
    }

    public int lamaLembur(){
        int lama = lamaKerja();

        if (lama >= 28800){
            return lama - 28800;
        }
        else{
            return 0;
        }
    }

    public int jamLembur(){
        return lamaLembur() / 3600;
    }

    public int getGaji(){
        switch (gol){
            case 1: return 150000;
            case 2: return 200000;
            case 3: return 400000;
            case 4: return 500000;
            default: return 0;
        }
    }

    public int getTarifLembur(){
        switch (gol){
            case 1: return  50000;
            case 2: return  75000;
            case 3: return 150000;
            case 4: return 200000;
            default: return 0;
        }
    }

    public int getLembur(){
        return jamLembur() * getTarifLembur();
    }

    public int getTotal(){
        return getGaji() + getLembur();
    }

    public String status(){
        if (lamaKerja() < 28800){
            return "Peringatan";
        }
        else {
            return "ok";
        }
    }

    public static String formatRupiah(int nilai) {
        String angka = String.valueOf(Math.abs(nilai));
        StringBuilder hasil = new StringBuilder();
        int hitung = 0;
        for (int i = angka.length() - 1; i >= 0; i--) {
            hasil.insert(0, angka.charAt(i));
            hitung++;
            if (hitung % 3 == 0 && i != 0) {
                hasil.insert(0, '.');
            }
        }
        return hasil.toString();
    }

    public void inputPegawai(Scanner sc){
        System.out.print("NIP           : ");
        NIP = sc.nextLine().trim();

        inputPerson(sc);   

        System.out.print("Golongan      : ");
        gol = Integer.parseInt(sc.nextLine().trim());

        System.out.println("\nWaktu datang");
        datang.inputWaktu(sc);

        System.out.println("\nWaktu pulang");
        pulang.inputWaktu(sc);
    }

    public void output(int no) {
        System.out.printf("%-3d %-6s %-10s %-10s %-4d %-9s %-9s %-9s %-10s %12s %10s %10s  %-10s%n",
                no,
                NIP,
                getNama(),
                getAlamat(),
                gol,
                datang.outputWaktu(),
                pulang.outputWaktu(),
                new Waktu(lamaKerja()).outputWaktu(),
                new Waktu(lamaLembur()).outputWaktu(),
                formatRupiah(getGaji()),
                formatRupiah(getLembur()),
                formatRupiah(getTotal()),
                status());
    }
}

class ArrayPegawai {
    private Pegawai[] pegawai;
    private int jumlah;

    public ArrayPegawai(){
        pegawai = null;
        jumlah = 0;
    }

    public ArrayPegawai(int jumlah){
        this.jumlah = jumlah;
        pegawai = new Pegawai[jumlah];

        for (int i = 0; i < jumlah; i++){
            pegawai[i] = new Pegawai();
        }
    }

    public ArrayPegawai(Pegawai[] isi, int jumlah) {
        this.jumlah = jumlah;
        this.pegawai = new Pegawai[jumlah];
        for (int i = 0; i < jumlah; i++) {
            this.pegawai[i] = isi[i];
        }
    }

    public void setPegawai(Pegawai[] isi, int jumlah){
        this.jumlah = jumlah;
        this.pegawai = new Pegawai[jumlah];

        for(int i = 0; i < jumlah; i++){
            this.pegawai[i] = isi[i];
        }
    }

    public void setPegawaiKe(int index, Pegawai p) {
        if (pegawai != null && index >= 0 && index < jumlah) {
            pegawai[index] = p;
        }
    }

    public Pegawai[] getPegawai(){
        return pegawai;
    }

    public void setJumlah(int jumlah){
        this.jumlah = jumlah;
    }

    public int getJumlah(){
        return jumlah;
    }

    public void input(Scanner sc){
        int n = 0;
        while (n < 1){
            try {
                System.out.print("Jumlah pegawai: ");
                n = Integer.parseInt(sc.nextLine().trim());
                if (n < 1){
                    System.out.println("Jumlah tidak valid, harap ulangi.");
                }
            }
            catch(NumberFormatException e){
                System.out.println("Input harus berupa angka!");
            }
        }

        this.jumlah = n;
        this.pegawai = new Pegawai[n];

        for (int i = 0; i < n; i++){
            System.out.println("\nData Pegawai ke-" + (i + 1));
            this.pegawai[i] = new Pegawai();
            this.pegawai[i].inputPegawai(sc);
        }
    }

    public int totalGaji(){
        int total = 0;
        for(int i = 0; i < jumlah; i++){
            total += pegawai[i].getTotal();
        }
        return total;
    }

    public int rataRataGaji(){
        return Math.round((float) totalGaji() / jumlah);
    }

    public Pegawai gajiTertinggi(){
        Pegawai max = pegawai[0];
        for (int i = 1; i < jumlah; i++){
            if (pegawai[i].getTotal() > max.getTotal()){
                max = pegawai[i];
            }
        }
        return max;
    }

    public Pegawai gajiTerendah(){
        Pegawai min = pegawai[0];
        for (int i = 1; i < jumlah; i++){
            if (pegawai[i].getTotal() < min.getTotal()){
                min = pegawai[i];
            }
        }
        return min;
    }

    public void output() {
        if (pegawai == null || jumlah == 0){
            System.out.println("Belum ada data pegawai.");
            return;
        }

        String garis = "-".repeat(125);

        System.out.println();
        System.out.println("                                  Daftar Gaji Harian PT Informatika");
        System.out.println(garis);
        System.out.printf("%-3s %-6s %-10s %-10s %-4s %-9s %-9s %-9s %-10s %12s %10s %10s  %-10s%n",
                "No", "NIP", "Nama", "Alamat", "Gol", "Datang", "Pulang", "Lama",
                "Jam Lembur", "Gaji Harian", "Lembur", "Total", "Status");
        System.out.println(garis);

        for (int i = 0; i < jumlah; i++){
            pegawai[i].output(i + 1);
        }

        System.out.println(garis);

        Pegawai max = gajiTertinggi();
        Pegawai min = gajiTerendah();

        System.out.println("Rata-rata Gaji : " + Pegawai.formatRupiah(rataRataGaji()));
        System.out.println("Gaji Tertinggi : " + Pegawai.formatRupiah(max.getTotal()) + " (" + max.getNama() + ")");
        System.out.println("Gaji Terendah  : " + Pegawai.formatRupiah(min.getTotal()) + " (" + min.getNama() + ")");
    }
}

class Menu {
    private Scanner sc;
    private int pilihan;

    public Menu() {
        sc = new Scanner(System.in);
        pilihan = 0;
    }

    public Menu(Scanner sc) {
        this.sc = sc;
        pilihan = 0;
    }

    public void tampilanMenu() {
        System.out.println("\n==========================================");
        System.out.println("     MENU PROGRAM GAJI HARIAN PEGAWAI     ");
        System.out.println("==========================================");
        System.out.println("1. Constructor");
        System.out.println("2. Setter");
        System.out.println("3. Input Dalam Class");
        System.out.println("4. Input Luar Class");
        System.out.println("5. Keluar");
        System.out.println("------------------------------------------");
    }

    public void inputPilihan() {
        System.out.print("Pilih Menu (1-5): ");
        try {
            pilihan = Integer.parseInt(sc.nextLine().trim());
        }
        catch (NumberFormatException e) {
            pilihan = 0;
        }
        System.out.println();
    }

    public void run() {
        do {
            tampilanMenu();
            inputPilihan();

            switch (pilihan) {
                case 1:
                    Constructor();
                    break;
                case 2:
                    Setter();
                    break;
                case 3:
                    inputDalam();
                    break;
                case 4:
                    inputLuar();
                    break;
                case 5:
                    System.out.println("Selesai. Keluar dari program.");
                    break;
                default:
                    System.out.println("Pilihan menu tidak valid! Silakan masukkan opsi 1-5.");
                    break;
            }
        }
        while(pilihan != 5);
    }

    private void Constructor(){
        System.out.println("--- 1. Constructor ---");
        Pegawai[] isi = {
            new Pegawai("001", "Ali", "Dago 4",   3, new Waktu(8, 0, 0),  new Waktu(17, 15, 10)),
            new Pegawai("004", "ida", "Uber 3",   2, new Waktu(8, 30, 0), new Waktu(15, 0, 0)),
            new Pegawai("005", "Adi", "Riung 10", 1, new Waktu(7, 45, 0), new Waktu(18, 50, 30))
        };
        ArrayPegawai arrayPegawai = new ArrayPegawai(isi, 3);
        arrayPegawai.output();
    }

    private void Setter(){
        System.out.println("--- 2. Setter ---");
        ArrayPegawai arrayPegawai = new ArrayPegawai(2);

        Pegawai p1 = new Pegawai();
        p1.setNIP("010");
        p1.setNama("Budi");
        p1.setAlamat("Cihampelas");
        p1.setGol(4);
        p1.setDatang(new Waktu(7, 30, 0));
        p1.setPulang(new Waktu(17, 0, 0));

        Pegawai p2 = new Pegawai();
        p2.setNIP("011");
        p2.setNama("Sari");
        p2.setAlamat("Setiabudi");
        p2.setGol(2);
        p2.setDatang(new Waktu(9, 0, 0));
        p2.setPulang(new Waktu(15, 30, 0));

        arrayPegawai.setPegawaiKe(0, p1);
        arrayPegawai.setPegawaiKe(1, p2);
        arrayPegawai.output();
    }

    private void inputDalam() {
        System.out.println("--- 3. Input Dalam Class ---");
        ArrayPegawai arrayPegawai = new ArrayPegawai();
        try {
            arrayPegawai.input(sc);
            arrayPegawai.output();
        } catch (NumberFormatException e) {
            System.out.println("Input harus berupa angka! Kembali ke menu.");
        }
    }

    private void inputLuar() {
        System.out.println("--- 4. Input Luar Class ---");
        try {
            int jumlah = 0;
            while (jumlah < 1) {
                System.out.print("Jumlah pegawai: ");
                jumlah = Integer.parseInt(sc.nextLine().trim());
                if (jumlah < 1) {
                    System.out.println("Jumlah tidak valid, ulangi.");
                }
            }

            Pegawai[] isi = new Pegawai[jumlah];

            for (int i = 0; i < jumlah; i++) {
                System.out.println("\nData Pegawai ke-" + (i + 1));

                System.out.print("NIP           : ");
                String nip = sc.nextLine().trim();

                System.out.print("Nama          : ");
                String nama = sc.nextLine().trim();

                System.out.print("Alamat        : ");
                String alamat = sc.nextLine().trim();

                System.out.print("Gol           : ");
                int gol = Integer.parseInt(sc.nextLine().trim());

                System.out.println("\nWaktu datang");
                System.out.print("Jam           : ");
                int jamDatang = Integer.parseInt(sc.nextLine().trim());
                System.out.print("Menit         : ");
                int menitDatang = Integer.parseInt(sc.nextLine().trim());
                System.out.print("Detik         : ");
                int detikDatang = Integer.parseInt(sc.nextLine().trim());
                Waktu datang = new Waktu(jamDatang, menitDatang, detikDatang);

                System.out.println("\nWaktu pulang");
                System.out.print("Jam           : ");
                int jamPulang = Integer.parseInt(sc.nextLine().trim());
                System.out.print("Menit         : ");
                int menitPulang = Integer.parseInt(sc.nextLine().trim());
                System.out.print("Detik         : ");
                int detikPulang = Integer.parseInt(sc.nextLine().trim());
                Waktu pulang = new Waktu(jamPulang, menitPulang, detikPulang);

                isi[i] = new Pegawai(nip, nama, alamat, gol, datang, pulang);
            }

            ArrayPegawai arrayPegawai = new ArrayPegawai();
            arrayPegawai.setPegawai(isi, jumlah);
            arrayPegawai.output();
        } catch (NumberFormatException e) {
            System.out.println("Format input salah! Kembali ke menu.");
        }
    }
}

public class GajiPegawai {
    public static void main(String[] args) {
        Menu menu = new Menu();
        menu.run();
    }
}