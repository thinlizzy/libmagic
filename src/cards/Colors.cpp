#include "Colors.h"

namespace mtg {

ColorSet & ColorSet::set(Color colors)
{
	colorBits |= colorValue(colors);
	return *this;
}

bool ColorSet::hasColor(Color colors) const
{
	return colorBits & colorValue(colors);
}

bool ColorSet::colorless() const
{
	return colorBits == 0;
}

bool ColorSet::colored() const
{
	return ! colorless();
}

bool ColorSet::monoColored() const
{
	return colorValue(color()) != 0;
}

Color ColorSet::colors() const
{
	return Color(colorBits);
}

Color ColorSet::color() const
{
	switch(Color(colorBits)) {
		case Color::green: return Color::green;
		case Color::blue: return Color::blue;
		case Color::red: return Color::red;
		case Color::white: return Color::white;
		case Color::black: return Color::black;
		default: return {};
	}
}

char colorText(Color color)
{
	switch(color) {
		case Color::green: return 'G';
		case Color::blue: return 'U';
		case Color::red: return 'R';
		case Color::white: return 'W';
		case Color::black: return 'B';
		default: return ' ';
	}
}

std::uint8_t colorValue(Color color)
{
	return std::uint8_t(color);
}

}

