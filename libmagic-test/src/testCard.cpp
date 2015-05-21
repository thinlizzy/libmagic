#include <tut.h>

#include <magic.h>

namespace {
	struct setup {
		mtg::Card card;
		mtg::Card card2;
		setup()
		{
			using namespace mtg;
			card.mainStat.cost = parseCost("1B");
			card.mainStat.name = "diego";

			card2 = Card(splitCard,card.mainStat,CardStat());
			card2.secondaryStat->name = "jose";
			card2.secondaryStat->cost = parseCost("RG");
		}
	};
}

namespace tut { 

	typedef test_group<setup> tg;
	tg card_test_group("Card");

	typedef tg::object testobject;

	template<>
	template<>
	void testobject::test<1>()
	{
		using namespace mtg;
		set_test_name("hasColor");
		// simple
		ensure( card.hasColor(black) );
		// split
		ensure( card2.hasColor(black) );
		ensure( card2.hasColor(green) );
		ensure( card2.hasColor(red) );
		ensure( ! card2.hasColor(blue) );
		ensure( ! card2.hasColor(white) );
		// changed to transform to ensure only split counts both colors
		card2.kind = transformCard;
		ensure( card2.hasColor(black) );
		ensure( ! card2.hasColor(green) );
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		using namespace mtg;
		set_test_name("hasName");
		// simple
		ensure( card.hasName("diego") );
		// dual
		ensure( card2.hasName("diego") );
		ensure( card2.hasName("jose") );
	}
}
