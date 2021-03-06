#include "SymbolPermuter.h"
#include <algorithm>

namespace mtg {

namespace matcher {

void Permuter::tryPermutations(Cost::Symbols const & symbols, Solver solver)
{
	currentMatcher.resize(symbols.size());
	matchers.clear();
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

		// don't call solver if a matcher was already recorded
		if( std::find(matchers.begin(),matchers.end(),currentSymbols) != matchers.end() ) return false;
		matchers.push_back(currentSymbols);

		// expand generic matchers to have only 1. it will make multiple solutions available
		auto generic = 0;
		for( auto & symbol : currentSymbols ) {
			if( symbol.generic > 1 ) {
				generic += symbol.generic-1;
				symbol.generic = 1;
			}
		}
		for( auto g = 0; g != generic; ++g ) {
			currentSymbols.push_back(CostSymbol(1));
		}

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
