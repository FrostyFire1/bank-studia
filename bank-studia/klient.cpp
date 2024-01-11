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

std::list<KontoBankowe> KontoKlienta::getListaKontBankowych()
{
	return listaKontBankowe;
}

std::list<Lokata> KontoKlienta::getListaLokat()
{
	return listaLokat;
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
		std::cout << "Podano bledne dane, nie mozna zalozyc konta bankowego\n";
		return;
	}
	RodzajKonta typKonta = menuWyboruKonta();
	std::string nrKonta = generujNumerKonta(aktualnyKlient);
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
		std::cout << "Podano bledne dane, nie mozna zalozyc lokaty\n";
		return;
	}
	RodzajLokaty typLokaty = menuWyboruLokaty();
	RodzajCzasuLokaty czasLokaty = menuWyboruCzasuLokaty();
	std::string nrKonta = generujNumerKonta(aktualnyKlient);
	double srodki;
	std::cout << "Podaj kwote lokaty: ";
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
		std::cout << "Podano bledne dane, nie mozna zalozyc lokaty\n";
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

void KontoKlienta::wyswietlKontaBankowe(KontoKlienta klient)
{
	system("cls");
	for (KontoBankowe aktualny : klient.listaKontBankowe)
	{
		aktualny.wyswietlDane();
		std::cout << "\n\n";
	}
	std::cout << "Nacisnij dowolny klawisz aby kontynuowac";
	_getch();
}
void KontoKlienta::wyswietlLokaty(KontoKlienta klient)
{
	system("cls");
	for (Lokata aktualna : klient.listaLokat)
	{
		aktualna.wyswietlDaneLokat();
		std::cout << "\n\n";
	}
	std::cout << "Nacisnij dowolny klawisz aby kontynuowac";
	_getch();
}


std::string generujNumerKonta(KontoKlienta* klient)
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
		test = sprawdzNumerKontaBankowego(klient->getListaKontBankowych(), klient->getListaLokat(), temp);
		if (test == true)
		{
			numerKonta = "7021372405" + temp;
		}

	} while (test == false);

	return numerKonta;

}
bool sprawdzNumerKontaBankowego(std::list<KontoBankowe> listaKontBankowych,std::list<Lokata> listaLokat,std::string numerKonta)
{
	bool czyWolny = true;
	for (KontoBankowe konto : listaKontBankowych)
	{
		if (konto.getNrKontaBankowego() == numerKonta)
		{
			czyWolny = false;
		}
	}
	for (Lokata konto : listaLokat)
	{
		if (konto.getNrLokaty() == numerKonta)
		{
			czyWolny = false;
		}
	}

	return czyWolny;
}

RodzajKonta menuWyboruKonta()
{

	int menuWybor;
	for (;;)
	{
		system("cls");
		std::cout << "--------------------\n"
			<< "| 1. Konto oszczednosciowe\n"
			<< "| 2. Konto rozliczeniowe\n"
			<< "| 3. Konto walutowe\n"
			<< "--------------------\n";

		menuWybor = _getch();

		if (menuWybor < 52 && menuWybor > 48) menuWybor -= 48;
		switch (menuWybor)
		{
		case 1:
			return RODZAJ_KONTO_OSZCZEDNOSCIOWE;
			break;
		case 2:
			return RODZAJ_KONTO_ROZLICZENIOWE;
			break;
		case 3:
			return RODZAJ_KONTO_WALUTOWE;
			break;
		default:
			break;
		}
	}
}
RodzajLokaty menuWyboruLokaty()
{
	int menuWybor;
	for (;;)
	{
		system("cls");
		std::cout << "--------------------\n"
			<< "| 1. Lokata zwykla\n"
			<< "| 2. Lokata oszczednosciowa\n"
			<< "| 3. Lokata walutowa\n"
			<< "--------------------\n";

		menuWybor = _getch();

		if (menuWybor < 52 && menuWybor > 48) menuWybor -= 48;
		switch (menuWybor)
		{
		case 1:
			return RODZAJ_LOKATA_ZWYKLA;
			break;
		case 2:
			return RODZAJ_LOKATA_OSZCZEDNOSCIOWA;
			break;
		case 3:
			return RODZAJ_LOKATA_WALUTOWA;
			break;
		default:
			break;
		}
	}
}
RodzajCzasuLokaty menuWyboruCzasuLokaty()
{
	int menuWybor;
	for (;;)
	{
		system("cls");
		std::cout << "--------------------\n"
			<< "| 1. Lokata na okres 3 miesiecy, oprocentowanie x1\n"
			<< "| 2. Lokata na okres 6 miesiecy, oprocentowanie x1.5\n"
			<< "| 3. Lokata na okres 12 miesiecy, oprocentowanie x2\n"
			<< "--------------------\n";

		menuWybor = _getch();

		if (menuWybor < 52 && menuWybor > 48) menuWybor -= 48;
		switch (menuWybor)
		{
		case 1:
			return RODZAJ_CZASU_LOKATA_3MIESIECZNA;
			break;
		case 2:
			return RODZAJ_CZASU_LOKATA_6MIESIECZNA;
			break;
		case 3:
			return	RODZAJ_CZASU_LOKATA_12MIESIECZNA;
			break;
		default:
			break;
		}
	}
}


void zapiszKontoBankoweDoPliku(KontoBankowe* konto, std::string nazwaPliku)
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
void zapiszLokateDoPliku(Lokata* lokata,std::string nazwaPliku)
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
			listaKontBankowe.push_front(*nowe);
			delete nowe;
			getline(plik, linia);
		}
		plik.close();
	}
	else std::cout << "Nie mozna otworzyc pliku";
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
	else std::cout << "Nie mozna otworzyc pliku";
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
	std::string temp_pelnaSciezka = working_directory + "\\KontaBankowe\\tempKontaBankowe.txt";
	std::ofstream temp_plik(temp_pelnaSciezka);
	if (plik.is_open() && temp_plik.is_open())
	{
		while (getline(plik, linia))
		{
			nrKonta = linia;
			plik>>typKonta;
			plik >> srodki;

			KontoBankowe* nowe = new KontoBankowe(nrKonta, static_cast<RodzajKonta>(typKonta),srodki);
			if (nowe->getNrKontaBankowego() != numerKonta)
			{
				temp_plik << nrKonta << "\n";
				temp_plik << typKonta << "\n";
				temp_plik << srodki << "\n";
			}

			delete nowe;
			getline(plik, linia);
		}
		plik.close();
		plik.clear();
		temp_plik.close();
		temp_plik.clear();

		if (std::remove(pelnaSciezka.c_str()) != 0) {
			std::cerr << "Blad podczas usuwania pliku." << std::endl;
		}

		if (std::rename(temp_pelnaSciezka.c_str(), pelnaSciezka.c_str()) != 0)
		{
			std::cout << "Nie mozna zastapić pliku";
		}
	}
	else
	{
		std::cout << "Nie mozna otworzyc pliku";
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
	std::string temp_pelnaSciezka = working_directory + "\\Lokaty\\tempLokaty.txt";
	std::ofstream temp_plik(temp_pelnaSciezka);

	if (plik.is_open() && temp_plik.is_open())
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
				temp_plik << rodzaj << "\n";
				temp_plik << okres << "\n";
				temp_plik << numerLokaty << "\n";
				temp_plik << srodki << "\n";
				temp_plik << oprocentowanie << "\n";
				temp_plik << dataRozpoczecia << "\n";
				temp_plik << ostatnieNaliczenie << "\n";
			}

			delete nowa;
			getline(plik, linia);

		}
		plik.close();
		plik.clear();
		temp_plik.close();
		temp_plik.clear();

		if (std::remove(pelnaSciezka.c_str()) != 0) {
			std::cerr << "Blad podczas usuwania pliku." << std::endl;
		}

		if (std::rename(temp_pelnaSciezka.c_str(), pelnaSciezka.c_str()) != 0)
		{
			std::cout << "Nie mozna zastapić pliku";
		}
	}
	else
	{
		std::cout << "Nie mozna otworzyc pliku";
	}
}

void aktualizacjaKontaBankowego(KontoBankowe* konto, std::list<KontoBankowe> listaKont, std::string nazwaPliku)
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
	std::string temp_pelnaSciezka = working_directory + "\\KontaBankowe\\tempKontaBankowe.txt";
	std::ofstream temp_plik(temp_pelnaSciezka);
	if (!temp_plik.is_open()) {
		std::cerr << "Blad otwierania pliku do zapisu." << std::endl;
		return;
	}

	for (std::list<KontoBankowe>::iterator it = listaKont.begin(); it != listaKont.end(); ++it) {
		temp_plik << konto->getNrKontaBankowego() << "\n";
		temp_plik << konto->getTypKontaBankowego() << "\n";
		temp_plik << konto->getSrodki() << "\n";
		getline(plik, linia);
	}
		temp_plik.close();
		temp_plik.clear();

		if (std::remove(pelnaSciezka.c_str()) != 0) {
			std::cerr << "Blad podczas usuwania pliku." << std::endl;
		}

		if (std::rename(temp_pelnaSciezka.c_str(), pelnaSciezka.c_str()) != 0)
		{
			std::cout << "Nie mozna zastapic pliku";
		}
}
void aktualizacjaLokaty(Lokata* lokata, std::list<Lokata> listaLokat, std::string nazwaPliku)
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
	std::string temp_pelnaSciezka = working_directory + "\\Lokaty\\tempLokaty.txt";
	std::ofstream temp_plik(temp_pelnaSciezka);

	if (!temp_plik.is_open()) {
		std::cerr << "Blad otwierania pliku do zapisu." << std::endl;
		return;
	}

	for (std::list<Lokata>::iterator it = listaLokat.begin(); it != listaLokat.end(); ++it) {
		temp_plik << lokata->getRodzajLokaty() << "\n";
		temp_plik << lokata->getRodzajCzasuLokaty() << "\n";
		temp_plik << lokata->getNrLokaty() << "\n";
		temp_plik << lokata->getSrodki() << "\n";
		temp_plik << lokata->getOprocentowanie() << "\n";
		temp_plik << lokata->getDataRozpoczecia() << "\n";
		temp_plik << lokata->getOstatnieNaliczenie() << "\n";
		getline(plik, linia);
	}
		temp_plik.close();
		temp_plik.clear();

		if (std::remove(pelnaSciezka.c_str()) != 0) {
			std::cerr << "Blad podczas usuwania pliku." << std::endl;
		}

		if (std::rename(temp_pelnaSciezka.c_str(), pelnaSciezka.c_str()) != 0)
		{
			std::cout << "Nie mozna zastapic pliku";
		}
}
