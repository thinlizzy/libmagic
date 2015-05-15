#ifndef BOARD_STREAM_OPS_H_j432422388fd8fydst7324gg
#define BOARD_STREAM_OPS_H_j432422388fd8fydst7324gg

#include <ostream>
#include "../board/Permanent.h"
#include "../board/Player.h"

namespace mtg {

std::ostream & operator<<(std::ostream & os, Player const & player);
std::ostream & operator<<(std::ostream & os, Permanent const & permanent);
std::ostream & operator<<(std::ostream & os, CardIt cardIt);
std::ostream & operator<<(std::ostream & os, PermanentIt permIt);

}

#endif
