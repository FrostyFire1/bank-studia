#include "bank.h"

int main()
{
	Bank* bank = new Bank;
	KontoKlienta* aktualnyKlient = new KontoKlienta;
	int* iloscKlientow = new int;

	*iloscKlientow = getListaKlientow(bank);

	int  menuWybor = 0;

	while (menuWybor >= 0)
	{
		switch (menuWybor)
		{
		case 0: //glowne menu przed zalogowaniem
			menuWybor = menu::start();
			break;

		case 1: // logowanie do konta klienta
			if (bank->Logowanie(aktualnyKlient))
			{	//pomyslne zalogowanie sie do konta
				std::cout << "Zalogowano do konta: " << aktualnyKlient->getLogin(); _getch();
				//załadowanie kont bankowych z pliku
				menu::main(aktualnyKlient, bank, iloscKlientow);
			}

			menuWybor = 0;
			break;

		case 2: // dodanie konta klienta
			bank->dodajKlienta(iloscKlientow);
			menuWybor = 0;
			break;

		case 3:
			menuWybor = -1;
			break;

		default:
			menuWybor = 0;
			break;
		}
	}

	delete aktualnyKlient;
	delete bank;

	return 0;
}