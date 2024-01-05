#pragma once
#include <iostream>
#include <conio.h>
#include <list>
#include "klient.h"

class Bank
{
public:
	Bank();
	~Bank();
	void dodajKlienta();
	void wyswietlKlientow();
	void usunKlienta();

private:
	int okresWeryfikacji = 100;
	std::list<Klient> listaKlientow;
};

