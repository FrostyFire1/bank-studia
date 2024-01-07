#include "KontoKlienta.h"
#include <iostream>
#include <conio.h>
#include "bank.h"
#include <math.h>
#include <algorithm>




KontoKlienta::KontoKlienta() {


}
KontoKlienta::~KontoKlienta() {

}

void KontoKlienta::dodajKontoBankowe() {
	std::string login;
	std::string haslo;
	login = ustawLoginBankowy(listaKontBankowe);
	haslo = ustawHaslo();
	std::string nrKonta = generujNumerKonta();
	std::cout << nrKonta;
	KontoBankowe* nowy = new KontoBankowe(login, haslo, nrKonta);
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

bool KontoKlienta::dodajLokate() {
	return 1;
}
bool KontoKlienta::usunLokate() {
	return 1;


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
std::string KontoKlienta::generujNumerKonta()
{
	std::string numerKonta;
	srand(time(NULL));
	bool test = false;

	do {
		std::string temp;
		int testNumeru;
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
std::string ustawLoginBankowy(std::list<KontoBankowe> listaKont)
{
	std::string wyborLogin;
	bool czyWolny = false;
	do
	{
		system("cls");
		std::cout << "Login: ";
		std::getline(std::cin, wyborLogin);

		czyWolny = czyWolnyLoginBankowy(listaKont, wyborLogin);

		if (!czyWolny)
		{
			std::cout << "Login zajety!";
			_getch();
		}
	} while (!czyWolny && wyborLogin.length() < 4);

	return wyborLogin;
}
bool czyWolnyLoginBankowy(std::list<KontoBankowe> listaKont, std::string newLogin)
{
	bool czyWolny = true;
	for (KontoBankowe konto : listaKont)
	{
		if (konto.login == newLogin)
		{
			czyWolny = false;
			break;
		}
	}

	return czyWolny;
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

