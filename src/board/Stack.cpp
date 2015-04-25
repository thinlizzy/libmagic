#include "Stack.h"
#include "Targets.h"

namespace mtg {

void addTargetPlayer(StackObject & so, Player & player)
{
    so.targets.emplace(TargetType::player,std::unique_ptr<Target>(new TargetPlayer(&player)));
}

void addTargetLibrary(StackObject & so, Player & owner)
{
    so.targets.emplace(TargetType::library,std::unique_ptr<Target>(new TargetLibrary(&owner)));
}

void addTargetPermanent(StackObject & so, PermanentIt permIt)
{
    so.targets.emplace(TargetType::permanent,std::unique_ptr<Target>(new TargetPermanent(permIt)));
}

void addTargetCard(StackObject & so, CardRef card)
{
    so.targets.emplace(TargetType::card,std::unique_ptr<Target>(new TargetCard(card)));
}

void addTargetStackObject(StackObject & so, Stack::iterator obj)
{
    so.targets.emplace(TargetType::stack,std::unique_ptr<Target>(new TargetStackObject(obj)));
}

}
