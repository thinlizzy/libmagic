#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

Rarity parseRarity(std::string const & value) {
	static std::unordered_map<std::string,Rarity> map;
	if( map.empty() ) {
		map["common"] = common;
		map["uncommon"] = uncommon;
		map["rare"] = rare;
		map["mythicRare"] = mythicRare;
		map["timeshifted"] = timeshifted;
	}
	return map.at(value);
}

std::string RarityStr(Rarity value) {
	switch(value) {
	case common:
		return "common";
	case uncommon:
		return "uncommon";
	case rare:
		return "rare";
	case mythicRare:
		return "mythicRare";
	case timeshifted:
		return "timeshifted";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
