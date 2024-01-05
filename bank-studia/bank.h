#pragma once
#include <iostream>
#include <conio.h>
#include <list>
#include "klient.h"

class Bank
{
public:

private:
	int okresWeryfikacji = 100;
	std::list<Klient> listaKlientow;

	Bank();

	~Bank();

	void dodajKlienta();

	void usunKlienta();
};

