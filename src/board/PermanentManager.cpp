#include "PermanentManager.h"
#include <algorithm>

namespace mtg {

PermanentIt PermanentManager::addPermanent(Permanent const & permanent)
{
    permanents.push_back(permanent);
    PermanentIt result = std::prev(permanents.end());
    addToIndex(result);
    return result;
}

PermanentIt PermanentManager::addPermanent(Permanent && permanent)
{
    permanents.push_back(std::move(permanent));
    PermanentIt result = std::prev(permanents.end());
    addToIndex(result);
    return result;
}

void PermanentManager::replace(PermanentIt permIt, Permanent const & permanent)
{
    removeFromIndex(permIt);
    *permIt = permanent;
    addToIndex(permIt);    
}

void PermanentManager::erase(PermanentIt permIt)
{
    removeFromIndex(permIt);
    permanents.erase(permIt);
}

void PermanentManager::addToIndex(PermanentIt permIt)
{
    permByOwner[permIt->owner].insert(permIt);
    permByController[permIt->controller].insert(permIt);
}

void PermanentManager::removeFromIndex(PermanentIt permIt)
{
    permByOwner[permIt->owner].erase(permIt);
    permByController[permIt->controller].erase(permIt);
}

size_t PermanentManager::size() const
{
    return permanents.size();
}

PermanentConstIt PermanentManager::begin() const
{
    return permanents.begin();
}

PermanentConstIt PermanentManager::end() const
{
    return permanents.end();
}

PermanentIt PermanentManager::begin()
{
    return permanents.begin();
}

PermanentIt PermanentManager::end()
{
    return permanents.end();
}

    
auto PermanentManager::byOwner(Player const & owner) -> PermSet & 
{
    return permByOwner[&owner];
}
    
auto PermanentManager::byController(Player const & controller) -> PermSet &
{
    return permByController[&controller];
}


}