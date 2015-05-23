#ifndef PLAYER_H_jkdfjfdsksjk93482a
#define PLAYER_H_jkdfjfdsksjk93482a

#include "Zone.h"
#include "OwnedCards.h"
#include "Counter.h"
#include "ManaPool.h"
#include "../cards/Colors.h"
#include <unordered_map>
#include <string>

namespace mtg {

class Permanent;
class StackObject;

class Player {
    std::string name;
public:
    OwnedCards cards;

	int life;
	ManaPool manaPool;

    std::unordered_map<Counter,unsigned> counters;
    std::unordered_set<Permanent *> attachments;      // enchant player cards
    

    explicit Player(std::string name);
    std::string const & getName() const;
    
	// library actions
	void shuffleLibrary();
	CardIt draw();
	CardIts draw(int cards);
	CardIts mill(int cards);

	// hand actions
	CardIt discardAtRandom();
	StackObject cast(CardIt card, Zone zone = Zone::hand);
    Permanent play(CardIt card, Zone zone = Zone::hand);

	void shuffleGraveyardToLibrary();
};

}

#endif
