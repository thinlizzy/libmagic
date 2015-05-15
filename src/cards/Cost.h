#ifndef COST_H_kjk4530k3n
#define COST_H_kjk4530k3n

#include <vector>
#include <string>
#include <bitset>
#include <ostream>
#include "Color.h"

namespace mtg {

struct ManaPattern {
	ColorSet colors;   // green, blue, red, white, black
	struct Specific {
		bool X : 1;
		bool Y : 1;
		bool Z : 1;
		bool phyrexian : 1;
		bool snow : 1;

		bool operator==(Specific const & specific) const {
			// boring :(
			return X == specific.X && Y == specific.Y && Z == specific.Z && phyrexian == specific.phyrexian && snow == specific.snow;
		}
	};
	Specific specific = {};
	using Generic = unsigned char;
	Generic generic;

	ManaPattern();
	ManaPattern(Generic generic);
	ManaPattern(Generic generic, Color c);
	ManaPattern(Color c, Color c2);

	ManaPattern & setChar(char c);
	unsigned cmc() const;
	bool hasColor(Color c) const;
	bool colorless() const;
    bool monoColored() const;

	bool operator==(ManaPattern const & mp) const;
};

class Cost {
public:
	using Symbols = std::vector<ManaPattern>;
	Symbols symbols;

	Cost() = default;

	unsigned convertedManaCost() const;
	bool hasColor(Color c) const;
	bool colorless() const;
	ColorSet colors() const;

	bool operator==(Cost const & cost) const;
	bool operator!=(Cost const & cost) const;
};

}

namespace std {
    
template<>
struct hash<mtg::ManaPattern> {
    size_t operator()(mtg::ManaPattern const & mp) const { 
        return 
            std::hash<decltype(mp.colors)>()(mp.colors) ^
            std::hash<decltype(mp.generic)>()(mp.generic)
        ;
    }
};

}

#endif
