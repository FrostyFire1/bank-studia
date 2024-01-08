#pragma once
#include <list>
#include "Blokada.h"
#include "RodzajKonta.h"

class KontoBankowe {
	friend class KontoKlienta;
private:
	double srodki;
	std::list<Blokada> blokady;
protected:
	RodzajKonta rodzaj;
	std::string numerKonta;


public:
	KontoBankowe(std::string,RodzajKonta );
	~KontoBankowe();
	void wyswietlDane();

};
