#ifndef STACK_OBJECT_H_k34243248344387dfuh87hfdew3g
#define STACK_OBJECT_H_k34243248344387dfuh87hfdew3g

#include <unordered_map>
#include <memory>
#include <experimental/optional>
#include "Player.h"
#include "Target.h"
#include "Permanent.h"
#include "../cards/Card.h"
#include "../cards/Cost.h"

namespace mtg {
    
class StackObject {
public:
	std::experimental::optional<CardIt> source;    // the source card. it can be the card spell itself or the card source of an ability, if relevant
    // std::experimental::optional<Ability> ability;   // TODO :))) activated and triggered abilities, source permanent, etc
private:
    PlayerPtr owner;           // owner never changes
    PlayerPtr controller;      // controller may change

    std::experimental::optional<Card> copiedSpell;
public:
    Cost castingCost;
    std::unordered_multimap<TargetType,std::unique_ptr<Target>> targets;
    
    StackObject(Player & owner, Player & controller);
    
    // cria um stack object usando uma carta do jogador
    StackObject(Player & owner, Player & controller, CardIt source);
    // controller and owner are the same
    StackObject(Player & owner, CardIt source);
    
    StackObject copySpell(Player & controller) const;

    Player & getOwner();
    Player const & getOwner() const;
    Player & getController();
    Player const & getController() const;
    void setController(Player & controller);
    
    bool isCopy() const;
    
    Card const & getCardData() const;
};

}

#endif
