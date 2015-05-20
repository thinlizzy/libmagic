#ifndef COLOR_H_LIBMAGIC_2015_04_17
#define COLOR_H_LIBMAGIC_2015_04_17

#include <bitset>

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
    colorless = 10,
    firstColor = green,
};

using ColorSet = std::bitset<nColors>;

constexpr char colorText[] = "GURWB";

/*
class ColorSet {
	unsigned char colors;
	static unsigned char colorBit(Color c) { return 1 << (c+1); }
public:
	ColorSet(): colors{} {}
	bool hasColor(Color c) const { return colors & colorBit(c); }
	bool setColor(Color c) { colors |= colorBit(c); }
	bool colorless() const { return colors == 0; }
    bool monoColored() const { return ! colorless() && (colors & (colors-1)) == 0; }
};
 */

}

#endif
