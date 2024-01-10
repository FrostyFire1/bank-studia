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
bool czyWolnyLogin(std::list<KontoKlienta>, std::string);
void wyswietlKlientow(Bank*);
int getListaKlientow(Bank*);
void setListaKlientow(int*, Bank*);
void wczytajKlienta(Bank*, std::ifstream*);
void zapiszKlienta(Bank*, std::ofstream*);
void zapiszKlienta(KontoKlienta, std::ofstream*);
std::string getHaslo(bool);

namespace menu
{
	int start();
	void main(KontoKlienta*, Bank*, int*);
	void zarzadzanie(KontoKlienta*, Bank*, int*);
}