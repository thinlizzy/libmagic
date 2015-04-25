// this file is only included by generated.h

#include <string>
#include "../EnchantmentType.h"

namespace mtg {

EnchantmentType parseEnchantmentType(std::string const & value);
std::string EnchantmentTypeStr(EnchantmentType value);

template<>
struct TypeToStr<EnchantmentType> {
	static std::string toString(EnchantmentType value) { return EnchantmentTypeStr(value); }
};

template<>
struct StrToType<EnchantmentType> {
	static EnchantmentType toType(std::string const & value) { return parseEnchantmentType(value); }
};

}

