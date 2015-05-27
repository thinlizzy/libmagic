#include <tut.h>
#include <magic.h>

namespace {
	struct setup {
		mtg::matcher::Permuter symbolPermuter;
	};
}

namespace tut {
	typedef test_group<setup> tg;
	tg mana_test_group("permuter");

	typedef tg::object testobject;

	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("permute simple");
		mtg::Cost cost = mtg::parseCost("R");
		int times = 0;
		symbolPermuter.tryPermutations(cost.symbols,[&times](mtg::Cost::Symbols const & symbols) -> bool {
			++times;
			ensure_equals( symbols.size() , 1 );
			ensure_equals( symbols[0] , mtg::CostSymbol(mtg::Color::red) );
			return false;
		});
		ensure_equals( times , 1 );
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("permute expand");
		mtg::Cost cost = mtg::parseCost("X3W");
		int times = 0;
		symbolPermuter.tryPermutations(cost.symbols,[&times](mtg::Cost::Symbols const & symbols) -> bool {
			++times;
			ensure_equals( symbols.size() , 5 );
			ensure_equals( symbols[0] , mtg::CostSymbol(mtg::Color::white) );
			ensure_equals( symbols[1] , mtg::CostSymbol(1) );
			ensure_equals( symbols[2] , mtg::CostSymbol(mtg::CostSymbol::X) );
			ensure_equals( symbols[3] , mtg::CostSymbol(1) );
			ensure_equals( symbols[4] , mtg::CostSymbol(1) );
			return false;
		});
		ensure_equals( times , 1 );
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("permute multiple");
		mtg::Cost cost = mtg::parseCost("W/BGU/R");
		int times = 0;
		symbolPermuter.tryPermutations(cost.symbols,[&times](mtg::Cost::Symbols const & symbols) -> bool {
			++times;
			ensure_equals( symbols.size() , 3 );
			ensure_equals( symbols[0] , mtg::CostSymbol(mtg::Color::green) ); // green is always the first color
			return false;
		});
		ensure_equals( times , 4 );
	}

	template<>
	template<>
	void testobject::test<4>()
	{
		set_test_name("permute repeated with beseech the queen");
		mtg::Cost cost = mtg::parseCost("2/B2/B2/B");
		int times = 0;
		symbolPermuter.tryPermutations(cost.symbols,[&times](mtg::Cost::Symbols const & symbols) -> bool {
			++times;
			return false;
		});
		ensure_equals( times , 4 );
	}
}
