#pragma once
#include <iostream>
class Waluta {
public:
	std::string nazwa;
	double przelicznik;
	Waluta();
	Waluta(std::string, double);
};