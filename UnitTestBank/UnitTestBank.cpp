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
			int expected = 0;
			int actual = getIloscKlientow();
			Assert::AreEqual(expected, actual);
		}
	};
}
