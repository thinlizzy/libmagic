#include <tut.h>

#include <magic.h>

namespace {
    struct setup {
    };
}

namespace tut { 

    typedef test_group<setup> tg;
    tg factory4th_test_group("Cost");
    
    typedef tg::object testobject;
    
    template<> 
    template<> 
    void testobject::test<1>() 
    {
        set_test_name("noncolored only");
		mtg::Cost cost = "10";
		ensure_equals( cost.convertedManaCost() , 10 );
    }   

    template<> 
    template<> 
    void testobject::test<2>() 
    {
        set_test_name("red");
		mtg::Cost cost = "3RR";
		ensure_equals( cost.convertedManaCost() , 5 );
    }   

    template<> 
    template<> 
    void testobject::test<3>() 
    {
        set_test_name("beseech the queen");
		mtg::Cost cost = "2/B2/B2/B";
		ensure_equals( cost.convertedManaCost() , 6 );
		ensure( cost.getColors().hasColor(mtg::black) );
    }   

    template<> 
    template<> 
    void testobject::test<4>() 
    {
        set_test_name("mixed");
		mtg::Cost cost = "1WR/B";
		ensure_equals( cost.convertedManaCost() , 3 );
		ensure( ! cost.getColors().hasColor(mtg::green) );
		ensure( ! cost.getColors().hasColor(mtg::blue) );
		ensure( cost.getColors().hasColor(mtg::black) );
		ensure( cost.getColors().hasColor(mtg::red) );
		ensure( cost.getColors().hasColor(mtg::white) );
    }   

    template<> 
    template<> 
    void testobject::test<5>() 
    {
        set_test_name("fireball");
		mtg::Cost cost = "XR";
		ensure_equals( cost.convertedManaCost() , 1 );
		ensure( cost.getColors().hasColor(mtg::red) );
		ensure( ! cost.getColors().hasColor(mtg::green) );
    }   

    template<> 
    template<> 
    void testobject::test<6>() 
    {
        set_test_name("mind warp");
		mtg::Cost cost = "X3B";
		ensure_equals( cost.convertedManaCost() , 4 );
		ensure( cost.getColors().hasColor(mtg::black) );
    }   

    template<> 
    template<> 
    void testobject::test<7>() 
    {
        set_test_name("unknown card");
		mtg::Cost cost = "15 2/R/G";
		ensure_equals( cost.convertedManaCost() , 17 );
		ensure( cost.getColors().hasColor(mtg::red) );
		ensure( cost.getColors().hasColor(mtg::green) );
    }   

    template<>
    template<>
    void testobject::test<8>()
    {
        set_test_name("snow");
		mtg::Cost cost = "S1";
		ensure_equals( cost.convertedManaCost() , 2 );
		ensure( cost.getColors().monoColored() );
    }

    template<>
    template<>
    void testobject::test<9>()
    {
        set_test_name("snow with colors");
		mtg::Cost cost = "G2S1";
		ensure_equals( cost.convertedManaCost() , 5 );
		ensure( cost.getColors().hasColor(mtg::green) );
    }

}
