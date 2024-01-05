#include <stdlib.h>
#include <conio.h>
#include <list>
#include "bank.h"

Bank::Bank()
{
	okresWeryfikacji = 100;
}

Bank::~Bank()
{

}

void Bank::dodajKlienta()
{
	std::string imie;
	std::string nazwisko;
	std::string adres;
	std::string mail;
	
	system("cls");
	std::cout << "Imie: ";
	std::cin >> imie;
	std::cout << "\nNazwisko: ";
	std::cin >> nazwisko;
	std::cout << "\nAdres zamieszkania: ";
	std::cin >> adres;
	std::cout << "\nAdres Email: ";
	std::cin >> mail;
}

void Bank::usunKlienta()
{

}
