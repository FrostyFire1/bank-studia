#include "pch.h"
#include "CppUnitTest.h"
#include "..\bank-studia\KontoBankowe.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestBank
{
    TEST_CLASS(UtworzPrzelew)
    {
    public:

        KontoBankowe tested = KontoBankowe("101", RodzajKonta::RODZAJ_KONTO_ROZLICZENIOWE);
        //UNIT TESTY WYKONYWANE SA ALFABETYCZNIE!!!!

        TEST_METHOD(SprawdzaRodzajPrzelewu) {
            //Waluta w funkcji powinna zostac zignorowana
            tested.utworzPrzelew("010", 20.0, RodzajPrzelewu::NATYCHMIASTOWY, "Keks", 0, Waluta("EUR", 4.0));
            Przelew przelew = tested.getPrzelewy().front();

            Assert::AreEqual(-20.0, tested.getSrodki(), 1e-10);

        }
        TEST_METHOD(TworzyBlokade) {
            tested.utworzPrzelew("010", 20.0, RodzajPrzelewu::NATYCHMIASTOWY, "Keks", 0, Waluta("PLN", 1.0));
            std::vector<Blokada> blokady = tested.getBlokady();

            Assert::AreEqual((int)blokady.size(), 1);

            Blokada blokada = blokady.front();
            Assert::AreEqual(20.0, blokada.srodki);



        }
        TEST_METHOD(TworzyPrzelew) {
            tested.utworzPrzelew("010", 20.0, RodzajPrzelewu::NATYCHMIASTOWY, "Keks", 0, Waluta("PLN", 1.0));
            Przelew przelew = tested.getPrzelewy().front();

            Assert::AreEqual(20.0, przelew.kwota, 1e-10);
            Assert::AreEqual(std::string("Keks"), przelew.opis);
            Assert::AreEqual(toString(RodzajPrzelewu::NATYCHMIASTOWY), toString(przelew.rodzajPrzelewu));
            Assert::AreEqual(std::string("101"), przelew.nadawca);
            Assert::AreEqual(std::string("010"), przelew.adresat);
            Assert::AreEqual(0, przelew.timestamp);
            Assert::AreEqual(std::string("PLN"), przelew.waluta.nazwa);
            Assert::AreEqual(1.0, przelew.waluta.przelicznik,1e-10);
            Assert::AreEqual(3, przelew.idPrzelewu); //To jest drugi przelew unit testu
            Assert::AreEqual(0,przelew.okres);
            Assert::AreEqual(0, przelew.ostatnieRozliczenie);

        }

        TEST_METHOD(ZabieraPieniadze) {
            tested.utworzPrzelew("010", 20.0, RodzajPrzelewu::NATYCHMIASTOWY, "Keks", 0, Waluta("PLN", 1.0));
            Przelew przelew = tested.getPrzelewy().front();

            Assert::AreEqual(4, przelew.idPrzelewu); //Trzeci przelew unit testu
            Assert::AreEqual(-20.0, tested.getSrodki(), 1e-10);
        }

        TEST_METHOD(ZabieraPieniadzePoKonwersji) {
            tested.utworzPrzelew("010", 20.0, RodzajPrzelewu::WALUTOWY, "Keks", 0, Waluta("EUR", 4.0));
            Przelew przelew = tested.getPrzelewy().front();
            Assert::AreEqual(-80.0, tested.getSrodki(), 1e-10);

        }
    };
}