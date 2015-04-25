// this file is only included by generated.h

#include <string>
#include "../SpellType.h"

namespace mtg {

SpellType parseSpellType(std::string const & value);
std::string SpellTypeStr(SpellType value);

template<>
struct TypeToStr<SpellType> {
	static std::string toString(SpellType value) { return SpellTypeStr(value); }
};

template<>
struct StrToType<SpellType> {
	static SpellType toType(std::string const & value) { return parseSpellType(value); }
};

}

