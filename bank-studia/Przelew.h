#pragma once
#include <iostream>
#include "Waluta.h"
#include "RodzajPrzelewu.h"
class Przelew {
public:
	double kwota;
	std::string opis;
	RodzajPrzelewu rodzajPrzelewu;
	std::string nadawca, adresat;
	int timestamp;
	Waluta waluta;
	int idPrzelewu;
	int okres;
	int ostatnieRozliczenie;
	Przelew();
	Przelew(double, std::string, RodzajPrzelewu, std::string, std::string, int, Waluta, int, int, int);
};