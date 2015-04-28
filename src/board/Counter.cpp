#include "Counter.h"

namespace mtg {

Counter::Counter(std::string name, int powerModifier, int toughnessModifier):
    name_(name),
    powerModifier_(powerModifier),
    toughnessModifier_(toughnessModifier)
{}

bool Counter::operator==(Counter const & other) const
{
    return name_ == other.name_;
}

Counter Counter::poison("poison");
Counter Counter::plusOneOne("+1/+1",1,1);
Counter Counter::minusOneOne("-1/-1",-1,-1);
Counter Counter::age("age");
Counter Counter::time("time");
Counter Counter::levelUp("levelUp");
Counter Counter::loyalty("loyalty");

}
