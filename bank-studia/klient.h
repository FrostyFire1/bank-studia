#pragma once

class Klient
{
public:
	Klient(std::string, std::string, std::string, std::string);
	~Klient();
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
private:
	int numerKonta = 0;
	std::string login;
	std::string haslo;

	KontoKlienta();
	~KontoKlienta();
};
