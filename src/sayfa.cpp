#define NULL 0

#include "sayfa.h"

Sayfa::Sayfa()
: isim(""), baslik(""), ayirici(""), aciklama("")
{}

//GETTER
std::string Sayfa::get_isim() {
    return isim;
}

std::string Sayfa::get_baslik() {
    return baslik;
}

std::string Sayfa::get_ayirici() {
    return ayirici;
}

std::string Sayfa::get_aciklama() {
    return aciklama;
}

//SETTER
void Sayfa::set_isim(std::string isim) {
    this->isim = isim;
}

void Sayfa::set_baslik(std::string baslik) {
    this->baslik = baslik;
}

void Sayfa::set_ayirici(std::string ayirici) {
    this->ayirici = ayirici;
}

void Sayfa::set_aciklama(std::string aciklama) {
    this->aciklama = aciklama;
}

//
void Sayfa::yazdir() {
    temizle_ekran();
    yazdir_ayirici();
    yazdir_baslik();
    yazdir_isim();
    yazdir_bos_satir(2);
    yazdir_bos_satir(1);
    yazdir_data();
    yazdir_bos_satir();
    yazdir_ayirici();
    yazdir_aciklama();
    secilen = girdi_secilen();
}

void Sayfa::yazdir_data() {}

std::string Sayfa::girdi_secilen() {
    secilen = "";
    std::getline(std::cin, secilen);
    secilen = trim(secilen);
    return secilen;
}

// PROTECTED
void Sayfa::temizle_ekran() {
    system("cls");
}

void Sayfa::yazdir_baslik() {
    std::cout << baslik << '\n';
}

void Sayfa::yazdir_bos_satir(int satir_sayisi) {
    if (satir_sayisi > 0) {
        std::cout << std::string(satir_sayisi, '\n');
    }
}

void Sayfa::yazdir_ayirici() {
    std::cout << ayirici << '\n';
}

void Sayfa::yazdir_isim() {
    std::cout << get_isim() << " >\n";
}

void Sayfa::geri_bildirim(std::string gb) {
    std::cout << gb << '\n';
}

void Sayfa::yazdir_aciklama() {
    std::cout << aciklama << "\n: ";
}

void Sayfa::bekle_milisaniye(int ms) {
    Sleep(ms);
}
