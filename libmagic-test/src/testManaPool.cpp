#include <tut.h>
#include <magic.h>

namespace {
    struct setup {
		mtg::ManaPool pool;

		void checkAllColor(mtg::Color color, int tot) {
			int t = 0;
			for( auto mana : pool.getByColor(color) ) {
				++t;
				tut::ensure_equals( mana->color , color );
			}
			tut::ensure_equals( t , tot );
		}
    };
}

namespace tut {
    typedef test_group<setup> tg;
    tg mana_test_group("mana pool");

    typedef tg::object testobject;

    template<>
    template<>
    void testobject::test<1>()
    {
        set_test_name("empty");

		ensure_equals( pool.mana().size() , 0 );

		auto bc = pool.getByColor(mtg::red);
		ensure( bc.begin() == bc.end() );
    }

    template<>
    template<>
    void testobject::test<2>()
    {
        set_test_name("noncolored only");

        pool.add(mtg::colorless);
		ensure_equals( pool.mana().size() , 1 );

		auto bc = pool.getByColor(mtg::colorless);
		ensure( bc.begin() != bc.end() );

		checkAllColor(mtg::colorless,1);
    }

    template<>
    template<>
    void testobject::test<3>()
    {
        set_test_name("multiple colors");

        pool.add(mtg::colorless);
        pool.add(mtg::colorless, mtg::Mana::snow, {});
        pool.add(mtg::red);
        pool.add(mtg::green);
        pool.add(mtg::green);
		ensure_equals( pool.mana().size() , 5 );

		checkAllColor(mtg::colorless,2);
		checkAllColor(mtg::red,1);
		checkAllColor(mtg::green,2);
		checkAllColor(mtg::blue,0);
		checkAllColor(mtg::white,0);
		checkAllColor(mtg::black,0);
    }

    template<>
    template<>
    void testobject::test<4>()
    {
        set_test_name("snow and annotated");

        pool.add(mtg::colorless);
        pool.add(mtg::black, mtg::Mana::snow, {});
        pool.add(mtg::black, {}, {mtg::Mana::abilities});
        pool.add(mtg::white, mtg::Mana::snow, {mtg::Mana::abilities, mtg::Mana::artifact, });
		ensure_equals( pool.mana().size() , 4 );

		checkAllColor(mtg::colorless,1);
		checkAllColor(mtg::black,2);
		checkAllColor(mtg::white,1);

		int ts = 0;
		for( auto mana : pool.getBySource(mtg::Mana::snow) ) {
			ensure_equals( mana->source , mtg::Mana::snow );
			ensure( mana->color == mtg::black || mana->color == mtg::white );
			++ts;
		}
		ensure_equals( ts , 2 );

		int taa = 0;
		for( auto mana : pool.getByAnnotation(mtg::Mana::abilities) ) {
			ensure( mana->annotations & mtg::Mana::abilities );
			ensure( mana->color == mtg::black || mana->color == mtg::white );
			++taa;
		}
		ensure_equals( taa , 2 );

		int tar = 0;
		for( auto mana : pool.getByAnnotation(mtg::Mana::artifact) ) {
			ensure( mana->annotations & mtg::Mana::artifact );
			ensure( mana->color == mtg::white );
			++tar;
		}
		ensure_equals( tar , 1 );
    }

    // TODO test canCast

    // TODO test remove
}

