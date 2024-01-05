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
}

void Bank::usunKlienta()
{

}

void Bank::wyswietlKlientow()
{
	for (Klient aktualny : listaKlientow)
	{
		aktualny.wyswietlDane();
	}
}
