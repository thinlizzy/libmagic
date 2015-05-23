#ifndef COLORS_H_LIBMAGIC_2015_22_05
#define COLORS_H_LIBMAGIC_2015_22_05

#include <cstdint>
#include <functional>
#include <iterator>

namespace mtg {

enum class Color : std::uint8_t {
	colorless = 0,
	green = 1,
	blue = 2,
	red = 4,
	white = 8,
	black = 16,
	first = 1,
	last = 32,
};

char colorText(Color color);
std::uint8_t colorValue(Color color);

class ColorSet {
	friend struct std::hash<ColorSet>;
	std::uint8_t colorBits = 0;
public:
	ColorSet & set(Color colors);
	bool hasColor(Color colors) const;
	bool colorless() const;
	bool colored() const;
    bool monoColored() const;
    Color color() const;
    Color colors() const;
	bool operator==(ColorSet const & cs) const { return colorBits == cs.colorBits; }
	bool operator!=(ColorSet const & cs) const { return ! (*this == cs); }
};

class ColorIterator: public std::iterator<std::forward_iterator_tag, Color> {
	Color color;
public:
	explicit ColorIterator(Color color): color(color) {}
	typename ColorIterator::value_type operator*() { return color; }
	ColorIterator & operator++() { color = Color(colorValue(color) << 1); return *this; }
	ColorIterator operator++(int) { auto result = *this; ++*this; return result; }
	bool operator==(ColorIterator const & it) const { return color == it.color; }
	bool operator!=(ColorIterator const & it) const { return ! (*this == it); }
};

struct ColorList {
	ColorIterator begin() { return ColorIterator{Color::first}; }
	ColorIterator end() { return ColorIterator{Color::last}; }
};

} /* namespace mtg */

namespace std {

template<>
struct hash<mtg::Color> {
    size_t operator()(mtg::Color const & c) const {
        return std::hash<decltype(colorValue(c))>()(colorValue(c));
    }
};

template<>
struct hash<mtg::ColorSet> {
    size_t operator()(mtg::ColorSet const & cs) const {
        return std::hash<decltype(cs.colors())>()(cs.colors());
    }
};

}

#endif
