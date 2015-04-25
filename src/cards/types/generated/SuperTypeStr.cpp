#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

SuperType parseSuperType(std::string const & value) {
	static std::unordered_map<std::string,SuperType> map;
	if( map.empty() ) {
		map["legendary"] = legendary;
		map["snow"] = snow;
		map["world"] = world;
		map["basic"] = basic;
	}
	return map.at(value);
}

std::string SuperTypeStr(SuperType value) {
	std::string result = "|";
	if( (value & legendary) == legendary ) result += "legendary|";	
	if( (value & snow) == snow ) result += "snow|";	
	if( (value & world) == world ) result += "world|";	
	if( (value & basic) == basic ) result += "basic|";	
	return result;
}

}
