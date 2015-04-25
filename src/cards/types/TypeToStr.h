#ifndef TYPETOSTR_H_LIBMAGIC_2015
#define TYPETOSTR_H_LIBMAGIC_2015

#include <string>

namespace mtg {

template<typename E>
struct TypeToStr {
	static std::string toString(E value) { return std::to_string(long(value)); }
};

template<typename E>
std::string typeToStr(E value) { return TypeToStr<E>::toString(value); }

template<typename E>
struct StrToType {
	static E toType(std::string const & value) { return E{}; }
};

}

#include "generated/generated.h"

#endif
