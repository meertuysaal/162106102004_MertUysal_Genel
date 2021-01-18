#ifndef ANASAYFA_H
#define ANASAYFA_H

#include "sayfa.h"
#include "goster_sayfa.h"
#include "ice_aktar_sayfa.h"
#include "soru_sayfa.h"

class Anasayfa : public Sayfa {
public:
    typedef Sayfa super;
    Anasayfa();
    ~Anasayfa();
    void yazdir_data();
    void yazdir();
    bool calistir();
private:
    Matris *A = Matris::sifirlar(1, 1);
    Matris *B = Matris::sifirlar(1, 1);
    Ice_aktar_sayfa *ice_aktar_sayfa_A = NULL;
    Ice_aktar_sayfa *ice_aktar_sayfa_B = NULL;
    Goster_sayfa *goster_sayfa = NULL;
    Soru_sayfa* soru_sayfa = NULL;
};

#endif