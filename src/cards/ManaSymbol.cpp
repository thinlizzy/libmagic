#include "ManaSymbol.h"

namespace mtg {

ManaSymbol::ManaSymbol():
	generic(0)
{}

ManaSymbol::ManaSymbol(Generic generic):
	generic(generic)
{
}

ManaSymbol::ManaSymbol(Generic generic, Color c):
	generic(generic)
{
	colors.set(c);
}

ManaSymbol::ManaSymbol(Color c, Color c2):
	generic(0)
{
	colors.set(c);
	colors.set(c2);
}

Cmc ManaSymbol::cmc() const
{
	if( generic > 0 ) return generic;
	if( colored() ) return 1;
	return 0;
}

Cmc ManaSymbol::min_cmc() const
{
	if( specific == phyrexian ) return 0;
	if( colored() ) return 1;
	return generic;
}

bool ManaSymbol::hasColor(Color c) const
{
	return colors[c];
}

bool ManaSymbol::colorless() const
{
	return colors.none();
}

bool ManaSymbol::colored() const
{
	return colors.any();
}

bool ManaSymbol::monoColored() const
{
    return colors.count() == 1;
}

bool ManaSymbol::operator==(ManaSymbol const & mp) const
{
	return colors == mp.colors && generic == mp.generic && specific == mp.specific;
}

} /* namespace mtg */
