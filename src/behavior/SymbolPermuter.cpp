#include "SymbolPermuter.h"
#include <algorithm>

namespace mtg {

namespace matcher {

void Permuter::tryPermutations(Cost::Symbols const & symbols, Solver solver)
{
	currentMatcher.resize(symbols.size());
	this->symbols = &symbols;
	this->solver = solver;
	done = false;
	tryPermutations(0);
}

int symbolRank(CostSymbol symbol)
{
	auto cv = colorValue(symbol.colors.colors());
	if( cv > 0 ) return cv;

	switch( symbol.specific ) {
		case CostSymbol::snow: return 1000;
		case CostSymbol::phyrexian: return 1001;
		case CostSymbol::X:
		case CostSymbol::Y:
		case CostSymbol::Z:
			return 10000;
		default:
			return 100 + symbol.generic;
	}
}

// decouple and serialize a symbol matcher (e.g: W/P = list with [W P]. 2/W = [W 1 1]). use colored first
auto symbolMatchers(CostSymbol symbol)
{
	std::vector<CostSymbol> result;
	if( symbol.colored() ) {
		for( auto color : ColorList() ) {
			if( symbol.hasColor(color) ) {
				result.push_back(CostSymbol(color));
			}
		}
	}
	if( symbol.specific != 0 ) {
		result.push_back(CostSymbol(symbol.specific));
	} else
	if( symbol.generic > 0 ) {
		result.push_back(CostSymbol(symbol.generic));
	}
	return result;
}

bool Permuter::tryPermutations(size_t pos)
{
	if( done ) return true;

	if( pos == currentMatcher.size() ) {
		// symbols will be sorted like colored,snow,P,generic,XYZ to increase the chance of having an early solution
		auto currentSymbols = currentMatcher;
		std::sort(currentSymbols.begin(),currentSymbols.end(),[](auto s1, auto s2) {
			return symbolRank(s1) < symbolRank(s2);
		});

		// TODO expand generic matchers to have 1 (and remove that damned for loop). it will make multiple solutions available

		done = solver(currentSymbols);
	    return done;
	}

	for( auto symbol : symbolMatchers((*symbols)[pos]) ) {
		currentMatcher[pos] = symbol;
		if( tryPermutations(pos+1) ) return true;
	}

	return false;
}

}

} /* namespace mtg */
