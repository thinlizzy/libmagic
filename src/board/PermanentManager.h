#ifndef PERMANENT_MANAGER_H_jff3429432dsfdsf
#define PERMANENT_MANAGER_H_jff3429432dsfdsf

#include "Permanent.h"
#include "Zone.h"
#include <unordered_set>
#include <unordered_map>

namespace mtg {

class PermanentManager {
    Permanents permanents;
    typedef std::unordered_set<PermanentIt> PermSet;
    typedef std::unordered_map<Player const *,PermSet> PermByPlayer;
    PermByPlayer permByOwner;
    PermByPlayer permByController;
    
    void addToIndex(PermanentIt permIt);
    void removeFromIndex(PermanentIt permIt);
public:
    PermanentIt addPermanent(Permanent const & permanent);
    PermanentIt addPermanent(Permanent && permanent);
    void replace(PermanentIt permIt, Permanent const & permanent);
    void erase(PermanentIt permIt);
    
    size_t size() const;
    
    PermanentConstIt begin() const;
    PermanentConstIt end() const;
    PermanentIt begin();
    PermanentIt end();
    
    typedef PermSet::iterator PermanentItIt;
    PermSet & byOwner(Player const & owner);
    PermSet & byController(Player const & controller);
};

}


#endif