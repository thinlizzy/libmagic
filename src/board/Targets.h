#ifndef TARGET_SUBCLASSES_H_kkfdsfd934732gdsfjh2348fdsnh3
#define TARGET_SUBCLASSES_H_kkfdsfd934732gdsfjh2348fdsnh3

#include "Target.h"
#include "Player.h"
#include "CardRef.h"
#include "Stack.h"

namespace mtg {
    
template<typename T>
class ConcreteTarget: public Target {
public:
    T target;
    explicit ConcreteTarget(T target): target(target) {}
    virtual ConcreteTarget * clone() const { return new ConcreteTarget(*this); }
};

typedef ConcreteTarget<PlayerPtr> TargetPlayer;
typedef ConcreteTarget<PlayerPtr> TargetLibrary; 
typedef ConcreteTarget<PermanentIt> TargetPermanent; 
typedef ConcreteTarget<CardRef> TargetCard; 
typedef ConcreteTarget<StackIt> TargetStackObject; 

}

#endif