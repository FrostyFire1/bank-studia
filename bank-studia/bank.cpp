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

void Bank::dodajKlienta(int *iloscKlientow)
{
	std::string new_imie;
	std::string new_nazwisko;
	std::string new_adres;
	std::string new_mail;
	std::string new_login;
	std::string new_haslo;
	
	system("cls");
	std::cout << "Imie: ";
	std::getline(std::cin, new_imie);
	std::cout << "Nazwisko: ";
	std::getline(std::cin, new_nazwisko);
	std::cout << "Adres zamieszkania: ";
	std::getline(std::cin, new_adres);
	std::cout << "Adres Email: ";
	std::getline(std::cin, new_mail);

	KontoKlienta *nowy = new KontoKlienta(new_imie, new_nazwisko, new_adres, new_mail);
	listaKontKlientow.push_front(*nowy);
	delete nowy;

	new_login = ustawLogin(listaKontKlientow);
	listaKontKlientow.front().login = new_login;

	new_haslo = ustawHaslo();
	listaKontKlientow.front().haslo = new_haslo;

	listaKontKlientow.front().numerKonta = *iloscKlientow;

	(*iloscKlientow)++;
}

void Bank::usunKlienta()
{
	//confirm passwort


}

void wyswietlKlientow(Bank bank)
{
	system("cls");
	for (KontoKlienta aktualny : bank.listaKontKlientow)
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
		std::cout << "Login: ";
		std::getline(std::cin, wyborLogin);

		czyWolny = czyWolnyLogin(listaKont, wyborLogin);

		if (!czyWolny)
		{
			std::cout << "Login zajety!";
			_getch();
		}
	} while (!czyWolny && wyborLogin.length() < 4);

	return wyborLogin;
}

std::string ustawHaslo()
{
	std::string wyborHaslo;
	std::string powtorzHaslo;

	do {
		system("cls");
		std::cout << "Haslo: ";
		std::getline(std::cin, wyborHaslo);

		system("cls");
		std::cout << "Powtorz haslo: ";
		std::getline(std::cin, powtorzHaslo);

		if (wyborHaslo != powtorzHaslo)
		{
			system("cls");
			std::cout << "Podane hasla roznia sie :c";
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

int getIloscKlientow()
{
	std::ifstream plilkListaKlientow;
	plilkListaKlientow.open("listaKlientow.txt");

	int iloscKlientow = 0;
	if(plilkListaKlientow.is_open()) plilkListaKlientow >> iloscKlientow;
	plilkListaKlientow.close();

	return iloscKlientow;
}

void setIloscKlientow(int *iloscKlientow)
{
	std::ofstream plilkListaKlientow;
	plilkListaKlientow.open("listaKlientow.txt");

	if (plilkListaKlientow.is_open()) plilkListaKlientow << *iloscKlientow;
	plilkListaKlientow.close();

	delete iloscKlientow;
}