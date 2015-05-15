#include "Factory4th.h"

namespace mtg {

Factory4th::Factory4th():
	id()
{
	createBasicLands();
	// create non-basic lands
	createColorless();
	// create black
		// create creatures
		// create enchantments
		// create sorceries
		// create instants
	// ...
}

Card Factory4th::newCard(CardStat const & cardStat, Expansion exp)
{
	Card result(cardStat);
	result.expansion = exp;
	result.id = ++id;
	return result;
}


void Factory4th::createBasicLands()
{
	for( int v = 1; v <= 3; ++v ) {
		cards.push_back(newCard(prototypes->forest,Expansion::fourth));
		cards.push_back(newCard(prototypes->island,Expansion::fourth));
		cards.push_back(newCard(prototypes->mountain,Expansion::fourth));
		cards.push_back(newCard(prototypes->plains,Expansion::fourth));
		cards.push_back(newCard(prototypes->swamp,Expansion::fourth));
	}
}

void Factory4th::createColorless()
{
	// create artifacts
	CardStat alladinsLamp = prototypes->artifact;
	alladinsLamp.name = "Alladin's Lamp";
	alladinsLamp.cost = parseCost("10");
	alladinsLamp.text = 
		"{X},{T}: The next time you would draw a card this turn, instead look at the top X cards of your library, "
		"put all but one of them on the bottom of your library in a random order, then draw a card. X can't be 0.";

	cards.push_back(newCard(alladinsLamp,Expansion::fourth));

	// create artifact creatures
}


}
