#ifndef COST_H_kjk4530k3n
#define COST_H_kjk4530k3n

#include <vector>
#include <string>
#include <bitset>
#include <ostream>
#include "types/Color.h"

namespace mtg {

struct ManaPattern {
	ColorSet colors;   // green, blue, red, white, black
	std::bitset<5> specific; // x, y, z, p, s
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
	bool empty() const;

	bool operator==(ManaPattern const & mp) const;
};

class Cost {
private:
	std::vector<ManaPattern> symbols;
public:
	Cost() = default;
	Cost(char const * cost);
	Cost(std::string const & cost);

	unsigned convertedManaCost() const;
	bool hasColor(Color c) const;
	bool colorless() const;
	ColorSet colors() const;

	std::vector<ManaPattern> const & getSymbols() const { return symbols; }

	bool operator==(Cost const & cost) const;
	bool operator!=(Cost const & cost) const;
private:
	void parse(std::string const & cost);
	void sortSymbols();
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
