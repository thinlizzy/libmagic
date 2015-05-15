#ifndef PROTOTYPES_H_kj45932gmj4309g
#define PROTOTYPES_H_kj45932gmj4309g

#include <string>
#include "../cards/Card.h"
#include "../cards/types/LandType.h"
#include "singleton.h"

namespace mtg {

class Prototypes {
private:
	CardStat createBasicLand(std::string const & name, LandType type, Color color);
	CardStat createAura();
public:
	CardStat land,creature,artifact,enchantment,aura,sorcery,instant,planeswalker;
	CardStat forest,island,mountain,plains,swamp;

	Prototypes();
	CardStat createCreature(std::string const & name, CreatureType subType1, CreatureType subType2, int power, int toughness);
	CardStat createArtifactCreature(std::string const & name, CreatureType subType1, CreatureType subType2, int power, int toughness);
};

extern singleton<Prototypes> prototypes;

}

#endif

