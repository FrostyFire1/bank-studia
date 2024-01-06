#pragma once

class KontoKlienta
{
public:
	std::string login;
	KontoKlienta(std::string);
	KontoKlienta(std::string, std::string, std::string, std::string);
	~KontoKlienta();
	void wyswietlDane();

protected:


private:
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
	int numerKonta = 0;
	std::string haslo;
};