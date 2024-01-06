#include "bank.h"

int main()
{
	std::cout << "BANK\n";

	Bank bank;

	bank.dodajKlienta();
	wyswietlKlientow(bank);

	_getch();
	bank.dodajKlienta();
	wyswietlKlientow(bank);

	_getch();
	bank.dodajKlienta();
	wyswietlKlientow(bank);


	return 0;
}