#ifndef SYMBOLPERMUTER_H_2015_05_25
#define SYMBOLPERMUTER_H_2015_05_25

#include "../cards/Cost.h"
#include <functional>
#include <vector>

namespace mtg {

namespace matcher {

class Permuter {
	using Solver = std::function<bool(Cost::Symbols const &)>;
	Cost::Symbols currentMatcher;
	std::vector<Cost::Symbols> matchers;
	Cost::Symbols const * symbols;
	Solver solver;
	bool done;
public:
	void tryPermutations(Cost::Symbols const & symbols, Solver solver);
private:
	bool tryPermutations(size_t pos);
};

}

} /* namespace mtg */

#endif /* SYMBOLPERMUTER_H_ */
