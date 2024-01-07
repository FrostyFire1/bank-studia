#include "bank.h"

int main()
{
	std::cout << "BANK\n";

	Bank *bank = new Bank;
	int* iloscKlientow = new int;
	*iloscKlientow = getIloscKlientow(bank);

	wyswietlKlientow(bank);
	_getch();

	bank->dodajKlienta(iloscKlientow);
	wyswietlKlientow(bank);

	_getch();
	bank->dodajKlienta(iloscKlientow);
	wyswietlKlientow(bank);

	delete bank;

	return 0;
}