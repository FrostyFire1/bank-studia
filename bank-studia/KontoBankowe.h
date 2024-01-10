#pragma once
#include <list>
#include "Blokada.h"
#include "RodzajKonta.h"
#include "Przelew.h"
class KontoBankowe {
	friend class KontaKlienta;
	friend class KontoKlienta;
private:
	double srodki;
	std::list<Blokada> blokady;
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
	double getSrodki();
	Przelew utworzPrzelew(std::string, double, RodzajPrzelewu, std::string, int, Waluta);


};
