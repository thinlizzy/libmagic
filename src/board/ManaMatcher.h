#ifndef MANAMATCHER_H_LIBMAGIC_2015_17_05
#define MANAMATCHER_H_LIBMAGIC_2015_17_05

#include "ManaPool.h"
#include "../cards/Cost.h"
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
		bool operator==(Solution const & sol) const { return mana == sol.mana && life == sol.life; }
	};
	using Solutions = std::vector<Solution>;
private:
	Visited visited;
	Life life;
	Solutions solutions;
	size_t maxSolutions;
public:
	ManaMatcher(size_t maxSolutions = 1);
	// annotations argument is generated by someFunction(gameStep, sourceOfCost)
	ManaMatcher & match(Cost const & cost, ManaPool const & manaPool, Mana::Annotations annotations = 0);
	explicit operator bool() const { return ! solutions.empty(); }
	Solutions const & getSolutions() const { return solutions; }
private:
	bool doMatch(Cost::Symbols::const_reverse_iterator costIt, Cost::Symbols::const_reverse_iterator costEnd,
			ManaPool const & manaPool, Mana::Annotations annotations);
};

} /* namespace mtg */

#endif /* MANAMATCHER_H_ */