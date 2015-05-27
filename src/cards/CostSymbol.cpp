#include "CostSymbol.h"

namespace mtg {

CostSymbol::CostSymbol(Generic generic):
	generic(generic)
{}

CostSymbol::CostSymbol(Color c, Generic generic):
	generic(generic)
{
	colors.set(c);
}

CostSymbol::CostSymbol(Color c, Color c2)
{
	colors.set(c);
	colors.set(c2);
}

CostSymbol::CostSymbol(Specific s, Generic generic):
	specific(s),
	generic(generic)
{}

CostSymbol::CostSymbol(Specific s, Color c):
	specific(s)
{
	colors.set(c);
}

Cmc CostSymbol::cmc() const
{
	if( generic > 0 ) return generic;
	if( colored() ) return 1;
	return 0;
}

Cmc CostSymbol::min_cmc() const
{
	if( specific == phyrexian ) return 0;
	if( colored() ) return 1;
	return generic;
}

bool CostSymbol::hasColor(Color c) const
{
	return colors.hasColor(c);
}

bool CostSymbol::colorless() const
{
	return colors.colorless();
}

bool CostSymbol::colored() const
{
	return colors.colored();
}

bool CostSymbol::monoColored() const
{
    return colors.monoColored();
}

Color CostSymbol::firstColor() const
{
	return colors.color();
}

bool CostSymbol::operator==(CostSymbol const & mp) const
{
	return colors == mp.colors && generic == mp.generic && specific == mp.specific;
}

bool CostSymbol::operator!=(CostSymbol const & mp) const
{
	return ! (*this == mp);
}

} /* namespace mtg */
