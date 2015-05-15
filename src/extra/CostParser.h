#ifndef COSTPARSER_H_LIBMAGIC_2015_15_05
#define COSTPARSER_H_LIBMAGIC_2015_15_05

#include "../cards/Cost.h"

namespace mtg {

Cost parseCost(char const * cost);
Cost parseCost(std::string cost);

}

#endif /* COSTPARSER_H_ */
