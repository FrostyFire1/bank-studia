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

void Bank::dodajKlienta()
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

	Konto *nowy = new Konto(new_imie, new_nazwisko, new_adres, new_mail);
	listaKontKlientow.push_front(*nowy);
	delete nowy;

	new_login = ustawLogin(listaKontKlientow);
	listaKontKlientow.front().login = new_login;

	new_haslo = ustawHaslo();
	listaKontKlientow.front().haslo = new_haslo;

	int number = static_cast<int>(new_imie[0]);
	number += 10 * static_cast<int>(new_imie[1]);
	number += 100 * static_cast<int>(new_imie[2]);
	number += 1000 * static_cast<int>(new_imie[3]);
	listaKontKlientow.front().numerKonta = number;
}

void Bank::usunKlienta()
{
}
bool Bank::logowanie()
{
	std::string login;
	std::string haslo;
	std::list<Konto>::iterator it;
	bool czyZalogowany = false;
	int proba = 0;
	do
	{
		system("cls");
		std::cout << "Login: ";
		std::getline(std::cin, login);
		std::cout << "Haslo: ";
		std::getline(std::cin, haslo);

		for (it = listaKontKlientow.begin(); it != listaKontKlientow.end(); it++)
		{
			if (it->login == login && it->haslo == haslo)
			{
				czyZalogowany = true;
				break;
			}
		}
		if (!czyZalogowany)
		{
			std::cout << "Niepoprawne dane logowania!";
			_getch();
			proba++;
		}
	} while (!czyZalogowany && proba < 3);

	return czyZalogowany;
}

void wyswietlKlientow(Bank bank)
{
	system("cls");
	for (Konto aktualny : bank.listaKontKlientow)
	{
		aktualny.wyswietlDane();
		std::cout << "\n\n";
	}
}

std::string ustawLogin(std::list<Konto> listaKont)
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

bool czyWolnyLogin(std::list<Konto> listaKont, std::string newLogin)
{
	bool czyWolny = 1;
	for (Konto konto : listaKont)
	{
		if (konto.login==newLogin)
		{
			czyWolny = 0;
			break;
		}
	}

	return czyWolny;
}
