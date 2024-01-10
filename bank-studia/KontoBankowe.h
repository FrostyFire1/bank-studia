#pragma once
#include <list>
#include <vector>
#include "Blokada.h"
#include "RodzajKonta.h"
#include "Przelew.h"
class KontoBankowe {
	friend class KontaKlienta;
	friend class KontoKlienta;
private:
	double srodki;
	std::vector<Blokada> blokady;
	std::list<Przelew> przelewy;
	Waluta waluta;
protected:
	RodzajKonta rodzaj;
	std::string numerKonta;


public:
	KontoBankowe(std::string,RodzajKonta );
	KontoBankowe(std::string, RodzajKonta,double);
	KontoBankowe();
	~KontoBankowe();
	void wyswietlDane();
	RodzajKonta getTypKontaBankowego();
	std::string getNrKontaBankowego();
	std::vector<Blokada>* getBlokady();
	std::list<Przelew>* getPrzelewy();
	double getSrodki();
	Waluta getWaluta();
	void setSrodki(double);
	void utworzPrzelew(std::string, double, RodzajPrzelewu, std::string, int, Waluta);


};
