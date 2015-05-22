#ifndef CARDS_STREAM_OPERATORS_H_jf432932432lv03bnxzcty2135
#define CARDS_STREAM_OPERATORS_H_jf432932432lv03bnxzcty2135

#include <ostream>
#include "../cards/types/ArtifactType.h"
#include "../cards/types/CreatureType.h"
#include "../cards/types/EnchantmentType.h"
#include "../cards/types/SpellType.h"
#include "../cards/types/SuperType.h"
#include "../cards/types/CardType.h"
#include "../cards/types/PlaneswalkerType.h"
#include "../cards/Color.h"

namespace mtg {
    
class Land;
class Creature;
class Planeswalker;
class CardStat;
class Card;
class Cost;
class ManaPattern;

std::ostream & operator<<(std::ostream & os, Land const & land);
std::ostream & operator<<(std::ostream & os, Creature const & creature);
std::ostream & operator<<(std::ostream & os, Planeswalker const & planeswalker);
std::ostream & operator<<(std::ostream & os, SuperType const & supertype);
std::ostream & operator<<(std::ostream & os, CardType const & cardtype);
std::ostream & operator<<(std::ostream & os, ArtifactType const & type);
std::ostream & operator<<(std::ostream & os, EnchantmentType const & type);
std::ostream & operator<<(std::ostream & os, CreatureType const & type);
std::ostream & operator<<(std::ostream & os, PlaneswalkerType const & type);
std::ostream & operator<<(std::ostream & os, SpellType const & type);
std::ostream & operator<<(std::ostream & os, CardStat const & stat);
std::ostream & operator<<(std::ostream & os, Card const & card);
std::ostream & operator<<(std::ostream & os, mtg::ManaPattern const & mp);
std::ostream & operator<<(std::ostream & os, mtg::Cost const & cost);
std::ostream & operator<<(std::ostream & os, mtg::ColorSet const & colorSet);
std::ostream & operator<<(std::ostream & os, mtg::Color const & color);

}



#endif
