#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <conio.h>
#include "Lokata.h"
#include "RodzajLokaty.h"
#include "RodzajCzasuLokaty.h"


Lokata::Lokata(RodzajLokaty new_rodzaj, RodzajCzasuLokaty new_okres, double new_srodki,std::string new_nrLokaty)
{
	rodzaj = new_rodzaj;
	okres = new_okres;
	srodki = new_srodki;
	nrLokaty = new_nrLokaty;
	dataRozpoczecia = Data(BRAK);
	ostatnieNaliczenie = Data(okres);
}

Lokata::Lokata(RodzajLokaty new_rodzaj, RodzajCzasuLokaty new_okres, double new_srodki, std::string new_nrLokaty,std::string new_dataRozpoczecia,std::string new_ostatnieNaliczenie)
{
	rodzaj = new_rodzaj;
	okres = new_okres;
	srodki = new_srodki;
	nrLokaty = new_nrLokaty;
	dataRozpoczecia = new_dataRozpoczecia;
	ostatnieNaliczenie = new_ostatnieNaliczenie;
}

Lokata::Lokata()
{

	rodzaj = RODZAJ_LOKATA_ZWYKLA;
	okres = RODZAJ_CZASU_LOKATA_3MIESIECZNA;
	srodki = 0.0;
	nrLokaty = "00000000000000000000000000";

}

std::string Lokata::Data(RodzajCzasuLokaty okres)
{
	// Pobierz bieżącą datę i czas
	std::chrono::system_clock::time_point teraz = std::chrono::system_clock::now();
	std::time_t czasTeraz = std::chrono::system_clock::to_time_t(teraz);

	// Dodaj 3 miesiące do bieżącej daty

	std::tm czasInfo;
	localtime_s(&czasInfo, &czasTeraz);

	if (okres== RODZAJ_CZASU_LOKATA_3MIESIECZNA)
	{

		czasInfo.tm_mon += 3;
	}
	else if (okres== RODZAJ_CZASU_LOKATA_6MIESIECZNA)
	{
		czasInfo.tm_mon += 6;
	}
	else if (okres == RODZAJ_CZASU_LOKATA_12MIESIECZNA)
	{
		czasInfo.tm_mon += 12;
	}

	if (czasInfo.tm_mon > 11)
	{
		czasInfo.tm_mon %= 12;
		czasInfo.tm_year += 1; 
	}

	std::mktime(&czasInfo);

	char czasBuff[11];

	std::strftime(czasBuff, sizeof(czasBuff), "%d:%m:%Y", &czasInfo);

	return czasBuff;
}


void Lokata::wyswietlDaneLokat()
{

	std::cout << "Nr Lokaty: " << nrLokaty << "\nRodzaj lokaty: " << rodzaj<<"\nCzas trwania lokaty: "<< okres<<"\nSrodki: "<<srodki<<"\nData rozpoczecia: "<< dataRozpoczecia<<"\nData zakończenia loakty: "<< ostatnieNaliczenie;
	_getch();

}

RodzajLokaty Lokata::getRodzajLokaty()
{
	return rodzaj;
}

RodzajCzasuLokaty Lokata::getRodzajCzasuLokaty()
{
	return okres;
}

double Lokata::getSrodki()
{
	return srodki;
}

std::string Lokata::getNrLokaty()
{
	return nrLokaty;
}

std::string Lokata::getDataRozpoczecia()
{
	return dataRozpoczecia;
}

std::string Lokata::getOstatnieNaliczenie()
{
	return ostatnieNaliczenie;
}

