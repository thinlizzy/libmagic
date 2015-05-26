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
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("1RR");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		ensure_equals( matcher.getSolutions().size() , 1 );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.life , 0 );
		ensure_equals( solution.mana.size() , 3 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::Color::blue} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::Color::red} );
		ensure_equals( *solution.mana[2] , mtg::Mana{mtg::Color::red} );
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("match single color with repeated solutions");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::blue);
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
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::colorless);
		pool.add(mtg::Color::colorless);
		mtg::Cost cost = mtg::parseCost("2");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::Color::colorless} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::Color::black} );
	}

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("match colorless with colored");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("2");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::Color::green} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::Color::red} );
	}

	template<>
	template<>
	void testobject::test<6>()
	{
		set_test_name("match fail single color");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("RR");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<7>()
	{
		set_test_name("match fail multi colored");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::blue);
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::black);
		mtg::Cost cost = mtg::parseCost("1GWRU");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<8>()
	{
		set_test_name("snow simple");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::white, mtg::Mana::snow, {});
		mtg::Cost cost = mtg::parseCost("1S");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 2 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::Color::red} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::Color::white,mtg::Mana::snow} );
	}

	template<>
	template<>
	void testobject::test<9>()
	{
		set_test_name("snow multiple");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::white);
		pool.add(mtg::Color::white, mtg::Mana::snow, {});
		pool.add(mtg::Color::colorless, mtg::Mana::snow, {});
		mtg::Cost cost = mtg::parseCost("2SW");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.mana.size() , 4 );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::Color::colorless,mtg::Mana::snow} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::Color::red} );
		ensure_equals( *solution.mana[2] , mtg::Mana{mtg::Color::white} );
		ensure_equals( *solution.mana[3] , mtg::Mana{mtg::Color::white,mtg::Mana::snow} );
	}

	template<>
	template<>
	void testobject::test<10>()
	{
		set_test_name("snow fail");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::white, mtg::Mana::snow, {});
		pool.add(mtg::Color::colorless);
		mtg::Cost cost = mtg::parseCost("1SW");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<11>()
	{
		set_test_name("fireball");
		pool.add(mtg::Color::red);
		mtg::Cost cost = mtg::parseCost("XR");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}


	template<>
	template<>
	void testobject::test<12>()
	{
		set_test_name("multiple color matchers single");
		pool.add(mtg::Color::white);
		mtg::Cost cost = mtg::parseCost("W/R");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<13>()
	{
		set_test_name("multiple color matchers");
		pool.add(mtg::Color::white);
		pool.add(mtg::Color::red);
		mtg::Cost cost = mtg::parseCost("{W/R}{R/G}");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<14>()
	{
		set_test_name("multiple color matchers fail");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::blue);
		pool.add(mtg::Color::black);
		mtg::Cost cost = mtg::parseCost("{1}{W/R}{R/G}");
		mtg::ManaMatcher matcher;
		ensure_not( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<15>()
	{
		set_test_name("multiple color matchers two solutions");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::white);
		pool.add(mtg::Color::red);
		mtg::Cost cost = mtg::parseCost("{W/R}{R/G}");
		mtg::ManaMatcher matcher(3);
		ensure_equals( matcher.match(cost, pool).getSolutions().size() , 2 );
	}

	template<>
	template<>
	void testobject::test<16>()
	{
		set_test_name("beseech the queen black only");
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::black);
		mtg::Cost cost = mtg::parseCost("{2/B}{2/B}{2/B}");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<17>()
	{
		set_test_name("beseech the queen generic only");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::blue);
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::blue);
		pool.add(mtg::Color::green);
		mtg::Cost cost = mtg::parseCost("{2/B}{2/B}{2/B}");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<18>()
	{
		set_test_name("beseech the queen mixed exact");
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::blue);
		pool.add(mtg::Color::green);
		mtg::Cost cost = mtg::parseCost("{2/B}{2/B}{2/B}");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}

	template<>
	template<>
	void testobject::test<19>()
	{
		set_test_name("beseech the queen mixed more solutions");
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("{2/B}{2/B}{2/B}");
		mtg::ManaMatcher matcher{6};
		ensure_equals( matcher.match(cost, pool).getSolutions().size() , 4 );
	}

	template<>
	template<>
	void testobject::test<20>()
	{
		set_test_name("unknown card mixed");
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("{2/B}{2/R}");
		mtg::ManaMatcher matcher;
		ensure( bool(matcher.match(cost, pool)) );
	}

	// TODO add more tests (annotations, W/P)

	// TODO test for more than one solution with phyrexian, generic and multiple
}



