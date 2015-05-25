#include "ManaMatcher.h"
#include "MatchRangeIterator.h"
#include <vector>
#include <algorithm>

namespace mtg {

// TODO after implementation, consider removing indices for annotated mana. they seem useless

// return all (non-visited) mana pool units for a symbol - use the indices (color,snow) to be more greedy
// generic mana and even colored mana can match a lot of combinations
// for each tested group, it needs to match mana.allowsRestrictions(annotations)

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

//

ManaMatcher::ManaMatcher(size_t maxSolutions):
	maxSolutions(maxSolutions)
{
	solutions.reserve(maxSolutions);
}

ManaMatcher & ManaMatcher::match(Cost const & cost, ManaPool const & manaPool, Mana::Annotations annotations)
{
	solutions.clear();

	// test the obvious solution
	if( cost.convertedManaCost() == 0 ) {
		Solution solution;
		solution.life = 0;
		solutions.push_back(std::move(solution));
		return *this;
	}

	// early bail out on impossible solutions
	if( manaPool.mana().size() < cost.minimumManaCost() ) return *this;
/*
	CostSymbolPermuter permuter;
	permuter.tryPermutations(cost.symbols,[this,&manaPool,&annotations](Cost::Symbols const & symbols) -> bool {
		SymbolMatcher matcher;
		matcher.match(symbols,manaPool,annotations,maxSolutions,solutions);
		return solutions.size() >= maxSolutions;
	});
*/
	currentMatcher.resize(cost.symbols.size());
	tryPermutations(0,cost.symbols,manaPool,annotations);
	return *this;
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

bool ManaMatcher::tryPermutations(unsigned pos, Cost::Symbols const & symbols, ManaPool const & manaPool, Mana::Annotations annotations)
{
	if( pos == currentMatcher.size() ) {
		// symbols will be sorted like colored,snow,P,generic,XYZ to increase the chance of having an early solution
		auto currentSymbols = currentMatcher;
		std::sort(currentSymbols.begin(),currentSymbols.end(),[](auto s1, auto s2) {
			return symbolRank(s1) < symbolRank(s2);
		});

		// TODO expand generic matchers to have 1 (and remove that damned for loop). it will make multiple solutions available

		// clear status and try a match
		visited.clear();
		life = 0;
		doMatch(currentSymbols.begin(),currentSymbols.end(),manaPool,annotations);
	    return solutions.size() >= maxSolutions;
	}

	for( auto symbol : symbolMatchers(symbols[pos]) ) {
		currentMatcher[pos] = symbol;
		if( tryPermutations(pos+1,symbols,manaPool,annotations) ) return true;
	}

	return false;
}

bool ManaMatcher::doMatch(Cost::Symbols::const_iterator costIt, Cost::Symbols::const_iterator costEnd,
		ManaPool const & manaPool, Mana::Annotations annotations)
{
	if( solutions.size() >= maxSolutions ) return true; // terminate early if all solutions were recorded
	if( costIt == costEnd ) {
		// all cost is consumed, so record a solution
		Solution solution;
		solution.life = life;
		solution.mana.assign(visited.begin(),visited.end());
		// sort mana to compare with previous solutions
		std::sort(solution.mana.begin(),solution.mana.end(),[](auto mr1, auto mr2) {
			return mr1->rank() < mr2->rank();
		});
		if( std::find(solutions.begin(),solutions.end(),solution) == solutions.end() ) {
			solutions.push_back(std::move(solution));
		}
		return true;
	}

	auto symbol = *costIt;
	if( symbol.specific == CostSymbol::X || symbol.specific == CostSymbol::Y || symbol.specific == CostSymbol::Z ) {
		// just consume it
		if( doMatch(std::next(costIt),costEnd,manaPool,annotations) ) {
			return true;
		}
	} else
	if( symbol.specific == CostSymbol::phyrexian ) {
		life += 2;
		if( doMatch(std::next(costIt),costEnd,manaPool,annotations) ) {
			return true;
		}
		life -= 2;
	} else
	if( symbol.generic > 0 ) {
		std::vector<ManaPool::ManaCRef> gen;
		for( auto match : MatchRange{manaPool,visited,symbol,annotations} ) {
			gen.push_back(match);
			if( gen.size() >= symbol.generic ) break;
		}
		if( gen.size() < symbol.generic ) return false; // not enough to match generic mana

		for( auto elem : gen ) {
			visited.insert(elem);
		}
		if( doMatch(std::next(costIt),costEnd,manaPool,annotations) ) {
			return true;
		}
		for( auto elem : gen ) {
			visited.erase(elem);
		}
	} else {
		for( auto match : MatchRange{manaPool,visited,symbol,annotations} ) {
			visited.insert(match);
			if( doMatch(std::next(costIt),costEnd,manaPool,annotations) ) {
				return true;
			}
			visited.erase(match);
		}
	}

	return false;  // exhausted all matchers for a symbol, so give up on this iteration
}

} /* namespace mtg */
