#pragma once
#include <iostream>
enum RodzajPrzelewu {
	NATYCHMIASTOWY,
	OKRESOWY,
	WALUTOWY,

};
std::string toString(RodzajPrzelewu);