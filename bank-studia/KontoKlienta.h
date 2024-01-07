#pragma once
#include <string>
#include <list>
#include "KontoBankowe.h"
#include "Lokata.h"


class KontoKlienta {

private:
	std::list<Lokata> lokaty;

public:
	KontoKlienta();
	~KontoKlienta();
	void dodajKontoBankowe();
	void usunKontoBankowe(std::string);
	bool dodajLokate();
	bool usunLokate();
	std::string generujNumerKonta();
	bool sprawdzNumerKontaBankowego(std::list<KontoBankowe>,std::string);
	std::list<KontoBankowe> listaKontBankowe;
};

bool czyWolnyLoginBankowy(std::list<KontoBankowe>,std::string);
void wyswietlKontaBankowe(KontoKlienta);
std::string ustawLoginBankowy(std::list<KontoBankowe>);



