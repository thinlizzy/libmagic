#ifndef COLOR_H_LIBMAGIC_2015_04_17
#define COLOR_H_LIBMAGIC_2015_04_17

namespace mtg {

// TODO this needs redesign. review the interactions with Card, Colors.h and Cost.ManaPattern

// TODO make colorless at the first value = 0, but see other TODOs first

// TODO use bit values?
enum Color {
	green,
	blue,
	red,
	white,
	black,
	nColors,
    colorless,
};

}

#endif
