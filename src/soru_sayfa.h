#pragma once
#ifndef SORU_SAYFA_H
#define SORU_SAYFA_H

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <math.h>   // std::pow(), std::sqrt()
#include "sayfa.h"
#include "matris.h"

namespace fs = std::filesystem;

class Soru_sayfa : public Sayfa {
public:
    typedef Sayfa super;
    Soru_sayfa(Matris *A, Matris *B);
    void yazdir_soru_listesi();
    void hesapla_soru_01();
    void hesapla_soru_02();
    void hesapla_soru_03();
    void hesapla_soru_04();
    void hesapla_soru_05();
    void hesapla_soru_06();
    void hesapla_soru_07();
    void hesapla_soru_11();
    void hesapla_soru_13();
    void yazdir_data();
    void yazdir();
    void yazdir_sonuc_kaydet(std::string dosya_adi);
    void kaydet_log(std::string dosya_adi);
    bool calistir();
    
private:
    int aktif_soru_id = 0;
    const int cozulmus_sorular[9] = { 1, 2, 3, 4, 5, 6, 7, 11, 13 };
    Matris *A = NULL;
    Matris *B = NULL;
    std::filesystem::path program_dizini_mutlak;
    std::string arabellek = "";
    std::string araciktilar = "";
    bool olmak_hesaplanmis = false;
    
};

#endif