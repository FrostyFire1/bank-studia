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
	bool Logowanie(std::list<KontoKlienta>, KontoKlienta*);

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
std::string getHaslo(bool);

namespace menu
{
	int start();
	int main(KontoKlienta*);
	int zarzadzanie(KontoKlienta*);
}