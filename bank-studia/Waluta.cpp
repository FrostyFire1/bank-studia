#include "Waluta.h"

Waluta::Waluta() {

}
Waluta::Waluta(std::string nazwa, double przelicznik) {
	this->nazwa = nazwa;
	this->przelicznik = przelicznik;

}
/*
* Operator porownania walut
*/
bool Waluta::operator==(const Waluta& b) {
	return this->nazwa == b.nazwa && this->przelicznik == b.przelicznik;
}
/*
* Operator porownania walut
*/
bool Waluta::operator!=(const Waluta& b) {
	return this->nazwa != b.nazwa || this->przelicznik != b.przelicznik;
}