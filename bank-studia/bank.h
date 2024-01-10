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
	void usunKlienta(KontoKlienta*, Bank*, int*);

	bool Logowanie(std::list<KontoKlienta>, KontoKlienta*);
	bool weryfikacjaTozsamosci(KontoKlienta*);

protected:

private:
	int okresWeryfikacji = 100;
};

std::string ustawLogin(std::list<KontoKlienta>);
std::string ustawHaslo();
std::string getHaslo(bool);
bool czyWolnyLogin(std::list<KontoKlienta>, std::string);

int getListaKlientow(Bank*);
void setListaKlientow(int*, Bank*);

int znajdzKlienta(Bank*, KontoKlienta*);
void updateListaKlientow(int*, Bank*, KontoKlienta*, int);

void wczytajKlienta(Bank*, std::ifstream*);
void zapiszKlienta(Bank*, std::ofstream*);
void zapiszKlienta(KontoKlienta, std::ofstream*);

namespace menu
{
	int start();
	void main(KontoKlienta*, Bank*, int*);
	void zarzadzanie(KontoKlienta*, Bank*, int*);
}