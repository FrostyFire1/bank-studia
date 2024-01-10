#include "RodzajPrzelewu.h"

std::string toString(RodzajPrzelewu rodzajPrzelewu) {
	switch (rodzajPrzelewu) {
	case RodzajPrzelewu::NATYCHMIASTOWY:
		return "NATYCHMIASTOWY";
	case RodzajPrzelewu::OKRESOWY:
		return "OKRESOWY";
	case RodzajPrzelewu::WALUTOWY:
		return "WALUTOWY";
	default:
		return "0";
	}
}