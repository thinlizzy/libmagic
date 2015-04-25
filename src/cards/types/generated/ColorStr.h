// this file is only included by generated.h

#include <string>
#include "../Color.h"

namespace mtg {

Color parseColor(std::string const & value);
std::string ColorStr(Color value);

template<>
struct TypeToStr<Color> {
	static std::string toString(Color value) { return ColorStr(value); }
};

template<>
struct StrToType<Color> {
	static Color toType(std::string const & value) { return parseColor(value); }
};

}

