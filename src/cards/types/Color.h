#ifndef COLOR_H_LIBMAGIC_2015_04_17
#define COLOR_H_LIBMAGIC_2015_04_17

namespace mtg {

// enumeration used to represent unique color values and even a colorless one if the context applies
// they are conveniently ordered to work as array indices and quantities for bit shifting too
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
