#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "bank.h"
#include "klient.h"

Bank::Bank()
{
	okresWeryfikacji = 100;
}

Bank::~Bank()
{

}

void Bank::dodajKlienta(int *iloscKlientow, Bank* bank)
{
	(*iloscKlientow)++;

	std::string new_imie;
	std::string new_nazwisko;
	std::string new_adres;
	std::string new_mail;
	std::string new_login;
	std::string new_haslo;
	
	system("cls");
	std::cout << "Imie: ";
	std::cin >> new_imie;
	std::cout << "Nazwisko: ";
	std::cin >> new_nazwisko;
	std::cout << "Adres zamieszkania: ";
	std::cin.ignore();
	std::getline(std::cin, new_adres);
	std::cout << "Adres Email: ";
	std::cin >> new_mail;

	KontoKlienta *nowy = new KontoKlienta(new_imie, new_nazwisko, new_adres, new_mail);
	listaKontKlientow.push_back(*nowy);
	delete nowy;

	new_login = ustawLogin(listaKontKlientow);
	listaKontKlientow.back().login = new_login;
	new_haslo = ustawHaslo();
	listaKontKlientow.back().haslo = new_haslo;
	listaKontKlientow.back().numerKonta = *iloscKlientow;

	setListaKlientow(iloscKlientow, bank);

	std::cout << "Utworzono konto"; _getch();
}

void Bank::usunKlienta()
{
	//confirm passwort


}

bool Bank::weryfikacjaTozsamosc(std::list<KontoKlienta> listaKont, KontoKlienta *aktualnyKlient)
{
	std::string cinLogin;
	std::string cinHaslo;
	bool czyIstnieje = 0;

	system("cls");
	std::cout << "Login: ";
	std::cin >> cinLogin;

	for (KontoKlienta konto : listaKont)
	{
		if (konto.login == cinLogin)
		{
			*aktualnyKlient = konto;
			czyIstnieje = 1;
			break;
		}
	}

	if (czyIstnieje)
	{
		while (aktualnyKlient->haslo != cinHaslo)
		{
			std::cout << "Haslo: ";
			std::cin >> cinHaslo;
			if (aktualnyKlient->haslo == cinHaslo) return 1;
			else
			{
				std::cout << "Niepoprawne haslo!;"; _getch();
			}
		}
	}
	else
	{
		std::cout << "Nie odnaleziono loginu!"; _getch();
		return 0;
	}
}

void wyswietlKlientow(Bank *bank)
{
	system("cls");
	for (KontoKlienta aktualny : bank->listaKontKlientow)
	{
		aktualny.wyswietlDane();
		std::cout << "\n\n";
	}
}

std::string ustawLogin(std::list<KontoKlienta> listaKont)
{
	std::string wyborLogin;
	bool czyWolny = 0;
	do
	{
		system("cls");
		std::cout << "--------------------\n| ";
		std::cout << "Login: ";
		std::cin >> wyborLogin;

		czyWolny = czyWolnyLogin(listaKont, wyborLogin);

		if (!czyWolny)
		{
			std::cout << "| Login zajety!";
			_getch();
		}
	} while (!czyWolny || wyborLogin.length() < 2);

	return wyborLogin;
}

std::string ustawHaslo()
{
	std::string wyborHaslo;
	std::string powtorzHaslo;

	do {
		system("cls");
		std::cout << "--------------------\n| ";
		std::cout << "Haslo: ";
		std::cin.ignore();
		std::cin >> wyborHaslo;

		std::cout << "--------------------\n| ";
		std::cout << "Powtorz haslo: ";
		std::cin >> powtorzHaslo;

		if (wyborHaslo != powtorzHaslo)
		{
			system("cls");
			std::cout << "| Podane hasla roznia sie :c";
			_getch();
		}
	} while (wyborHaslo != powtorzHaslo);

	return wyborHaslo;
}

bool czyWolnyLogin(std::list<KontoKlienta> listaKont, std::string newLogin)
{
	bool czyWolny = 1;
	for (KontoKlienta konto : listaKont)
	{
		if (konto.login==newLogin)
		{
			czyWolny = 0;
			break;
		}
	}

	return czyWolny;
}

int getListaKlientow(Bank *bank)
{
	std::ifstream* plikListaKlientow = new std::ifstream;
	plikListaKlientow->open("listaKlientow.txt");

	int iloscKlientow = 0;
	if (plikListaKlientow->is_open())
	{
		*plikListaKlientow >> iloscKlientow;

		for (int i = 0; i < iloscKlientow; i++)
		{
			wczytajKlienta(bank, plikListaKlientow);
		}
	}

	plikListaKlientow->close();
	delete plikListaKlientow;

	return iloscKlientow;
}

void setListaKlientow(int *iloscKlientow, Bank *bank)
{
	std::ofstream* plikListaKlientow = new std::ofstream;
	plikListaKlientow->open("listaKlientow.txt");

	if (plikListaKlientow->is_open())
	{
		*plikListaKlientow << *iloscKlientow << std::endl;

		for (int i = 0; i < *iloscKlientow; i++)
		{
			zapiszKlienta(bank, plikListaKlientow);
			bank->listaKontKlientow.pop_front();
		}
	}

	*iloscKlientow = getListaKlientow(bank);

	plikListaKlientow->close();
	delete plikListaKlientow;
}

void wczytajKlienta(Bank *bank, std::ifstream *plik)
{
	std::string new_imie;
	std::string new_nazwisko;
	std::string new_adres;
	std::string new_mail;
	std::string new_login;
	std::string new_haslo;
	int new_numerKonta;

	*plik >> new_numerKonta;
	*plik >> new_login;
	*plik >> new_haslo;
	*plik >> new_imie;
	*plik >> new_nazwisko;
	plik->ignore();
	std::getline(*plik, new_adres);
	*plik >> new_mail;

	KontoKlienta* nowy = new KontoKlienta(new_imie, new_nazwisko, new_adres, new_mail, new_login, new_haslo, new_numerKonta);
	bank->listaKontKlientow.push_back(*nowy);
	delete nowy;
}

void zapiszKlienta(Bank* bank, std::ofstream* plik)
{
	*plik << bank->listaKontKlientow.front().numerKonta;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().login;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().haslo;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().imie;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().nazwisko;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().adres;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().mail;
	*plik << std::endl;
}


int menu::start()
{
	int menuWybor;
	system("cls");

	std::cout << "--------------------\n"
		<< "BANK\n"
		<< "1. Zaloguj sie\n"
		<< "2. Zarejestruj sie\n"
		<< "3. Wyjdz\n"
		<< "--------------------\n";

	std::cin >> menuWybor;

	return menuWybor;
}