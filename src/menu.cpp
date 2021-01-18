#include "menu.h"

Menu::Menu(Matris A, Matris B) {
    olmak_bitmis = false;
    this->A = A;
    this->B = B;
    //anasayfa
    
}

// ANAMENU

void Menu::baslat() {
   anasayfa->calistir();
}

// SORU-SONUC


void Menu::sayfa_soru_secenekler() {
    std::cout << "\\Anasayfa\\Soru\\ >\n\n"
        << "(1-19) Soru numarasini girin\n"
        << "\n"
        << "(geri) Geri: \\Anasayfa\\\n"
        << "(cikis)\tCikis\n";
}


void Menu::sayfa_ice_aktar_secenekler() {
    std::cout << "\\AnaSayfa\\Soru\\ >\n\n"
        << "\n"
        << "(geri)\tGeri (\\AnaMenu\\MatrisMenu)\n"
        << "(cikis)\tCikis\n";
}


