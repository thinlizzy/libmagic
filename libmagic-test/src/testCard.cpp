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
		ensure( card.hasColor(Color::black) );
		// split
		ensure( card2.hasColor(Color::black) );
		ensure( card2.hasColor(Color::green) );
		ensure( card2.hasColor(Color::red) );
		ensure( ! card2.hasColor(Color::blue) );
		ensure( ! card2.hasColor(Color::white) );
		// changed to transform to ensure only split counts both colors
		card2.kind = transformCard;
		ensure( card2.hasColor(Color::black) );
		ensure( ! card2.hasColor(Color::green) );
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
