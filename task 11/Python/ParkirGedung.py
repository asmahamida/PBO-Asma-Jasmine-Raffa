# Nama Program        : Gaji Pegawai
# Nama NPM Anggota 1  : Jasmine Salsabila (140810250017)
# Nama NPM Anggota 2  : Raffa Pasha Hidayat (140810250043)
# Nama NPM Anggota 3  : Asma Hamidah (140810250053)
# Tanggal Pengerjaan  : 10 November 2026
# Deskripsi           : Program Sistem Parkir Gedung merupakan program berbasis Java yang digunakan untuk mengelola data parkir kendaraan, baik untuk pengguna umum maupun pegawai. Program ini mencatat identitas pengguna, jenis kendaraan, lokasi parkir, tanggal dan waktu masuk, serta durasi parkir. Biaya parkir dihitung berdasarkan jenis kendaraan, status pengguna, dan lama parkir, dengan penerapan diskon bagi pengguna umum sesuai ketentuan kunjungan. Program ini menerapkan konsep OOP, meliputi encapsulation, inheritance, polymorphism, abstraction, dan composition.

from datetime import date, datetime, timedelta
from math import ceil


# ==========================================
# CLASS WAKTU
# ==========================================
class Waktu:
    def __init__(self, jam=0, menit=0, detik=0):
        self.jam = jam
        self.menit = menit
        self.detik = detik

    def total_detik(self):
        return self.jam * 3600 + self.menit * 60 + self.detik

    def tampil(self):
        return f"{self.jam:02d}:{self.menit:02d}:{self.detik:02d}"


# ==========================================
# CLASS PERSON
# ==========================================
class Person:
    def __init__(self, nama, alamat):
        self.__nama = nama
        self.__alamat = alamat

    def output(self):
        print(f"Nama           : {self.__nama}")
        print(f"Alamat         : {self.__alamat}")


# ==========================================
# CLASS KENDARAAN (INDUK)
# ==========================================
class Kendaraan:
    def __init__(self, nomor_plat):
        self.nomor_plat = nomor_plat

    def get_tarif_umum(self):
        raise NotImplementedError

    def get_tarif_pegawai(self):
        raise NotImplementedError

    def get_jenis(self):
        raise NotImplementedError

    def hitung_biaya_umum(self, jam):
        return self.get_tarif_umum() * jam

    def hitung_biaya_pegawai(self, hari):
        return self.get_tarif_pegawai() * hari


# ==========================================
# CLASS MOBIL
# ==========================================
class Mobil(Kendaraan):
    def get_tarif_umum(self):
        return 3000

    def get_tarif_pegawai(self):
        return 6000

    def get_jenis(self):
        return "Mobil"


# ==========================================
# CLASS TRUK
# ==========================================
class Truk(Kendaraan):
    def get_tarif_umum(self):
        return 5000

    def get_tarif_pegawai(self):
        return 5000

    def get_jenis(self):
        return "Truk"


# ==========================================
# CLASS MOTOR
# ==========================================
class Motor(Kendaraan):
    def get_tarif_umum(self):
        return 2000

    def get_tarif_pegawai(self):
        return 3000

    def get_jenis(self):
        return "Motor"