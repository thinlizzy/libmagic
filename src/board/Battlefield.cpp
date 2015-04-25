#include "Battlefield.h"
#include "CardRef.h"

namespace mtg { 

PermanentIt Battlefield::play(Player & player, CardIt card, Zone zsrc)
{
    return permanents.addPermanent(player.play(card,zsrc));
}

StackIt Battlefield::cast(Player & player, CardIt card, Zone zsrc)
{
    stack.push_back(player.cast(card,zsrc));
    return std::prev(stack.end());
}

StackIt Battlefield::copySpell(StackIt sit, Player & controller)
{
    stack.push_back(std::move(sit->copySpell(controller)));
    return std::prev(stack.end());
}

PermanentIt Battlefield::play(CardRef cardRef)
{
    return play(*cardRef.owner,cardRef.it,cardRef.zone);
}

StackIt Battlefield::cast(CardRef cardRef)
{
    return cast(*cardRef.owner,cardRef.it,cardRef.zone);
}

PermanentIt Battlefield::play(StackIt stackIt)
{
    PermanentIt result = play(stackIt->getOwner(),*stackIt->source,Zone::stack);
    stack.erase(stackIt);
    return result;
}

StackObject Battlefield::move(StackIt stackIt, Zone zdest)
{
    if( ! stackIt->isCopy() ) {
        stackIt->getOwner().cards.move(*stackIt->source,Zone::stack,zdest);
    }
 
    StackObject result = std::move(*stackIt);
    stack.erase(stackIt);
    return std::move(result);
}

Permanent Battlefield::move(PermanentIt permIt, Zone zdest)
{
    if( ! permIt->isToken() ) {
        permIt->getOwner().cards.move(permIt->getSource(),Zone::battlefield,zdest);
    }
    
    Permanent result = *permIt;
    permanents.erase(permIt);
    return result;
}

}