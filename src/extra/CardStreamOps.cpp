#include "CardStreamOps.h"
#include "../cards/Card.h"
#include "../cards/Land.h"
#include "../cards/Creature.h"
#include "../cards/Planeswalker.h"
#include "../cards/types/TypeToStr.h"
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

std::ostream & operator<<(std::ostream & os, mtg::ColorSet const & colorSet)
{
    bool printed = false;
	for( auto color : ColorList() ) {
		if( colorSet.hasColor(color) ) {
			if( printed ) os << '/';
			os << colorText(color);
			printed = true;
		}
	}
	return os;
}

std::ostream & operator<<(std::ostream & os, mtg::Color const & color)
{
	switch(color) {
		case Color::green: return os << "green";
		case Color::blue: return os << "blue";
		case Color::red: return os << "red";
		case Color::white: return os << "white";
		case Color::black: return os << "black";
		case Color::colorless: return os << "colorless";
		default: return os << "multiple";
	}
}

std::ostream & operator<<(std::ostream & os, mtg::CostSymbol const & symbol)
{
    bool printed = false;
	if( symbol.specific != 0 ) {
		if( printed ) os << '/';
		char const specChar[] = " SPXYZ";
		os << specChar[symbol.specific];
		printed = true;
	}
	if( symbol.generic > 0 && symbol.specific != mtg::CostSymbol::snow ) {
		os << unsigned(symbol.generic);
		printed = true;
	}
	for( auto color : ColorList() ) {
		if( symbol.hasColor(color) ) {
			if( printed ) os << '/';
			os << mtg::colorText(color);
			printed = true;
		}
	}
	if( ! printed ) {
		os << '0';
	}
    return os;
}

std::ostream & operator<<(std::ostream & os, mtg::Cost const & cost)
{
    std::copy(cost.symbols.begin(),cost.symbols.end(),std::ostream_iterator<mtg::CostSymbol>(os));
    return os;
}

std::ostream & operator<<(std::ostream & os, CardStat const & stat)
{
    os << stat.name << '|';
    if( stat.colors_ ) {
        os << *stat.colors_ << '|';
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

std::ostream & operator<<(std::ostream & os, Card const & card)
{
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

} // namespace mtg

/*
inline int showcolors_i() {
    static int i = std::ios_base::xalloc();
    return i;
}

std::ostream & showcolors(std::ostream & os) {
    os.iword(showcolors_i()) = 1;
    return os;
}

    if( os.iword(showcolors_i()) ) {
        for( Color c = Color(0); c != mtg::nColors; c = Color(c+1) ) {
            if( mp.colors[c] ) {
                if( printed ) os << '/';
                os << mtg::colors->colorDesc.getLeft()[c];
                printed = true;
            }
        }
        os.iword(showcolors_i()) = 0;
    } else {
 */
