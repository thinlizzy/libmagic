#ifndef CARD_PLAYER_REFERENCES_H_3kj42j3dsfsdfdsf
#define CARD_PLAYER_REFERENCES_H_3kj42j3dsfsdfdsf

#include "../cards/Card.h"
#include "Zone.h"
#include <list>
#include <functional>
#include <vector>

namespace mtg {

typedef std::list<Card> Cards;
typedef Cards::iterator CardIt;
typedef std::vector<CardIt> CardIts;

class Player;
typedef Player * PlayerPtr;

struct CardRef {
    CardIt it;
    Zone zone;
    PlayerPtr owner;
};

}

namespace std {
    
template<>
struct hash<mtg::CardIt> {
    std::size_t operator()(mtg::CardIt const & cardIt) {
        return hash<mtg::Card *>()(&*cardIt);
    }
};
    
}



#endif
