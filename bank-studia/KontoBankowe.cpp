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
	this->waluta = Waluta("PLN", 1.0);

}

KontoBankowe::KontoBankowe(std::string new_nrKonta, RodzajKonta new_rodzajKonta,double new_srodki)
{
	numerKonta = new_nrKonta;
	rodzaj = new_rodzajKonta;
	srodki = new_srodki;
	this->waluta = Waluta("PLN", 1.0);

}
KontoBankowe::KontoBankowe()
{
	numerKonta = "00000000000000000000000000";
	rodzaj = RODZAJ_KONTO_OSZCZEDNOSCIOWE;
	srodki = 0.0;
	this->waluta = Waluta("PLN", 1.0);
}


KontoBankowe::~KontoBankowe()
{
}


//funckja do wyswietlania danych konta
void KontoBankowe::wyswietlDane()
{
	std::cout <<"Nr konta bankowego: "<<numerKonta<<"\n Rodzaj konta: "<< wyswietlRodzajKontaBankowego(rodzaj)<<"\nŚrodki: "<<srodki;
}

//gettery i settery
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
void KontoBankowe::setSrodki(double srodki) {
	this->srodki = srodki;
}
Waluta KontoBankowe::getWaluta() {
	return this->waluta;
}
std::vector<Blokada>* KontoBankowe::getBlokady() {
	return &(this->blokady);
}
std::list<Przelew>* KontoBankowe::getPrzelewy() {
	return &(this->przelewy);
}

//funkcja tworzaca przelew
void KontoBankowe::utworzPrzelew(std::string adresat, double kwota, RodzajPrzelewu rodzajPrzelewu, std::string opis, int okres = 0, Waluta waluta = Waluta("PLN", 1.0)) {
	Przelew result = Przelew();
	result.nadawca = this->numerKonta;
	result.adresat = adresat;
	result.kwota = kwota;
	result.rodzajPrzelewu = rodzajPrzelewu;
	result.opis = opis;
	if (rodzajPrzelewu == RodzajPrzelewu::WALUTOWY) result.waluta = waluta;
	else result.waluta = this->waluta;
	result.timestamp = 0;
	result.ostatnieRozliczenie = result.timestamp;
	if (rodzajPrzelewu == RodzajPrzelewu::OKRESOWY) result.okres = okres;
	else result.okres = 0;

	przelewy.push_back(result);
	Blokada blokada = Blokada();
	blokada.idPrzelewu = result.idPrzelewu;
	blokada.numerBlokujacego = result.adresat;

	double toTake = (result.waluta.przelicznik / this->waluta.przelicznik) * result.kwota;
	blokada.srodki = toTake;
	blokady.push_back(blokada);

	this->srodki -= toTake;
}

//funkcja ktora zmiania wartosc aenuma na string
std::string wyswietlRodzajKontaBankowego(RodzajKonta rodzaj)
{
	{
		switch (rodzaj)
		{
		case RODZAJ_KONTO_OSZCZEDNOSCIOWE:
			return "Konto oszczednosciowe";
			break;
		case RODZAJ_KONTO_ROZLICZENIOWE:
			return "Konto rozliczeniowe";
			break;
		case RODZAJ_KONTO_WALUTOWE:
			return "Konto walutowe";
			break;
		default:
			return "brak loakty";
			break;
		}
	}
}

KontoBankowe get(std::list<KontoBankowe> _list, int _i) {
	std::list<KontoBankowe>::iterator it = _list.begin();
	for (int i = 0; i < _i; i++) {
		++it;
	}
	if (_i == 1) return _list.front();
	else return _list.back();
}