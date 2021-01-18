#ifndef MATRIS_HPP
#define MATRIS_HPP

#include <iostream> // std::cout
#include <iomanip>  // std::setprecision()
#include <math.h>   // std::pow(), std::sqrt()
#include <cstddef>  // NULL
#include "matris.h"
#include <string>

class Matris {
public:
    Matris();
    Matris(const int satir_sayisi, const int sutun_sayisi, long double **dizi_2b);
    Matris(const Matris &orijinal);
    ~Matris();
    // gorsellestirme
    std::string to_string( const std::string indentasyon = "") const;
    std::string to_csv() const;
    // getter
    int get_satir_sayisi() const;
    int get_sutun_sayisi() const;
    long double get_eleman(const int satir, const int sutun) const;
    Matris* get_dikdortgen(const int satir_id, const int sutun_id, const int yukseklik, const int genislik) const;
    Matris* get_satir(const int satir_id) const;
    Matris* get_sutun(const int sutun) const;
    Matris* get_minor(const int satir_id, const int sutun_id) const;
    long double get_kofaktor(const int satir_id, const int sutun_id) const;
    Matris* get_komatris() const;
    Matris* get_transpoze() const;
    long double get_determinant() const;
    long double get_satir_normu(const int satir) const;
    long double get_sutun_normu(const int sutun) const;
    long double get_oklid_normu() const;
    long double get_iz() const;
    Matris* get_kosegen_form(bool yapmak_indirgenmis = false) const; // get_gauss_jordan_tersi fonksiyonunun basit hali
    Matris* get_gauss_tersi() const;
    Matris* get_gauss_jordan_tersi() const;
    Matris* get_kramer_tersi() const;
    // setter
    void set_satir(const int satir_id, const Matris &satir);
    void set_sutun(const int sutun_id, const Matris &sutun);
    void set_eleman(const int satir, const int sutun, const long double deger);
    void set_dikdortgen(const int satir_id, const int sutun_id, const Matris &dikdortgen);
    //modifiye eden
    void toplam(const long double deger);
    void katla(const long double deger);
    //asagidaki gauss yontemlerini gauss-jordan yapmak icin yapmak_indirgenmis parametresini "true" olarak verin
    void gauss_elimine_alt_ucgen(bool yapmak_indirgenmis = false);
    void gauss_elimine_alt_ucgen(Matris &tekrarci, bool yapmak_indirgenmis = false);
    void gauss_elimine_ust_ucgen(bool yapmak_indirgenmis = false);
    void gauss_elimine_ust_ucgen(Matris &tekrarci, bool yapmak_indirgenmis = false);
    // gauss-jordan yerine gauss yontemi secilmisse, kosegen formu indirgemek icin kullanilir, ayni sonuca ulasilmaktadir
    void gauss_kosegenden_birime(Matris &tekrarci);
    // statik
    static Matris* birim(const int boyut);
    static Matris* sifirlar(const int satir_sayisi, const int sutun_sayisi);
    static Matris* birler(const int satir_sayisi, const int sutun_sayisi);
    static Matris* toplam(const Matris &sol, const Matris &sag);
    static Matris* carpim(const Matris &sol, const Matris &sag);
    static Matris* soldan_bolum(const Matris &sol, const Matris &sag);
         
private:
    int satir_sayisi = 0;
    int sutun_sayisi = 0;
    long double **dizi_2b = NULL; // matris satirlarini iceren iki boyutlu dizi (pointer pointer long double)
    bool olmak_kare() const;
    bool olmak_bos() const;
    bool olmak_null_dizi_2b() const;
    bool olmak_aralik_icinde_satir(const int satir_id) const;
    bool olmak_aralik_icinde_sutun(const int sutun_id) const;
};
#endif