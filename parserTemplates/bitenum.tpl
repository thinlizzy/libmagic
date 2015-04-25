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
	std::string result = "|";
$BEGIN_ENUM$	if( (value & $ENUM$) == $ENUM$ ) result += "$VALUE$|";	
$END_ENUM$	return result;
}

}
