#ifndef TARGET_H_kkkkkkkkkk4r49fs87gdvfhbjngdj823g
#define TARGET_H_kkkkkkkkkk4r49fs87gdvfhbjngdj823g

#include <functional>

namespace mtg {

enum class TargetType {
    player, library, hand, graveyard,       
    permanent, card, stack,
};

class Target {
public:
    virtual ~Target() = 0;
    virtual Target * clone() const = 0;
};

}

namespace std {
    
template<>
struct hash<mtg::TargetType> {
    std::size_t operator()(mtg::TargetType type) const {
        return hash<int>()(int(type));
    }
};
    
}


#endif