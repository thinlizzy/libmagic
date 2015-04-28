#ifndef COUNTER_H_jfdsfksj432932glk650sfdnh437gf
#define COUNTER_H_jfdsfksj432932glk650sfdnh437gf

#include <string>
#include <functional>

namespace mtg {

class Counter {
    std::string name_;
    int powerModifier_;
    int toughnessModifier_;
public:
    Counter(std::string name, int powerModifier = 0, int toughnessModifier = 0);
    
    std::string name() const;
    int powerModifier() const;
    int toughnessModifier() const;
    
    bool operator==(Counter const & other) const;

    static Counter poison;          // players can have these
    static Counter plusOneOne;      // standard creature boost
    static Counter minusOneOne;     // standard creature lessening - both cancel each other
    static Counter age;             // cumulative upkeep and fading
    static Counter time;            // suspend and vanishing
    static Counter levelUp;         // level up creatures
    static Counter loyalty;         // planeswalkers
};

}

namespace std {
    
template<>
struct hash<mtg::Counter> {
    std::size_t operator()(mtg::Counter const & counter) const {
        return hash<std::string>()(counter.name());
    }
};
    
}

#endif
