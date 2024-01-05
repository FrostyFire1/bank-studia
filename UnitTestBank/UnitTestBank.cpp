#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\gymzo\source\repos\bank-studia\bank-studia\bank.h"
#include "C:\Users\gymzo\source\repos\bank-studia\bank-studia\klient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestBank
{
	TEST_CLASS(UnitTestBank)
	{
	public:
		
		TEST_METHOD(TestSetLogin)
		{
			Bank bank;

			std::list<KontoKlienta> listaKont;

			for (int i = 0; i < 10; i++)
			{
				KontoKlienta* konto = new KontoKlienta(std::to_string(i + i * 20));
				listaKont.push_back(*konto);
				delete konto;
			}

			KontoKlienta* konto = new KontoKlienta("papamobile");
			listaKont.push_back(*konto);
			delete konto;

			for (int i = 10; i < 20; i++)
			{
				KontoKlienta* konto = new KontoKlienta(std::to_string(i + i * 20));
				listaKont.push_back(*konto);
				delete konto;
			}

			std::string nowyLogin = "papamobile";

			Assert::IsTrue(bank.czyWolnyLogin(nowyLogin));

		}
	};
}
