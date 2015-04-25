#ifndef OWNED_CARDS_H_fj3429udfsjds9fjdsf
#define OWNED_CARDS_H_fj3429udfsjds9fjdsf

#include "CardRef.h"

namespace mtg {

class OwnedCards {
	static Cards OwnedCards::*listFromZone[int(Zone::zones)];
public:
    // hidden zones
	Cards library;
	Cards hand;
	Cards sideboard;    // for wishes
    // public zones
	Cards graveyard;
	Cards exile;
	Cards hiddenExile;  // face down exiled cards
	Cards battlefield;
	Cards stack;
	Cards command;
    Cards ante;
    
    Cards & fromZone(Zone zone);
	CardIts randomSelect(int cards, Zone zone);
	void move(CardIt it, Zone zsrc, Zone zdest);
	void moveCards(CardIts & its, Zone zsrc, Zone zdest);
};

}


#endif