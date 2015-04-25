#include "Permanent.h"

namespace mtg {

Permanent::Permanent(Player & owner, Player & controller, CardIt source) :
    source(source),
    owner(&owner),
    controller(&controller),
    cardProperties(*source)
{}

// same above, but controller and owner are the same
Permanent::Permanent(Player & owner, CardIt source) : 
    Permanent(owner, owner, source)
{}

// cria uma permanente que representa um token
Permanent::Permanent(Player & owner, Card const & token) :
    token(token),
    owner(&owner),
    controller(&owner),
    cardProperties(token)
{}

bool Permanent::isToken() const { return bool(token); }

CardIt Permanent::getSource() const { return source; }

Card const & Permanent::getSourceCardData() const { return token ? *token : *source; }
Card const & Permanent::getCurrentCardData() const { return cardProperties; }

Player & Permanent::getOwner() { return *owner; }
Player & Permanent::getController() { return *controller; }
Player const & Permanent::getOwner() const { return *owner; }
Player const & Permanent::getController() const { return *controller; }
void Permanent::setOwner(Player & player) { owner = &player; }
void Permanent::setController(Player & player) { controller = &player; }

bool Permanent::hasAttachment(Permanent & permanent) const
{
    return attachments.count(&permanent);
}

void Permanent::attachInto(Permanent & permanent)
{
    unattach();
    attachedOnPermanent = &permanent; 
    permanent.attachments.insert(this); 
}

void Permanent::attachInto(Player & player)
{ 
    unattach();
    attachedOnPlayer = &player; 
    player.attachments.insert(this); 
}

void Permanent::unattach()
{
    if( attachedOnPermanent ) {
        attachedOnPermanent->attachments.erase(this);
        attachedOnPermanent = 0;
    }
    if( attachedOnPlayer ) {
        attachedOnPlayer->attachments.erase(this);
        attachedOnPlayer = 0;
    }
}

}



