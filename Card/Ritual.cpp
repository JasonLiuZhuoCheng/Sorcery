#include "Ritual.h"
#include "../Player.h"

Ritual::Ritual(int cost, std::string name, std::string description, int charges, int activeCost) :
        Card(cost, name, description), charges{charges}, activeCost{activeCost} {}

void Ritual::mutateCharges(int i) { charges += i; }

void Ritual::trigger(Trigger t, Player &){

}
void Ritual::trigger(Trigger t, Player &, Card &){}

bool Ritual::play(Player& player){

    player.getMyBoard()->setRitual(this);
}

bool Ritual::play(Player&, Card &){}

bool Ritual::canPlay(){
    if(activeCost <= charges){ return true; }
    return false;
}
DarkRitual::DarkRitual():
    Ritual(0, "DarkRitual", "At the start of you turn, Gain 1 magic", 5, 1){}


void DarkRitual::trigger(Card::Trigger t, Player &player) {
    if(t == Card::Trigger::START_OF_TURN && canPlay()) {
        player.mutateMagic(1);
        this->mutateCharges(-1);
        mutateCharges(-activeCost);
    }
}

void DarkRitual::trigger(Card::Trigger t, Player &, Card &) {}


AuraOfPower::AuraOfPower():
    Ritual(1, "AuraOfPower", "Whenever a minion enter a play under your control, it gains +1/+1", 4, 1){}

void AuraOfPower::trigger(Trigger t, Player &){}

void AuraOfPower::trigger(Trigger t, Player & player, Card & minion){
    if(t == Card::Trigger::MINION_ENTER && canPlay()) {
        dynamic_cast<Minion &>(minion).mutateAtt(1);
        dynamic_cast<Minion &>(minion).mutateDef(1);
        mutateCharges(-activeCost);
    }
}

Standstill::Standstill():
        Ritual(1, "Standstill", "Whenever a minion enter a play, destroy it", 4, 2){}


void Standstill::trigger(Trigger t, Player &){}

void Standstill::trigger(Trigger t, Player & player, Card & minion){
    if(t == Card::Trigger::MINION_ENTER && canPlay()) {
        Board *temp = player.getMyBoard();
        temp->addToGraveyard(temp->removeMinion(temp->getMinion(dynamic_cast<Minion &>(minion))));
        mutateCharges(-activeCost);
    }
}


