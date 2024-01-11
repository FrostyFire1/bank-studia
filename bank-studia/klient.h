#pragma once
#include <list>
#include "KontoBankowe.h"
#include "bank.h"
#include "Lokata.h"

class KontoKlienta
{
	friend class Bank;
	friend class KontoBankowe;
	friend class Lokata;
	friend bool czyWolnyLogin(std::list<KontoKlienta>, std::string);
	friend void zapiszKlienta(Bank*, std::ofstream*);
	friend void zapiszKlienta(KontoKlienta*, std::ofstream*);
public:
	std::list<Lokata> listaLokat;
	std::list<KontoBankowe> listaKontBankowe;
	KontoKlienta();
	KontoKlienta(std::string);
	KontoKlienta(std::string, std::string, std::string, std::string);
	KontoKlienta(std::string, std::string, std::string, std::string, std::string, std::string, int);
	~KontoKlienta();
	bool operator==(KontoKlienta);

	void wyswietlDane();

	std::string getLogin();
	std::string getHaslo();
	std::string getImie();
	std::string getNazwisko();
	std::string getMail();
	std::string getAdres();
	std::list<KontoBankowe> getListaKontBankowych();
	std::list<Lokata> getListaLokat();
	int getNumerKonta();

	void setLogin(std::string);
	void setImie(std::string);
	void setNazwisko(std::string);
	void setMail(std::string);
	void setAdres(std::string);

	void dodajKontoBankowe(KontoKlienta*,Bank*);
	void usunKontoBankowe(KontoKlienta*, Bank* ,std::string);

	void dodajLokate(KontoKlienta*, Bank*);
	void usunLokate(KontoKlienta* , Bank* , std::string);

	void wyswietlKontaBankowe(KontoKlienta);
	void wyswietlLokaty(KontoKlienta);

	void wczytajKontaBankoweZPliku( std::string);
	void wczytajLokatyZPliku( std::string);

protected:
	std::string login;
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
	int numerKonta = 0;
	std::string haslo;
private:


	void usunKontoBankoweZPliku( std::string,std::string);
	void usunLokateZPliku( std::string,std::string);

};

void zapiszKontoBankoweDoPliku(KontoBankowe*, std::string);
void zapiszLokateDoPliku(Lokata*, std::string);
void aktualizacjaKontaBankowego(KontoBankowe*, std::list<KontoBankowe>, std::string);
void aktualizacjaLokaty(Lokata*, std::list<Lokata>, std::string);
std::string generujNumerKonta(KontoKlienta*);
bool sprawdzNumerKontaBankowego(std::list<KontoBankowe>, std::list<Lokata>,std::string);
RodzajKonta menuWyboruKonta();
RodzajLokaty menuWyboruLokaty();
RodzajCzasuLokaty menuWyboruCzasuLokaty();
