#include <algorithm>
#include "SymbolMatcher.h"
#include "MatchRangeIterator.h"

namespace mtg {

namespace matcher {

bool Symbol::match(Cost::Symbols const & symbols, ManaPool const & manaPool, ManaFilter manaFilter,
		size_t maxSolutions, Solutions & solutions)
{
	life = 0;
	visited.clear();
	this->manaPool = &manaPool;
	this->manaFilter = manaFilter;
	this->maxSolutions = maxSolutions;
	this->solutions = &solutions;
	doMatch(symbols.begin(),symbols.end());
	return allDone();
}

bool Symbol::doMatch(Cost::Symbols::const_iterator costIt, Cost::Symbols::const_iterator costEnd)
{
	if( allDone() ) return true;

	if( costIt == costEnd ) {
		recordSolution();
		return allDone();
	}

	auto symbol = *costIt;
	if( symbol.specific == CostSymbol::X || symbol.specific == CostSymbol::Y || symbol.specific == CostSymbol::Z ) {
		// just consume it
		if( doMatch(std::next(costIt),costEnd) ) {
			return true;
		}
	} else
	if( symbol.specific == CostSymbol::phyrexian ) {
		life += 2;
		if( doMatch(std::next(costIt),costEnd) ) {
			return true;
		}
		life -= 2;
	} else {
		for( auto match : MatchRange{*manaPool,visited,symbol,manaFilter} ) {
			visited.insert(match);
			if( doMatch(std::next(costIt),costEnd) ) {
				return true;
			}
			visited.erase(match);
		}
	}

	return false;  // exhausted all matchers for a symbol, so give up on this iteration
}

bool Symbol::allDone() const
{
	return solutions->size() >= maxSolutions;
}

void Symbol::recordSolution()
{
	Solution solution;
	solution.life = life;
	solution.mana.assign(visited.begin(),visited.end());
	// sort mana to compare with previous solutions
	std::sort(solution.mana.begin(),solution.mana.end(),[](auto mr1, auto mr2) {
		return mr1->rank() < mr2->rank();
	});
	if( std::find(solutions->begin(),solutions->end(),solution) == solutions->end() ) {
		solutions->push_back(std::move(solution));
	}
}

}

} /* namespace mtg */
