#ifndef BEHAVIOR_MANAFILTER_H_LIBMAGIC_2015_06_16
#define BEHAVIOR_MANAFILTER_H_LIBMAGIC_2015_06_16

#include "../board/ManaPool.h"

namespace mtg {

namespace matcher {

// returns true if mana symbol needs to be filtered out
using ManaFilter = std::function<bool(ManaPool::ManaCRef)>;

} /* namespace matcher */

} /* namespace mtg */



#endif /* BEHAVIOR_MANAFILTER_H_ */
