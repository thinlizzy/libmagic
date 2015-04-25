#include "Player.h"
#include "Permanent.h"
#include "StackObject.h"

#include <vector>
#include <algorithm>

namespace mtg {

namespace {

CardIts getIndex(Cards & list)
{
	CardIts index;
	for( auto it = list.begin(); it != list.end(); ++it ) {
		index.push_back(it);
	}
	return index;
}

CardIt popInto(Cards & src, Cards & dest)
{
	auto result = src.begin();
	dest.splice(dest.begin(),src,result);
	return result;
}


CardIts popCards(int cards, Cards & src, Cards & dest)
{
	CardIts result;
	for( decltype(cards) n = 0; n < cards; ++n ) {
		result.push_back(popInto(src,dest));
	}
	return result;
}

}

Player::Player(std::string name):
    name(name)
{}

std::string const & Player::getName() const
{
    return name;
}

void Player::shuffleLibrary()
{
	// copy list iterators to index vector
	CardIts index = getIndex(cards.library);
	// shuffle it
	std::random_shuffle(index.begin(),index.end());
	// splice the iterators to a temp list
	Cards temp;
	for( auto it = index.begin(); it != index.end(); ++it ) {
		temp.splice(temp.end(),cards.library,*it);
	}
	// swap it back to list
	temp.swap(cards.library);
}

CardIt Player::draw()
{
	if( cards.library.empty() ) return cards.library.end();

	return popInto(cards.library,cards.hand);
}

CardIts Player::draw(int ncards)
{
	return popCards(ncards,cards.library,cards.hand);
}

CardIts Player::mill(int ncards)
{
	return popCards(ncards,cards.library,cards.graveyard);
}

CardIt Player::discardAtRandom()
{
	if( cards.hand.empty() ) return cards.hand.end();

	auto its = cards.randomSelect(1,Zone::hand);
	CardIt result = its[0];
    cards.move(result,Zone::hand,Zone::graveyard);
	return result;
}

void Player::shuffleGraveyardToLibrary()
{
	cards.library.splice(cards.library.end(),cards.graveyard);
	shuffleLibrary();
}

StackObject Player::cast(CardIt card, Zone zsrc)
{
    cards.move(card,zsrc,Zone::stack);
    return std::move(StackObject(*this,card));
}

Permanent Player::play(CardIt card, Zone zsrc)
{
    cards.move(card,zsrc,Zone::battlefield);
    return Permanent(*this,card);
}

}
