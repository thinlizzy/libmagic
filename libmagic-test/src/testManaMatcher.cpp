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
		ensure_equals( *solution.mana[2] , mtg::Mana{mtg::red} );
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
		pool.add(mtg::black);
		pool.add(mtg::colorless);
		pool.add(mtg::colorless);
		mtg::Cost cost = mtg::parseCost("2");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::colorless} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::black} );
	}

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("match colorless with colored");
		pool.add(mtg::red);
		pool.add(mtg::green);
		pool.add(mtg::blue);
		mtg::Cost cost = mtg::parseCost("2");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::green} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::red} );
	}

	template<>
	template<>
	void testobject::test<6>()
	{
		set_test_name("match fail single color");
		pool.add(mtg::red);
		pool.add(mtg::green);
		pool.add(mtg::blue);
		mtg::Cost cost = mtg::parseCost("RR");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<7>()
	{
		set_test_name("match fail multi colored");
		pool.add(mtg::red);
		pool.add(mtg::green);
		pool.add(mtg::blue);
		pool.add(mtg::black);
		pool.add(mtg::black);
		mtg::Cost cost = mtg::parseCost("1GWRU");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<8>()
	{
		set_test_name("snow simple");
		pool.add(mtg::red);
		pool.add(mtg::white, mtg::Mana::snow, {});
		mtg::Cost cost = mtg::parseCost("1S");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::red} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::white,mtg::Mana::snow} );
	}

	template<>
	template<>
	void testobject::test<9>()
	{
		set_test_name("snow multiple");
		pool.add(mtg::red);
		pool.add(mtg::white);
		pool.add(mtg::white, mtg::Mana::snow, {});
		pool.add(mtg::colorless, mtg::Mana::snow, {});
		mtg::Cost cost = mtg::parseCost("2SW");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 4 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::colorless,mtg::Mana::snow} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::red} );
		ensure_equals( *solution.mana[2] , mtg::Mana{mtg::white} );
		ensure_equals( *solution.mana[3] , mtg::Mana{mtg::white,mtg::Mana::snow} );
	}

	template<>
	template<>
	void testobject::test<10>()
	{
		set_test_name("snow fail");
		pool.add(mtg::red);
		pool.add(mtg::white, mtg::Mana::snow, {});
		pool.add(mtg::colorless);
		mtg::Cost cost = mtg::parseCost("1SW");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<11>()
	{
		set_test_name("fireball");
		pool.add(mtg::red);
		mtg::Cost cost = mtg::parseCost("XR");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}

	// TODO add more tests (annotations, W/P, 2/W, R/W)

	// TODO test for more than one solution with phyrexian, generic and multiple
}



