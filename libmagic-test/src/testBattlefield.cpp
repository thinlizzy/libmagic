#include <tut.h>
#include <magic.h>
#include "Factory4th.h"

namespace {
	struct setup {
		mtg::Factory4th factory;
		mtg::Player player;
		mtg::Battlefield battlefield;

		setup():
			player("player 1")
		{
			player.cards.library.assign(factory.cards.begin(),factory.cards.end());
		}
	};
}

namespace tut { 

	typedef test_group<setup> tg;
	tg Player_test_group("Battlefield");

	typedef tg::object testobject;

	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("play");

		auto card1 = player.cards.library.begin();
		mtg::PermanentIt perm1 = battlefield.play(player,card1,mtg::Zone::library);
		auto card2 = player.cards.library.begin();
		mtg::PermanentIt perm2 = battlefield.play(player,card2,mtg::Zone::library);

		ensure_equals(player.cards.battlefield.size(),2);
		ensure_equals(player.cards.battlefield.begin(),card2);
		ensure_equals(std::next(player.cards.battlefield.begin()),card1);

		ensure_equals(battlefield.permanents.size(),2);
		ensure_equals(battlefield.permanents.begin(),perm1);
		ensure_equals(std::next(battlefield.permanents.begin()),perm2);
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("cast");

		player.draw(7);
		auto card1 = player.cards.hand.begin();
		mtg::StackIt sit = battlefield.cast(player,card1);

		ensure_equals(player.cards.hand.size(),6);
		ensure_equals(player.cards.stack.size(),1);
		ensure_equals(player.cards.stack.begin(),card1);

		ensure_equals(battlefield.stack.size(),1);

		mtg::Player player2("player 2");
		auto card2 = player.cards.hand.begin();
		mtg::PermanentIt perm1 = battlefield.play(player,card2);

		mtg::addTargetPlayer(*sit,player);
		mtg::addTargetPlayer(*sit,player2);
		mtg::addTargetPermanent(*sit,perm1);

		ensure_equals(sit->targets.size(),3);
		ensure_equals(sit->targets.count(mtg::TargetType::player),2);
		ensure_equals(sit->targets.count(mtg::TargetType::permanent),1);

		auto it = sit->targets.find(mtg::TargetType::player);
		ensure(dynamic_cast<mtg::TargetPlayer *>(it->second.get()) != 0);

		auto it2 = sit->targets.find(mtg::TargetType::permanent);
		auto tgtPerm = dynamic_cast<mtg::TargetPermanent *>(it2->second.get());
		ensure(tgtPerm != 0);
		ensure_equals(tgtPerm->target,perm1);
	}

	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("by owner");

		auto card1 = player.cards.library.begin();
		mtg::PermanentIt perm1 = battlefield.play(player,card1,mtg::Zone::library);
		auto card12 = player.cards.library.begin();
		mtg::PermanentIt perm12 = battlefield.play(player,card12,mtg::Zone::library);

		mtg::Player player2("player 2");
  		player2.cards.library.assign(factory.cards.begin(),factory.cards.end());
		auto card2 = player2.cards.library.begin();
		mtg::PermanentIt perm2 = battlefield.play(player2,card2,mtg::Zone::library);

		ensure_equals(battlefield.permanents.size(),3);
		ensure_equals("1",battlefield.permanents.begin(),perm1);
		ensure_equals("2",std::next(battlefield.permanents.begin()),perm12);
		ensure_equals("3",std::next(std::next(battlefield.permanents.begin())),perm2);

		ensure_equals(battlefield.permanents.byOwner(player).size(),2);
		ensure_equals(battlefield.permanents.byOwner(player2).size(),1);

		ensure_equals(battlefield.permanents.byOwner(player).count(perm1),1);
		ensure_equals("4",*battlefield.permanents.byOwner(player2).begin(),perm2);
	}
   
	template<>
	template<>
	void testobject::test<4>()
	{
		set_test_name("by controller");

		auto card1 = player.cards.library.begin();
		battlefield.play(player,card1,mtg::Zone::library);
		auto card12 = player.cards.library.begin();
		battlefield.play(player,card12,mtg::Zone::library);

		mtg::Player player2("player 2");
  		player2.cards.library.assign(factory.cards.begin(),factory.cards.end());
		auto card2 = player2.cards.library.begin();
		battlefield.play(player2,card2,mtg::Zone::library);

		ensure_equals(battlefield.permanents.size(),3);
		ensure_equals(battlefield.permanents.byController(player).size(),2);
		ensure_equals(battlefield.permanents.byController(player2).size(),1);

		auto permIt = battlefield.permanents.begin();
		ensure_equals(&permIt->getController(),&player);

		auto perm = *permIt;
		perm.setController(player2);
		battlefield.permanents.replace(permIt,perm);

		ensure_equals(battlefield.permanents.byController(player).size(),1);
		ensure_equals(battlefield.permanents.byController(player2).size(),2);
	}

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("cast and play");

		player.draw(7);
		auto card1 = player.cards.hand.begin();
		mtg::StackIt sit = battlefield.cast(player,card1);

		ensure_equals(player.cards.hand.size(),6);

		mtg::PermanentIt permIt = battlefield.play(sit);

		ensure_equals(player.cards.battlefield.size(),1);

		ensure_equals(battlefield.stack.size(),0);
		ensure_equals(battlefield.permanents.size(),1);
		ensure_equals(battlefield.permanents.byController(player).size(),1);
		ensure_equals(*battlefield.permanents.byController(player).begin(),permIt);
	}

	template<>
	template<>
	void testobject::test<6>()
	{
		set_test_name("cast instant and copy it");

		player.draw(7);
		auto card1 = player.cards.hand.begin();
		mtg::StackIt sit = battlefield.cast(player,card1);
		mtg::addTargetPlayer(*sit,player);

		ensure_equals(player.cards.hand.size(),6);
		ensure_equals(player.cards.stack.size(),1);
		ensure_equals(battlefield.stack.size(),1);

		mtg::Player player2("player 2");
		mtg::StackIt sit2 = battlefield.copySpell(sit,player2);

		ensure_equals(battlefield.stack.size(),2);

		mtg::StackObject so = battlefield.move(sit,mtg::Zone::graveyard);
		ensure_equals(*so.source,card1);
		ensure(!so.isCopy());
		ensure_equals(&so.getOwner(),&player);
		ensure_equals(&so.getController(),&player);
		ensure_equals(so.targets.size(),1);

		ensure_equals(battlefield.stack.size(),1);
		ensure_equals(player.cards.stack.size(),0);
		ensure_equals(player.cards.graveyard.size(),1);
		ensure_equals(player.cards.battlefield.size(),0);
		ensure_equals(battlefield.permanents.size(),0);

		so = battlefield.move(sit2,mtg::Zone::graveyard);
		ensure(so.isCopy());
		ensure_equals(so.getCardData(),*card1);
		ensure_equals(&so.getOwner(),&player);
		ensure_equals(&so.getController(),&player2);

		ensure_equals(battlefield.stack.size(),0);
	}

	template<>
	template<>
	void testobject::test<7>()
	{
		set_test_name("bounce");

		auto card1 = player.cards.library.begin();
		battlefield.play(player,card1,mtg::Zone::library);
		auto card12 = player.cards.library.begin();
		battlefield.play(player,card12,mtg::Zone::library);

		mtg::Player player2("player 2");
  		player2.cards.library.assign(factory.cards.begin(),factory.cards.end());
		auto card2 = player2.cards.library.begin();
		battlefield.play(player2,card2,mtg::Zone::library);

		// TODO finish this test
	}
}
