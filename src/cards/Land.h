#ifndef LAND_H_jk32j4kljdkldsf
#define LAND_H_jk32j4kljdkldsf

#include <unordered_set>
#include "types/LandType.h"

namespace mtg {

class Land {
public:
	bool basic;
	std::unordered_set<LandType,std::hash<int>> types;
	bool operator==(Land const & rhs) const { return basic == rhs.basic && types == rhs.types; }
};

}

#endif
