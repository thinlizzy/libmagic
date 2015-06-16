#include "ManaMatcher.h"
#include "SymbolMatcher.h"
#include "SymbolPermuter.h"

namespace mtg {

namespace matcher {

Mana::Mana(size_t maxSolutions):
	maxSolutions(maxSolutions)
{
	solutions.reserve(maxSolutions);
}

Mana & Mana::match(Cost const & cost, ManaPool const & manaPool, ManaFilter manaFilter)
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

	Permuter permuter;
	permuter.tryPermutations(cost.symbols,[this,&manaPool,&manaFilter](Cost::Symbols const & symbols) -> bool {
		Symbol matcher;
		matcher.match(symbols,manaPool,manaFilter,maxSolutions,solutions);
		return solutions.size() >= maxSolutions;
	});

	return *this;
}

} /* namespace matcher */

} /* namespace mtg */
