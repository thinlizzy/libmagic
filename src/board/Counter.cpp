#include "Counter.h"

namespace mtg {

Counter::Counter(std::string name, int powerModifier, int toughnessModifier):
    name(name),
    powerModifier(powerModifier),
    toughnessModifier(toughnessModifier)
{}

bool Counter::operator==(Counter const & other) const
{
    return name == other.name;
}

Counter Counter::poison("poison");
Counter Counter::plusOneOne("+1/+1",1,1);
Counter Counter::minusOneOne("-1/-1",-1,-1);
Counter Counter::age("age");
Counter Counter::time("time");
Counter Counter::levelUp("levelUp");
Counter Counter::loyalty("loyalty");

}
