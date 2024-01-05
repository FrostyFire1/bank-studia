#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <list>
#include "bank.h"

Bank::Bank()
{
	okresWeryfikacji = 100;
}

Bank::~Bank()
{

}

void Bank::dodajKlienta()
{
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
	
	system("cls");
	std::cout << "Imie: ";
	std::getline(std::cin, imie);
	std::cout << "Nazwisko: ";
	std::getline(std::cin, nazwisko);
	std::cout << "Adres zamieszkania: ";
	std::getline(std::cin, adres);
	std::cout << "Adres Email: ";
	std::getline(std::cin, mail);

	Klient *nowy = new Klient(imie, nazwisko, adres, mail);
	listaKlientow.push_back(*nowy);
	delete nowy;

	ustawLogin();


}

void Bank::usunKlienta()
{
	std::string confirmPassword;
	std::cout << "Haslo: ";
	std::getline(std::cin, confirmPassword);


}

void Bank::wyswietlKlientow()
{
	for (Klient aktualny : listaKlientow)
	{
		aktualny.wyswietlDane();
	}
}

void Bank::ustawLogin()
{
	std::string wyborLogin;
	bool czyWolny = 0;
	do
	{
		system("cls");
		std::cout << "Login: ";
		std::getline(std::cin, wyborLogin);

		czyWolny = czyWolnyLogin(wyborLogin);

		if (!czyWolny) std::cout << "Login zajety!";
	} while (!czyWolny);
}

bool Bank::czyWolnyLogin(std::string newLogin)
{
	bool czyWolny = 1;
	for (KontoKlienta konto : listaKontKlientow)
	{
		if (konto.login==newLogin)
		{
			czyWolny = 0;
			break;
		}
	}

	return czyWolny;
}
