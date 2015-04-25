#ifndef LAND_TYPE_H_LIBMAGIC_2015_04_18
#define LAND_TYPE_H_LIBMAGIC_2015_04_18

#define EE_VALUE(v)

namespace mtg {

// TODO use Type<LandType> in Card

// TODO add missing mtg land types after testing
enum LandType {
	swamp=1, forest, plains, mountain, island,
	desert,
	lair,
	locus,
	urza_s EE_VALUE("urza's"),
	mine,
	tower,
	powerPlant,
};

}

#endif
