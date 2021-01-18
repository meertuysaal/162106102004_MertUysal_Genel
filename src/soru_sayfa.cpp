#include "soru_sayfa.h"

Soru_sayfa::Soru_sayfa(Matris *A, Matris *B) {
	this->A = A;
	this->B = B;
	program_dizini_mutlak = fs::absolute(fs::current_path());
}

void Soru_sayfa::yazdir_soru_listesi() {
	std::cout
		<< "(1)\tSoru  1\n"
		<< "(2)\tSoru  2\n"
		<< "(3)\tSoru  3\n"
		<< "(4)\tSoru  4\n"
		<< "(5)\tSoru  5\n"
		<< "(6)\tSoru  6\n"
		<< "(7)\tSoru  7\n"
		<< "(11)\tSoru 11\n"
		<< "(13)\tSoru 13\n"
		<< "\n\n"
		<< "(geri) Anamenu'ye Geri Don\n"
		<< "(cikis)\tCikis\n";
}

void Soru_sayfa::hesapla_soru_01() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			arabellek = "det(A): ";
			arabellek.append(std::to_string(A->get_determinant()));

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");
		}
		catch (std::invalid_argument &exc) {
			arabellek = exc.what();
		}
	}
}

void Soru_sayfa::hesapla_soru_02() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			Matris* AT = A->get_transpoze();
			Matris* AT_carpim_A = Matris::carpim(*AT, *A);
			long double iz_AT_carpim_A = AT_carpim_A->get_iz();

			arabellek = "iz(ATA): ";
			arabellek.append(std::to_string(iz_AT_carpim_A));

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");
			araciktilar.append("AT:\n");
			araciktilar.append(AT->to_string("\t"));
			araciktilar.append("\n");
			araciktilar.append("AT_carpim_A:\n");
			araciktilar.append(AT_carpim_A->to_string("\t"));
			araciktilar.append("\n");

			delete AT_carpim_A;
			AT_carpim_A = NULL;
			delete AT;
			AT = NULL;
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}
}

void Soru_sayfa::hesapla_soru_03() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			arabellek = "A'nin satir normlari:\n";
			for (int sayim_m = 0; sayim_m < A->get_satir_sayisi(); sayim_m++) {
				arabellek.append("\tSatir-");
				arabellek.append(std::to_string(sayim_m + 1));
				arabellek.append(": ");
				arabellek.append(std::to_string(A->get_satir_normu(sayim_m)));
				if (sayim_m != A->get_satir_sayisi() - 1) {
					arabellek.append("\n");
				}

				araciktilar = "";
				araciktilar.append("A:\n");
				araciktilar.append(A->to_string("\t"));
				araciktilar.append("\n");
			}
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}

	
}

void Soru_sayfa::hesapla_soru_04() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			arabellek = "A'nin sutun normlari:\n";
			for (int sayim_n = 0; sayim_n < A->get_sutun_sayisi(); sayim_n++) {
				arabellek.append("\tSutun-");
				arabellek.append(std::to_string(sayim_n + 1));
				arabellek.append(": ");
				arabellek.append(std::to_string(A->get_sutun_normu(sayim_n)));
				if (sayim_n != A->get_sutun_sayisi() - 1) {
					arabellek.append("\n");
				}
			}

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}
}

void Soru_sayfa::hesapla_soru_05() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			arabellek = "A'nin Oklid normu ( N(A) ): ";
			arabellek.append(std::to_string(A->get_oklid_normu()));

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}
}

void Soru_sayfa::hesapla_soru_06() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			Matris* AT = A->get_transpoze();
			Matris *AT_carpim_A = Matris::carpim(*AT, *A);
			long double iz_AT_carpim_A = AT_carpim_A->get_iz();
			if (A->get_oklid_normu() == std::sqrt(iz_AT_carpim_A)) {
				arabellek = "N(A)           : ";
				arabellek.append(std::to_string(A->get_oklid_normu()));
				arabellek.append("\n(iz(ATA))^(1/2): ");
				arabellek.append(std::to_string(std::sqrt(iz_AT_carpim_A)));
				arabellek.append("\n");
			}
			else {
				arabellek = "N(A) esit degildir (iz(ATA))^(1/2)";
			}

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");
			araciktilar.append("AT:\n");
			araciktilar.append(AT->to_string("\t"));
			araciktilar.append("\n");
			araciktilar.append("AT_carpim_A:\n");
			araciktilar.append(AT_carpim_A->to_string("\t"));
			araciktilar.append("\n");
			araciktilar.append("iz_AT_carpim_A:\n\t");
			araciktilar.append(std::to_string(iz_AT_carpim_A));
			araciktilar.append("\n");

			delete AT_carpim_A;
			AT_carpim_A = NULL;
			delete AT;
			AT = NULL;
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}
}

void Soru_sayfa::hesapla_soru_07() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			Matris* A_normalize = new Matris(*A);
			long double A_oklid_normu = A->get_oklid_normu();
			long double bir_bolu_A_oklid_normu = 1 / A_oklid_normu;
			A_normalize->katla(bir_bolu_A_oklid_normu);

			arabellek = "Normlastirilmis A (Oklid normuna gore):\n";
			arabellek.append(A_normalize->to_string());

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");
			araciktilar.append("A_oklid_normu:\n\t");
			araciktilar.append(std::to_string(A_oklid_normu));
			araciktilar.append("\n\n");
			araciktilar.append("bir_bolu_A_oklid_normu:\n\t");
			araciktilar.append(std::to_string(bir_bolu_A_oklid_normu));
			araciktilar.append("\n");

			delete A_normalize;
			A_normalize = NULL;
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}
}

void Soru_sayfa::hesapla_soru_11() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			Matris* kramer_tersi = A->get_kramer_tersi();

			arabellek = "A matrisinin tersi (Kramer kurali) :\n";
			arabellek.append(std::string(kramer_tersi->to_string("\t")));

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");

			delete kramer_tersi;
			kramer_tersi = NULL;
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}


}

void Soru_sayfa::hesapla_soru_13() {
	if (!olmak_hesaplanmis) {
		olmak_hesaplanmis = true;
		try {
			Matris* gauss_tersi = A->get_gauss_jordan_tersi();

			arabellek = "[Uyari: Dogru sonuc bulunamadi]\nA matrisinin tersi (Gauss kurali):\n";
			arabellek.append(gauss_tersi->to_string("\t"));

			araciktilar = "";
			araciktilar.append("A:\n");
			araciktilar.append(A->to_string("\t"));
			araciktilar.append("\n");

			delete gauss_tersi;
			gauss_tersi = NULL;
		}
		catch (std::invalid_argument& exc) {
			arabellek = exc.what();
		}
	}
}

void Soru_sayfa::yazdir_data() {
	switch (aktif_soru_id) {
	case 0:
		yazdir_soru_listesi();
		break;
	case 1:
		hesapla_soru_01();
		break;
	case 2:
		hesapla_soru_02();
		break;
	case 3:
		hesapla_soru_03();
		break;
	case 4:
		hesapla_soru_04();
		break;
	case 5:
		hesapla_soru_05();
		break;;
	case 6:
		hesapla_soru_06();
		break;
	case 7:
		hesapla_soru_07();
		break;
	case 11:
		hesapla_soru_11();
		break;
	case 13:
		hesapla_soru_13();
		break;
	default:
		std::cout << "\nOngorulemeyen Hata: aktif_soru_id aralik disinda\n";
		break;
	}

	// hesaplanan soruyu yazdir
	if (olmak_hesaplanmis) {
		std::cout << arabellek
			<< "\n\n"
			<< "(evet) Soru ciktisini kaydet (ornek: soru_01.txt)\n"
			<< "(hayir) Sorular'a Geri Don\n";
	}
}

void Soru_sayfa::yazdir() {
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

void Soru_sayfa::yazdir_sonuc_kaydet(std::string dosya_adi) {
	if (!secilen.compare("hayir")) {
		//Sorular'a don
		aktif_soru_id = 0;
		olmak_hesaplanmis = false;
		arabellek = "";
	}
	else if (!secilen.compare("evet")) {
		kaydet_log(dosya_adi);
		//Sorular'a don
		aktif_soru_id = 0;
		olmak_hesaplanmis = false;
		arabellek = "";
	}
	else if (olmak_hesaplanmis) { // sorular menusunden gelinmemisse
		geri_bildirim("Lutfen kaydetmek isteyip istemediginizi giriniz");
		bekle_milisaniye(2000);
	}
}

void Soru_sayfa::kaydet_log(std::string dosya_adi) {
	std::cout << "\n" << dosya_adi << '\n' << std::string(40, '-') << '\n';
	std::cout << "SONUCLAR:\n---------\n";
	std::cout << arabellek << "\n";
	std::cout << "\n\nARACIKTILAR:\n------------\n";
	std::cout << araciktilar << '\n';
	bekle_milisaniye(2000);

	std::ofstream dosya_out(dosya_adi);
	dosya_out << "SONUCLAR:\n---------\n";
	dosya_out << arabellek << "\n";
	dosya_out << "\n\nARACIKTILAR:\n------------\n";
	dosya_out << araciktilar << '\n';
	dosya_out.close();
}

bool Soru_sayfa::calistir() {
	while (true) {
		yazdir();

		// sorular menusundeyse girdinin listede olup olmadigina bak, varsa aktif_soru_id'i degistir
		if (!aktif_soru_id) {
			for (int sayim_i = 0; sayim_i < sizeof(cozulmus_sorular) / sizeof(cozulmus_sorular[0]); sayim_i++) {
				if (!secilen.compare(std::to_string(cozulmus_sorular[sayim_i]))) {
					aktif_soru_id = cozulmus_sorular[sayim_i];
				}
			}
		}

		switch (aktif_soru_id) {
		case 1:
			yazdir_sonuc_kaydet("soru_01.txt");
			break;
		case 2:
			yazdir_sonuc_kaydet("soru_02.txt");
			break;
		case 3:
			yazdir_sonuc_kaydet("soru_03.txt");
			break;
		case 4:
			yazdir_sonuc_kaydet("soru_04.txt");
			break;
		case 5:
			yazdir_sonuc_kaydet("soru_05.txt");
			break;
		case 6:
			yazdir_sonuc_kaydet("soru_06.txt");
			break;
		case 7:
			yazdir_sonuc_kaydet("soru_07.txt");
			break;
		case 11:
			yazdir_sonuc_kaydet("soru_11.txt");
			break;
		case 13:
			yazdir_sonuc_kaydet("soru_13.txt");
			break;
		default:
			if (!secilen.compare("cikis")) {
				//anamenuden cikis yapilsin
				return true;
			}
			else if (!secilen.compare("geri")) {
				//anamenuden cikis yapilmasin
				return false;
			}
			else {
				geri_bildirim("Secim liste disinda, tekrar deneyin.");
				bekle_milisaniye(2000);
			}
			break;
		}
	}
}