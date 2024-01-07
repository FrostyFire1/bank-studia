#include <iostream>
#include <string>
#include "KontoBankowe.h"


KontoBankowe::KontoBankowe(std::string new_login, std::string new_haslo, std::string new_nrKonta)
{
	login = new_login;
	haslo = new_haslo;
	numerKonta = new_nrKonta;
	
}

KontoBankowe::KontoBankowe()
{
	login = "brak";
	haslo = "brak";
}

KontoBankowe::~KontoBankowe()
{
}

void KontoBankowe::wyswietlDane()
{
	std::cout << "Login:" << login << "\n" << "Haslo: " << haslo << "\n" << "Nr konta bankowego: "<<numerKonta;
}
