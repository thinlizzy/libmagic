#ifndef PERMANENT_H_GUARD
#define PERMANENT_H_GUARD

#include "Zone.h"
#include "Player.h"
#include "../cards/Card.h"
#include "Counter.h"
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <list>
#include <experimental/optional>

namespace mtg {

class Permanent;
typedef Permanent * PermanentPtr;

class Permanent {
    friend class PermanentManager;
    
    CardIt source; // original card data
    std::experimental::optional<Card> token;          // token properties. isToken() = true -> source = undef
    
    PlayerPtr owner;               // owner never changes
    PlayerPtr controller;          // controller may change
    
    // enchantment and equipment data
    std::unordered_set<PermanentPtr> attachments;    
public:
    
    bool tapped = false;
    bool sick = true;
    
    bool faceDown = false;
    bool flipped = false;
    bool transformed = false;
    
    std::unordered_map<Counter,unsigned> counters;

    // creature data
    bool attacking = false;
    bool blocking = false;
    unsigned damageMarked = 0;
    
    Card cardProperties;            // holds the latest card changes
    std::experimental::optional<Card> copiedValues;    // values generated due to a copy effect
    
    // cria uma permanente usando uma carta do jogador
    Permanent(Player & owner, Player & controller, CardIt source);

    // same above, but controller and owner are the same
    Permanent(Player & owner, CardIt source);

    // cria uma permanente que representa um token
    Permanent(Player & owner, Card const & token);

    bool isToken() const;

    CardIt getSource() const;
    
    Card const & getSourceCardData() const;
    Card const & getCurrentCardData() const;
    
    Player & getOwner();
    Player & getController();
    Player const & getOwner() const;
    Player const & getController() const;
    void setOwner(Player & player);
    void setController(Player & player);

    // attachments
    PermanentPtr attachedOnPermanent = 0;
    PlayerPtr attachedOnPlayer = 0;    
    bool hasAttachment(Permanent & permanent) const;
    void attachInto(Permanent & permanent);
    void attachInto(Player & player);
    void unattach();
};

typedef std::list<Permanent> Permanents;
typedef Permanents::iterator PermanentIt;
typedef Permanents::const_iterator PermanentConstIt;

}

namespace std {
    
template<>
struct hash<mtg::PermanentIt> {
    std::size_t operator()(mtg::PermanentIt permIt) const {
        return hash<mtg::Permanent *>()(&*permIt);
    }
};
    
}


#endif
