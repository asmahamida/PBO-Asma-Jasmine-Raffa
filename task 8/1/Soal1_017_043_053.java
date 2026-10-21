/*
Nama Program        : Soal1_017_043_053.java
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 7 Oktober 2026
Deskripsi           : Program OOP untuk mencari nilai rata-rata, nilai tertinggi,
                      nilai terendah, serta sorting data integer.
*/

import java.util.Scanner;

class Nilai {
    private int[] data;

    public Nilai() {
    }

    public Nilai(int[] data) {
        this.data = data;
    }

    public void setData(int[] data) {
        this.data = data;
    }

    public int[] getData() {
        return this.data;
    }

    public void input(Scanner sc) {
        if (this.data != null) {
            System.out.print("Array sudah ada. Hapus array lama? (y/n): ");
            String pilihan = sc.nextLine();

            if (pilihan.equals("n")) {
                System.out.println("Array batal diubah.");
                return;
            }

            if (pilihan.equals("y")) {
                this.data = null;
            }
        }

        System.out.print("Masukkan jumlah data: ");
        int jumlah = Integer.parseInt(sc.nextLine());

        this.data = new int[jumlah];

        for (int i = 0; i < jumlah; i++) {
            System.out.print("Data ke-" + (i + 1) + ": ");
            this.data[i] = Integer.parseInt(sc.nextLine());
        }
    }

    public void tampilData() {
        for (int i = 0; i < this.data.length; i++) {
            System.out.print(this.data[i] + " ");
        }
        System.out.println();
    }

    public double rataRata() {
        int jumlah = 0;

        for (int i = 0; i < this.data.length; i++) {
            jumlah += this.data[i];
        }

        return (double) jumlah / this.data.length;
    }

    public int nilaiTertinggi() {
        int tertinggi = this.data[0];

        for (int i = 1; i < this.data.length; i++) {
            if (this.data[i] > tertinggi) {
                tertinggi = this.data[i];
            }
        }

        return tertinggi;
    }

    public int nilaiTerendah() {
        int terendah = this.data[0];

        for (int i = 1; i < this.data.length; i++) {
            if (this.data[i] < terendah) {
                terendah = this.data[i];
            }
        }

        return terendah;
    }

    public void sortingAscending() {
        for (int i = 0; i < this.data.length - 1; i++) {
            for (int j = 0; j < this.data.length - 1 - i; j++) {
                if (this.data[j] > this.data[j + 1]) {
                    int temp = this.data[j];
                    this.data[j] = this.data[j + 1];
                    this.data[j + 1] = temp;
                }
            }
        }
    }

    public void sortingDescending() {
        for (int i = 0; i < this.data.length - 1; i++) {
            for (int j = 0; j < this.data.length - 1 - i; j++) {
                if (this.data[j] < this.data[j + 1]) {
                    int temp = this.data[j];
                    this.data[j] = this.data[j + 1];
                    this.data[j + 1] = temp;
                }
            }
        }
    }

    public void output() {
        System.out.print("Data            : ");
        tampilData();
        System.out.println("Rata-rata       : " + rataRata());
        System.out.println("Nilai tertinggi : " + nilaiTertinggi());
        System.out.println("Nilai terendah  : " + nilaiTerendah());
    }
}

class Menu {
    private Scanner sc;

    public Menu(Scanner sc) {
        this.sc = sc;
    }

    public int tampilMenu() {
        System.out.println("\n===== MENU =====");
        System.out.println("1. Input Data");
        System.out.println("2. Tampilkan Hasil");
        System.out.println("3. Sorting Ascending");
        System.out.println("4. Sorting Descending");
        System.out.println("5. Keluar");
        System.out.print("Pilih menu: ");

        return Integer.parseInt(sc.nextLine());
    }

    public void jalankan(Nilai nilai) {
        int pilihan = 0;

        while (pilihan != 5) {
            pilihan = tampilMenu();

            switch (pilihan) {
                case 1:
                    nilai.input(sc);
                    break;

                case 2:
                    if (nilai.getData() == null) {
                        System.out.println("Array belum dibuat.");
                    }
                    else {
                        nilai.output();
                    }
                    break;

                case 3:
                    if (nilai.getData() == null) {
                        System.out.println("Array belum dibuat.");
                    }
                    else {
                        nilai.sortingAscending();
                        System.out.print("Ascending : ");
                        nilai.tampilData();
                    }
                    break;

                case 4:
                    if (nilai.getData() == null) {
                        System.out.println("Array belum dibuat.");
                    }
                    else {
                        nilai.sortingDescending();
                        System.out.print("Descending : ");
                        nilai.tampilData();
                    }
                    break;

                case 5:
                    System.out.println("Program selesai.");
                    break;

                default:
                    System.out.println("Menu tidak tersedia.");
            }
        }
    }
}

public class Soal1_017_043_053 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Nilai nilai = new Nilai();
        Menu menu = new Menu(sc);

        menu.jalankan(nilai);

        sc.close();
    }
}
