#ifndef MANAMATCHER_H_LIBMAGIC_2015_17_05
#define MANAMATCHER_H_LIBMAGIC_2015_17_05

#include "../board/ManaPool.h"
#include "../cards/Cost.h"
#include "MatcherSolutions.h"
#include "ManaFilter.h"
#include <functional>

namespace mtg {

namespace matcher {

class Mana {
	Solutions solutions;
	size_t maxSolutions;
public:
	Mana(size_t maxSolutions = 1);
	Mana & match(Cost const & cost, ManaPool const & manaPool, ManaFilter manaFilter);
	explicit operator bool() const { return ! solutions.empty(); }
	Solutions const & getSolutions() const { return solutions; }
};

} /* namespace matcher */

} /* namespace mtg */

#endif /* MANAMATCHER_H_ */
