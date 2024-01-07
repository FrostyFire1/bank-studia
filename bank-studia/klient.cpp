#include <iostream>
#include <string>
#include "klient.h"

Konto::Konto(std::string nowy_login)
{
	login = nowy_login;
}

Konto::Konto(std::string new_imie, std::string new_nazwisko, std::string new_adres, std::string new_mail)
{
	imie = new_imie;
	nazwisko = new_nazwisko;
	adres = new_adres;
	mail = new_mail;
}

Konto::~Konto() {}

void Konto::wyswietlDane()
{
	std::cout << imie << " " << nazwisko << "\n" << adres << "\n" << mail << " \n" << login << " " << haslo << "\n" << numerKonta;
}


