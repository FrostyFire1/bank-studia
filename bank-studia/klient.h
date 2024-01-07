#pragma once
#include <list>

class Konto
{
	friend class Bank;
	friend bool czyWolnyLogin(std::list<Konto>, std::string);
public:
	Konto(std::string);
	Konto(std::string, std::string, std::string, std::string);
	~Konto();
	void wyswietlDane();

protected:
	std::string login;

private:
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
	int numerKonta = 0;
	std::string haslo;
};