#ifndef MANASYMBOL_H_LIBMAGIC_2015_17_05
#define MANASYMBOL_H_LIBMAGIC_2015_17_05

#include <bitset>
#include "Colors.h"

namespace mtg {

using Cmc = unsigned;

struct CostSymbol {
	enum Specific {
		snow=1, phyrexian,
		X, Y, Z,
	};
	using Generic = unsigned char;

	ColorSet colors;
	Specific specific = {};
	Generic generic = 0;

	explicit CostSymbol(Generic generic = 0);
	explicit CostSymbol(Color c, Generic generic = 0);
	CostSymbol(Color c, Color c2);
	explicit CostSymbol(Specific s, Generic generic = 0);
	CostSymbol(Specific s, Color c);

	Cmc cmc() const;
	Cmc min_cmc() const;
	bool hasColor(Color c) const;
	bool colorless() const;
	bool colored() const;
    bool monoColored() const;
    Color firstColor() const;

	bool operator==(CostSymbol const & mp) const;
};

} /* namespace mtg */

namespace std {

template<>
struct hash<mtg::CostSymbol> {
    size_t operator()(mtg::CostSymbol const & mp) const {
        return
            std::hash<decltype(mp.colors)>()(mp.colors) ^
            std::hash<decltype(mp.generic)>()(mp.generic)
        ;
    }
};

}

#endif
