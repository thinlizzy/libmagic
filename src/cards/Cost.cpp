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

Cmc Cost::convertedManaCost() const
{
	return std::accumulate(symbols.begin(),symbols.end(),0,[](Cmc t, CostSymbol symbol) {
		return t+symbol.cmc();
	});
}

Cmc Cost::minimumManaCost() const
{
	return std::accumulate(symbols.begin(),symbols.end(),0,[](Cmc t, CostSymbol symbol) {
		return t+symbol.min_cmc();
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

}
