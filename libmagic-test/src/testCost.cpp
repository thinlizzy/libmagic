#include <tut.h>

#include <magic.h>

namespace {
    struct setup {
    };
}

namespace tut { 

    typedef test_group<setup> tg;
    tg cost_test_group("Cost");
    
    typedef tg::object testobject;
    
    template<> 
    template<> 
    void testobject::test<1>() 
    {
        set_test_name("noncolored only");
		mtg::Cost cost = mtg::parseCost("10");
		ensure_equals( cost.convertedManaCost() , 10 );
    }   

    template<> 
    template<> 
    void testobject::test<2>() 
    {
        set_test_name("red");
		mtg::Cost cost = mtg::parseCost("3RR");
		ensure_equals( cost.convertedManaCost() , 5 );
    }   

    template<> 
    template<> 
    void testobject::test<3>() 
    {
        set_test_name("beseech the queen");
		mtg::Cost cost = mtg::parseCost("2/B2/B2/B");
		ensure_equals( cost.convertedManaCost() , 6 );
		ensure( cost.hasColor(mtg::black) );
    }   

    template<> 
    template<> 
    void testobject::test<4>() 
    {
        set_test_name("mixed");
		mtg::Cost cost = mtg::parseCost("1WR/B");
		ensure_equals( cost.convertedManaCost() , 3 );
		ensure( ! cost.hasColor(mtg::green) );
		ensure( ! cost.hasColor(mtg::blue) );
		ensure( cost.hasColor(mtg::black) );
		ensure( cost.hasColor(mtg::red) );
		ensure( cost.hasColor(mtg::white) );
    }   

    template<> 
    template<> 
    void testobject::test<5>() 
    {
        set_test_name("fireball");
		mtg::Cost cost = mtg::parseCost("XR");
		ensure_equals( cost.convertedManaCost() , 1 );
		ensure( cost.hasColor(mtg::red) );
		ensure( ! cost.hasColor(mtg::green) );
    }   

    template<> 
    template<> 
    void testobject::test<6>() 
    {
        set_test_name("mind warp");
		mtg::Cost cost = mtg::parseCost("X3B");
		ensure_equals( cost.convertedManaCost() , 4 );
		ensure( cost.hasColor(mtg::black) );
    }   

    template<> 
    template<> 
    void testobject::test<7>() 
    {
        set_test_name("unknown card");
		mtg::Cost cost = mtg::parseCost("15 2/R/G");
		ensure_equals( cost.convertedManaCost() , 17 );
		ensure( cost.hasColor(mtg::red) );
		ensure( cost.hasColor(mtg::green) );
    }   

    template<>
    template<>
    void testobject::test<8>()
    {
        set_test_name("snow");
		mtg::Cost cost = mtg::parseCost("S1");
		ensure_equals( cost.convertedManaCost() , 2 );
		ensure( cost.colorless() );
    }

    template<>
    template<>
    void testobject::test<9>()
    {
        set_test_name("snow with colors");
		mtg::Cost cost = mtg::parseCost("G2S1");
		ensure_equals( cost.convertedManaCost() , 5 );
		ensure( cost.hasColor(mtg::green) );
    }

    template<>
    template<>
    void testobject::test<10>()
    {
        set_test_name("verify sorting");
		mtg::Cost cost = mtg::parseCost("YXG2S1R/P");
		// put all colorless mana to the start
		std::stable_sort(cost.symbols.begin(),cost.symbols.end(),[](auto s1, auto s2) {
			return s1.colorless() > s2.colorless();
		});

		ensure_equals( cost.convertedManaCost() , 6 );
		ensure( cost.symbols[0].specific.Y );
		ensure( cost.symbols[1].specific.X );
		ensure_equals( cost.symbols[2].generic , 2 );
		ensure( cost.symbols[3].specific.snow );
		ensure_equals( cost.symbols[3].generic , 1 );
		ensure_equals( cost.symbols[4].generic , 1 );
		ensure( cost.symbols[5].hasColor(mtg::green) );
		ensure( cost.symbols[6].hasColor(mtg::red) );
		ensure( cost.symbols[6].specific.phyrexian );
    }
}
