#pragma once
#include <list>

class KontoBankowe {
	friend class KontoKlienta;
	friend bool czyWolnyLoginBankowy(std::list<KontoBankowe> listaKont, std::string newLogin);
private:

protected:
	std::string numerKonta;
	std::string haslo;
	std::string login;

public:
	KontoBankowe(std::string,std::string ,std::string );
	KontoBankowe();
	~KontoBankowe();
	void wyswietlDane();

};
