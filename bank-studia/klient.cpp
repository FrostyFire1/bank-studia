#include <iostream>
#include <string>
#include "klient.h"

KontoKlienta::KontoKlienta() {};

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

KontoKlienta::KontoKlienta(std::string new_imie, std::string new_nazwisko, std::string new_adres, std::string new_mail, std::string new_login, std::string new_haslo, int new_numerKonta)
{
	imie = new_imie;
	nazwisko = new_nazwisko;
	adres = new_adres;
	mail = new_mail;
	login = new_login;
	haslo = new_haslo;
	numerKonta = new_numerKonta;
}

KontoKlienta::~KontoKlienta() {}

void KontoKlienta::wyswietlDane()
{
	std::cout << imie << " " 
			  << nazwisko << "\n"
			  << adres << "\n"
			  << mail << " \n"
			  << login << " "
			  << haslo << "\n"
			  << numerKonta;
}

std::string KontoKlienta::getLogin()
{
	return login;
}

std::string KontoKlienta::getImie()
{
	return imie;
}

std::string KontoKlienta::getNazwisko()
{
	return nazwisko;
}

std::string KontoKlienta::getMail()
{
	return mail;
}

std::string KontoKlienta::getAdres()
{
	return adres;
}

int KontoKlienta::getNumerKonta()
{
	return numerKonta;
}


