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
	oprocentowanie = obliczOprocentowanie(rodzaj, okres);
	nrLokaty = new_nrLokaty;
	dataRozpoczecia = Data(BRAK);
	ostatnieNaliczenie = Data(okres);
}

Lokata::Lokata(RodzajLokaty new_rodzaj, RodzajCzasuLokaty new_okres, double new_srodki,double new_oprocentowanie, std::string new_nrLokaty,std::string new_dataRozpoczecia,std::string new_ostatnieNaliczenie)
{
	rodzaj = new_rodzaj;
	okres = new_okres;
	srodki = new_srodki;
	oprocentowanie = new_oprocentowanie;
	nrLokaty = new_nrLokaty;
	dataRozpoczecia = new_dataRozpoczecia;
	ostatnieNaliczenie = new_ostatnieNaliczenie;
}

Lokata::Lokata()
{
	oprocentowanie = 0;
	rodzaj = RODZAJ_LOKATA_ZWYKLA;
	okres = RODZAJ_CZASU_LOKATA_3MIESIECZNA;
	srodki = 0.0;
	nrLokaty = "00000000000000000000000000";

}

std::string Data(RodzajCzasuLokaty okres)
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

//funckja do wyswietlania danych lokaty
void Lokata::wyswietlDaneLokat()
{

	std::cout << "Nr Lokaty: " << nrLokaty << "\nRodzaj lokaty: " << wyswietlRodzajLokaty(rodzaj)<<"\nCzas trwania lokaty: "<< wyswietlRodzajCzasuLokaty(okres)<<"\nSrodki: "<<srodki<<"\nOprocentowanie: "<<oprocentowanie*100<< "%\nData rozpoczecia: " << dataRozpoczecia << "\nData zakończenia loakty: " << ostatnieNaliczenie;

}
//getter i setter
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

double Lokata::getOprocentowanie()
{
	return oprocentowanie;
}

//funkcja do konwersji enuma wyswietlania rodzaju lokaty na string
std::string wyswietlRodzajLokaty(RodzajLokaty rodzaj)
{
	switch (rodzaj)
	{
	case RODZAJ_LOKATA_ZWYKLA:
		return "Lokata zwykla";
		break;
	case RODZAJ_LOKATA_OSZCZEDNOSCIOWA:
		return "Lokata oszczednosciowa";
		break;
	case RODZAJ_LOKATA_WALUTOWA:
		return "Lokata walurowa";
		break;
	default:
		return "brak loakty";
		break;
	}
}

//funkcja do konwersji enuma wyswietlRodzajCzasuLokaty rodzaju lokaty na string
std::string wyswietlRodzajCzasuLokaty(RodzajCzasuLokaty okres)
{
	switch (okres)
	{
	case RODZAJ_CZASU_LOKATA_3MIESIECZNA:
		return "3 miesiace";
		break;
	case RODZAJ_CZASU_LOKATA_6MIESIECZNA:
		return "6 miesiecy";
		break;
	case RODZAJ_CZASU_LOKATA_12MIESIECZNA:
		return "12 miesiecy";
		break;
	default:
		return "brak okresu";
		break;
	}
}

//funkcja do obliczania oprocentowania
double obliczOprocentowanie(RodzajLokaty rodzaj, RodzajCzasuLokaty okres)
{
	double lokataZwykla = 0.02;
	double lokataOszczednosciowa = 0.04;
	double lokataWalutowa = 0.03;
	double okres3Miesieczny = 1;
	double okres6Miesieczny = 1.5;
	double okres12Miesieczny = 2;
	switch (rodzaj)
	{
	case RODZAJ_LOKATA_ZWYKLA:
		switch (okres)
		{
		case RODZAJ_CZASU_LOKATA_3MIESIECZNA:
			return lokataZwykla*okres3Miesieczny;
			break;
		case RODZAJ_CZASU_LOKATA_6MIESIECZNA:
			return lokataZwykla*okres6Miesieczny;
			break;
		case RODZAJ_CZASU_LOKATA_12MIESIECZNA:
			return lokataZwykla*okres12Miesieczny;
			break;
		}
		break;
	case RODZAJ_LOKATA_OSZCZEDNOSCIOWA:
		switch (okres)
		{
		case RODZAJ_CZASU_LOKATA_3MIESIECZNA:
			return lokataOszczednosciowa*okres3Miesieczny;
			break;
		case RODZAJ_CZASU_LOKATA_6MIESIECZNA:
			return lokataOszczednosciowa*okres6Miesieczny;
			break;
		case RODZAJ_CZASU_LOKATA_12MIESIECZNA:
			return lokataOszczednosciowa*okres12Miesieczny;
			break;
		}
		break;
	case RODZAJ_LOKATA_WALUTOWA:
		switch (okres)
		{
		case RODZAJ_CZASU_LOKATA_3MIESIECZNA:
			return lokataWalutowa*okres3Miesieczny;
			break;
		case RODZAJ_CZASU_LOKATA_6MIESIECZNA:
			return lokataWalutowa*okres6Miesieczny;
			break;
		case RODZAJ_CZASU_LOKATA_12MIESIECZNA:
			return lokataWalutowa * okres12Miesieczny;
			break;
		}
		break;
	default:
		return 0.0;
		break;
	}
	
}

