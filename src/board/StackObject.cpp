#include "StackObject.h"

namespace mtg {
    
StackObject::StackObject(Player & owner, Player & controller) :
    owner(&owner),
    controller(&controller)
{}

StackObject::StackObject(Player & owner, Player & controller, CardIt source) :
    source(source),
    owner(&owner),
    controller(&controller),
    castingCost(source->mainStat.cost)
{}

StackObject::StackObject(Player & owner, CardIt source) : 
    StackObject(owner, owner, source)
{}

StackObject StackObject::copySpell(Player & controller) const
{
    StackObject result(*owner,controller);
    result.castingCost = castingCost;
    result.copiedSpell = **source;
    for(auto & target : targets) {
        result.targets.emplace(target.first,std::unique_ptr<Target>(target.second->clone()));
    }
    
    return std::move(result);
}


Player & StackObject::getOwner() { return *owner; }
Player const & StackObject::getOwner() const { return *owner; }
Player & StackObject::getController() { return *controller; }
Player const & StackObject::getController() const { return *controller; }
void StackObject::setController(Player & controller) { this->controller = &controller; }

bool StackObject::isCopy() const 
{ 
    return bool(copiedSpell);
}

Card const & StackObject::getCardData() const
{
    if( copiedSpell ) return *copiedSpell;
    
    return **source;
}

}

