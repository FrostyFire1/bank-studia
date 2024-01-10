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
	void dodajKlienta(int*);
	void usunKlienta(KontoKlienta*, int*);

	bool Logowanie(KontoKlienta*);
	bool weryfikacjaTozsamosci(KontoKlienta*);
	std::list<KontoBankowe*> wszystkieKontaBankowe();
	void przetworzPrzelewy();
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
	void kontoBankowe(KontoKlienta*, Bank*);
	void lokata(KontoKlienta*, Bank*);
}