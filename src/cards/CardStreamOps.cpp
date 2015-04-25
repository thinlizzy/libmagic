#include "CardStreamOps.h"
#include "Card.h"
#include "Land.h"
#include "Creature.h"
#include "Planeswalker.h"
#include "types/TypeToStr.h"
#include <algorithm>
#include <iterator>

namespace mtg {
    
std::ostream & operator<<(std::ostream & os, Land const & land) {
    os << std::boolalpha << land.basic << ' ';
    std::transform(land.types.begin(),land.types.end(),std::ostream_iterator<std::string>(os," "),
        [](mtg::LandType type){ return typeToStr(type); });
    return os;
}

std::ostream & operator<<(std::ostream & os, Creature const & creature) {
    std::transform(creature.types.begin(),creature.types.end(),std::ostream_iterator<std::string>(os," "),
        [](mtg::CreatureType type){ return typeToStr(type); });
    os << std::boolalpha << creature.power << '/' << creature.toughness;
    return os;
}

std::ostream & operator<<(std::ostream & os, Planeswalker const & planeswalker) {
    os << typeToStr(planeswalker.type) << ' ' << planeswalker.loyalty;
    return os;
}

std::ostream & operator<<(std::ostream & os, SuperType const & supertype) {
    os << typeToStr(supertype);
    return os;
}

std::ostream & operator<<(std::ostream & os, CardType const & cardtype) {
    os << typeToStr(cardtype);
    return os;
}

std::ostream & operator<<(std::ostream & os, ArtifactType const & type) {
    os << typeToStr(type);
    return os;
}

std::ostream & operator<<(std::ostream & os, EnchantmentType const & type) {
    os << typeToStr(type);
    return os;
}

std::ostream & operator<<(std::ostream & os, CreatureType const & type) {
    os << typeToStr(type);
    return os;
}

std::ostream & operator<<(std::ostream & os, PlaneswalkerType const & type) {
    os << typeToStr(type);
    return os;
}

std::ostream & operator<<(std::ostream & os, SpellType const & type) {
    os << typeToStr(type);
    return os;
}

std::ostream & operator<<(std::ostream & os, CardStat const & stat) {
    os << stat.name << '|';
    if( stat.colors ) {
        os << showcolors << *stat.colors << '|';
    }
    os << stat.cost << '|';
    os << typeToStr(SuperType(stat.supertypes)) << '|';
    os << typeToStr(CardType(stat.cardTypes)) << '|';
    if( stat.land ) {
    	os << *stat.land << '|';
    }
    if( stat.creature ) {
    	os << *stat.creature << '|';
    }
    os << stat.artifactType << '|';
    os << stat.enchantmentType << '|';
    if( stat.planeswalker ) {
    	os << *stat.planeswalker << '|';
    }
    os << stat.spellType << '|';
    os << stat.tribalType << '|';
    os << stat.text;
    return os;
}

std::ostream & operator<<(std::ostream & os, Card const & card) {
    os << card.id << ' ';
    os << card.expansion << ' ';
    os << card.rarity << ' ';
    os << card.kind << ' ';
    os << card.mainStat << ' ';
    if( card.secondaryStat ) {
    	os << *card.secondaryStat;
    }
    return os;
}
    
}

