#include <tut.h>
#include <magic.h>

/*
 	// TODO remove these annotations from here and move them to the rules engine
	enum Annotation : unsigned {
		spells = 1, abilities = 2,
		cumulativeUpkeepCost = 4,
		artifact = 8, creature = 16,

		firstAnnotation = 1,
		lastAnnotation = 16,
	};
	using Annotations = unsigned;

	Annotations annotations;

	// TODO left out rank() on Mana.h - consider removing it
    int rank() const {
    	return int(annotations) * 100 + colorValue(color) * 10 + int(source);
    }

	bool operator==(Mana const & mana) const {
		return color == mana.color && source == mana.source && annotations == mana.annotations;
	}

	// TODO move this checking to the matcher. pass a functor to it that filters the mana. the functor will consult the rules engine (a map from mana ref to some custom annotation system)
	bool allowsRestrictions(Annotations restrictions) const {
		return (annotations & restrictions) == annotations;
	}

	Mana::Annotations packedAnnotations{};
	for( auto annotation : annotations ) {
		packedAnnotations |= Mana::Annotations(annotation);
	}
 */

namespace {
	struct setup {
		mtg::ManaPool pool;
		mtg::matcher::ManaFilter noFilter = [](mtg::ManaPool::ManaCRef){ return false; };
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
		mtg::matcher::Mana matcher;
		ensure_not( bool(matcher.match(cost,pool,noFilter)) );
		ensure_equals( matcher.getSolutions().size() , 0u );
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
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
		ensure_equals( matcher.getSolutions().size() , 1u );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.life , 0 );
		ensure_equals( solution.mana.size() , 3u );
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

		mtg::matcher::Mana matcher2(2);
		matcher2.match(cost, pool, noFilter);
		ensure_equals( matcher2.getSolutions().size() , 1u );
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
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher;
		ensure_not( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher;
		ensure_not( bool(matcher.match(cost, pool, noFilter)) );
	}

	template<>
	template<>
	void testobject::test<8>()
	{
		set_test_name("snow simple");
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::white, mtg::Mana::snow);
		mtg::Cost cost = mtg::parseCost("1S");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		pool.add(mtg::Color::white, mtg::Mana::snow);
		pool.add(mtg::Color::colorless, mtg::Mana::snow);
		mtg::Cost cost = mtg::parseCost("2SW");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		pool.add(mtg::Color::white, mtg::Mana::snow);
		pool.add(mtg::Color::colorless);
		mtg::Cost cost = mtg::parseCost("1SW");
		mtg::matcher::Mana matcher;
		ensure_not( bool(matcher.match(cost, pool, noFilter)) );
	}

	template<>
	template<>
	void testobject::test<11>()
	{
		set_test_name("fireball");
		pool.add(mtg::Color::red);
		mtg::Cost cost = mtg::parseCost("XR");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
	}


	template<>
	template<>
	void testobject::test<12>()
	{
		set_test_name("multiple color matchers single");
		pool.add(mtg::Color::white);
		mtg::Cost cost = mtg::parseCost("W/R");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
	}

	template<>
	template<>
	void testobject::test<13>()
	{
		set_test_name("multiple color matchers");
		pool.add(mtg::Color::white);
		pool.add(mtg::Color::red);
		mtg::Cost cost = mtg::parseCost("{W/R}{R/G}");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher;
		ensure_not( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher(3);
		ensure_equals( matcher.match(cost, pool, noFilter).getSolutions().size() , 2 );
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
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
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
		mtg::matcher::Mana matcher{6};
		ensure_equals( matcher.match(cost, pool, noFilter).getSolutions().size() , 4 );
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
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
	}

	template<>
	template<>
	void testobject::test<21>()
	{
		set_test_name("phyrexian has mana");
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("{2}{U/P}");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.life , 0 );
		ensure_equals( solution.mana.size() , 3u );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::Color::blue} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::Color::black} );
		ensure_equals( *solution.mana[2] , mtg::Mana{mtg::Color::black} );
	}

	template<>
	template<>
	void testobject::test<22>()
	{
		set_test_name("phyrexian no mana");
		pool.add(mtg::Color::black);
		pool.add(mtg::Color::black);
		mtg::Cost cost = mtg::parseCost("{2}{U/P}");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost, pool, noFilter)) );
		auto & solution = matcher.getSolutions()[0];
		ensure_equals( solution.life , 2 );
		ensure_equals( solution.mana.size() , 2u );
		ensure_equals( *solution.mana[0] , mtg::Mana{mtg::Color::black} );
		ensure_equals( *solution.mana[1] , mtg::Mana{mtg::Color::black} );
	}

	template<>
	template<>
	void testobject::test<23>()
	{
		set_test_name("Moltensteel Dragon multiple solutions");
		pool.add(mtg::Color::colorless);
		pool.add(mtg::Color::colorless);
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::colorless);
		pool.add(mtg::Color::colorless);
		mtg::Cost cost = mtg::parseCost("{4}{R/P}{R/P}");
		mtg::matcher::Mana matcher(4);
		ensure( bool(matcher.match(cost, pool, noFilter)) );
		ensure_equals( matcher.getSolutions().size() , 3u );
		auto & solution0 = matcher.getSolutions()[0];
		ensure_equals( solution0.life , 2 );
		ensure_equals( solution0.mana.size() , 5u );
		ensure_equals( *solution0.mana[0] , mtg::Mana{mtg::Color::colorless} );
		ensure_equals( *solution0.mana[4] , mtg::Mana{mtg::Color::red} );
		auto & solution1 = matcher.getSolutions()[1];
		ensure_equals( solution1.life , 4 );
		ensure_equals( solution1.mana.size() , 4u );
		ensure_equals( *solution0.mana[0] , mtg::Mana{mtg::Color::colorless} );
		ensure_equals( *solution0.mana[4] , mtg::Mana{mtg::Color::red} );
		auto & solution2 = matcher.getSolutions()[2];
		ensure_equals( solution2.life , 4 );
		ensure_equals( solution2.mana.size() , 4u );
		ensure_equals( *solution2.mana[0] , mtg::Mana{mtg::Color::colorless} );
		ensure_equals( *solution2.mana[3] , mtg::Mana{mtg::Color::colorless} );
	}

	template<>
	template<>
	void testobject::test<24>()
	{
		set_test_name("match single color filtered");
		pool.add(mtg::Color::red);
		auto artifactMana = pool.add(mtg::Color::red,{});
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("1RR");
		mtg::matcher::Mana matcher;
		ensure( bool(matcher.match(cost,pool,noFilter)) );
		ensure_not( bool(matcher.match(cost,pool,[artifactMana](auto mana){ return mana == artifactMana; })) );
	}

	template<>
	template<>
	void testobject::test<25>()
	{
		set_test_name("match single color filtered multiple solutions");
		pool.add(mtg::Color::red);
		auto creatureAbilitiesMana = pool.add(mtg::Color::red,{});
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::blue);
		mtg::Cost cost = mtg::parseCost("1RR");
		mtg::matcher::Mana matcher{4};
		ensure( bool(matcher.match(cost,pool,[creatureAbilitiesMana](auto mana){ return mana == creatureAbilitiesMana; })) );
		ensure_equals( matcher.getSolutions().size() , 1u );
		ensure( bool(matcher.match(cost,pool,noFilter)) );
		ensure_equals( matcher.getSolutions().size() , 2u );
	}
}
