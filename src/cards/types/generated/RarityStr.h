// this file is only included by generated.h

#include <string>
#include "../Rarity.h"

namespace mtg {

Rarity parseRarity(std::string const & value);
std::string RarityStr(Rarity value);

template<>
struct TypeToStr<Rarity> {
	static std::string toString(Rarity value) { return RarityStr(value); }
};

template<>
struct StrToType<Rarity> {
	static Rarity toType(std::string const & value) { return parseRarity(value); }
};

}

