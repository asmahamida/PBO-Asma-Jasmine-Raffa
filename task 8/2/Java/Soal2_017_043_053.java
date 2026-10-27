/*
Nama Program        : Soal2_017_043_053.java
Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
Nama NPM Anggota 3  : Asma Hamidah (140810250053)
Tanggal Pengerjaan  : 7 Oktober 2026
Deskripsi           : Program OOP untuk penjumlahan dan perkalian dua matriks.
*/

import java.util.Scanner;

class Matriks {
    private int[][] data;
    private int baris;
    private int kolom;

    public Matriks() {
    }

    public Matriks(int baris, int kolom) {
        this.baris = baris;
        this.kolom = kolom;
        this.data = new int[baris][kolom];
    }

    public void setData(int[][] data) {
        this.data = data;
    }

    public int[][] getData() {
        return this.data;
    }

    public void setBaris(int baris) {
        this.baris = baris;
    }

    public int getBaris() {
        return this.baris;
    }

    public void setKolom(int kolom) {
        this.kolom = kolom;
    }

    public int getKolom() {
        return this.kolom;
    }

    public void input(Scanner sc) {
        System.out.print("Masukkan jumlah baris: ");
        this.baris = Integer.parseInt(sc.nextLine());

        System.out.print("Masukkan jumlah kolom: ");
        this.kolom = Integer.parseInt(sc.nextLine());

        this.data = new int[this.baris][this.kolom];

        System.out.println("Masukkan elemen matriks:");
        for (int i = 0; i < this.baris; i++) {
            for (int j = 0; j < this.kolom; j++) {
                System.out.print("Data [" + i + "][" + j + "] = ");
                this.data[i][j] = Integer.parseInt(sc.nextLine());
            }
        }
    }

    public void output() {
        for (int i = 0; i < this.baris; i++) {
            for (int j = 0; j < this.kolom; j++) {
                System.out.print(this.data[i][j] + "\t");
            }
            System.out.println();
        }
    }

    public Matriks penjumlahan(Matriks matriks2) {
        Matriks hasil = new Matriks(this.baris, this.kolom);

        for (int i = 0; i < this.baris; i++) {
            for (int j = 0; j < this.kolom; j++) {
                hasil.data[i][j] =
                    this.data[i][j] + matriks2.data[i][j];
            }
        }

        return hasil;
    }

    public void penjumlahanVoid(Matriks matriks2, Matriks hasil) {
        for (int i = 0; i < this.baris; i++) {
            for (int j = 0; j < this.kolom; j++) {
                hasil.data[i][j] =
                    this.data[i][j] + matriks2.data[i][j];
            }
        }
    }

    public Matriks perkalian(Matriks matriks2) {
        Matriks hasil = new Matriks(this.baris, matriks2.kolom);

        for (int i = 0; i < this.baris; i++) {
            for (int j = 0; j < matriks2.kolom; j++) {
                for (int k = 0; k < this.kolom; k++) {
                    hasil.data[i][j] +=
                        this.data[i][k] * matriks2.data[k][j];
                }
            }
        }

        return hasil;
    }

    public void perkalianVoid(Matriks matriks2, Matriks hasil) {
        for (int i = 0; i < this.baris; i++) {
            for (int j = 0; j < matriks2.kolom; j++) {
                hasil.data[i][j] = 0;

                for (int k = 0; k < this.kolom; k++) {
                    hasil.data[i][j] +=
                        this.data[i][k] * matriks2.data[k][j];
                }
            }
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
        System.out.println("1. Input Matriks");
        System.out.println("2. Penjumlahan Matriks");
        System.out.println("3. Perkalian Matriks");
        System.out.println("4. Keluar");
        System.out.print("Pilih menu: ");

        return Integer.parseInt(sc.nextLine());
    }

    public void jalankan(Matriks matriks1, Matriks matriks2) {
        int pilihan = 0;

        while (pilihan != 4) {
            pilihan = tampilMenu();

            switch (pilihan) {
                case 1:
                    System.out.println("\n=== Matriks 1 ===");
                    matriks1.input(sc);

                    System.out.println("\n=== Matriks 2 ===");
                    matriks2.input(sc);
                    break;

                case 2:
                    if (matriks1.getBaris() != matriks2.getBaris()
                            || matriks1.getKolom() != matriks2.getKolom()) {
                        System.out.println("Matriks tidak dapat dijumlahkan.");
                        System.out.println("Ordo kedua matriks harus sama.");
                    }
                    else {
                        Matriks hasil = matriks1.penjumlahan(matriks2);

                        System.out.println("\nMatriks 1:");
                        matriks1.output();

                        System.out.println("\nMatriks 2:");
                        matriks2.output();

                        System.out.println("\nHasil Penjumlahan:");
                        hasil.output();
                    }
                    break;

                case 3:
                    if (matriks1.getKolom() != matriks2.getBaris()) {
                        System.out.println("Matriks tidak dapat dikalikan.");
                        System.out.println(
                            "Kolom matriks 1 harus sama dengan baris matriks 2."
                        );
                    }
                    else {
                        Matriks hasil = matriks1.perkalian(matriks2);

                        System.out.println("\nMatriks 1:");
                        matriks1.output();

                        System.out.println("\nMatriks 2:");
                        matriks2.output();

                        System.out.println("\nHasil Perkalian:");
                        hasil.output();
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

public class Soal2_017_043_053 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Matriks matriks1 = new Matriks();
        Matriks matriks2 = new Matriks();

        Menu menu = new Menu(sc);
        menu.jalankan(matriks1, matriks2);

        sc.close();
    }
}
