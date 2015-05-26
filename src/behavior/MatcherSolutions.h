#ifndef MATCHERSOLUTIONS_H_LIBMAGIC_2015_05_25
#define MATCHERSOLUTIONS_H_LIBMAGIC_2015_05_25

#include "../board/ManaPool.h"
#include "../board/SimpleTypes.h"
#include <vector>

namespace mtg {

namespace matcher {

struct Solution {
	std::vector<ManaPool::ManaCRef> mana;
	Life life;
	bool operator==(Solution const & sol) const { return mana == sol.mana && life == sol.life; }
};

using Solutions = std::vector<Solution>;

}

}


#endif /* MATCHERSOLUTIONS_H_ */
