#ifndef FACTORY_4TH_H_fkjdfsjh44459g
#define FACTORY_4TH_H_fkjdfsjh44459g

#include <vector>
#include <magic.h>

namespace mtg {

class Factory4th {
public:
	typedef std::vector<Card> CardCollection;
private:
	int id;
	void createBasicLands();
	void createColorless();
	Card newCard(CardStat const & cardStat, Expansion exp);
public:
	Factory4th();
	CardCollection cards;
};

}

#endif
