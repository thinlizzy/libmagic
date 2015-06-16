#ifndef MANA_H_LIBMAGIC_2015_21_05
#define MANA_H_LIBMAGIC_2015_21_05

#include "../cards/Colors.h"

namespace mtg {

struct Mana {
	enum Source { snow = 1, };

	Color color;
	Source source;

    int rank() const {
    	return colorValue(color) * 10 + int(source);
    }

	bool operator==(Mana const & mana) const {
		return color == mana.color && source == mana.source;
	}

	bool operator!=(Mana const & mana) const {
		return !operator==(mana);
	}
};

}

#endif /* MANA_H_ */
