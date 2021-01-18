#include "csv_oku_yaz.h"

std::vector<std::vector<long double>> csv_oku(std::string dosya_adi)
{
    std::vector<std::vector<long double>> okunan_matris;
    std::vector<long double> okunan_satir;
    std::ifstream csv_dosya(dosya_adi);
    std::string csv_satir;

    // dosyayi acmayi dene
    if (!csv_dosya.is_open()) {
        throw std::invalid_argument("HATA: dosya okunamadi");
    }

    while (!csv_dosya.eof()) {
        okunan_satir.clear();

        std::getline(csv_dosya, csv_satir);
        // satirlar bos degilse
        if (trim(csv_satir).compare("")) {
            std::stringstream csv_ss(csv_satir);
            std::string tmp_sayi_str;

            bool olmak_bos_sutun = false;

            while (getline(csv_ss, tmp_sayi_str, ',')) {
                // satir icindeki sutunlar bos degilse
                if (trim(tmp_sayi_str).compare("")) {
                    okunan_satir.push_back(std::stold(trim(tmp_sayi_str)));
                    tmp_sayi_str = "";
                }
                else {
                    olmak_bos_sutun = true;
                }
            }

            if (!olmak_bos_sutun) {
                okunan_matris.push_back(okunan_satir);
            }
        }
    }

    for (std::vector<long double> satir : okunan_matris) {
        std::cout << "\t\t";
        for (long double eleman : satir) {
        }
    }

    return okunan_matris;
}