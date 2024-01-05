#pragma once

class Klient
{
public:
	Klient(std::string, std::string, std::string, std::string);
	~Klient();
	void wyswietlDane();
protected:
private:
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
};

class KontoKlienta
{
public:
	std::string login;
	KontoKlienta(std::string);
	~KontoKlienta();
	



private:
	int numerKonta = 0;
	std::string haslo;
};
