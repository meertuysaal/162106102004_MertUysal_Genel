// 162106102004_MertUysal_Genel.cpp 

#include "anasayfa.h"

int main(int argc, const char* argv[]) {
    Anasayfa* anasayfa = new Anasayfa();
    anasayfa->set_isim("\\Anasayfa\\");
    anasayfa->set_ayirici(std::string(80, '-'));
    anasayfa->set_baslik(std::string(26, ' ').append("162106102004_MertUysal_Genel"));
    anasayfa->set_aciklama("Secmek icin parantez icindeki degeri girip Enter'a basiniz");

    anasayfa->calistir();

    return 0;
}
