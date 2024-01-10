#pragma once
#include <list>
#include "Blokada.h"
#include "RodzajKonta.h"

class KontoBankowe {
	friend class KontaKlienta;
	friend class KontoKlienta;
private:
	double srodki;
	std::list<Blokada> blokady;
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


};
