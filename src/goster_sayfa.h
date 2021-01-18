#ifndef GOSTER_SAYFA_H
#define GOSTER_SAYFA_H

#include "sayfa.h"
#include "matris.h"

class Goster_sayfa : public Sayfa {
public:
    typedef Sayfa super;
    Goster_sayfa(Matris *A, Matris *B);
    void yazdir_data();
    void yazdir();
    bool calistir();
private:
    Matris *A;
    Matris *B;
};

#endif