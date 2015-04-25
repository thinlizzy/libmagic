// this file is only included by generated.h

#include <string>
#include "../LandType.h"

namespace mtg {

LandType parseLandType(std::string const & value);
std::string LandTypeStr(LandType value);

template<>
struct TypeToStr<LandType> {
	static std::string toString(LandType value) { return LandTypeStr(value); }
};

template<>
struct StrToType<LandType> {
	static LandType toType(std::string const & value) { return parseLandType(value); }
};

}

