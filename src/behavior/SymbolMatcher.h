#ifndef SYMBOLMATCHER_H_LIBMAGIC_2015_05_25
#define SYMBOLMATCHER_H_LIBMAGIC_2015_05_25

#include "../board/ManaPool.h"
#include "../board/SimpleTypes.h"
#include "../cards/Cost.h"
#include "MatcherSolutions.h"
#include "ManaFilter.h"

namespace mtg {

namespace matcher {

class Symbol {
	Life life;
	ManaPool::ManaSet visited;
	ManaPool const * manaPool;
	ManaFilter manaFilter;
	size_t maxSolutions;
	Solutions * solutions;
public:
	bool match(Cost::Symbols const & symbols, ManaPool const & manaPool, ManaFilter manaFilter,
			size_t maxSolutions, Solutions & solutions);
private:
	bool doMatch(Cost::Symbols::const_iterator costIt, Cost::Symbols::const_iterator costEnd);
	void recordSolution();
	bool allDone() const;
};

}

} /* namespace mtg */

#endif /* SYMBOLMATCHER_H_ */
