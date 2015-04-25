#ifndef CARDTYPE_H_LIBMAGIC_2015_04_18
#define CARDTYPE_H_LIBMAGIC_2015_04_18

namespace mtg {

enum CardType {
	land = 1, 
	sorcery = 2, 
	instant = 4, 
	creature = 8,
	artifact = 16, 
	enchantment = 32, 
	planeswalker = 64,
	tribal = 128,
};

}

#endif
