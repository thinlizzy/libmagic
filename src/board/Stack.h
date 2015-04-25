#ifndef STACK_H_jff432933483uifgfiufijdsafd
#define STACK_H_jff432933483uifgfiufijdsafd

#include "StackObject.h"
#include "Permanent.h"
#include <list>

namespace mtg {

typedef std::list<StackObject> Stack;
typedef Stack::iterator StackIt;

class Player;
struct CardRef;

void addTargetPlayer(StackObject & so, Player & player);
void addTargetLibrary(StackObject & so, Player & owner);
void addTargetPermanent(StackObject & so, PermanentIt permIt);
void addTargetCard(StackObject & so, CardRef card);
void addTargetStackObject(StackObject & so, StackIt obj);

}

#endif