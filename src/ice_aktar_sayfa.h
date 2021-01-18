#ifndef ICE_AKTAR_SAYFA_H
#define ICE_AKTAR_SAYFA_H

#include <iostream>
#include <filesystem>
#include <vector>
#include "sayfa.h"
#include "matris.h"
#include "dosya_dizin.h"
#include "csv_oku_yaz.h"


class Ice_aktar_sayfa : public Sayfa {
public:
    typedef Sayfa super;
    Ice_aktar_sayfa(Matris *matris);
    void yazdir_asama_1();
    void yazdir_asama_2();
    void yazdir_data();
    void yazdir();
    bool calistir();
    void yazdir_aciklama();
private:
    bool olmak_csv_secilmis = false;
    std::string sonuc;
    Matris *matris = NULL;
    Matris *anasayfa_matris = NULL;
    std::filesystem::path program_dizini_mutlak;
    std::vector<std::string> csv_listesi;
};

#endif