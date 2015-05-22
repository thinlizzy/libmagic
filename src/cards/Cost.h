#ifndef COST_H_kjk4530k3n
#define COST_H_kjk4530k3n

#include <vector>
#include "Color.h"
#include "CostSymbol.h"

namespace mtg {

class Cost {
public:
	using Symbols = std::vector<CostSymbol>;
	Symbols symbols;

	Cost() = default;

	Cmc convertedManaCost() const;
	Cmc minimumManaCost() const;
	bool hasColor(Color c) const;
	bool colorless() const;
	ColorSet colors() const;

	bool operator==(Cost const & cost) const;
	bool operator!=(Cost const & cost) const;
};

}

#endif
