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
	void dodajKlienta(int*, Bank*);
	void usunKlienta();

protected:

private:
	int okresWeryfikacji = 100;
};

std::string ustawLogin(std::list<KontoKlienta>);
std::string ustawHaslo();
bool czyWolnyLogin(std::list<KontoKlienta>, std::string);
void wyswietlKlientow(Bank*);
int getListaKlientow(Bank*);
void setListaKlientow(int*, Bank*);
void wczytajKlienta(Bank*, std::ifstream*);
void zapiszKlienta(Bank*, std::ofstream*);


namespace menu
{
	int start();
}