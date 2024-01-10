#include "Przelew.h"

Przelew::Przelew() {

}
Przelew::Przelew(double kwota, std::string opis, RodzajPrzelewu rodzajPrzelewu, std::string nadawca, std::string adresat,
	int timestamp, Waluta waluta, int idPrzelewu, int okres, int ostatnieRozliczenie) {
	this->kwota = kwota;
	this->opis = opis;
	this->rodzajPrzelewu = rodzajPrzelewu;
	this->nadawca = nadawca;
	this->adresat = adresat;
	this->timestamp = timestamp;
	this->waluta = waluta;
	this->idPrzelewu = idPrzelewu;
	this->okres = okres;
	this->ostatnieRozliczenie = ostatnieRozliczenie;

}
