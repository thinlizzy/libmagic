// this file is only included by generated.h

#include <string>
#include "../$NAME$.h"

namespace mtg {

$NAME$ parse$NAME$(std::string const & value);
std::string $NAME$Str($NAME$ value);

template<>
struct TypeToStr<$NAME$> {
	static std::string toString($NAME$ value) { return $NAME$Str(value); }
};

template<>
struct StrToType<$NAME$> {
	static $NAME$ toType(std::string const & value) { return parse$NAME$(value); }
};

}

