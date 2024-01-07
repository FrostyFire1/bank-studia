#pragma once
#include <list>

class KontoKlienta
{
	friend class Bank;
	friend bool czyWolnyLogin(std::list<KontoKlienta>, std::string);
	friend void zapiszKlienta(Bank*, std::ofstream*);
public:
	KontoKlienta(std::string);
	KontoKlienta(std::string, std::string, std::string, std::string);
	KontoKlienta(std::string, std::string, std::string, std::string, std::string, std::string, int);
	~KontoKlienta();
	void wyswietlDane();

	

protected:
	std::string login;
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
	int numerKonta = 0;
	std::string haslo;

private:
};