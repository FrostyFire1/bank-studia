#pragma once
#ifndef LOKATA_H
#define LOKATA_H
#include <list>
#include <ctime>
#include <string>
#include "RodzajLokaty.h"
#include "RodzajCzasuLokaty.h"


class Lokata {
	friend class KontaKlienta;
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
	Lokata(RodzajLokaty, RodzajCzasuLokaty, double,double, std::string,std::string,std::string);
	Lokata();
	void wyswietlDaneLokat();
	std::string Data(RodzajCzasuLokaty);

	RodzajLokaty getRodzajLokaty();
	RodzajCzasuLokaty getRodzajCzasuLokaty();
	double getSrodki();	
	std::string getNrLokaty();
	std::string getDataRozpoczecia();
	std::string getOstatnieNaliczenie();
	std::double_t getOprocentowanie();

};
std::string wyswietlRodzajLokaty(RodzajLokaty);
std::string wyswietlRodzajCzasuLokaty(RodzajCzasuLokaty);
double obliczOprocentowanie(RodzajLokaty, RodzajCzasuLokaty);
#endif 