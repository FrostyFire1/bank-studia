#include "pch.h"
#include "CppUnitTest.h"
#include "..\bank-studia\KontoBankowe.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestBank
{
    TEST_CLASS(MoneyTransfer)
    {
    public:
        TEST_METHOD(UtworzPrzelew) {
            KontoBankowe tested = KontoBankowe("101", RodzajKonta::RODZAJ_KONTO_ROZLICZENIOWE);
            Przelew expected = Przelew();
            expected.kwota = 20.0;
            expected.opis = "Keks";
            expected.rodzajPrzelewu = RodzajPrzelewu::NATYCHMIASTOWY;
            expected.nadawca = "101";
            expected.adresat = "010";
            expected.timestamp = 0;
            expected.waluta = Waluta("PLN", 1.0);
            expected.idPrzelewu = 0;
            expected.okres = 0;
            expected.ostatnieRozliczenie = 0;
            Przelew result = tested.utworzPrzelew("010", 20.0, RodzajPrzelewu::NATYCHMIASTOWY, "Keks", 0, Waluta("PLN", 1.0));

            Assert::AreEqual(expected.kwota, result.kwota, 1e-10);
            Assert::AreEqual(std::string("Keks"), result.opis);
            Assert::AreEqual(toString(RodzajPrzelewu::NATYCHMIASTOWY), toString(result.rodzajPrzelewu));
            Assert::AreEqual(std::string("101"), result.nadawca);
            Assert::AreEqual(std::string("010"), result.adresat);
            Assert::AreEqual(0, result.timestamp);
            Assert::AreEqual(std::string("PLN"), result.waluta.nazwa);
            Assert::AreEqual(1.0, result.waluta.przelicznik,1e-10);
            Assert::AreEqual(0, result.idPrzelewu);
            Assert::AreEqual(0,result.okres);
            Assert::AreEqual(0, result.ostatnieRozliczenie);

        }
    };
}