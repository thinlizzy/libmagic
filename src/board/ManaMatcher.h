#ifndef MANAMATCHER_H_LIBMAGIC_2015_17_05
#define MANAMATCHER_H_LIBMAGIC_2015_17_05

#include "ManaPool.h"
#include <unordered_set>
#include <vector>

namespace mtg {

class ManaMatcher {
public:
	using Life = unsigned;
	using Visited = std::unordered_set<ManaPool::ManaCRef>;
	struct Solution {
		std::vector<ManaPool::ManaCRef> mana;
		Life life;
	};
	using Solutions = std::vector<Solution>;
private:
	Visited visited;
	Life life;
	Solutions solutions;
	size_t maxSolutions;
public:
	ManaMatcher(size_t maxSolutions);
	ManaMatcher & match(Cost const & cost, ManaPool const & manaPool, Mana::Annotations annotations);
	Solutions const & getSolutions() const { return solutions; }
private:
	bool doMatch(Cost::Symbols::const_reverse_iterator costIt, Cost::Symbols::const_reverse_iterator costEnd,
			ManaPool const & manaPool, Mana::Annotations annotations);
};

} /* namespace mtg */

#endif /* MANAMATCHER_H_ */
