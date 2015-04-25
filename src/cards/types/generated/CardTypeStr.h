// this file is only included by generated.h

#include <string>
#include "../CardType.h"

namespace mtg {

CardType parseCardType(std::string const & value);
std::string CardTypeStr(CardType value);

template<>
struct TypeToStr<CardType> {
	static std::string toString(CardType value) { return CardTypeStr(value); }
};

template<>
struct StrToType<CardType> {
	static CardType toType(std::string const & value) { return parseCardType(value); }
};

}

