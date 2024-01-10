#include <iostream>
#include <string>
#include <conio.h>
#include "KontoBankowe.h"
#include "RodzajKonta.h"


KontoBankowe::KontoBankowe(std::string new_nrKonta, RodzajKonta new_rodzajKonta)
{
	numerKonta = new_nrKonta;
	rodzaj = new_rodzajKonta;
	srodki=0.0;
}

KontoBankowe::KontoBankowe(std::string new_nrKonta, RodzajKonta new_rodzajKonta,double new_srodki)
{
	numerKonta = new_nrKonta;
	rodzaj = new_rodzajKonta;
	srodki = new_srodki;
}
KontoBankowe::KontoBankowe()
{
	numerKonta = "00000000000000000000000000";
	rodzaj = RODZAJ_KONTO_OSZCZEDNOSCIOWE;
	srodki = 0.0;
}


KontoBankowe::~KontoBankowe()
{
}

void KontoBankowe::wyswietlDane()
{
	std::cout <<"Nr konta bankowego: "<<numerKonta<<"\n Rodzaj konta: "<< wyswietlRodzajKontaBankowego(rodzaj);
	_getch();
}

RodzajKonta KontoBankowe::getTypKontaBankowego()
{
	return rodzaj;
}

std::string KontoBankowe::getNrKontaBankowego()
{
	return numerKonta;
}
double KontoBankowe::getSrodki()
{
	return srodki;
}


std::string wyswietlRodzajKontaBankowego(RodzajKonta konto)
{
	switch (konto)
	{
	case RODZAJ_KONTO_OSZCZEDNOSCIOWE:
		return "Konto Oszczednosciowe";
		break;
	case RODZAJ_KONTO_ROZLICZENIOWE:
		return "Konto Rozliczeniowe";
		break;
	case RODZAJ_KONTO_WALUTOWE:
		return "Konto Walutowe";
		break;
	default:
		return "Nieznany rodzaj konta";
		break;
	}

}
