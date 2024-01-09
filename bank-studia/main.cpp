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
		case 0: //glowne menu przed zalogowaniem
			menuWybor = menu::start();
			break;

		case 1: // logowanie do konta klienta
			if (bank->Logowanie(bank->listaKontKlientow, aktualnyKlient))
			{	//pomyslne zalogowanie sie do konta
				std::cout << "Zalogowano do konta: " << aktualnyKlient->getLogin(); _getch();
				menuWybor = 10;
			}
			else
			{	//niudane logowanie do konta
				menuWybor = 0;
			}
			break;

		case 2: // dodanie konta klienta
			bank->dodajKlienta(iloscKlientow, bank);
			menuWybor = 0;
			break;

		//----------------------------------------------
		//PO ZALOGOWANIU

		case 10: //glowne menu po zalogowaniu
			menuWybor = menu::main(aktualnyKlient);
			break;

		case 11:
			menuWybor = 10;
			break;

		case 12:
			menuWybor = 10;
			break;

		case 13: // menu zarzadzania kontem
			menuWybor = menu::zarzadzanie(aktualnyKlient);
			menuWybor = 10;
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