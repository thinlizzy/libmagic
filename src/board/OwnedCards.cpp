#include "OwnedCards.h"
#include <cstdlib>

namespace {

double dbRand()
{
	return std::rand() / double(RAND_MAX);
}

unsigned iRand(unsigned max)
{
	return unsigned((max-1) * dbRand());
}

}

namespace mtg {

Cards & OwnedCards::fromZone(Zone zone)
{
	return this->*listFromZone[int(zone)];
}

CardIts OwnedCards::randomSelect(int cards, Zone zone)
{
	Cards & src = fromZone(zone);
	// get initial sample from src
	CardIts result;
	result.reserve(cards);
	auto it = src.begin();
	for( int c = 0; c < cards && it != src.end(); ++c,++it ) {
		result.push_back(it);
	}
	// replace next elements
	for( double d = result.size()+1; it != src.end(); ++d,++it ) {
		double prob = result.size() / d;
		if( dbRand() < prob ) {
			result[iRand(result.size())] = it;
		}
	}
	return result;
}

void OwnedCards::move(CardIt it, Zone zsrc, Zone zdest)
{
	Cards & src = fromZone(zsrc);
	Cards & dest = fromZone(zdest);
	dest.splice(dest.begin(),src,it);
}

void OwnedCards::moveCards(CardIts & its, Zone zsrc, Zone zdest)
{
	Cards & src = fromZone(zsrc);
	Cards & dest = fromZone(zdest);
    for( CardIt it : its ) {
		dest.splice(dest.begin(),src,it);
	};
}



Cards OwnedCards::*OwnedCards::listFromZone[int(Zone::zones)] = { 
	&OwnedCards::library,
	&OwnedCards::hand,
	&OwnedCards::graveyard,
	&OwnedCards::exile,
	&OwnedCards::hiddenExile,
	&OwnedCards::battlefield,
	&OwnedCards::stack,
	&OwnedCards::command,
	&OwnedCards::ante,
};

}
