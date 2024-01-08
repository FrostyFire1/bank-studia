#include <iostream>
#include <conio.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "RodzajKonta.h"
#include "RodzajLokaty.h"
#include "KontoKlienta.h"
#include "bank.h"
#include "RodzajLokaty.h"
#include "RodzajCzasuLokaty.h"
#include "Lokata.h"
#include "RodzajKonta.h"


KontoKlienta::KontoKlienta() {
}
KontoKlienta::~KontoKlienta() {

}

void KontoKlienta::dodajKontoBankowe(Bank bank) {
	std::cout << "Zaloguj się ponownie w celu weryfikacji danych\n";
	_getch();
	bool test = bank.logowanie();
	if (!test)
	{
		std::cout << "Podano błędne dane, nie można założyć konta bankowego\n";
		return;
	}
	RodzajKonta typKonta = menuWyboruKonta();
	std::string nrKonta = generujNumerKonta();
	KontoBankowe* nowy = new KontoBankowe(nrKonta, typKonta);
	listaKontBankowe.push_front(*nowy);
	delete nowy;

}
void KontoKlienta::usunKontoBankowe(std::string numerKonta) {
	int poczatek = 0;
	std::list<KontoBankowe>::iterator it;
	for (it = listaKontBankowe.begin(); it != listaKontBankowe.end(); it++)
	{
		if (it->numerKonta == numerKonta)
		{
			listaKontBankowe.erase(it);
			std::cout << "Konto zostalo usuniete!";
			_getch();
			return;
		}
	}
	std::cout << "Nie znaleziono konta!";
	_getch();
}

void KontoKlienta::dodajLokate(Bank bank) {
std::cout << "Zaloguj się ponownie w celu weryfikacji danych\n";
	_getch();
	bool test = bank.logowanie();
	if (!test)
	{
		std::cout << "Podano błędne dane, nie można założyć lokaty\n";
		return;
	}
	RodzajLokaty typLokaty = menuWyboruLokaty();
	RodzajCzasuLokaty czasLokaty = menuWyboruCzasuLokaty();
	std::string nrKonta = generujNumerKonta();
	double srodki;
	std::cout<<"Podaj kwotę lokaty: ";
	std::cin >> srodki;
	std::cout << typLokaty<<"\n"<<czasLokaty;
	Lokata* nowa = new Lokata(typLokaty, czasLokaty, srodki, nrKonta);
	listaLokat.push_front(*nowa);
	delete nowa;

}
void KontoKlienta::usunLokate(std::string nrLokaty) {
	int poczatek = 0;
	std::list<Lokata>::iterator it;
	for (it = listaLokat.begin(); it != listaLokat.end(); it++)
	{
		if (it->nrLokaty == nrLokaty)
		{
			listaLokat.erase(it);
			std::cout << "Lokata zostala usunieta!";
			_getch();
			return;
		}
	}
	std::cout << "Nie znaleziono lokaty!";
	_getch();

}
void wyswietlKontaBankowe(KontoKlienta bank)
{
	system("cls");
	for (KontoBankowe aktualny : bank.listaKontBankowe)
	{
		aktualny.wyswietlDane();
		std::cout << "\n\n";
	}
}
void wyswietlLokaty(KontoKlienta bank)
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
		std::cout<<temp;
		test = sprawdzNumerKontaBankowego(listaKontBankowe,temp);
		if (test == true)
		{
			numerKonta = "7021372405" + temp;
		}

	} while (test==false);

	return numerKonta;

}
bool KontoKlienta::sprawdzNumerKontaBankowego(std::list<KontoBankowe> listaKont,std::string numerKonta)
{
	bool czyWolny = true;
	for (KontoBankowe konto : listaKont)
	{
		if (konto.numerKonta == numerKonta)
		{
			czyWolny = true;
			break;
		}
	}

	return czyWolny;
}

RodzajKonta menuWyboruKonta()
{
	 RodzajKonta wybranyTyp = wybierzTypKonta();
	switch (wybranyTyp) {
	case RODZAJ_KONTO_OSZCZĘDNOŚCIOWE:
		std::cout << "Wybrano konto oszczędnościowe.\n";
		return RODZAJ_KONTO_OSZCZĘDNOŚCIOWE;
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
void wyswietlMenuWyboruKonta(int aktualnaOpcja) {
	system("cls");
	std::cout << "Wybierz typ konta:\n";
	for (int i = 1; i <=3; ++i) {
		if (i == aktualnaOpcja) {
			std::cout << "-> ";
		}
		std::cout << (i == RODZAJ_KONTO_OSZCZĘDNOŚCIOWE+1 ? "Konto oszczędnościowe" :
			(i == RODZAJ_KONTO_ROZLICZENIOWE+1 ? "Konto rozliczeniowe" : "Konto walutowe")) << "\n";
	}
}
RodzajKonta wybierzTypKonta() {
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
			return static_cast<RodzajKonta>(aktualnaOpcja-1);
		default:
			break;
		}
	}
}

RodzajLokaty menuWyboruLokaty()
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
void wyswietlMenuWyboruLokaty(int aktualnaOpcja) {
	system("cls");
	std::cout << "Wybierz typ lokaty:\n";
	for (int i = 1; i <= 3; ++i) {
		if (i == aktualnaOpcja) {
			std::cout << "-> ";
		}
		std::cout << (i == RODZAJ_LOKATA_ZWYKLA+1  ? "Lokata zwykła" :
						(i == RODZAJ_LOKATA_OSZCZEDNOSCIOWA+1 ? "Lokata oszczędnościowa" : "Lokata walutowa")) << "\n";
	}
}
RodzajLokaty wybierzTypLokaty() {
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

RodzajCzasuLokaty menuWyboruCzasuLokaty()
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
void wyswietlMenuWyboruCzasuLokaty(int aktualnaOpcja) {
	system("cls");
	std::cout << "Wybierz okres trwania lokaty:\n";
	for (int i = 1; i <= 3; ++i) {
		if (i == aktualnaOpcja) {
			std::cout << "-> ";
		}
		std::cout << (i == RODZAJ_CZASU_LOKATA_3MIESIECZNA+1  ? "3 miesiące" :
						(i == RODZAJ_CZASU_LOKATA_6MIESIECZNA+1  ? "6 miesięcy" : "12 miesięcy")) << "\n";
	}
}

RodzajCzasuLokaty wybierzTypCzasuLokaty() {
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
