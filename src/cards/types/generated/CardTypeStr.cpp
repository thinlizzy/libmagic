#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

CardType parseCardType(std::string const & value) {
	static std::unordered_map<std::string,CardType> map;
	if( map.empty() ) {
		map["land"] = land;
		map["sorcery"] = sorcery;
		map["instant"] = instant;
		map["creature"] = creature;
		map["artifact"] = artifact;
		map["enchantment"] = enchantment;
		map["planeswalker"] = planeswalker;
		map["tribal"] = tribal;
	}
	return map.at(value);
}

std::string CardTypeStr(CardType value) {
	std::string result = "|";
	if( (value & land) == land ) result += "land|";	
	if( (value & sorcery) == sorcery ) result += "sorcery|";	
	if( (value & instant) == instant ) result += "instant|";	
	if( (value & creature) == creature ) result += "creature|";	
	if( (value & artifact) == artifact ) result += "artifact|";	
	if( (value & enchantment) == enchantment ) result += "enchantment|";	
	if( (value & planeswalker) == planeswalker ) result += "planeswalker|";	
	if( (value & tribal) == tribal ) result += "tribal|";	
	return result;
}

}
