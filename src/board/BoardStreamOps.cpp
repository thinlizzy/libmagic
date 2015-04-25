#include "BoardStreamOps.h"

namespace mtg {

std::ostream & operator<<(std::ostream & os, Player const & player)
{
    return os << player.getName() <<
            " life " << player.life;
    // TODO attachment info, card zones and counters
}

std::ostream & operator<<(std::ostream & os, Permanent const & permanent)
{    
    return os << "controller " << permanent.getController() << 
            " owner " << permanent.getOwner() <<
            " is token? " << permanent.isToken() <<
            " source card data " << permanent.getSourceCardData() <<
            " current card data " << permanent.getCurrentCardData();
    // TODO attachment info and card statuses
}

std::ostream & operator<<(std::ostream & os, CardIt cardIt) { return os << *cardIt; }

std::ostream & operator<<(std::ostream & os, PermanentIt permIt) { return os << *permIt; }

}
