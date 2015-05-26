#include "ManaMatcher.h"
#include "SymbolMatcher.h"
#include "SymbolPermuter.h"

namespace mtg {

// TODO after implementation, consider removing indices for annotated mana. they seem useless

// return all (non-visited) mana pool units for a symbol - use the indices (color,snow) to be more greedy
// generic mana and even colored mana can match a lot of combinations
// for each tested group, it needs to match mana.allowsRestrictions(annotations)

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
		matcher::Solution solution;
		solution.life = 0;
		solutions.push_back(std::move(solution));
		return *this;
	}

	// early bail out on impossible solutions
	if( manaPool.mana().size() < cost.minimumManaCost() ) return *this;

	matcher::Permuter permuter;
	permuter.tryPermutations(cost.symbols,[this,&manaPool,&annotations](Cost::Symbols const & symbols) -> bool {
		matcher::Symbol matcher;
		matcher.match(symbols,manaPool,annotations,maxSolutions,solutions);
		return solutions.size() >= maxSolutions;
	});

	return *this;
}

} /* namespace mtg */
