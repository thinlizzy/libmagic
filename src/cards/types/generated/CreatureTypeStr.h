// this file is only included by generated.h

#include <string>
#include "../CreatureType.h"

namespace mtg {

CreatureType parseCreatureType(std::string const & value);
std::string CreatureTypeStr(CreatureType value);

template<>
struct TypeToStr<CreatureType> {
	static std::string toString(CreatureType value) { return CreatureTypeStr(value); }
};

template<>
struct StrToType<CreatureType> {
	static CreatureType toType(std::string const & value) { return parseCreatureType(value); }
};

}

