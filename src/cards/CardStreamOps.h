#ifndef CARDS_STREAM_OPERATORS_H_jf432932432lv03bnxzcty2135
#define CARDS_STREAM_OPERATORS_H_jf432932432lv03bnxzcty2135

#include <ostream>
#include "types/ArtifactType.h"
#include "types/CreatureType.h"
#include "types/EnchantmentType.h"
#include "types/SpellType.h"
#include "types/SuperType.h"
#include "types/CardType.h"
#include "types/PlaneswalkerType.h"
#include "types/Color.h"

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

}



#endif
