#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

$NAME$ parse$NAME$(std::string const & value) {
	static std::unordered_map<std::string,$NAME$> map;
	if( map.empty() ) {
$BEGIN_ENUM$		map["$VALUE$"] = $ENUM$;
$END_ENUM$	}
	return map.at(value);
}

std::string $NAME$Str($NAME$ value) {
	switch(value) {
$BEGIN_ENUM$	case $ENUM$:
		return "$VALUE$";
$END_ENUM$	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
