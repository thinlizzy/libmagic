#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

Color parseColor(std::string const & value) {
	static std::unordered_map<std::string,Color> map;
	if( map.empty() ) {
		map["green"] = green;
		map["blue"] = blue;
		map["red"] = red;
		map["white"] = white;
		map["black"] = black;
		map["nColors"] = nColors;
		map["colorless"] = colorless;
	}
	return map.at(value);
}

std::string ColorStr(Color value) {
	switch(value) {
	case green:
		return "green";
	case blue:
		return "blue";
	case red:
		return "red";
	case white:
		return "white";
	case black:
		return "black";
	case nColors:
		return "nColors";
	case colorless:
		return "colorless";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
