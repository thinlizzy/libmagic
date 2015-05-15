#include "Card.h"
#include <stdexcept>

#include <sstream>
#include <algorithm>
#include <iterator>
#include "types/CardType.h"
#include "types/SuperType.h"
#include "types/TypeToStr.h"

namespace mtg {

CardStat::CardStat():
	supertypes(),
	cardTypes(),
	spellType(),
	artifactType(),
	enchantmentType(),
	tribalType()
{
}

bool CardStat::hasColor(Color color) const
{
	return colors()[color];
}

ColorSet CardStat::colors() const
{
	if( colors_ ) return *colors_;
	return cost.colors();
}

bool CardStat::operator==(CardStat const & card) const
{
	return name == card.name
		&& artifactType == card.artifactType
		&& cardTypes == card.cardTypes
		&& colors_ == card.colors_
		&& cost == card.cost
		&& creature == card.creature
		&& enchantmentType == card.enchantmentType
		&& land == card.land
		&& planeswalker == card.planeswalker
		&& spellType == card.spellType
		&& supertypes == card.supertypes
		&& text == card.text
		&& tribalType == card.tribalType
	;
}

bool CardStat::operator!=(CardStat const & card) const
{
    return ! (*this == card);
}

bool CardStat::operator<(CardStat const & card) const
{
	return name < card.name;
}

template<typename C, typename F>
std::string fetchTypes(C const & container, F func)
{
	if( container.empty() ) return "";

	std::ostringstream os(" ");
	std::transform(container.begin(),container.end(),std::ostream_iterator<std::string>(os," "),func);
	return os.str();
}

std::string CardStat::types() const
{
	std::string result =
		(supertypes ? typeToStr(SuperType(supertypes)) + " " : "") +
		typeToStr(CardType(cardTypes)) +
		(artifactType ? std::string(" ") + typeToStr(artifactType) : "") +
		(enchantmentType ? std::string(" ") + typeToStr(enchantmentType) : "") +
		(spellType ? std::string(" ") + typeToStr(spellType) : "") +
		(tribalType ? std::string(" ") + typeToStr(tribalType) : "") +
		(planeswalker ? std::string(" ") + typeToStr(planeswalker->type) : "")
	;
	if( land ) {
		result += fetchTypes(land->types,&typeToStr<LandType>);
	}
	if( creature ) {
		result += fetchTypes(creature->types,&typeToStr<CreatureType>);
	}

	return result;
}

// Card //

Card::Card(CardStat const & mainStat):
	id(),
	expansion(),
	rarity(),
	kind(),
	mainStat(mainStat),
	faceId(),
	secondaryFaceId()
{
}

Card::Card(CardKind kind, CardStat const & mainStat, CardStat const & secondaryStat):
	id(),
	expansion(),
	rarity(),
	kind(kind),
	mainStat(mainStat),
	secondaryStat(secondaryStat),
	faceId(),
	secondaryFaceId()
{
}

bool Card::isLand() const
{
    return bool(mainStat.land);
}

bool Card::hasColor(Color color) const
{
	return colors()[color];
}

ColorSet Card::colors() const
{
	auto result = mainStat.colors();
	if( kind == splitCard ) {
		if( ! secondaryStat ) throw std::logic_error("split cards should have a secondary stat");
		result |= secondaryStat->colors();
	}
	return result;
}

bool Card::hasName(std::string const & name) const
{
	return mainStat.name == name || (secondaryStat && secondaryStat->name == name);
}

std::string Card::displayName() const
{
	std::string result = mainStat.name;
	if( secondaryStat ) {
		result += " // " + secondaryStat->name;
	}
	return result;
}

bool Card::operator==(Card const & card) const
{
	return id == card.id
		&& expansion == card.expansion
		&& rarity == card.rarity
		&& kind == card.kind
		&& mainStat == card.mainStat
		&& secondaryStat == card.secondaryStat
	;
}

bool Card::operator!=(Card const & card) const { return ! (*this == card); }

}
