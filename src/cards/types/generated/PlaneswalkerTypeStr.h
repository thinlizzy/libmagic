// this file is only included by generated.h

#include <string>
#include "../PlaneswalkerType.h"

namespace mtg {

PlaneswalkerType parsePlaneswalkerType(std::string const & value);
std::string PlaneswalkerTypeStr(PlaneswalkerType value);

template<>
struct TypeToStr<PlaneswalkerType> {
	static std::string toString(PlaneswalkerType value) { return PlaneswalkerTypeStr(value); }
};

template<>
struct StrToType<PlaneswalkerType> {
	static PlaneswalkerType toType(std::string const & value) { return parsePlaneswalkerType(value); }
};

}

