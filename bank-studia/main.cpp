#include "bank.h"

int main()
{
	std::cout << "BANK\n";

	Bank bank;
	int* iloscKlientow = new int;
	*iloscKlientow = getIloscKlientow();

	bank.dodajKlienta(iloscKlientow);
	wyswietlKlientow(bank);

	_getch();
	bank.dodajKlienta(iloscKlientow);
	wyswietlKlientow(bank);

	_getch();
	bank.dodajKlienta(iloscKlientow);
	wyswietlKlientow(bank);

	setIloscKlientow(iloscKlientow);

	return 0;
}