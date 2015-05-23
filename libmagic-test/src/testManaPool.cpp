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

		auto bc = pool.getByColor(mtg::Color::red);
		ensure( bc.empty() );
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("noncolored only");

		pool.add(mtg::Color::colorless);
		ensure_equals( pool.mana().size() , 1 );

		auto bc = pool.getByColor(mtg::Color::colorless);
		ensure( ! bc.empty() );

		checkAllColor(mtg::Color::colorless,1);
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("multiple colors");

		pool.add(mtg::Color::colorless);
		pool.add(mtg::Color::colorless, mtg::Mana::snow, {});
		pool.add(mtg::Color::red);
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::green);
		ensure_equals( pool.mana().size() , 5 );

		checkAllColor(mtg::Color::colorless,2);
		checkAllColor(mtg::Color::red,1);
		checkAllColor(mtg::Color::green,2);
		checkAllColor(mtg::Color::blue,0);
		checkAllColor(mtg::Color::white,0);
		checkAllColor(mtg::Color::black,0);
	}

	template<>
	template<>
	void testobject::test<4>()
	{
		set_test_name("snow and annotated");

		pool.add(mtg::Color::colorless);
		pool.add(mtg::Color::black, mtg::Mana::snow, {});
		pool.add(mtg::Color::black, {}, {mtg::Mana::abilities});
		pool.add(mtg::Color::white, mtg::Mana::snow, {mtg::Mana::abilities, mtg::Mana::artifact, });
		ensure_equals( pool.mana().size() , 4 );

		checkAllColor(mtg::Color::colorless,1);
		checkAllColor(mtg::Color::black,2);
		checkAllColor(mtg::Color::white,1);

		int ts = 0;
		for( auto mana : pool.getBySource(mtg::Mana::snow) ) {
			ensure_equals( mana->source , mtg::Mana::snow );
			ensure( mana->color == mtg::Color::black || mana->color == mtg::Color::white );
			++ts;
		}
		ensure_equals( ts , 2 );

		int taa = 0;
		for( auto mana : pool.getByAnnotation(mtg::Mana::abilities) ) {
			ensure( mana->annotations & mtg::Mana::abilities );
			ensure( mana->color == mtg::Color::black || mana->color == mtg::Color::white );
			++taa;
		}
		ensure_equals( taa , 2 );

		int tar = 0;
		for( auto mana : pool.getByAnnotation(mtg::Mana::artifact) ) {
			ensure( mana->annotations & mtg::Mana::artifact );
			ensure( mana->color == mtg::Color::white );
			++tar;
		}
		ensure_equals( tar , 1 );
	}

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("remove");

		pool.add(mtg::Color::colorless);
		pool.add(mtg::Color::black, mtg::Mana::snow, {});
		pool.add(mtg::Color::black, {}, {mtg::Mana::abilities});
		pool.add(mtg::Color::white, mtg::Mana::snow, {mtg::Mana::abilities, mtg::Mana::artifact, });
		pool.add(mtg::Color::green);
		pool.add(mtg::Color::green, mtg::Mana::snow, {mtg::Mana::upkeep});
		pool.add(mtg::Color::green, mtg::Mana::snow, {mtg::Mana::spells});
		pool.add(mtg::Color::red, {}, {mtg::Mana::upkeep, mtg::Mana::creature});
		pool.add(mtg::Color::blue);

		ensure_equals( pool.mana().size() , 9 );
		ensure_equals( count(mtg::Mana::snow) , 4 );
		ensure_equals( count(mtg::Mana::abilities) , 2 );
		ensure_equals( count(mtg::Mana::artifact) , 1 );
		ensure_equals( count(mtg::Mana::upkeep) , 2 );

		// remove the first (and the only) white mana
		auto bc = pool.getByColor(mtg::Color::white);
		ensure( ! bc.empty() );
		pool.remove(*bc.begin());
		ensure_equals( pool.mana().size() , 8 );
		ensure_equals( count(mtg::Mana::snow) , 3 );
		bc = pool.getByColor(mtg::Color::white);
		ensure( bc.empty() );
		ensure_equals( count(mtg::Mana::abilities) , 1 );
		ensure_equals( count(mtg::Mana::artifact) , 0 );

		auto ba = pool.getByAnnotation(mtg::Mana::abilities);
		ensure( ! ba.empty() );
		auto blackManaAbilities = *ba.begin();
		ensure_equals( blackManaAbilities->color , mtg::Color::black );

		pool.remove(blackManaAbilities);
		ensure_equals( count(mtg::Mana::abilities) , 0 );
		ensure_equals( count(mtg::Color::black) , 1 );
	}
}

