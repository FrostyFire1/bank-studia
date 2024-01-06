#pragma once
#include <iostream>
#include <conio.h>
#include <list>
#include "klient.h"

class Bank
{
public:
	std::list<KontoKlienta> listaKontKlientow;

	Bank();
	~Bank();
	void dodajKlienta();
	void wyswietlKlientow();
	void usunKlienta();
	bool czyWolnyLogin(std::string);

private:
	int okresWeryfikacji = 100;
	std::list<KontoKlienta> listaKlientow;

	void ustawLogin();
};

