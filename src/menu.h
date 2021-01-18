#ifndef MENU_H
#define MENU_H

#define SORU_SAYISI_COZULEN 9

#include <iostream>
#include <string.h>
#include<windows.h>
#include <stdlib.h>
#include "matris.h"
#include "trim.h"
#include "sayfa.h"
#include "anasayfa.h"
#include "goster_sayfa.h"

class Menu {
public:
    Menu(Matris A, Matris b);
    // ANAMENU
    void baslat();
    // soru-sonuc
    void sayfa_soru();
    void sayfa_soru_secenekler();
    void sayfa_sonuc(int soru_id);
    void sayfa_sonuc_secenekler();
    void sayfa_sonucsuz();
    void sayfa_sonucsuz_secenekler();

    void ice_aktar_genel(Matris &M);
    void goster_genel(Matris &M);
    void sayfa_ice_aktar_genel();
    void sayfa_ice_aktar_secenekler();

    void soru_01();
    void soru_02();
    void soru_03();
    void soru_04();
    void soru_05();
    void soru_06();
    void soru_07();
    void soru_11();
    void soru_13();
private:
    Matris A;
    Matris B;       
    Anasayfa *anasayfa;
    Goster_sayfa *goster_sayfa;
    const int soru_sayisi = 19;
    const int cozulmus_sorular[SORU_SAYISI_COZULEN]{1, 2, 3, 4, 5, 6, 7, 11, 13};
    bool olmak_bitmis;
    std::string anasayfa_secilen;
    std::string sayfa_ice_aktar_secilen;
    std::string sayfa_soru_secilen;
    
};

#endif
