#ifndef BATTLEFIELD_H_j3244444ffg09fg09vbjcxjn324b32gg
#define BATTLEFIELD_H_j3244444ffg09fg09vbjcxjn324b32gg

#include "Player.h"
#include "PermanentManager.h"
#include "StackObject.h"
#include "Stack.h"
#include <deque>
#include <list>
#include <unordered_map>
#include <unordered_set>

// methods to deal with battlefield common issues
    // destroy (all)
    // enumerate

	// command zone owns permanents, emblems and vanguard avatars
    // planechase cards
    // scheme cards

namespace mtg {

class CardRef;
    
class Battlefield {
public:
    std::list<Player> players;
    Stack stack;
    
    PermanentManager permanents;

    // play a card from a zone
	PermanentIt play(Player & player, CardIt card, Zone zsrc = Zone::hand);
    PermanentIt play(CardRef cardRef);
    // cast a spell
    StackIt cast(Player & player, CardIt card, Zone zsrc = Zone::hand);
    StackIt cast(CardRef cardRef);
    // copy a spell
    StackIt copySpell(StackIt sit, Player & controller);
    // permanent spell resolves
    PermanentIt play(StackIt stackIt);    
    // copies and tokens are removed on move() calls    
    StackObject move(StackIt stackIt, Zone zdest);  // other spell resolves. returns a copy of stackobject for LKI    
    Permanent move(PermanentIt permIt, Zone zdest); // bounce, destroy, return, blink. returns a copy of permanent for LKI
};

}

#endif