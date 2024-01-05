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


KontoKlienta::KontoKlienta(){

}
KontoKlienta::~KontoKlienta()
{

}

