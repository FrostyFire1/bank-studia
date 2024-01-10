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

	void wczytajKontaBankoweZPliku(KontoKlienta*, std::string);
	void wczytajLokatyZPliku(KontoKlienta*, std::string);

protected:
	std::string login;
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
	int numerKonta = 0;
	std::string haslo;



private:



	std::string generujNumerKonta();
	bool sprawdzNumerKontaBankowego(std::list<KontoBankowe>, std::string);

	RodzajKonta menuWyboruKonta();
	void wyswietlMenuWyboruKonta(int aktualnaOpcja);
	RodzajKonta wybierzTypKonta();

	RodzajLokaty menuWyboruLokaty();
	void wyswietlMenuWyboruLokaty(int aktualnaOpcja);
	RodzajLokaty wybierzTypLokaty();

	RodzajCzasuLokaty menuWyboruCzasuLokaty();
	void wyswietlMenuWyboruCzasuLokaty(int aktualnaOpcja);
	RodzajCzasuLokaty wybierzTypCzasuLokaty();

	void zapiszKontoBankoweDoPliku(KontoBankowe*, std::string);
	void zapiszLokateDoPliku(Lokata*, std::string);





	void usunKontoBankoweZPliku(KontoKlienta*, std::string,std::string);
	void usunLokateZPliku(KontoKlienta*, std::string,std::string);

};