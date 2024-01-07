#include "KontoKlienta.h"
#include <conio.h>
#include "KontoBankowe.h"
#include <iostream>

int main()
{
	std::cout << "BANK\n";
	KontoKlienta klient;

	klient.dodajKontoBankowe();
	wyswietlKontaBankowe(klient);

	_getch();
	klient.dodajKontoBankowe();
	wyswietlKontaBankowe(klient);

	_getch();
	std::string test;
	std::cout << "Podaj numer konta do usuniecia: \n";
	std::getline(std::cin, test);
	klient.usunKontoBankowe(test);
	wyswietlKontaBankowe(klient);

	return 0;
}