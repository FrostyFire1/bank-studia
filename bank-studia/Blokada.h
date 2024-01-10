#ifndef BLOKADA_H
#define BLOKADA_H
#include "Waluta.h"
class Blokada {

public:
	double kwota;
	Waluta waluta;
	std::string numerBlokujacego;
	int idPrzelewu;
};

#endif
