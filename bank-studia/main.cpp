#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include "KontoKlienta.h"
#include "KontoBankowe.h"
#include "Bank.h"
#include "Lokata.h"

int main()
{

	std::cout << "BANK\n";
	Bank bank;
	KontoKlienta klient;
	Lokata lokata;

	bank.dodajKlienta();
	wyswietlKlientow(bank);

	klient.dodajKontoBankowe(bank);
	wyswietlKontaBankowe(klient);


	_getch();
	klient.dodajLokate(bank);
	wyswietlLokaty(klient);

	_getch();
	std::cout << "Podaj numer konta do usuniecia: ";
	std::string test2;
	std::cin >> test2;
	_getch();
	klient.usunLokate(test2);
	wyswietlLokaty(klient);
	_getch();

	return 0;
}