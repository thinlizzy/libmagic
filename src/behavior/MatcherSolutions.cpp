#include "MatcherSolutions.h"
#include <algorithm>

namespace mtg {

namespace matcher {

bool Solution::operator==(Solution const & sol) const
{
	return life == sol.life
		&& mana.size() == sol.mana.size()
		&& std::equal(mana.begin(),mana.end(),sol.mana.begin(),[](auto mr1, auto mr2) {
			return *mr1 == *mr2;
		});
}

}

}
