#include <tut.h>
#include <magic.h>
#include "Factory4th.h"
#include <algorithm>
#include <iostream>

namespace {
	struct setup {
		mtg::Player player;
		setup():
			player("player")
		{
			mtg::Factory4th factory;
			player.cards.library.assign(factory.cards.begin(),factory.cards.end());
		}
	};

	void printCard(mtg::Card const & card)
	{
		std::cout << card.displayName() << " (" << card.id << "), ";
	}

	void printCardIt(mtg::CardIt it)
	{
		printCard(*it);
	}
}

namespace tut { 

	typedef test_group<setup> tg;
	tg Player_test_group("Player");

	typedef tg::object testobject;

	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("game start");

		auto size = player.cards.library.size();
		player.draw(7);
		ensure_equals( player.cards.hand.size() , 7 );
		ensure_equals( size - player.cards.library.size() , 7 );

		std::cout << std::endl;
		std::for_each(player.cards.hand.begin(),player.cards.hand.end(),&printCard);
		std::cout << std::endl;
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("game start with shuffle and random discard");

		player.shuffleLibrary();

		player.draw(7);
		ensure_equals( player.cards.hand.size() , 7 );

		std::cout << std::endl;
		std::for_each(player.cards.hand.begin(),player.cards.hand.end(),&printCard);
		std::cout << std::endl;

		auto it1 = player.discardAtRandom();
		auto it2 = player.discardAtRandom();
		std::cout << "random discard: "; printCard(*it1); printCard(*it2); std::cout << std::endl;
		ensure_equals( player.cards.hand.size() , 5 );
		ensure( std::find_if(player.cards.graveyard.begin(),player.cards.graveyard.end(),[it1](mtg::Card const & card){ return card.mainStat == it1->mainStat; }) == it1 );
		ensure( std::find_if(player.cards.graveyard.begin(),player.cards.graveyard.end(),[it2](mtg::Card const & card){ return card.mainStat == it2->mainStat; }) == it2 );
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("random select and shuffle back");

		player.draw(7);
		auto size = player.cards.library.size();
		auto its = player.cards.randomSelect(2,mtg::Zone::hand);
		std::cout << std::endl;
		std::for_each(its.begin(),its.end(),&printCardIt);
		std::cout << std::endl;
		player.cards.moveCards(its,mtg::Zone::hand,mtg::Zone::graveyard);
		auto itg = player.cards.graveyard.begin();
		ensure( itg == its[1] );
		++itg;
		ensure( itg == its[0] );
		ensure_equals( player.cards.hand.size() , 5 );

		player.shuffleGraveyardToLibrary();
		ensure_equals( size + 2, player.cards.library.size() );
	}
}
