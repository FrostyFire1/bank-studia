#include <iostream>
#include <string>
#include "klient.h"

Klient::Klient(std::string new_imie, std::string new_nazwisko, std::string new_adres, std::string new_mail)
{
	imie = new_imie;
	nazwisko = new_nazwisko;
	adres = new_adres;
	mail = new_mail;
}

Klient::~Klient() {}

void Klient::wyswietlDane()
{
	std::cout << imie << " " << nazwisko << "\n" << adres << "\n" << mail << " \n";
}

KontoKlienta::KontoKlienta(std::string newLogin)
{
	login = newLogin;
}

KontoKlienta::~KontoKlienta()
{

}

