#include <tut.h>
#include <magic.h>

namespace {
	struct setup {
		mtg::ManaPool pool;
	};
}

namespace tut {
	typedef test_group<setup> tg;
	tg mana_test_group("matcher");

	typedef tg::object testobject;

	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("match empty");

		mtg::Cost cost = mtg::parseCost("3RR");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
		ensure_equals( matcher.getSolutions().size() , 0 );
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("match single color");

		pool.add(mtg::red);
		pool.add(mtg::red);
		pool.add(mtg::blue);
		mtg::Cost cost = mtg::parseCost("1RR");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		ensure_equals( matcher.getSolutions().size() , 1 );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.life , 0 );
		ensure_equals( solution.mana.size() , 3 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::blue} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::red} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::red} );
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("match single color with repeated solutions");
		pool.add(mtg::red);
		pool.add(mtg::red);
		pool.add(mtg::blue);
		mtg::Cost cost = mtg::parseCost("1RR");

		mtg::ManaMatcher matcher2(2);
		matcher2.match(cost, pool);
		ensure_equals( matcher2.getSolutions().size() , 1 );
	}

	template<>
	template<>
	void testobject::test<4>()
	{
		set_test_name("match colorless");

		pool.add(mtg::colorless);
		pool.add(mtg::colorless);
		pool.add(mtg::colorless);
		mtg::Cost cost = mtg::parseCost("2");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::colorless} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::colorless} );
	}

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("match colorless with colored");

		pool.add(mtg::red);
		pool.add(mtg::red);
		pool.add(mtg::red);
		mtg::Cost cost = mtg::parseCost("2");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::red} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::red} );
	}

	// TODO add more tests (snow, annotations, X, phyrexian, 2/W)

	// TODO test for more than one solution with phyrexian, generic and 2/W
}



