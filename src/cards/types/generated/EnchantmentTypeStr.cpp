#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

EnchantmentType parseEnchantmentType(std::string const & value) {
	static std::unordered_map<std::string,EnchantmentType> map;
	if( map.empty() ) {
		map["aura"] = aura;
		map["shrine"] = shrine;
		map["curse"] = curse;
	}
	return map.at(value);
}

std::string EnchantmentTypeStr(EnchantmentType value) {
	switch(value) {
	case aura:
		return "aura";
	case shrine:
		return "shrine";
	case curse:
		return "curse";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
