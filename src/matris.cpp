#include "matris.h"

// Matrisi hesaplama yaparken ayni anda olusturmak icin faydali (optimizasyon icin)
Matris::Matris() {}

// Donguler ile ugrasmadan matris olusturmak icin faydali (optimizasyon icin varsayilan constructor kullanilmali)
Matris::Matris(const int satir_sayisi, const int sutun_sayisi, long double **dizi_2b) {
    if (satir_sayisi <= 0 || sutun_sayisi <= 0) {
        throw std::invalid_argument("Hata_01: pozitif olmayan matris boyutlari");
    }

    this->satir_sayisi = satir_sayisi;
    this->sutun_sayisi = sutun_sayisi;
    this->dizi_2b = dizi_2b;
}

// Kopya constructor
Matris::Matris(const Matris &orijinal) {
    if (orijinal.olmak_bos()) {
        satir_sayisi = 0;
        sutun_sayisi = 0;
        dizi_2b = NULL;
    }
    else {
        satir_sayisi = orijinal.satir_sayisi;
        sutun_sayisi = orijinal.sutun_sayisi;
        dizi_2b = new long double*[satir_sayisi];
        for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
            dizi_2b[sayim_m] = new long double[sutun_sayisi];
            for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
                dizi_2b[sayim_m][sayim_n] = orijinal.dizi_2b[sayim_m][sayim_n];
            }
        }
    }
}

Matris::~Matris() {
    // dinamik tahsis edilmis dizi_2d ozelligini siler
    if (!dizi_2b) {
        for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
            delete[] dizi_2b[sayim_m];
        }
        delete[] dizi_2b;
        dizi_2b = NULL;
    }
}


// GORSELLESTIRME
// Konsola yazdirmak icin gerekli
std::string Matris::to_string(const std::string indentasyon) const {
    std::string str;

    if (olmak_bos()) {
        str = "[ ]";
    }
    else {
        str = "";

        for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
            str.append(indentasyon);

            if (sayim_m == 0) {
                str.append("[ ");
            }
            else {
                str.append("  ");
            }

            for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
                if (dizi_2b[sayim_m][sayim_n] >= 0) {
                    str.append(" ");
                }
                str.append(std::to_string(dizi_2b[sayim_m][sayim_n]));
                str.append("  ");
            }

            if (sayim_m == satir_sayisi - 1) {
                str.append("]");
            }

            str.append("\n");
        }
    }

    return str;
}

std::string Matris::to_csv() const {
    std::string str;

    if (olmak_bos()) {
        str = "\n";
    }
    else {
        str = "";

        for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
            for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
                str.append(std::to_string(dizi_2b[sayim_m][sayim_n]));
            }
            str.append("\n");
        }
    }

    return str;
}

// GETTER
int Matris::get_satir_sayisi() const {
    return satir_sayisi;
}

int Matris::get_sutun_sayisi() const {
    return sutun_sayisi;
}

long double Matris::get_eleman(const int satir_id, const int sutun_id) const {
    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    return dizi_2b[satir_id][sutun_id];
}

// Dikdortgen bolgenin kopyasini yaratir (aralik uygun ise)
Matris* Matris::get_dikdortgen(const int satir_id, const int sutun_id, const int yukseklik, const int genislik) const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    if (!olmak_aralik_icinde_satir(yukseklik - 1)) {
        throw std::invalid_argument("Hata_05: dikdortgen yuksekligi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(genislik - 1)) {
        throw std::invalid_argument("Hata_06: dikdortgen genisligi aralik disinda");
    }

    if (satir_id + yukseklik > satir_sayisi || sutun_id + genislik > sutun_sayisi) {
        throw std::invalid_argument("Hata_07: uyumsuz dikdortgen konumu");
    }

    Matris *dikdortgen = Matris::sifirlar(yukseklik, genislik);
    //dikdortgen->satir_sayisi = yukseklik;
    //dikdortgen->sutun_sayisi = genislik;
    //dikdortgen->dizi_2b = new long double*[dikdortgen->satir_sayisi];
    for (int sayim_m = 0; sayim_m < dikdortgen->satir_sayisi; sayim_m++) {
        //dikdortgen->dizi_2b[sayim_m] = new long double[dikdortgen->sutun_sayisi];
        for (int sayim_n = 0; sayim_n < dikdortgen->sutun_sayisi; sayim_n++) {
            dikdortgen->dizi_2b[sayim_m][sayim_n] = dizi_2b[satir_id + sayim_m][sutun_id + sayim_n];
        }
    }

    return dikdortgen;
}

// Satirin kopyasini yaratir ( (1)x(sutun_sayisi) boyutunda )
Matris* Matris::get_satir(const int satir_id) const {
    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    return get_dikdortgen(satir_id, 0, 1, sutun_sayisi);
}

// Sutunun kopyasini yaratir ( (sutun_sayisi)x(1) boyutunda )
Matris* Matris::get_sutun(const int sutun_id) const {
    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    return get_dikdortgen(0, sutun_id, satir_sayisi, 1);
}

Matris* Matris::get_minor(const int satir_id, const int sutun_id) const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    Matris *minor = Matris::sifirlar((satir_sayisi - 1), (sutun_sayisi - 1));
    int minor_sayim_i = 0;
    int minor_sayim_j;
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        minor_sayim_j = 0;
        if (sayim_m != satir_id) {
            for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
                if (sayim_n != sutun_id) {
                    minor->dizi_2b[minor_sayim_i][minor_sayim_j] = dizi_2b[sayim_m][sayim_n];
                    minor_sayim_j++;
                }
            }
            minor_sayim_i++;
        }
    }

    return minor;
}

long double Matris::get_kofaktor(const int satir_id, const int sutun_id) const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    // remainder by 2, rather than high number of power operations
    Matris *tmp_minor = get_minor(satir_id, sutun_id);
    long double kofaktor = ( std::pow((long double)(-1.0), (satir_id + sutun_id) % 2) ) * tmp_minor->get_determinant();
    delete tmp_minor;
    tmp_minor = NULL;

    return kofaktor;
}

Matris* Matris::get_komatris() const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }


    Matris *komatris = Matris::sifirlar(satir_sayisi, sutun_sayisi);
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        for (int sayim_n = 0; sayim_n < satir_sayisi; sayim_n++) {
            komatris->dizi_2b[sayim_m][sayim_n] = get_kofaktor(sayim_m, sayim_n);
        }
    }

    return komatris;
}

Matris* Matris::get_transpoze() const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    // satir_sayisi ile sutun_sayisi yerleri degistirilir
    Matris *transpoze = new Matris();
    transpoze->satir_sayisi = sutun_sayisi;
    transpoze->sutun_sayisi = satir_sayisi;

    transpoze->dizi_2b = new long double*[transpoze->satir_sayisi];
    for (int sayim_m = 0; sayim_m < transpoze->satir_sayisi; sayim_m++) {
        transpoze->dizi_2b[sayim_m] = new long double[transpoze->sutun_sayisi];
        for (int sayim_n = 0; sayim_n < transpoze->sutun_sayisi; sayim_n++) {
            transpoze->dizi_2b[sayim_m][sayim_n] = dizi_2b[sayim_n][sayim_m];
        }
    }

    return transpoze;
}

// Yari-ozyinelenen metod
long double Matris::get_determinant() const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    // bilinen, hizli hesaplamalar
    switch (satir_sayisi) {
    case 3:
        return (dizi_2b[0][0] * dizi_2b[1][1] * dizi_2b[2][2])
            +  (dizi_2b[0][1] * dizi_2b[1][2] * dizi_2b[2][0])
            +  (dizi_2b[0][2] * dizi_2b[1][0] * dizi_2b[2][1])
            -  (dizi_2b[0][2] * dizi_2b[1][1] * dizi_2b[2][0])
            -  (dizi_2b[0][1] * dizi_2b[1][0] * dizi_2b[2][2])
            -  (dizi_2b[0][0] * dizi_2b[1][2] * dizi_2b[2][1]);
        break;

    case 2:
        return ((dizi_2b[0][0] * dizi_2b[1][1]) - (dizi_2b[0][1] * dizi_2b[1][0]));
        break;

    case 1:
        return dizi_2b[0][0];
        break;
    }

    // ozyineli kisim
    const int en_sol_sutun = 0;
    long double determinant = 0;
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        // 2 ile kalan alinarak, cok sayida kuvvet operasyonunun onune gecilir
        determinant += dizi_2b[sayim_m][en_sol_sutun] * get_kofaktor(sayim_m, en_sol_sutun);
    }

    return determinant;
}


long double Matris::get_satir_normu(const int satir_id) const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    long double satir_normu_kare = 0;
    for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
        satir_normu_kare += std::pow(dizi_2b[satir_id][sayim_n], 2);
    }
    return std::sqrt(satir_normu_kare);
}

long double Matris::get_sutun_normu(const int sutun_id) const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    long double sutun_normu_kare = 0;
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        sutun_normu_kare += std::pow(dizi_2b[sayim_m][sutun_id], 2);
    }
    return std::sqrt(sutun_normu_kare);
}

long double Matris::get_oklid_normu() const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    long double oklid_normu_kare = 0;
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            oklid_normu_kare += std::pow(dizi_2b[sayim_m][sayim_n], 2);
        }
    }
    return std::sqrt(oklid_normu_kare);
}

long double Matris::get_iz() const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    long double trace = 0;
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        trace += dizi_2b[sayim_m][sayim_m];
    }

    return trace;
}

Matris* Matris::get_kosegen_form(bool yapmak_indirgenmis) const {
    Matris *kosegen = new Matris(*this);
    kosegen->gauss_elimine_alt_ucgen(yapmak_indirgenmis);
    kosegen->gauss_elimine_ust_ucgen(yapmak_indirgenmis);
    return kosegen;
}

Matris* Matris::get_gauss_tersi() const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    Matris *birim_modifiye = Matris::birim(satir_sayisi);
    Matris *kopya_modifiye = new Matris(*this);
    kopya_modifiye->gauss_elimine_alt_ucgen(*birim_modifiye, false);
    kopya_modifiye->gauss_elimine_ust_ucgen(*birim_modifiye, false);
    kopya_modifiye->gauss_kosegenden_birime(*birim_modifiye);

    delete kopya_modifiye;
    kopya_modifiye = NULL;

    return birim_modifiye;
}

Matris* Matris::get_gauss_jordan_tersi() const {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    Matris *birim_modifiye = Matris::birim(satir_sayisi);
    Matris *kopya_modifiye = new Matris(*this);
    kopya_modifiye->gauss_elimine_alt_ucgen(*birim_modifiye, true);
    kopya_modifiye->gauss_elimine_ust_ucgen(*birim_modifiye, true);

    delete kopya_modifiye;
    kopya_modifiye = NULL;

    return birim_modifiye;
}

Matris* Matris::get_kramer_tersi() const{
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    long double det_this = get_determinant();

    if (det_this == 0) {
        throw std::invalid_argument("Hata_20: determinant sifir");
    }

    Matris *komatris = get_komatris();
    Matris *kramer_tersi = komatris->get_transpoze();
    kramer_tersi->katla(1 / det_this);
    delete komatris;
    komatris = NULL;

    return kramer_tersi;
}


 // SETTER
 void Matris::set_satir(const int satir_id, const Matris &satir) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    if (satir.olmak_bos()) {
        throw std::invalid_argument("Hata_09: bos satir vektoru");
    }

    if (satir.satir_sayisi != 1 || satir.sutun_sayisi != sutun_sayisi ) {
        throw std::invalid_argument("Hata_11: uyumsuz satir vektoru boyutlari");
    }

    const int tek_sutun = 0;
    for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
        dizi_2b[satir_id][sayim_n] = satir.dizi_2b[tek_sutun][sayim_n];
    }
}

void Matris::set_sutun(const int sutun_id, const Matris &sutun) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    if (sutun.olmak_bos()) {
        throw std::invalid_argument("Hata_10: bos sutun vektoru");
    }

    if (sutun.sutun_sayisi != 1 || sutun.satir_sayisi != satir_sayisi) {
        throw std::invalid_argument("Hata_12: uyumsuz sutun vektoru boyutlari");
    }

    const int tek_satir = 0;
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
            dizi_2b[sayim_m][sutun_id] = sutun.dizi_2b[sayim_m][tek_satir];
    }
}


void Matris::set_eleman(const int satir_id, const int sutun_id, const long double deger) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    dizi_2b[satir_id][sutun_id] = deger;
}


void Matris::set_dikdortgen(const int satir_id, const int sutun_id, const Matris &dikdortgen) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_aralik_icinde_satir(satir_id)) {
        throw std::invalid_argument("Hata_03: satir indeksi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(sutun_id)) {
        throw std::invalid_argument("Hata_04: sutun indeksi aralik disinda");
    }

    if (dikdortgen.olmak_bos()) {
        throw std::invalid_argument("Hata_13: bos dikdortgen");
    }

    if (!olmak_aralik_icinde_satir(dikdortgen.satir_sayisi - 1)) {
        throw std::invalid_argument("Hata_05: dikdortgen yuksekligi aralik disinda");
    }

    if (!olmak_aralik_icinde_sutun(dikdortgen.sutun_sayisi - 1)) {
        throw std::invalid_argument("Hata_06: dikdortgen genisligi aralik disinda");
    }

    if (satir_id + dikdortgen.satir_sayisi > satir_sayisi || sutun_id + dikdortgen.sutun_sayisi > sutun_sayisi) {
        throw std::invalid_argument("Hata_07: uyumsuz dikdortgen konumu");
    }

    for (int sayim_m = 0; sayim_m < dikdortgen.satir_sayisi; sayim_m++) {
        for (int sayim_n = 0; sayim_n < dikdortgen.sutun_sayisi; sayim_n++) {
            dizi_2b[satir_id + sayim_m][sutun_id + sayim_n] = dikdortgen.dizi_2b[sayim_m][sayim_n];
        }
    }
}

// MODIFIYE EDEN
void Matris::toplam(const long double deger) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[sayim_m][sayim_n] += deger;
        }
    }
}

void Matris::katla(const long double deger) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[sayim_m][sayim_n] *= deger;
        }
    }
}

void Matris::gauss_elimine_alt_ucgen(bool yapmak_indirgenmis) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    int en_ust_satir = 0;
    int en_sol_sutun = 0;
    long double satir_basi_ust = dizi_2b[en_ust_satir][en_sol_sutun];
    long double tmp_satir_basi;
    long double katsayi_normalize = ((long double) 1.0) / satir_basi_ust;
    long double katsayi_elimine;

    // gerekliyse en ust satir normalize edilir
    if (yapmak_indirgenmis) {
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[en_ust_satir][sayim_n] *= katsayi_normalize;
        }
    }

    // satir_basi_ust guncellenir
    satir_basi_ust = dizi_2b[en_ust_satir][en_sol_sutun];

    // ozyineli
    if (satir_sayisi == 1) {
        return;
    }

    for (int sayim_m = (en_ust_satir + 1); sayim_m < satir_sayisi; sayim_m++) {
        tmp_satir_basi = dizi_2b[sayim_m][en_sol_sutun];
        katsayi_elimine = (- tmp_satir_basi) / satir_basi_ust;

        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[sayim_m][sayim_n] += katsayi_elimine * dizi_2b[en_ust_satir][sayim_n];
        }
    }

    Matris *ucgen_minor = get_minor(en_ust_satir, en_sol_sutun);

    ucgen_minor->gauss_elimine_alt_ucgen(yapmak_indirgenmis);

    set_dikdortgen((en_ust_satir + 1), (en_sol_sutun + 1), *ucgen_minor);

    delete ucgen_minor;
    ucgen_minor = NULL;
}

void Matris::gauss_elimine_alt_ucgen(Matris &tekrarci, bool yapmak_indirgenmis) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    if (tekrarci.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (!tekrarci.olmak_kare()) {
        throw std::invalid_argument("Hata_17: kare olmayan parametre-matris");
    }

    if (satir_sayisi != tekrarci.satir_sayisi) {
        throw std::invalid_argument("Hata_21: parametre-matris boyutlari farkli");
    }

    int en_ust_satir = 0;
    int en_sol_sutun = 0;
    long double satir_basi_ust = dizi_2b[en_ust_satir][en_sol_sutun];
    long double tmp_satir_basi;
    long double katsayi_normalize = ((long double) 1.0) / satir_basi_ust;
    long double katsayi_elimine;

    // gerekliyse en ust satir normalize edilir
    if (yapmak_indirgenmis) {
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[en_ust_satir][sayim_n] *= katsayi_normalize;
            tekrarci.dizi_2b[en_ust_satir][sayim_n] *= katsayi_normalize;
        }
    }

    // satir_basi_ust guncellenir
    satir_basi_ust = dizi_2b[en_ust_satir][en_sol_sutun];

    // ozyineli
    if (satir_sayisi == 1) {
        return;
    }

    for (int sayim_m = (en_ust_satir + 1); sayim_m < satir_sayisi; sayim_m++) {
        tmp_satir_basi = dizi_2b[sayim_m][en_sol_sutun];
        katsayi_elimine = (- tmp_satir_basi) / satir_basi_ust;

        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[sayim_m][sayim_n] += katsayi_elimine * dizi_2b[en_ust_satir][sayim_n];
            tekrarci.dizi_2b[sayim_m][sayim_n] += katsayi_elimine * tekrarci.dizi_2b[en_ust_satir][sayim_n];
        }
    }

    Matris *ucgen_minor = get_minor(en_ust_satir, en_sol_sutun);
    Matris *ucgen_minor_tekrarci = tekrarci.get_minor(en_ust_satir, en_sol_sutun);

    ucgen_minor->gauss_elimine_alt_ucgen(*ucgen_minor_tekrarci, yapmak_indirgenmis);

    set_dikdortgen((en_ust_satir + 1), (en_sol_sutun + 1), *ucgen_minor);
    tekrarci.set_dikdortgen((en_ust_satir + 1), (en_sol_sutun + 1), *ucgen_minor_tekrarci);

    delete ucgen_minor;
    ucgen_minor = NULL;
    delete ucgen_minor_tekrarci;
    ucgen_minor_tekrarci = NULL;
}

void Matris::gauss_elimine_ust_ucgen(bool yapmak_indirgenmis) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    int en_alt_satir = satir_sayisi - 1;
    int en_sag_sutun = sutun_sayisi - 1;
    long double satir_sonu_alt = dizi_2b[en_alt_satir][en_sag_sutun];
    long double tmp_satir_sonu;
    long double katsayi_normalize = ((long double) 1.0) / satir_sonu_alt;
    long double katsayi_elimine;

    // gerekliyse en alt satir normalize edilir
    if (yapmak_indirgenmis) {
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[en_alt_satir][sayim_n] *= katsayi_normalize;
        }
    }

    // satir_basi_ust guncellenir
    satir_sonu_alt = dizi_2b[en_alt_satir][en_sag_sutun];

    // ozyineli
    if (satir_sayisi == 1) {
        return;
    }

    for (int sayim_m = (satir_sayisi - 2); sayim_m >= 0; sayim_m--) {
        tmp_satir_sonu = dizi_2b[sayim_m][en_sag_sutun];
        katsayi_elimine = (- tmp_satir_sonu) / satir_sonu_alt;

        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[sayim_m][sayim_n] += katsayi_elimine * dizi_2b[en_alt_satir][sayim_n];
        }
    }

    Matris *ucgen_minor = get_minor(en_alt_satir, en_sag_sutun);

    ucgen_minor->gauss_elimine_ust_ucgen(yapmak_indirgenmis);

    set_dikdortgen(0, 0, *ucgen_minor);

    delete ucgen_minor;
    ucgen_minor = NULL;
}

void Matris::gauss_elimine_ust_ucgen(Matris &tekrarci, bool yapmak_indirgenmis) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    if (tekrarci.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (!tekrarci.olmak_kare()) {
        throw std::invalid_argument("Hata_17: kare olmayan parametre-matris");
    }

    if (satir_sayisi != tekrarci.satir_sayisi) {
        throw std::invalid_argument("Hata_21: parametre-matris boyutlari farkli");
    }

    int en_alt_satir = satir_sayisi - 1;
    int en_sag_sutun = sutun_sayisi - 1;
    long double satir_sonu_alt = dizi_2b[en_alt_satir][en_sag_sutun];
    long double tmp_satir_sonu;
    long double katsayi_normalize = ((long double) 1.0) / satir_sonu_alt;
    long double katsayi_elimine;

    // gerekliyse en alt satir normalize edilir
    if (yapmak_indirgenmis) {
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[en_alt_satir][sayim_n] *= katsayi_normalize;
            tekrarci.dizi_2b[en_alt_satir][sayim_n] *= katsayi_normalize;
        }
    }

    // satir_basi_ust guncellenir
    satir_sonu_alt = dizi_2b[en_alt_satir][en_sag_sutun];

    // ozyineli
    if (satir_sayisi == 1) {
        return;
    }

    for (int sayim_m = (satir_sayisi - 2); sayim_m >= 0; sayim_m--) {
        tmp_satir_sonu = dizi_2b[sayim_m][en_sag_sutun];
        katsayi_elimine = (- tmp_satir_sonu) / satir_sonu_alt;

        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[sayim_m][sayim_n] += katsayi_elimine * dizi_2b[en_alt_satir][sayim_n];
            tekrarci.dizi_2b[sayim_m][sayim_n] += katsayi_elimine * tekrarci.dizi_2b[en_alt_satir][sayim_n];
        }
    }

    Matris *ucgen_minor = get_minor(en_alt_satir, en_sag_sutun);
    Matris *ucgen_minor_tekrarci = tekrarci.get_minor(en_alt_satir, en_sag_sutun);

    ucgen_minor->gauss_elimine_ust_ucgen(*ucgen_minor_tekrarci, yapmak_indirgenmis);

    set_dikdortgen(0, 0, *ucgen_minor);
    tekrarci.set_dikdortgen(0, 0, *ucgen_minor_tekrarci);

    delete ucgen_minor;
    ucgen_minor = NULL;
    delete ucgen_minor_tekrarci;
    ucgen_minor_tekrarci = NULL;
}

// yapmak_indirgenmis == false gauss_jordan hesabini, sonradan normalize (birim matris) etmeye yarar
void Matris::gauss_kosegenden_birime(Matris &tekrarci) {
    if (olmak_bos()) {
        throw std::invalid_argument("Hata_02: bos matris");
    }

    if (!olmak_kare()) {
        throw std::invalid_argument("Hata_08: kare olmayan matris");
    }

    if (tekrarci.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (!tekrarci.olmak_kare()) {
        throw std::invalid_argument("Hata_17: kare olmayan parametre-matris");
    }

    if (satir_sayisi != tekrarci.satir_sayisi) {
        throw std::invalid_argument("Hata_21: parametre-matris boyutlari farkli");
    }

    long double katsayi_kosegen;
    for (int sayim_m = 0; sayim_m < satir_sayisi; sayim_m++) {
        katsayi_kosegen = dizi_2b[sayim_m][sayim_m];
        for (int sayim_n = 0; sayim_n < sutun_sayisi; sayim_n++) {
            dizi_2b[sayim_m][sayim_n] /= katsayi_kosegen;
            tekrarci.dizi_2b[sayim_m][sayim_n] /= katsayi_kosegen;
        }
    }
}

// STATIK
Matris* Matris::birim(const int boyut) {
    if (boyut <= 0) {
        throw std::invalid_argument("Hata_01: pozitif olmayan matris boyutlari");
    }

    Matris *birim = new Matris();
    birim->satir_sayisi = boyut;
    birim->sutun_sayisi = boyut;
    birim->dizi_2b = new long double*[birim->satir_sayisi];
    for (int sayim_m = 0; sayim_m < birim->satir_sayisi; sayim_m++) {
        birim->dizi_2b[sayim_m] = new long double[birim->sutun_sayisi];
        for (int sayim_n = 0; sayim_n < birim->sutun_sayisi; sayim_n++) {
            if (sayim_m == sayim_n) {
                birim->dizi_2b[sayim_m][sayim_n] = 1;
            }
            else {
                birim->dizi_2b[sayim_m][sayim_n] = 0;
            }
        }
    }

    return birim;
}

Matris* Matris::sifirlar(const int satir_sayisi, const int sutun_sayisi){
    if (satir_sayisi <= 0 || sutun_sayisi <= 0) {
        throw std::invalid_argument("Hata_01: pozitif olmayan matris boyutlari");
    }

    Matris *sifirlar = new Matris();
    sifirlar->satir_sayisi = satir_sayisi;
    sifirlar->sutun_sayisi = sutun_sayisi;
    sifirlar->dizi_2b = new long double*[sifirlar->satir_sayisi];
    for (int sayim_m = 0; sayim_m < sifirlar->satir_sayisi; sayim_m++) {
        sifirlar->dizi_2b[sayim_m] = new long double[sifirlar->sutun_sayisi];
        for (int sayim_n = 0; sayim_n < sifirlar->sutun_sayisi; sayim_n++) {
            sifirlar->dizi_2b[sayim_m][sayim_n] = 0;
        }
    }

    return sifirlar;
}

Matris* Matris::birler(const int satir_sayisi, const int sutun_sayisi){
    if (satir_sayisi <= 0 || sutun_sayisi <= 0) {
        throw std::invalid_argument("Hata_01: pozitif olmayan matris boyutlari");
    }

    Matris *birler = new Matris();
    birler->satir_sayisi = satir_sayisi;
    birler->sutun_sayisi = sutun_sayisi;
    birler->dizi_2b = new long double*[birler->satir_sayisi];
    for (int sayim_m = 0; sayim_m < birler->satir_sayisi; sayim_m++) {
        birler->dizi_2b[sayim_m] = new long double[birler->sutun_sayisi];
        for (int sayim_n = 0; sayim_n < birler->sutun_sayisi; sayim_n++) {
            birler->dizi_2b[sayim_m][sayim_n] = 1;
        }
    }

    return birler;
}

Matris* Matris::toplam(const Matris &sol, const Matris &sag) {
    if (sol.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (sag.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (sol.satir_sayisi != sag.satir_sayisi || sol.sutun_sayisi != sag.sutun_sayisi) {
        throw std::invalid_argument("Hata_15: toplamm icin uyumsuz matris boyutlari");
    }

    Matris *toplam = new Matris(sol);
    for (int sayim_m = 0; sayim_m < toplam->satir_sayisi; sayim_m++) {
        for (int sayim_n = 0; sayim_n < toplam->sutun_sayisi; sayim_n++) {
            toplam->dizi_2b[sayim_m][sayim_n] += sag.dizi_2b[sayim_m][sayim_n];
        }
    }

    return toplam;
}

Matris* Matris::carpim(const Matris &sol, const Matris &sag) {
    if (sol.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (sag.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (sol.sutun_sayisi != sag.satir_sayisi) {
        throw std::invalid_argument("Hata_16: carpimim icin uyumsuz matris boyutlari");
    }

    Matris *carpim = Matris::sifirlar(sol.satir_sayisi, sag.sutun_sayisi);
    for (int sayim_m = 0; sayim_m < carpim->satir_sayisi; sayim_m++) {
        for (int sayim_n = 0; sayim_n < carpim->sutun_sayisi; sayim_n++) {
            for (int sayim_i = 0; sayim_i < sol.sutun_sayisi; sayim_i++) {
                carpim->dizi_2b[sayim_m][sayim_n] += sol.dizi_2b[sayim_m][sayim_i] * sag.dizi_2b[sayim_i][sayim_n];
            }
        }
    }

    return carpim;
}

Matris* Matris::soldan_bolum(const Matris &sol, const Matris &sag) {
    if (sol.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (!sol.olmak_kare()) {
        throw std::invalid_argument("Hata_17: kare olmayan parametre-matris");
    }

    if (sag.olmak_bos()) {
        throw std::invalid_argument("Hata_14: bos parametre-matris");
    }

    if (sag.sutun_sayisi != 1) {
        throw std::invalid_argument("Hata_18: sutun vektoru degil");
    }

    if (sol.sutun_sayisi != sag.satir_sayisi) {
        throw std::invalid_argument("Hata_16: carpimim icin uyumsuz matris boyutlari");
    }

    const int tek_sutun = 0;
    long double det_sol = sol.get_determinant();

    if (det_sol == 0) {
        throw std::invalid_argument("Hata_19: parametre-matris determinant sifir");
    }

    Matris *sol_n = new Matris(sol);
    Matris *tmp_sutun = NULL;

    Matris *sonuc = Matris::sifirlar(sol.satir_sayisi, 1);
    for (int sayim_n = 0; sayim_n < sol.sutun_sayisi; sayim_n++) {
        // Her iterasyonda kopyayi asil haline getirir
        if (sayim_n > 0) {
            tmp_sutun = sol.get_sutun(sayim_n - 1);
            sol_n->set_sutun((sayim_n - 1), *tmp_sutun);
        }
        sol_n->set_sutun(sayim_n, sag);

        sonuc->dizi_2b[sayim_n][tek_sutun] = sol_n->get_determinant() / det_sol;

        delete tmp_sutun;
    }

    tmp_sutun = NULL;

    return sonuc;
}


// PRIVATE
bool Matris::olmak_kare() const {
    if (satir_sayisi != sutun_sayisi) {
        return false;
    }
    return true;
}

bool Matris::olmak_bos() const {
    if (!satir_sayisi || !sutun_sayisi || olmak_null_dizi_2b()) {
        return true;
    }
    return false;
}

bool Matris::olmak_null_dizi_2b() const {
    if (!dizi_2b) {
        return true;
    }

    return false;
}

bool Matris::olmak_aralik_icinde_satir(const int satir_id) const {
    return !(satir_id < 0 || satir_id >= satir_sayisi);
}

bool Matris::olmak_aralik_icinde_sutun(const int sutun_id) const {
    return !(sutun_id < 0 || sutun_id >= sutun_sayisi);
}
