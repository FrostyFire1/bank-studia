#include "bank.h"

int main()
{
	Bank *bank = new Bank;
	KontoKlienta* aktualnyKlient = new KontoKlienta;
	int* iloscKlientow = new int;
	*iloscKlientow = getListaKlientow(bank);

	int  menuWybor = 0;

	while (menuWybor>=0)
	{
		switch (menuWybor)
		{
		case 0:
			menuWybor = menu::start();
			break;

		case 1:
			if (bank->weryfikacjaTozsamosc(bank->listaKontKlientow, aktualnyKlient))
			{
				std::cout << "Zalogowano do konta: " << aktualnyKlient->getLogin(); _getch();
				menuWybor = 0;
			}
			else
			{
				menuWybor = 0;
			}
			break;

		case 2:
			bank->dodajKlienta(iloscKlientow, bank);
			menuWybor = 0;
			break;

		default:
			menuWybor = -1;
			break;
		}
	}

	delete aktualnyKlient;
	delete bank;

	return 0;
}