// this file is only included by generated.h

#include <string>
#include "../SuperType.h"

namespace mtg {

SuperType parseSuperType(std::string const & value);
std::string SuperTypeStr(SuperType value);

template<>
struct TypeToStr<SuperType> {
	static std::string toString(SuperType value) { return SuperTypeStr(value); }
};

template<>
struct StrToType<SuperType> {
	static SuperType toType(std::string const & value) { return parseSuperType(value); }
};

}

