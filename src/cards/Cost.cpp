#include "Cost.h"

#include <numeric>
#include <algorithm>
#include <iterator>
#include <functional>

namespace mtg {

bool Cost::operator==(Cost const & cost) const
{
	return symbols == cost.symbols;
}

bool Cost::operator!=(Cost const & cost) const { return ! (*this == cost); }

unsigned Cost::convertedManaCost() const
{
	return std::accumulate(symbols.begin(),symbols.end(),0,[](unsigned t, ManaPattern symbol) {
		return t+symbol.cmc();
	});
}

bool Cost::hasColor(Color c) const
{
	return std::find_if(symbols.begin(),symbols.end(),[c](auto symbol){
		return symbol.hasColor(c);
	}) != symbols.end();
}

bool Cost::colorless() const
{
	return std::find_if_not(symbols.begin(),symbols.end(),[](auto symbol){
		return symbol.colorless();
	}) == symbols.end();
}

ColorSet Cost::colors() const
{
	return std::accumulate(symbols.begin(),symbols.end(),ColorSet{},[](ColorSet t, auto symbol) {
		return t |= symbol.colors;
	});
}

//

ManaPattern::ManaPattern():
	generic(0)
{}

ManaPattern::ManaPattern(Generic generic):
	generic(generic)
{
}

ManaPattern::ManaPattern(Generic generic, Color c):
	generic(generic)
{
	colors.set(c);
}

ManaPattern::ManaPattern(Color c, Color c2):
	generic(0)
{
	colors.set(c);
	colors.set(c2);
}

unsigned ManaPattern::cmc() const
{
	if( generic > 0 ) return generic;
	if( colors.any() ) return 1;
	return 0;
}

ManaPattern & ManaPattern::setChar(char c)
{
	switch(c) {
        case 'G': colors.set(green); break;
        case 'U': colors.set(blue); break;
        case 'R': colors.set(red); break;
        case 'W': colors.set(white); break;
        case 'B': colors.set(black); break;
        case 'X': specific.X = true; break;
        case 'Y': specific.Y = true; break;
        case 'Z': specific.Z = true; break;
        case 'P': specific.phyrexian = true; break;
        case 'S': specific.snow = true; break;
        default: throw std::invalid_argument(c + std::string(" is a invalid char to set mana pattern"));
	}
	return *this;
}

bool ManaPattern::hasColor(Color c) const
{
	return colors[c];
}

bool ManaPattern::colorless() const
{
	return ! colors.any();
}

bool ManaPattern::monoColored() const
{
    return colors.count() == 1;
}

bool ManaPattern::operator==(ManaPattern const & mp) const
{
	return colors == mp.colors && generic == mp.generic && specific == mp.specific;
}

}
