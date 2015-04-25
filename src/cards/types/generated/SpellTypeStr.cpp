#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

SpellType parseSpellType(std::string const & value) {
	static std::unordered_map<std::string,SpellType> map;
	if( map.empty() ) {
		map["arcane"] = arcane;
		map["trap"] = trap;
	}
	return map.at(value);
}

std::string SpellTypeStr(SpellType value) {
	switch(value) {
	case arcane:
		return "arcane";
	case trap:
		return "trap";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
