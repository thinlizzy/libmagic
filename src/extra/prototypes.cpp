#include "prototypes.h"

#include "../cards/Land.h"
#include "../cards/types/CardType.h"

namespace mtg {

singleton<Prototypes> prototypes;

CardStat createCard(CardType type)
{
	CardStat result;
	result.cardTypes = type;
	return result;
}

CardStat createLand()
{
	CardStat result = createCard(land);
	Land landData;
	landData.basic = true;
	result.land = landData;
	return result;
}

CardStat createCreature()
{
	CardStat result = createCard(creature);
	Creature creatureData;
	creatureData.power = 0;
	creatureData.toughness = 0;
	result.creature = creatureData;
	return result;
}

CardStat createPlaneswalker()
{
	CardStat result = createCard(planeswalker);
	Planeswalker planeData;
	planeData.loyalty = 0;
	result.planeswalker = planeData;
	return result;
}

Prototypes::Prototypes():
	land(createLand()),
	creature(mtg::createCreature()),
	artifact(createCard(mtg::artifact)),
	enchantment(createCard(mtg::enchantment)),
	aura(createAura()),
	sorcery(createCard(mtg::sorcery)),
	instant(createCard(mtg::instant)),
	planeswalker(createPlaneswalker()),
	forest(createBasicLand("Forest",mtg::forest,Color::green)),
	island(createBasicLand("Island",mtg::island,Color::blue)),
	mountain(createBasicLand("Mountain",mtg::mountain,Color::red)),
	plains(createBasicLand("Plains",mtg::plains,Color::white)),
	swamp(createBasicLand("Swamp",mtg::swamp,Color::black))
{
}

CardStat Prototypes::createBasicLand(std::string const & name, LandType type, Color color)
{
	CardStat result(this->land);
	result.name = name;
	result.land->types.insert(type);
	result.text = std::string("{T} add {") + colorText(color) + "} to your mana pool";		// TODO change to format()
	return result;
}

CardStat Prototypes::createAura()
{
	CardStat result(this->enchantment);
	result.enchantmentType = mtg::aura;
	return result;
}


CardStat Prototypes::createCreature(std::string const & name, CreatureType subType1, CreatureType subType2, int power, int toughness)
{
	CardStat result(this->creature);
	result.name = name;
	result.creature->types.insert(subType1);
	if( subType2 != 0 ) {
		result.creature->types.insert(subType2);
	}
	result.creature->power = power;
	result.creature->toughness = toughness;
	return result;
}

CardStat Prototypes::createArtifactCreature(std::string const & name, CreatureType subType1, CreatureType subType2, int power, int toughness)
{
	CardStat result = createCreature(name,subType1,subType2,power,toughness);
	result.cardTypes |= mtg::artifact;
	return result;
}

}
