#pragma once
#ifndef LOKATA_H
#define LOKATA_H
#include <list>
#include <ctime>
#include <string>
#include "RodzajLokaty.h"
#include "RodzajCzasuLokaty.h"


class Lokata {
	friend class KontoKlienta;
private:
protected:
	RodzajLokaty rodzaj;
	RodzajCzasuLokaty okres;
	double srodki;
	double oprocentowanie;
	std::string nrLokaty;
	std::string dataRozpoczecia;
	std::string ostatnieNaliczenie;
public:
	Lokata(RodzajLokaty , RodzajCzasuLokaty ,double, std::string );
	Lokata();
	void wyswietlDaneLokat();
	std::string Data(RodzajCzasuLokaty);

};

#endif 