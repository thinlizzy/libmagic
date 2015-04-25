#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

PlaneswalkerType parsePlaneswalkerType(std::string const & value) {
	static std::unordered_map<std::string,PlaneswalkerType> map;
	if( map.empty() ) {
		map["Ajani"] = Ajani;
		map["Bolas"] = Bolas;
		map["Chandra"] = Chandra;
		map["Elspeth"] = Elspeth;
		map["Garruk"] = Garruk;
		map["Gideon"] = Gideon;
		map["Jace"] = Jace;
		map["Karn"] = Karn;
		map["Koth"] = Koth;
		map["Liliana"] = Liliana;
		map["Nissa"] = Nissa;
		map["Sarkhan"] = Sarkhan;
		map["Sorin"] = Sorin;
		map["Tamiyo"] = Tamiyo;
		map["Tezzeret"] = Tezzeret;
		map["Tibalt"] = Tibalt;
		map["Venser"] = Venser;
	}
	return map.at(value);
}

std::string PlaneswalkerTypeStr(PlaneswalkerType value) {
	switch(value) {
	case Ajani:
		return "Ajani";
	case Bolas:
		return "Bolas";
	case Chandra:
		return "Chandra";
	case Elspeth:
		return "Elspeth";
	case Garruk:
		return "Garruk";
	case Gideon:
		return "Gideon";
	case Jace:
		return "Jace";
	case Karn:
		return "Karn";
	case Koth:
		return "Koth";
	case Liliana:
		return "Liliana";
	case Nissa:
		return "Nissa";
	case Sarkhan:
		return "Sarkhan";
	case Sorin:
		return "Sorin";
	case Tamiyo:
		return "Tamiyo";
	case Tezzeret:
		return "Tezzeret";
	case Tibalt:
		return "Tibalt";
	case Venser:
		return "Venser";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
