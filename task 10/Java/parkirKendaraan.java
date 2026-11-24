import  java.util.Scanner;

class waktu{
    private int jam;
    private int menit;
    private int  detik;

    public waktu(){
        jam = 0;
        menit = 0;
        detik = 0;
    }

    public waktu (int jam, int menit, int  detik){
        this.jam = jam;
        this.menit = menit;
        this.detik  = detik;
    }

    public waktu(int totalDetik){
        this.jam = totalDetik / 3600;
        this.menit = (totalDetik % 3600) / 60;
        this.detik = totalDetik % 60;
    }

    public void setJam(int jam){
        this.jam = jam;
    }

    public void setMenit(int menit){
        this.menit = menit;
    }

    public void setDetik(int detik){
        this.detik = detik;
    }

    public int getJam(){
        return jam;
    }

    public int getMenit(){
        return menit;
    }

    public int getDetik(){
        return detik;
    }
}