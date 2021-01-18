#include "anasayfa.h"

Anasayfa::Anasayfa()
: super()
{
    ice_aktar_sayfa_A = new Ice_aktar_sayfa(A);
    ice_aktar_sayfa_A->set_isim("\\Anasayfa\\Ice Aktar A\\");
    ice_aktar_sayfa_A->set_ayirici(std::string(80, '-'));
    ice_aktar_sayfa_A->set_baslik(std::string(26, ' ').append("162106102004_MertUysal_Genel"));
    ice_aktar_sayfa_A->set_aciklama("");

    ice_aktar_sayfa_B = new Ice_aktar_sayfa(B);
    ice_aktar_sayfa_B->set_isim("\\Anasayfa\\Ice Aktar B\\");
    ice_aktar_sayfa_B->set_ayirici(std::string(80, '-'));
    ice_aktar_sayfa_B->set_baslik(std::string(26, ' ').append("162106102004_MertUysal_Genel"));
    ice_aktar_sayfa_B->set_aciklama("");

    goster_sayfa = new Goster_sayfa(A, B);
    goster_sayfa->set_isim("\\Anasayfa\\Goster\\");
    goster_sayfa->set_ayirici(std::string(80, '-'));
    goster_sayfa->set_baslik(std::string(26, ' ').append("162106102004_MertUysal_Genel"));
    goster_sayfa->set_aciklama("Secmek icin parantez icindeki degeri girip Enter'a basiniz");

    soru_sayfa = new Soru_sayfa(A, B);
    soru_sayfa->set_isim("\\Anasayfa\\Sorular\\");
    soru_sayfa->set_ayirici(std::string(80, '-'));
    soru_sayfa->set_baslik(std::string(26, ' ').append("162106102004_MertUysal_Genel"));
    soru_sayfa->set_aciklama("Secmek icin parantez icindeki degeri girip Enter'a basiniz");

}

Anasayfa::~Anasayfa() {
    delete A;
    A = NULL;
    delete B;
    B = NULL;
    delete goster_sayfa;
    goster_sayfa = NULL;
    delete ice_aktar_sayfa_A;
    ice_aktar_sayfa_A = NULL;
    delete ice_aktar_sayfa_B;
    ice_aktar_sayfa_B = NULL;
}

void Anasayfa::yazdir_data() {
    std::cout
        << "(1)\tMatris Ice Aktar  - A [Sorulara gitmeden once ice aktariniz.]\n"
        << "(2)\tMatris Ice Aktar  - B [Sorulara gitmeden once ice aktariniz.]\n"
        << "(3)\tMatrisleri Goster - A, B\n"
        << "(4)\tSoru sec\n"
        << "\n\n"
        << "(cikis)\tCikis\n";
}



void Anasayfa::yazdir() {
    temizle_ekran();
    yazdir_ayirici();
    yazdir_baslik();
    yazdir_isim();
    yazdir_bos_satir(2);
    yazdir_data();
    yazdir_bos_satir();
    yazdir_ayirici();
    yazdir_aciklama();
    secilen = girdi_secilen();
}

bool Anasayfa::calistir() {
    while(true) {

        yazdir();

        if (!secilen.compare("cikis")) {
            return true;
        }
        else if (!secilen.compare("1")) {
            if (ice_aktar_sayfa_A->calistir()) {
                return true;
            }
        }
        else if (!secilen.compare("2")) {
            if (ice_aktar_sayfa_B->calistir()) {
                return true;
            }
        }
        else if (!secilen.compare("3")) {
            if (goster_sayfa->calistir()) {
                return true;
            }
        }
        else if (!secilen.compare("4")) {
            if (soru_sayfa->calistir()) {
                return true;
            }
        }
        else {
            geri_bildirim("Secim aralik disinda, tekrar deneyin.");
            bekle_milisaniye(2000);
        }
    }
}



