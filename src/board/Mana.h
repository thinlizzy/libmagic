#ifndef MANA_H_LIBMAGIC_2015_21_05
#define MANA_H_LIBMAGIC_2015_21_05

#include "../cards/Color.h"

namespace mtg {

struct Mana {
	enum Source { snow = 1, };
	enum Annotation : unsigned {
		spells = 1, abilities = 2,
		upkeep = 4,
		artifact = 8, creature = 16,

		lastAnnotation = 16,
	};
	using Annotations = unsigned;

	Color color;
	Source source;
	Annotations annotations;

    int rank() const {
    	return int(annotations) * 100 + (color == colorless ? 0 : int(color)+1) * 10 + int(source);
    }

	bool operator==(Mana const & mana) const {
		return color == mana.color && source == mana.source && annotations == mana.annotations;
	}

	bool operator!=(Mana const & mana) const {
		return !operator==(mana);
	}

	bool allowsRestrictions(Annotations restrictions) const {
		return (annotations & restrictions) == annotations;
	}
};

}

#endif /* MANA_H_ */
