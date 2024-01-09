#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "bank.h"
#include "klient.h"

Bank::Bank()
{
	okresWeryfikacji = 10;
}

Bank::~Bank()
{

}

void Bank::dodajKlienta(int *iloscKlientow, Bank* bank)
{
	(*iloscKlientow)++;

	std::string new_imie;
	std::string new_nazwisko;
	std::string new_adres;
	std::string new_mail;
	std::string new_login;
	std::string new_haslo;
	int new_numer = listaKontKlientow.back().numerKonta +1;
	
	system("cls");
	std::cout << "| Imie: ";
	std::cin >> new_imie;
	std::cout << "| Nazwisko: ";
	std::cin >> new_nazwisko;
	std::cout << "| Adres zamieszkania: ";
	std::cin.ignore();
	std::getline(std::cin, new_adres);
	std::cout << "| Adres Email: ";
	std::cin >> new_mail;

	KontoKlienta *nowy = new KontoKlienta(new_imie, new_nazwisko, new_adres, new_mail);
	listaKontKlientow.push_back(*nowy);
	delete nowy;

	new_login = ustawLogin(listaKontKlientow);
	listaKontKlientow.back().login = new_login;
	new_haslo = ustawHaslo();
	listaKontKlientow.back().haslo = new_haslo;
	listaKontKlientow.back().numerKonta = new_numer;

	setListaKlientow(iloscKlientow, bank);

	std::cout << "| Utworzono konto"; _getch();
}

void Bank::usunKlienta(KontoKlienta* aktualnyKlient, Bank* bank, int* iloscKlientow)
{
	std::string zgoda;

	std::cout << "| Czy na pewno chcesz usunac swoje konto klienta?\n"
		<< "| Jest to akcja nieodwracalna!\n"
		<< "| [tak/nie]\n"
		<< "| >";

	std::cin >> zgoda;

	if (zgoda == "tak")
	{
		if (weryfikacjaTozsamosci(aktualnyKlient))
		{
			std::ofstream* plikListaKlientow = new std::ofstream;
			plikListaKlientow->open("listaKlientow.txt");

			if (plikListaKlientow->is_open())
			{
				*plikListaKlientow << ((*iloscKlientow)-1) << std::endl;

				for (int i = 1; i <= *iloscKlientow; i++)
				{
					if (i != aktualnyKlient->numerKonta)
					{
						zapiszKlienta(this, plikListaKlientow);
					}
					this->listaKontKlientow.pop_front();
				}
			}

			*iloscKlientow = getListaKlientow(bank);

			plikListaKlientow->close();
			delete plikListaKlientow;
		}
		else
		{
			std::cout << "| Niepoprawnie haslo!"; _getch();
		}
	}
}

bool Bank::Logowanie(std::list<KontoKlienta> listaKont, KontoKlienta *aktualnyKlient)
{
	std::string cinLogin;
	std::string cinHaslo;
	bool czyIstnieje = 0;

	system("cls");
	std::cout << "| Login: ";
	std::cin >> cinLogin;

	for (KontoKlienta konto : listaKont)
	{
		if (konto.login == cinLogin)
		{
			*aktualnyKlient = konto;
			czyIstnieje = 1;
			break;
		}
	}

	if (czyIstnieje)
	{
		while (aktualnyKlient->haslo != cinHaslo)
		{
			std::cout << "| Haslo: ";
			cinHaslo = getHaslo(1);
			if (aktualnyKlient->haslo == cinHaslo) return 1;
			else
			{
				std::cout << "| Niepoprawne haslo!"; _getch();
				system("cls");
				std::cout << "| Login: " << aktualnyKlient->login << "\n";
			}
		}
	}
	else
	{
		std::cout << "| Nie odnaleziono loginu!"; _getch();
		return 0;
	}
}

bool Bank::weryfikacjaTozsamosci(KontoKlienta* aktualnyKlient)
{
	std::string cinHaslo;

	std::cout << "\n| Haslo: ";
	cinHaslo = getHaslo(1);

	if (aktualnyKlient->haslo == cinHaslo) return 1;
	else return 0;
}

void wyswietlKlientow(Bank *bank)
{
	system("cls");
	for (KontoKlienta aktualny : bank->listaKontKlientow)
	{
		aktualny.wyswietlDane();
		std::cout << "\n\n";
	}
}

std::string ustawLogin(std::list<KontoKlienta> listaKont)
{
	std::string wyborLogin;
	bool czyWolny = 0;
	do
	{
		system("cls");
		std::cout << "--------------------\n| ";
		std::cout << "Login: ";
		std::cin >> wyborLogin;

		czyWolny = czyWolnyLogin(listaKont, wyborLogin);

		if (!czyWolny)
		{
			std::cout << "| Login zajety!";
			_getch();
		}
	} while (!czyWolny || wyborLogin.length() < 2);

	return wyborLogin;
}

std::string ustawHaslo()
{
	std::string wyborHaslo;
	std::string powtorzHaslo;

	do {
		system("cls");
		std::cout << "--------------------\n";
		std::cout << "| Haslo: ";
		wyborHaslo = getHaslo(1);

		std::cout << "--------------------\n";
		std::cout << "| Powtorz haslo: ";
		powtorzHaslo = getHaslo(1);

		if (wyborHaslo != powtorzHaslo)
		{
			system("cls");
			std::cout << "| Podane hasla roznia sie :c";
			_getch();
		}
	} while (wyborHaslo != powtorzHaslo);

	return wyborHaslo;
}

bool czyWolnyLogin(std::list<KontoKlienta> listaKont, std::string newLogin)
{
	bool czyWolny = 1;
	for (KontoKlienta konto : listaKont)
	{
		if (konto.login==newLogin)
		{
			czyWolny = 0;
			break;
		}
	}

	return czyWolny;
}

int getListaKlientow(Bank *bank)
{
	std::ifstream* plikListaKlientow = new std::ifstream;
	plikListaKlientow->open("listaKlientow.txt");

	int iloscKlientow = 0;
	if (plikListaKlientow->is_open())
	{
		*plikListaKlientow >> iloscKlientow;

		for (int i = 0; i < iloscKlientow; i++)
		{
			wczytajKlienta(bank, plikListaKlientow);
		}
	}

	plikListaKlientow->close();
	delete plikListaKlientow;

	return iloscKlientow;
}

void setListaKlientow(int *iloscKlientow, Bank *bank)
{
	std::ofstream* plikListaKlientow = new std::ofstream;
	plikListaKlientow->open("listaKlientow.txt");

	if (plikListaKlientow->is_open())
	{
		*plikListaKlientow << *iloscKlientow << std::endl;

		for (int i = 0; i < *iloscKlientow; i++)
		{
			zapiszKlienta(bank, plikListaKlientow);
			bank->listaKontKlientow.pop_front();
		}
	}

	*iloscKlientow = getListaKlientow(bank);

	plikListaKlientow->close();
	delete plikListaKlientow;
}

void wczytajKlienta(Bank *bank, std::ifstream *plik)
{
	std::string new_imie;
	std::string new_nazwisko;
	std::string new_adres;
	std::string new_mail;
	std::string new_login;
	std::string new_haslo;
	int new_numerKonta;

	*plik >> new_numerKonta;
	*plik >> new_login;
	*plik >> new_haslo;
	*plik >> new_imie;
	*plik >> new_nazwisko;
	plik->ignore();
	std::getline(*plik, new_adres);
	*plik >> new_mail;

	KontoKlienta* nowy = new KontoKlienta(new_imie, new_nazwisko, new_adres, new_mail, new_login, new_haslo, new_numerKonta);
	bank->listaKontKlientow.push_back(*nowy);
	delete nowy;
}

void zapiszKlienta(Bank* bank, std::ofstream* plik)
{
	*plik << bank->listaKontKlientow.front().numerKonta;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().login;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().haslo;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().imie;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().nazwisko;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().adres;
	*plik << std::endl;
	*plik << bank->listaKontKlientow.front().mail;
	*plik << std::endl;
}

void zapiszKlienta(KontoKlienta* aktualnyKlient, std::ofstream* plik)
{
	*plik << aktualnyKlient->numerKonta;
	*plik << std::endl;
	*plik << aktualnyKlient->login;
	*plik << std::endl;
	*plik << aktualnyKlient->haslo;
	*plik << std::endl;
	*plik << aktualnyKlient->imie;
	*plik << std::endl;
	*plik << aktualnyKlient->nazwisko;
	*plik << std::endl;
	*plik << aktualnyKlient->adres;
	*plik << std::endl;
	*plik << aktualnyKlient->mail;
	*plik << std::endl;
}

std::string getHaslo(bool show_asterisk = true)
{
	const char BACKSPACE = 8;
	const char RETURN = 13;

	std::string password;
	unsigned char ch = 0;

	while ((ch = _getch()) != RETURN)
	{
		if (ch == BACKSPACE)
		{
			if (password.length() != 0)
			{
				if (show_asterisk)
					std::cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else if (ch == 0 || ch == 224) // handle escape sequences
		{
			_getch(); // ignore non printable chars
			continue;
		}
		else
		{
			password += ch;
			if (show_asterisk)
				std::cout << '*';
		}
	}
	std::cout << std::endl;
	return password;
}

int menu::start()
{
	int menuWybor;
	system("cls");

	std::cout << "--------------------\n"
		<< "| BANK\n"
		<< "| 1. Zaloguj sie\n"
		<< "| 2. Zarejestruj sie\n"
		<< "| 3. Wyjdz\n"
		<< "--------------------\n"
		<< "| >";

	std::cin >> menuWybor;

	if (menuWybor < 1 || menuWybor>2) menuWybor = 3;
	return menuWybor;
}

void menu::main(KontoKlienta *aktualnyKlient, Bank* bank, int* iloscKlientow)
{
	int menuWybor;
	int czyUsuniete = *iloscKlientow;
	
	for (;;)
	{
		system("cls");
		std::cout << "--------------------\n"
			<< "| " << aktualnyKlient->getImie() << " "
			<< "| " << aktualnyKlient->getNazwisko() << "\n"
			<< "| 1. Konta Bankowe\n"
			<< "| 2. Lokaty\n"
			<< "| 3. Zarzadzanie kontem\n"
			<< "| 4. Wyloguj\n"
			<< "--------------------\n"
			<< "| >";

		std::cin >> menuWybor;

		switch (menuWybor)
		{
		case 1:
			break;

		case 2:
			break;

		case 3:
			menu::zarzadzanie(aktualnyKlient, bank, iloscKlientow);
			if (czyUsuniete != *iloscKlientow) return;
			break;

		case 4:
			return;
			break;

		default:
			break;
		}
	}
}

void menu::zarzadzanie(KontoKlienta* aktualnyKlient, Bank* bank, int* iloscKlientow)
{
	int menuWybor;
	int czyUsuniete = *iloscKlientow;

	for (;;)
	{
		system("cls");
		std::cout << "--------------------\n"
			<< "| Login: " << aktualnyKlient->getLogin() << "\n"
			<< "| Imie: " << aktualnyKlient->getImie() << "\n"
			<< "| Nazwisko: " << aktualnyKlient->getNazwisko() << "\n"
			<< "| Adres mailowy: " << aktualnyKlient->getMail() << "\n"
			<< "| Adres zamieszkania: " << aktualnyKlient->getAdres() << "\n"
			<< "| Numer Konta: " << aktualnyKlient->getNumerKonta() << "\n"
			<< "--------------------\n"
			<< "| 1. Zmien login\n"
			<< "| 2. Zmien imie\n"
			<< "| 3. Zmien nazwisko\n"
			<< "| 4. Zmien adres mailowy\n"
			<< "| 5. Zmien adres zamieszkania\n"
			<< "| 6. Usun konto\n"
			<< "| 7. Wroc\n"
			<< "--------------------\n"
			<< "| >";

		std::cin >> menuWybor;
		switch (menuWybor)
		{
		case 1:
			if (bank->weryfikacjaTozsamosci(aktualnyKlient))
			{
				std::string new_login;
				std::cout << "|\n| Nowy login: ";
				std::cin >> new_login;
				aktualnyKlient->setLogin(new_login);
			}
			break;

		case 2:
			if (bank->weryfikacjaTozsamosci(aktualnyKlient))
			{
				std::string new_imie;
				std::cout << "|\n| Nowe imie: ";
				std::cin >> new_imie;
				aktualnyKlient->setImie(new_imie);
			}
			break;

		case 3:
			if (bank->weryfikacjaTozsamosci(aktualnyKlient))
			{
				std::string new_nazwisko;
				std::cout << "|\n| Nowe nazwisko: ";
				std::cin >> new_nazwisko;
				aktualnyKlient->setNazwisko(new_nazwisko);
			}
			break;

		case 4:
			if (bank->weryfikacjaTozsamosci(aktualnyKlient))
			{
				std::string new_mail;
				std::cout << "|\n| Nowy mail: ";
				std::cin >> new_mail;
				aktualnyKlient->setMail(new_mail);
			}
			break;

		case 5:
			if (bank->weryfikacjaTozsamosci(aktualnyKlient))
			{
				std::string new_adres;
				std::cout << "|\n| Nowy adres: ";
				std::cin >> new_adres;
				aktualnyKlient->setAdres(new_adres);
			}
			break;

		case 6:
			bank->usunKlienta(aktualnyKlient, bank, iloscKlientow);
			if (czyUsuniete != *iloscKlientow) return;
			break;

		case 7:
			return;
			break;

		default:
			break;
		}
	}
}