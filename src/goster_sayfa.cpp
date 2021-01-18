#include "goster_sayfa.h"

Goster_sayfa::Goster_sayfa(Matris *A, Matris *B)
: super()
{
    this->A = A;
    this->B = B;
}

void Goster_sayfa::yazdir_data() {
    std::cout
        << "Matris A:\n";
        if (A) {
            std::cout << A->to_string("\t");
        }
        else {
            std::cout << "\tMatris yuklenmemis\n";
        }
        std::cout << "\n"
        << "Matris B:\n";
        if (A) {
            std::cout << B->to_string("\t");
        }
        else {
            std::cout << "\tMatris yuklenmemis\n";
        }
        std::cout << "\n\n"
        << "(geri) Anamenuye Geri Don\n"
        <<"(cikis)\tCikis\n";
}

void Goster_sayfa::yazdir() {
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

bool Goster_sayfa::calistir() {
    while(true) {

        yazdir();

        if (!secilen.compare("cikis")) {
            return true;
        }
        else if (!secilen.compare("geri")) {
            return false;
        }
        else if (!secilen.compare("1")) {
            //sayfa_soru();
        }
        else {
            geri_bildirim("Secim aralik disinda, tekrar deneyin.");
            bekle_milisaniye();
        }
    }
}