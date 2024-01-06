#include <iostream>
#include <string>
#include "klient.h"

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

KontoKlienta::~KontoKlienta() {}

void KontoKlienta::wyswietlDane()
{
	std::cout << imie << " " << nazwisko << "\n" << adres << "\n" << mail << " \n";
}


