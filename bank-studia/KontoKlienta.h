#pragma once
#include <string>
#include <iostream>
#include <list>
#include "KontoBankowe.h"
#include "RodzajKonta.h"
#include "bank.h"
#include "Lokata.h"
#include "RodzajLokaty.h"
#include "RodzajCzasuLokaty.h"


class KontoKlienta {

private:

public:
	std::list<Lokata> listaLokat;
	std::list<KontoBankowe> listaKontBankowe;
	KontoKlienta();
	~KontoKlienta();
	void dodajKontoBankowe(Bank);
	void usunKontoBankowe(std::string);
	void dodajLokate(Bank bank);
	void usunLokate(std::string);
	std::string generujNumerKonta();
	bool sprawdzNumerKontaBankowego(std::list<KontoBankowe>,std::string);

};


void wyswietlKontaBankowe(KontoKlienta);
void wyswietlLokaty(KontoKlienta);

RodzajKonta menuWyboruKonta();
void wyswietlMenuWyboruKonta(int aktualnaOpcja);
RodzajKonta wybierzTypKonta();


RodzajLokaty menuWyboruLokaty();
void wyswietlMenuWyboruLokaty(int aktualnaOpcja);
RodzajLokaty wybierzTypLokaty();


RodzajCzasuLokaty menuWyboruCzasuLokaty();
void wyswietlMenuWyboruCzasuLokaty(int aktualnaOpcja);
RodzajCzasuLokaty wybierzTypCzasuLokaty();




