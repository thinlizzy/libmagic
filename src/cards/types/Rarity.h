#ifndef RARITY_H_LIBMAGIC_2015_04_17
#define RARITY_H_LIBMAGIC_2015_04_17

#define EE_VALUE(v)

namespace mtg {

enum Rarity {
	common = 1,
	uncommon,
	rare,
	mythicRare EE_VALUE("mythic rare"),
	timeshifted,
};
// sentinel value is used for some generated cards which have no rarity, like generated basic lands and tokens

}

#endif
