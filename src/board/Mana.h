#ifndef MANA_H_LIBMAGIC_2015_21_05
#define MANA_H_LIBMAGIC_2015_21_05

#include "../cards/Colors.h"

namespace mtg {

struct Mana {
	enum Source { snow = 1, };

	// TODO remove these annotations from here and move them to the rules engine
	enum Annotation : unsigned {
		spells = 1, abilities = 2,
		cumulativeUpkeepCost = 4,
		artifact = 8, creature = 16,

		firstAnnotation = 1,
		lastAnnotation = 16,
	};
	using Annotations = unsigned;

	Color color;
	Source source;
	Annotations annotations;

    int rank() const {
    	return int(annotations) * 100 + colorValue(color) * 10 + int(source);
    }

	bool operator==(Mana const & mana) const {
		return color == mana.color && source == mana.source && annotations == mana.annotations;
	}

	bool operator!=(Mana const & mana) const {
		return !operator==(mana);
	}

	// TODO move this checking to the matcher. pass a functor to it that filters the mana. the functor will consult the rules engine (a map from mana ref to some custom annotation system)
	bool allowsRestrictions(Annotations restrictions) const {
		return (annotations & restrictions) == annotations;
	}
};

}

#endif /* MANA_H_ */
