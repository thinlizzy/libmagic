#ifndef CARD_H_Jjd3kjrekdsfj
#define CARD_H_Jjd3kjrekdsfj

#include <string>
#include <experimental/optional>
#include "Cost.h"
#include "Color.h"
#include "Land.h"
#include "Creature.h"
#include "Planeswalker.h"
#include "types/ArtifactType.h"
#include "types/CreatureType.h"
#include "types/EnchantmentType.h"
#include "types/SpellType.h"
#include "types/Expansion.h"
#include "types/Rarity.h"

namespace mtg {

class CardStat {
public:
	std::string name;
	Cost cost;

	std::experimental::optional<ColorSet> colors_;
	std::string text;

	unsigned supertypes;		// SuperType bit set
	unsigned cardTypes;			// CardType bit set
	std::experimental::optional<Land> land;
	std::experimental::optional<Creature> creature;
	std::experimental::optional<Planeswalker> planeswalker;
	SpellType spellType;				// sorceries and instants only
	ArtifactType artifactType;
	EnchantmentType enchantmentType;
	CreatureType tribalType;

	CardStat();
	bool hasColor(Color color) const;
	ColorSet colors() const;
	std::string types() const;
	bool operator==(CardStat const & card) const;
	bool operator!=(CardStat const & card) const;
	bool operator<(CardStat const & card) const;
};

// TODO move to a separate enum and parse it
enum CardKind { normalCard, splitCard, flipCard, transformCard, };

typedef unsigned CardId;

class Card {
public:
	// TODO review the need of this id. Need to find something to differentiate card reprints. Perhaps a collector number, instead
	CardId id;
	Expansion expansion;
	Rarity rarity;
	CardKind kind;
	CardStat mainStat;
	std::experimental::optional<CardStat> secondaryStat;
	unsigned faceId;
	unsigned secondaryFaceId;

	explicit Card(CardStat const & mainStat = CardStat());
	Card(CardKind kind, CardStat const & mainStat, CardStat const & secondaryStat);
    bool isLand() const;
	bool hasColor(Color color) const;
	ColorSet colors() const;
	bool hasName(std::string const & name) const;
	std::string displayName() const;
	bool operator==(Card const & card) const;
	bool operator!=(Card const & card) const;
};

}

#endif
