#ifndef COST_H_kjk4530k3n
#define COST_H_kjk4530k3n

#include <vector>
#include <string>
#include <bitset>
#include <ostream>
#include "types/Color.h"

namespace mtg {

struct ManaPattern {
	typedef std::bitset<10> Specific;	// green, blue, red, white, black, x, y, z, p, s
	Specific colors;
	unsigned char generic;

	ManaPattern();
	ManaPattern(unsigned char generic);
	ManaPattern(unsigned char generic, Color c);
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
	Cost();
	Cost(std::string const & cost);
	Cost(char const * cost);
	unsigned convertedManaCost() const;
	ManaPattern getColors() const;

	std::vector<ManaPattern> const & getSymbols() const { return symbols; }

	bool operator==(Cost const & cost) const;
	bool operator!=(Cost const & cost) const;
private:
	void parse(std::string const & cost);
};

std::ostream & operator<<(std::ostream & os, mtg::ManaPattern const & mp);
std::ostream & operator<<(std::ostream & os, mtg::Cost const & cost);
std::ostream & showcolors(std::ostream & os);

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
