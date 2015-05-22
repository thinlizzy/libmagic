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
	return colors[c];
}

bool CostSymbol::colorless() const
{
	return colors.none();
}

bool CostSymbol::colored() const
{
	return colors.any();
}

bool CostSymbol::monoColored() const
{
    return colors.count() == 1;
}

Color CostSymbol::firstColor() const
{
	for( auto color = mtg::firstColor; color != nColors; color = Color(color+1) ) {
		if( hasColor(color) ) return color;
	}
	return mtg::colorless;
}

bool CostSymbol::operator==(CostSymbol const & mp) const
{
	return colors == mp.colors && generic == mp.generic && specific == mp.specific;
}

} /* namespace mtg */
