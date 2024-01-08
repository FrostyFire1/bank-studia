#include <iostream>
#include <string>
#include "KontoBankowe.h"


KontoBankowe::KontoBankowe(std::string new_nrKonta, RodzajKonta new_rodzajKonta)
{
	numerKonta = new_nrKonta;
	rodzaj = new_rodzajKonta;
}


KontoBankowe::~KontoBankowe()
{
}

void KontoBankowe::wyswietlDane()
{
	std::cout <<"Nr konta bankowego: "<<numerKonta<<"\n Rodzaj konta: "<<rodzaj;
}
