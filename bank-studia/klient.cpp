#include <iostream>
#include <fstream>
#include <stdio.h>
#include <direct.h>
#include <string>
#include "klient.h"
#include "bank.h"

KontoKlienta::KontoKlienta()
{
	numerKonta = 0;
};

KontoKlienta::KontoKlienta(std::string nowy_login)
{
	login = nowy_login;
}

KontoKlienta::KontoKlienta(std::string new_imie, std::string new_nazwisko, std::string new_adres, std::string new_mail)
{
	imie = new_imie;
	nazwisko = new_nazwisko;
	adres = new_adres;
	mail = new_mail;
}

KontoKlienta::KontoKlienta(std::string new_imie, std::string new_nazwisko, std::string new_adres, std::string new_mail, std::string new_login, std::string new_haslo, int new_numerKonta)
{
	imie = new_imie;
	nazwisko = new_nazwisko;
	adres = new_adres;
	mail = new_mail;
	login = new_login;
	haslo = new_haslo;
	numerKonta = new_numerKonta;
}

KontoKlienta::~KontoKlienta() {}

bool KontoKlienta::operator==(KontoKlienta konto1)
{
	return (this->numerKonta == konto1.numerKonta);
}

void KontoKlienta::wyswietlDane()
{
	std::cout << imie << " "
		<< nazwisko << "\n"
		<< adres << "\n"
		<< mail << " \n"
		<< login << " "
		<< haslo << "\n"
		<< numerKonta;
}

//gettery i settery --------------------------------------------

std::string KontoKlienta::getLogin()
{
	return login;
}

std::string KontoKlienta::getHaslo()
{
	return haslo;
}

std::string KontoKlienta::getImie()
{
	return imie;
}

std::string KontoKlienta::getNazwisko()
{
	return nazwisko;
}

std::string KontoKlienta::getMail()
{
	return mail;
}

std::string KontoKlienta::getAdres()
{
	return adres;
}

int KontoKlienta::getNumerKonta()
{
	return numerKonta;
}

void KontoKlienta::setLogin(std::string new_login)
{
	login = new_login;
}

void KontoKlienta::setImie(std::string new_imie)
{
	imie = new_imie;
}

void KontoKlienta::setNazwisko(std::string new_nazwisko)
{
	nazwisko = new_nazwisko;
}

void KontoKlienta::setMail(std::string new_mail)
{
	mail = new_mail;
}

void KontoKlienta::setAdres(std::string new_adres)
{
	adres = new_adres;
}


void KontoKlienta::dodajKontoBankowe(KontoKlienta* aktualnyKlient,Bank* aktualnyBank) {
	std::cout << "Zaloguj się ponownie w celu weryfikacji danych\n";
	_getch();
	bool test = aktualnyBank->weryfikacjaTozsamosci(aktualnyKlient);
	if (!test)
	{
		std::cout << "Podano błędne dane, nie można założyć konta bankowego\n";
		return;
	}
	RodzajKonta typKonta = menuWyboruKonta();
	std::string nrKonta = generujNumerKonta();
	KontoBankowe* nowy = new KontoBankowe(nrKonta, typKonta);
	listaKontBankowe.push_front(*nowy);
	zapiszKontoBankoweDoPliku(nowy, aktualnyKlient->getLogin());
	delete nowy;

}
void KontoKlienta::usunKontoBankowe(KontoKlienta* aktualnyKlient, Bank* aktualnyBank,std::string numerKonta) {
	int poczatek = 0;
	std::list<KontoBankowe>::iterator it;
	for (it = listaKontBankowe.begin(); it != listaKontBankowe.end(); it++)
	{
		if (it->numerKonta == numerKonta)
		{
			listaKontBankowe.erase(it);
			usunKontoBankoweZPliku( aktualnyKlient->getLogin(), numerKonta);
			std::cout << "Konto zostalo usuniete!";
			_getch();
			return;
		}
	}
	std::cout << "Nie znaleziono konta!";
	_getch();
}

void KontoKlienta::dodajLokate(KontoKlienta* aktualnyKlient, Bank* aktualnyBank) {
	std::cout << "Zaloguj się ponownie w celu weryfikacji danych\n";
	_getch();
	bool test = aktualnyBank->weryfikacjaTozsamosci(aktualnyKlient);
	if (!test)
	{
		std::cout << "Podano błędne dane, nie można założyć lokaty\n";
		return;
	}
	RodzajLokaty typLokaty = menuWyboruLokaty();
	RodzajCzasuLokaty czasLokaty = menuWyboruCzasuLokaty();
	std::string nrKonta = generujNumerKonta();
	double srodki;
	std::cout << "Podaj kwotę lokaty: ";
	std::cin >> srodki;
	Lokata* nowa = new Lokata(typLokaty, czasLokaty, srodki, nrKonta);
	listaLokat.push_front(*nowa);
	zapiszLokateDoPliku(nowa, aktualnyKlient->getLogin());

	delete nowa;

}
void KontoKlienta::usunLokate(KontoKlienta* aktualnyKlient, Bank* aktualnyBank, std::string nrLokaty) {
	bool test = aktualnyBank->weryfikacjaTozsamosci(aktualnyKlient);
	if (!test)
	{
		std::cout << "Podano błędne dane, nie można założyć lokaty\n";
		return;
	}
	int poczatek = 0;
	std::list<Lokata>::iterator it;
	for (it = listaLokat.begin(); it != listaLokat.end(); it++)
	{
		if (it->nrLokaty == nrLokaty)
		{
			listaLokat.erase(it);
			usunLokateZPliku( aktualnyKlient->getLogin(), nrLokaty);
			std::cout << "Lokata zostala usunieta!";
			_getch();
			return;
		}
	}
	std::cout << "Nie znaleziono lokaty!";
	_getch();

}

void KontoKlienta::wyswietlKontaBankowe(KontoKlienta bank)
{
	system("cls");
	for (KontoBankowe aktualny : bank.listaKontBankowe)
	{
		aktualny.wyswietlDane();
		std::cout << "\n\n";
	}
}
void KontoKlienta::wyswietlLokaty(KontoKlienta bank)
{
	system("cls");
	for (Lokata aktualna : bank.listaLokat)
	{
		aktualna.wyswietlDaneLokat();
		std::cout << "\n\n";
	}
}


std::string KontoKlienta::generujNumerKonta()
{
	std::string numerKonta;
	srand(time(NULL));
	bool test = false;

	do {
		std::string temp;
		for (int i = 0; i <= 16; i++)
		{
			if (i != 0)
			{
				temp = temp += std::to_string(rand() % 10);
			}
		}
		test = sprawdzNumerKontaBankowego(listaKontBankowe, temp);
		if (test == true)
		{
			numerKonta = "7021372405" + temp;
		}

	} while (test == false);

	return numerKonta;

}
bool KontoKlienta::sprawdzNumerKontaBankowego(std::list<KontoBankowe> listaKont, std::string numerKonta)
{
	bool czyWolny = true;
	for (KontoBankowe konto : listaKont)
	{
		if (konto.numerKonta == numerKonta)
		{
			czyWolny = false;
		}
	}

	return czyWolny;
}

RodzajKonta  KontoKlienta::menuWyboruKonta()
{
	RodzajKonta wybranyTyp = wybierzTypKonta();
	switch (wybranyTyp) {
	case RODZAJ_KONTO_OSZCZEDNOSCIOWE:
		std::cout << "Wybrano konto oszczędnościowe.\n";
		return RODZAJ_KONTO_OSZCZEDNOSCIOWE;
		break;
	case RODZAJ_KONTO_ROZLICZENIOWE:
		std::cout << "Wybrano konto rozliczeniowe.\n";
		return RODZAJ_KONTO_ROZLICZENIOWE;
		break;
	case RODZAJ_KONTO_WALUTOWE:
		std::cout << "Wybrano konto walutowe.\n";
		return RODZAJ_KONTO_WALUTOWE;
		break;
	default:
		std::cout << "Nieprawidłowy wybór.\n";
		break;

	}
}
void KontoKlienta::wyswietlMenuWyboruKonta(int aktualnaOpcja) {
	system("cls");
	std::cout << "Wybierz typ konta:\n";
	for (int i = 1; i <= 3; ++i) {
		if (i == aktualnaOpcja) {
			std::cout << "-> ";
		}
		std::cout << (i == RODZAJ_KONTO_OSZCZEDNOSCIOWE + 1 ? "Konto oszczędnościowe" :
			(i == RODZAJ_KONTO_ROZLICZENIOWE + 1 ? "Konto rozliczeniowe" : "Konto walutowe")) << "\n";
	}
}
RodzajKonta  KontoKlienta::wybierzTypKonta() {
	int aktualnaOpcja = 1;

	while (true) {
		wyswietlMenuWyboruKonta(aktualnaOpcja);
		char klawisz = _getch();
		switch (klawisz) {
		case 72: //gora
			if (aktualnaOpcja > 1) {
				--aktualnaOpcja;
			}
			else if (aktualnaOpcja == 1) {
				aktualnaOpcja = 3;
			}
			break;
		case 80: //dol
			if (aktualnaOpcja < 3) {
				++aktualnaOpcja;
			}
			else if (aktualnaOpcja == 3) {
				aktualnaOpcja = 1;
			}
			break;
		case 13:
			return static_cast<RodzajKonta>(aktualnaOpcja - 1);
		default:
			break;
		}
	}
}

RodzajLokaty KontoKlienta::menuWyboruLokaty()
{
	RodzajLokaty wybranyTyp = wybierzTypLokaty();
	switch (wybranyTyp) {
	case RODZAJ_LOKATA_ZWYKLA:
		std::cout << "Wybrano lokate zwykła, oprocentowanie 2%\n";
		return RODZAJ_LOKATA_ZWYKLA;
		break;
	case RODZAJ_LOKATA_OSZCZEDNOSCIOWA:
		std::cout << "Wybrano lokatę oszczednosciowa, oprocentowanie 4%\n";
		return RODZAJ_LOKATA_OSZCZEDNOSCIOWA;
		break;
	case RODZAJ_LOKATA_WALUTOWA:
		std::cout << "Wybrano lokatę walutowa, oprocentowanie 3%\n";
		return RODZAJ_LOKATA_WALUTOWA;
		break;
	default:
		std::cout << "Nieprawidłowy wybor.\n";
		break;

	}
}
void KontoKlienta::wyswietlMenuWyboruLokaty(int aktualnaOpcja) {
	system("cls");
	std::cout << "Wybierz typ lokaty:\n";
	for (int i = 1; i <= 3; ++i) {
		if (i == aktualnaOpcja) {
			std::cout << "-> ";
		}
		std::cout << (i == RODZAJ_LOKATA_ZWYKLA + 1 ? "Lokata zwykła" :
			(i == RODZAJ_LOKATA_OSZCZEDNOSCIOWA + 1 ? "Lokata oszczędnościowa" : "Lokata walutowa")) << "\n";
	}
}
RodzajLokaty KontoKlienta::wybierzTypLokaty() {
	int aktualnaOpcja = 1;

	while (true) {
		wyswietlMenuWyboruLokaty(aktualnaOpcja);
		char klawisz = _getch();
		switch (klawisz) {
		case 72: //gora
			if (aktualnaOpcja > 1) {
				--aktualnaOpcja;
			}
			else if (aktualnaOpcja == 1) {
				aktualnaOpcja = 3;
			}
			break;
		case 80: //dol
			if (aktualnaOpcja < 3) {
				++aktualnaOpcja;
			}
			else if (aktualnaOpcja == 3) {
				aktualnaOpcja = 1;
			}
			break;
		case 13:
			return static_cast<RodzajLokaty>(aktualnaOpcja - 1);
		default:
			break;
		}
	}
}

RodzajCzasuLokaty KontoKlienta::menuWyboruCzasuLokaty()
{
	RodzajCzasuLokaty wybranyTyp = wybierzTypCzasuLokaty();
	switch (wybranyTyp) {
	case RODZAJ_CZASU_LOKATA_3MIESIECZNA:
		std::cout << "Okres trwania lokaty 3 miesiące,oprocentowanie x1\n";
		return RODZAJ_CZASU_LOKATA_3MIESIECZNA;
		break;
	case RODZAJ_CZASU_LOKATA_6MIESIECZNA:
		std::cout << "Okres trwania lokaty 6 miesiecy,oprocentowanie x1,5\n";
		return RODZAJ_CZASU_LOKATA_6MIESIECZNA;
		break;
	case RODZAJ_CZASU_LOKATA_12MIESIECZNA:
		std::cout << "Okres trwania lokaty 12 miesiecy,oprocentowanie x2\n";
		return RODZAJ_CZASU_LOKATA_12MIESIECZNA;
		break;
	default:
		std::cout << "Nieprawidłowy wybor.\n";
		break;
	}
}
void KontoKlienta::wyswietlMenuWyboruCzasuLokaty(int aktualnaOpcja) {
	system("cls");
	std::cout << "Wybierz okres trwania lokaty:\n";
	for (int i = 1; i <= 3; ++i) {
		if (i == aktualnaOpcja) {
			std::cout << "-> ";
		}
		std::cout << (i == RODZAJ_CZASU_LOKATA_3MIESIECZNA + 1 ? "3 miesiące" :
			(i == RODZAJ_CZASU_LOKATA_6MIESIECZNA + 1 ? "6 miesięcy" : "12 miesięcy")) << "\n";
	}
}
RodzajCzasuLokaty KontoKlienta::wybierzTypCzasuLokaty() {
	int aktualnaOpcja = 1;

	while (true) {
		wyswietlMenuWyboruCzasuLokaty(aktualnaOpcja);
		char klawisz = _getch();
		switch (klawisz) {
		case 72: //gora
			if (aktualnaOpcja > 1) {
				--aktualnaOpcja;
			}
			else if (aktualnaOpcja == 1) {
				aktualnaOpcja = 3;
			}
			break;
		case 80: //dol
			if (aktualnaOpcja < 3) {
				++aktualnaOpcja;
			}
			else if (aktualnaOpcja == 3) {
				aktualnaOpcja = 1;
			}
			break;
		case 13:
			return static_cast<RodzajCzasuLokaty>(aktualnaOpcja - 1);
		default:
			break;
		}
	}
}


void KontoKlienta::zapiszKontoBankoweDoPliku(KontoBankowe* konto, std::string nazwaPliku)
{

	char* cwd = _getcwd(0, 0);
	std::string working_directory(cwd);
	std::free(cwd);
	std::string pelnaSciezka = working_directory + "\\KontaBankowe\\" + nazwaPliku + "KontaBankowe.txt";
	std::ofstream plik(pelnaSciezka, std::ios::app | std::ios::out);
	plik << konto->getNrKontaBankowego() << "\n";
	plik << konto->getTypKontaBankowego() << "\n";
	plik << konto->getSrodki() << "\n";
	plik.close();
}
void KontoKlienta::zapiszLokateDoPliku(Lokata* lokata,std::string nazwaPliku)
{
	char* cwd = _getcwd(0, 0);
	std::string working_directory(cwd);
	std::free(cwd);
	std::string pelnaSciezka = working_directory + "\\Lokaty\\" + nazwaPliku + "Lokaty.txt";
	std::ofstream plik(pelnaSciezka, std::ios::app | std::ios::out);

	plik << lokata->getRodzajLokaty() << "\n";
	plik << lokata->getRodzajCzasuLokaty() << "\n";
	plik << lokata->getNrLokaty() << "\n";
	plik << lokata->getSrodki() << "\n";
	plik << lokata->getOprocentowanie() << "\n";
	plik << lokata->getDataRozpoczecia() << "\n";
	plik << lokata->getOstatnieNaliczenie() << "\n";
	plik.close();
}

void KontoKlienta::wczytajKontaBankoweZPliku(std::string nazwaPliku)
{
	char* cwd = _getcwd(0, 0);
	std::string working_directory(cwd);
	std::free(cwd);
	std::string pelnaSciezka = working_directory + "\\KontaBankowe\\" + nazwaPliku + "KontaBankowe.txt";
	std::ifstream plik(pelnaSciezka);

	std::string linia;
	std::string nrKonta;
	int typKonta;
	double srodki;
	if (plik.is_open())
	{
		while (getline(plik, linia))
		{
			 nrKonta=linia;
			plik >> typKonta;
			plik >> srodki;
			KontoBankowe* nowe = new KontoBankowe(nrKonta, static_cast<RodzajKonta>(typKonta));
			nowe->srodki = srodki;
			listaKontBankowe.push_front(*nowe);
			delete nowe;
			getline(plik, linia);
		}
		plik.close();
	}
	else std::cout << "Nie można otworzyć pliku";
}
void KontoKlienta::wczytajLokatyZPliku(std::string nazwaPliku)
{
	char* cwd = _getcwd(0, 0);
	std::string working_directory(cwd);
	std::free(cwd);
	std::string pelnaSciezka = working_directory + "\\Lokaty\\" + nazwaPliku + "Lokaty.txt";
	std::ifstream plik(pelnaSciezka);
	std::string linia;
	std::string nrLokaty;
	int rodzaj;
	int okres;
	double srodki;
	double oprocentowanie;
	std::string dataRozpoczecia;
	std::string ostatnieNaliczenie;
	if (plik.is_open())
	{
		while (getline(plik, linia))
		{
			rodzaj = std::stoi(linia);
			plik >> okres;
			plik >> nrLokaty;
			plik >> srodki;
			plik >> oprocentowanie;
			plik >> dataRozpoczecia;
			plik >> ostatnieNaliczenie;
			Lokata* nowa = new Lokata(static_cast<RodzajLokaty>(rodzaj), static_cast<RodzajCzasuLokaty>(okres), srodki,oprocentowanie, nrLokaty, dataRozpoczecia, ostatnieNaliczenie);
			listaLokat.push_front(*nowa);
			delete nowa;
			getline(plik, linia);
		}
		plik.close();
	}
	else std::cout << "Nie można otworzyć pliku";
}	

void KontoKlienta::usunKontoBankoweZPliku( std::string nazwaPliku, std::string numerKonta)
{
	char* cwd = _getcwd(0, 0);
	std::string working_directory(cwd);
	std::free(cwd);
	std::string pelnaSciezka = working_directory + "\\KontaBankowe\\" + nazwaPliku + "KontaBankowe.txt";
	std::ifstream plik(pelnaSciezka);

	std::string linia;
	std::string nrKonta;
	int typKonta;
	double srodki;

	// plik tymczasowy do zapisu kont, ktore nie zostaną usunięte
	std::string tempFilename = working_directory + "\\KontaBankowe\\tempKontaBankowe.txt";
	std::ofstream tempFile(tempFilename);
	if (plik.is_open() && tempFile.is_open())
	{
		while (getline(plik, linia))
		{
			nrKonta = linia;
			plik>>typKonta;
			plik >> srodki;

			KontoBankowe* nowe = new KontoBankowe(nrKonta, static_cast<RodzajKonta>(typKonta),srodki);
			if (nowe->getNrKontaBankowego() != numerKonta)
			{
				tempFile << nrKonta << "\n";
				tempFile << typKonta << "\n";
				tempFile << srodki << "\n";
			}

			delete nowe;
			getline(plik, linia);
		}
		plik.close();
		plik.clear();
		tempFile.close();
		tempFile.clear();

		if (std::remove(pelnaSciezka.c_str()) != 0) {
			std::cerr << "Błąd podczas usuwania pliku." << std::endl;
		}

		if (std::rename(tempFilename.c_str(), pelnaSciezka.c_str()) != 0)
		{
			std::cout << "Nie można zastąpić pliku";
		}
	}
	else
	{
		std::cout << "Nie można otworzyć pliku";
	}
}
void KontoKlienta::usunLokateZPliku(std::string nazwaPliku, std::string nrLokaty)
{
	char* cwd = _getcwd(0, 0);
	std::string working_directory(cwd);
	std::free(cwd);
	std::string pelnaSciezka = working_directory + "\\Lokaty\\" + nazwaPliku + "Lokaty.txt";
	std::ifstream plik(pelnaSciezka);

	int rodzaj;
	int okres;
	double srodki;
	double oprocentowanie;
	std::string linia;
	std::string numerLokaty;
	std::string dataRozpoczecia;
	std::string ostatnieNaliczenie;

	// Create a temporary file
	std::string tempFilename = working_directory + "\\Lokaty\\tempLokaty.txt";
	std::ofstream tempFile(tempFilename);

	if (plik.is_open() && tempFile.is_open())
	{
		while (getline(plik, linia))
		{
			rodzaj = std::stoi(linia);
			plik >> okres;
			plik >> numerLokaty;
			plik >> srodki;
			plik >> oprocentowanie;
			plik >> dataRozpoczecia;
			plik >> ostatnieNaliczenie;

			Lokata* nowa = new Lokata(static_cast<RodzajLokaty>(rodzaj), static_cast<RodzajCzasuLokaty>(okres), srodki,oprocentowanie, numerLokaty, dataRozpoczecia, ostatnieNaliczenie);

			if (nowa->getNrLokaty() != nrLokaty)
			{
				tempFile << rodzaj << "\n";
				tempFile << okres << "\n";
				tempFile << numerLokaty << "\n";
				tempFile << srodki << "\n";
				tempFile << oprocentowanie << "\n";
				tempFile << dataRozpoczecia << "\n";
				tempFile << ostatnieNaliczenie << "\n";
			}

			delete nowa;
			getline(plik, linia);

		}
		plik.close();
		plik.clear();
		tempFile.close();
		tempFile.clear();

		if (std::remove(pelnaSciezka.c_str()) != 0) {
			std::cerr << "Błąd podczas usuwania pliku." << std::endl;
		}

		if (std::rename(tempFilename.c_str(), pelnaSciezka.c_str()) != 0)
		{
			std::cout << "Nie można zastąpić pliku";
		}
	}
	else
	{
		std::cout << "Nie można otworzyć pliku";
	}
}
