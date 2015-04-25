#ifndef PLANESWALKER_H_jf4440fgl32b
#define PLANESWALKER_H_jf4440fgl32b

#include "types/PlaneswalkerType.h"

namespace mtg {

class Planeswalker {
public:
	PlaneswalkerType type;
	int loyalty;
	bool operator==(Planeswalker const & rhs) const { return loyalty == rhs.loyalty && type == rhs.type; }
};

}

#endif
