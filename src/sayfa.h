#ifndef SAYFA_H
#define SAYFA_H

#include <iostream>
#include <string.h>
#include<windows.h>
#include <stdlib.h>
#include "matris.h"
#include "trim.h"

class Sayfa {
public:
    Sayfa();
    //getter
    std::string get_isim();
    std::string get_baslik();
    std::string get_ayirici();
    std::string get_aciklama();
    //setter
    void set_isim(std::string isim);
    void set_baslik(std::string baslik);
    void set_ayirici(std::string ayirici);
    void set_aciklama(std::string aciklama);
    // diger
    void yazdir();
    std::string girdi_secilen();
    // implemente edilmemisler
    void yazdir_data();
    void calistir();
    
    
protected:
    std::string isim;
    const std::string taksim = "\\";
    std::string baslik;
    std::string ayirici;
    std::string aciklama;
    std::string secilen;
    
    void temizle_ekran();
    void yazdir_baslik();
    void yazdir_ayirici();
    void yazdir_isim();
    void yazdir_aciklama();
    void yazdir_bos_satir(int satir_sayisi = 1);
    void geri_bildirim(std::string gb);
    void bekle_milisaniye(int ms = 1500);
};

#endif
