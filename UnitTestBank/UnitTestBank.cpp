#include "pch.h"
#include "CppUnitTest.h"
#include "..\bank-studia\bank.h"
#include "..\bank-studia\klient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestBank
{
	TEST_CLASS(AccountCreation)
	{
	public:
		
		TEST_METHOD(TestSetLogin)
		{
			Bank bank;

			for (int i = 0; i < 10; i++)
			{
				KontoKlienta* konto = new KontoKlienta(std::to_string(i+i*10));
				bank.listaKontKlientow.push_front(*konto);
				delete konto;
			}

			KontoKlienta* konto = new KontoKlienta("papamobile");
			bank.listaKontKlientow.push_front(*konto);
			delete konto;

			for (int i = 10; i < 20; i++)
			{
				KontoKlienta* konto = new KontoKlienta(std::to_string(i+i*10));
				bank.listaKontKlientow.push_front(*konto);
				delete konto;
			}

			std::string nowyLogin = "papamobile";
			std::string nowyLogin2 = "pepenobile";

			Assert::IsFalse(czyWolnyLogin(bank.listaKontKlientow, nowyLogin));
			Assert::IsTrue(czyWolnyLogin(bank.listaKontKlientow, nowyLogin2));
		}

		TEST_METHOD(TestGetIloscKlientow)
		{
			Bank bank;
			int expected = 0;
			int actual = getListaKlientow(&bank);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestZnajdzKlienta)
		{
			int znajdz = 0;
			Bank* bank = new Bank();
			KontoKlienta* aktualny = new KontoKlienta();

			Assert::AreEqual(znajdz, znajdzKlienta(bank, aktualny));
		}

		TEST_METHOD(TestGetListaKlientow)
		{
			Bank* bank = new Bank();
			int expected = 0;
			Assert::AreEqual(expected, getListaKlientow(bank));
		}

	};

	TEST_CLASS(BankAccount)
	{
	public:
		TEST_METHOD(TestRodzajKonta)
		{
			std::string expected = "Konto oszczednosciowe";
			Assert::AreEqual(expected, wyswietlRodzajKontaBankowego(RODZAJ_KONTO_OSZCZEDNOSCIOWE));
		}

		TEST_METHOD(TestSrodki)
		{
			double expected = 0;
			KontoBankowe* actual = new KontoBankowe();

			Assert::AreEqual(expected, actual->getSrodki());
		}

		TEST_METHOD(TestSrodkiLokata)
		{
			double expected = 0;
			Lokata* actual = new Lokata();

			Assert::AreEqual(expected, actual->getSrodki());
		}

		TEST_METHOD(TestProcentLokata)
		{
			double expected = 0;
			Lokata* actual = new Lokata();

			Assert::AreEqual(expected, actual->getOprocentowanie());
		}

		TEST_METHOD(TestCzasLokata)
		{
			std::string expected = "3 miesiace";
			Assert::AreEqual(expected, wyswietlRodzajCzasuLokaty(RODZAJ_CZASU_LOKATA_3MIESIECZNA));
		}

		TEST_METHOD(TestOprocetowanie)
		{
			double expected = 0.02;
			Assert::AreEqual(expected, obliczOprocentowanie(RODZAJ_LOKATA_ZWYKLA, RODZAJ_CZASU_LOKATA_3MIESIECZNA));
		}
	};
}

namespace UnitTestKlient
{
	TEST_CLASS(OperatorOverloads)
	{
	public:

		TEST_METHOD(TestEqualOperator)
		{
			KontoKlienta konto1;
			KontoKlienta konto2;

			Assert::IsTrue(konto1 == konto2);
		}
	};
}