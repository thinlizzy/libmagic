#include <tut.h>
#include <magic.h>
#include <algorithm>

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

		int count(mtg::Color color) {
			auto bc = pool.getByColor(color);
			return std::distance(bc.begin(),bc.end());
		}

		int count(mtg::Mana::Source source) {
			auto bs = pool.getBySource(source);
			return std::distance(bs.begin(),bs.end());
		}

		int count(mtg::Mana::Annotation annotation) {
			auto ba = pool.getByAnnotation(annotation);
			return std::distance(ba.begin(),ba.end());
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
		ensure( bc.empty() );
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("noncolored only");

		pool.add(mtg::colorless);
		ensure_equals( pool.mana().size() , 1 );

		auto bc = pool.getByColor(mtg::colorless);
		ensure( ! bc.empty() );

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

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("remove");

		pool.add(mtg::colorless);
		pool.add(mtg::black, mtg::Mana::snow, {});
		pool.add(mtg::black, {}, {mtg::Mana::abilities});
		pool.add(mtg::white, mtg::Mana::snow, {mtg::Mana::abilities, mtg::Mana::artifact, });
		pool.add(mtg::green);
		pool.add(mtg::green, mtg::Mana::snow, {mtg::Mana::upkeep});
		pool.add(mtg::green, mtg::Mana::snow, {mtg::Mana::spells});
		pool.add(mtg::red, {}, {mtg::Mana::upkeep, mtg::Mana::creature});
		pool.add(mtg::blue);

		ensure_equals( pool.mana().size() , 9 );
		ensure_equals( count(mtg::Mana::snow) , 4 );
		ensure_equals( count(mtg::Mana::abilities) , 2 );
		ensure_equals( count(mtg::Mana::artifact) , 1 );
		ensure_equals( count(mtg::Mana::upkeep) , 2 );

		// remove the first (and the only) white mana
		auto bc = pool.getByColor(mtg::white);
		ensure( ! bc.empty() );
		pool.remove(*bc.begin());
		ensure_equals( pool.mana().size() , 8 );
		ensure_equals( count(mtg::Mana::snow) , 3 );
		bc = pool.getByColor(mtg::white);
		ensure( bc.empty() );
		ensure_equals( count(mtg::Mana::abilities) , 1 );
		ensure_equals( count(mtg::Mana::artifact) , 0 );

		auto ba = pool.getByAnnotation(mtg::Mana::abilities);
		ensure( ! ba.empty() );
		auto blackManaAbilities = *ba.begin();
		ensure_equals( blackManaAbilities->color , mtg::black );

		pool.remove(blackManaAbilities);
		ensure_equals( count(mtg::Mana::abilities) , 0 );
		ensure_equals( count(mtg::black) , 1 );
	}
}

