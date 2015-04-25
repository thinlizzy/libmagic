#include <tut.h>
#include <magic.h>
#include "Factory4th.h"

namespace {
    struct setup {
		mtg::Factory4th factory;
		mtg::Player player;
        setup(): player("player") {}
    };
}

namespace tut { 

    typedef test_group<setup> tg;
    tg Player_test_group("Permanent");
    
    typedef tg::object testobject;

    template<> 
    template<> 
    void testobject::test<1>() 
    {
        set_test_name("play and check");

		player.cards.library.assign(factory.cards.begin(),factory.cards.end());
		player.draw();
		auto card = player.cards.hand.begin();
        
		mtg::Permanent perm(player,card);

		ensure_not( perm.isToken() );
        ensure_equals(&perm.getSourceCardData(),&*card);
        ensure_equals(perm.getCurrentCardData(),*card);
    }

    template<> 
    template<> 
    void testobject::test<2>() 
    {
        set_test_name("token");

		mtg::Permanent perm(player,factory.cards[0]);

		ensure( perm.isToken() );
		ensure_equals(perm.getSourceCardData().mainStat,factory.cards[0].mainStat);
        ensure_equals(perm.getCurrentCardData(),factory.cards[0]);
    }

    template<> 
    template<> 
    void testobject::test<3>() 
    {
        set_test_name("attachments");

 		player.cards.library.assign(factory.cards.begin(),factory.cards.end());
		auto card1 = player.cards.library.begin();
		mtg::Permanent perm1(player,card1);
		auto card2 = std::next(card1);
		mtg::Permanent perm2(player,card2);

        perm1.attachInto(perm2);
        perm2.attachInto(player);
        
        ensure_equals( perm1.attachedOnPermanent , &perm2 );
        ensure( perm2.hasAttachment(perm1) );
        ensure_equals( perm2.attachedOnPlayer , &player );
        ensure_equals( player.attachments.count(&perm2) ,1 );
   }

}
