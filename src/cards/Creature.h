#ifndef CREATURE_H_f43kj50ghl495
#define CREATURE_H_f43kj50ghl495

#include <unordered_set>
#include "types/CreatureType.h"

namespace mtg {

class Creature {
public:
	std::unordered_set<CreatureType,std::hash<int>> types;
	int power;
	int toughness;
	bool operator==(Creature const & rhs) const { return power == rhs.power && toughness == rhs.toughness && types == rhs.types; }
};

}

#endif

