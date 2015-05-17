#ifndef MANASYMBOL_H_LIBMAGIC_2015_17_05
#define MANASYMBOL_H_LIBMAGIC_2015_17_05

#include <bitset>
#include "Color.h"

namespace mtg {

using Cmc = unsigned;

struct ManaSymbol {
	enum Specific {
		X=1, Y, Z, phyrexian, snow,
	};
	using Generic = unsigned char;

	ColorSet colors;   // green, blue, red, white, black
	Specific specific = {};
	Generic generic;

	ManaSymbol();
	ManaSymbol(Generic generic);
	ManaSymbol(Generic generic, Color c);
	ManaSymbol(Color c, Color c2);
	// TODO review these constructors

	Cmc cmc() const;
	Cmc min_cmc() const;
	bool hasColor(Color c) const;
	bool colorless() const;
	bool colored() const;
    bool monoColored() const;

	bool operator==(ManaSymbol const & mp) const;
};

} /* namespace mtg */

namespace std {

template<>
struct hash<mtg::ManaSymbol> {
    size_t operator()(mtg::ManaSymbol const & mp) const {
        return
            std::hash<decltype(mp.colors)>()(mp.colors) ^
            std::hash<decltype(mp.generic)>()(mp.generic)
        ;
    }
};

}

#endif
