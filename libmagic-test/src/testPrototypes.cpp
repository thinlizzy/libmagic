#include <tut.h>
#include <magic.h>

namespace {
	struct setup {
	};
}

namespace tut { 

	typedef test_group<setup> tg;
	tg prototypes_test_group("prototypes");

	typedef tg::object testobject;

	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("swamp proto");

		auto land = mtg::prototypes->swamp;
		// cout << land.name << endl;
		ensure_equals(0,land.cost.convertedManaCost());
		ensure("no land type",bool(land.land));
		ensure(land.land->types.find(mtg::swamp) != land.land->types.end());
		ensure_equals(1,land.land->types.size());
		ensure(! land.hasColor(mtg::Color::green));
		ensure(! land.colors_);
	}

}
