#include "ice_aktar_sayfa.h"

namespace fs = std::filesystem;

Ice_aktar_sayfa::Ice_aktar_sayfa(Matris *matris)
: super()
{
    anasayfa_matris = matris;
    program_dizini_mutlak = fs::absolute(fs::current_path());
}

void Ice_aktar_sayfa::yazdir_asama_1() {
    csv_listesi = get_csvler(program_dizini_mutlak.string());

    std::cout
        << "Listelenen Dizin: " << '\n'
        << std::string(17, '-') << '\n'
        << program_dizini_mutlak.string() << "\n\n"
        << "Bulunan Matris Dosyalari ('.csv'):" << '\n'
        << std::string(26, '-') << '\n';

    for (std::string eleman : csv_listesi) {
        std::cout << '\t' << eleman << '\n';
    }

    std::cout
        << "\n\n"
        << "(geri) Anamenu'ye Geri Don\n"
        << "(cikis)\tCikis\n";    
}

void Ice_aktar_sayfa::yazdir_asama_2() {
    if (matris) {
        std::cout << matris->to_string() << '\n';
    }
    else {
        std::cout << "\tSecilen dosya ice aktarilamadi.\n"
            << "\tMatris ogeleri diktortgen formda olmali,\n"
            << "\tbos satir icerilebilir fakat sayi degeri\n"
            << "\tolmayan icerik (yorum vb.) kabul edilmiyor.\n";
    }
}

void Ice_aktar_sayfa::yazdir_data() {
    if (!olmak_csv_secilmis) {
        yazdir_asama_1();
    }
    else {
        yazdir_asama_2();
    }
}

void Ice_aktar_sayfa::yazdir() {
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

bool Ice_aktar_sayfa::calistir() {
    while(true) {
        yazdir();

        if (!olmak_csv_secilmis) {
            if (!secilen.compare("cikis")) {
                //anamenuden cikis yapilsin
                return true;
            }
            else if (!secilen.compare("geri")) {
                //anamenuden cikis yapilmasin
                return false;
            }

            for (std::string csv_dosya_adi : csv_listesi) {
                // saglanan string, dosya listesi icindeyse
                if (!secilen.compare(csv_dosya_adi)) {
                    std::vector<std::vector<long double>> matris_adayi;
                    try {
                        matris_adayi = csv_oku(secilen);
                    }
                    catch (std::invalid_argument& e) {
                    }

                    bool olmak_dikdortgen = true;
                    int satir_sayisi = 0;
                    int sutun_sayisi = 0;
                    int sutun_sayisi_onceki = 0;
                    for (std::vector<long double> matris_satir : matris_adayi) {
                        sutun_sayisi = 0;
             
                        for (long double eleman : matris_satir) {
                            sutun_sayisi++;
                        }

                        if (satir_sayisi != 0 && sutun_sayisi != sutun_sayisi_onceki) {
                            olmak_dikdortgen = false;
                        }

                        sutun_sayisi_onceki = sutun_sayisi;

                        satir_sayisi++;                        
                    }

                    if (olmak_dikdortgen && (satir_sayisi > 0) && (sutun_sayisi > 0)) {
                        matris = Matris::sifirlar(satir_sayisi, sutun_sayisi);
                        for (int sayim_m = 0; sayim_m < matris->get_satir_sayisi(); sayim_m++) {
                            for (int sayim_n = 0; sayim_n < matris->get_sutun_sayisi(); sayim_n++) {
                                matris->set_eleman(sayim_m, sayim_n, matris_adayi[sayim_m][sayim_n]);
                            }
                        }
                    }

                    olmak_csv_secilmis = true;
                }
            }

            if (!olmak_csv_secilmis) {
                csv_listesi.clear();
                geri_bildirim("Girilen '.csv' dosyasi bulunamadi, tekrar deneyin.\nOrnekler asagidadir:\nA.csv\nB.csv");
                bekle_milisaniye(3000);
            }
        }
        else {
            if (matris) {
                *anasayfa_matris = *matris;
                //delete matris;
                matris = NULL;
            }
            
            olmak_csv_secilmis = false;

            //anamenuden  cikis yapilmasin
            return false;
        }
    }
}

void Ice_aktar_sayfa::yazdir_aciklama() {
    if (!olmak_csv_secilmis) {
        std::cout << "Matrisi ice aktarmak icin tam adini giriniz (Ornek: 'A.csv', 'B.csv')\n(Not: Buyuk-kucuk harfe duyarlidir, yazdirildigi gibi giriniz.)\n: ";
    }
    else {
        std::cout << "Anamenu'ye Donmek icin Enter'a basin\n: ";
    }
}