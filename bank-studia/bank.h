#pragma once
#include <iostream>
#include <conio.h>
#include <list>
#include "klient.h"

class Bank
{
public:
	std::list<Konto> listaKontKlientow;

	Bank();
	~Bank();
	void dodajKlienta();
	void usunKlienta();

protected:

private:
	int okresWeryfikacji = 100;
};

std::string ustawLogin(std::list<Konto>);
std::string ustawHaslo();
bool czyWolnyLogin(std::list<Konto>, std::string);
void wyswietlKlientow(Bank);

