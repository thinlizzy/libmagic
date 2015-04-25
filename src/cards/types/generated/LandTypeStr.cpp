#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

LandType parseLandType(std::string const & value) {
	static std::unordered_map<std::string,LandType> map;
	if( map.empty() ) {
		map["swamp"] = swamp;
		map["forest"] = forest;
		map["plains"] = plains;
		map["mountain"] = mountain;
		map["island"] = island;
		map["desert"] = desert;
		map["lair"] = lair;
		map["locus"] = locus;
		map["urza_s"] = urza_s;
		map["mine"] = mine;
		map["tower"] = tower;
		map["powerPlant"] = powerPlant;
	}
	return map.at(value);
}

std::string LandTypeStr(LandType value) {
	switch(value) {
	case swamp:
		return "swamp";
	case forest:
		return "forest";
	case plains:
		return "plains";
	case mountain:
		return "mountain";
	case island:
		return "island";
	case desert:
		return "desert";
	case lair:
		return "lair";
	case locus:
		return "locus";
	case urza_s:
		return "urza_s";
	case mine:
		return "mine";
	case tower:
		return "tower";
	case powerPlant:
		return "powerPlant";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
