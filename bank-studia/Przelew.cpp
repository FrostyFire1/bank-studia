
class Przelew {

private:
	double kwota;
	string opis;
	RodzajPrzelewu rodzajPrzelewu;
	int nadawca;
	int adresat;
	int timestamp;
	Waluta waluta;
	int idPrzelewu;
	boolean jestOkresowy;
	int okres;
	int ostatnieRozliczenie;
};

enum RodzajPrzelewu {
	OKRESOWY,
	NATYCHMIASTOWY,
};