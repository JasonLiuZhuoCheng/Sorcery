#include <iostream>
#include "Ritual.h"
#include "../Player.h"

using namespace std;
Ritual::Ritual(int cost, std::string name, std::string description, int charges, int activeCost) :
        Card(cost, name, description), charges{charges}, activeCost{activeCost} {}

void Ritual::mutateCharges(int i) { charges += i; }

void Ritual::trigger(Trigger t, Player &){

}
void Ritual::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer){}

int Ritual::getActiveCost() {
    return activeCost;
}

int Ritual::getCharges() {
    return cost;
}

bool Ritual::play(Player& player){ return true;}

bool Ritual::play(Player&, Card &){ return false; }

//---------------------------------------------------Dark Ritual---------------------------------------------
DarkRitual::DarkRitual():
    Ritual(0, "DarkRitual", "At the start of you turn, Gain 1 magic", 5, 1){}


void DarkRitual::trigger(Card::Trigger t, Player &player) {
    if(t == Card::Trigger::START_OF_TURN && canPlay()) {//if the condition is right and the player is able to use this card
        player.mutateMagic(1);
        mutateCharges(-activeCost);
    }
}

void DarkRitual::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}


//---------------------------------------------------Aura of Power----------------------------------------
AuraOfPower::AuraOfPower():
    Ritual(1, "AuraOfPower", "Whenever a minion enter a play under your control, it gains +1/+1", 4, 1){}

void AuraOfPower::trigger(Trigger t, Player &){}

void AuraOfPower::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer){
    if(t == Card::Trigger::MY_MINION_ENTER && canPlay()) {
        dynamic_cast<Minion &>(myMinion).mutateAtt(1);
        dynamic_cast<Minion &>(myMinion).mutateDef(1);
        mutateCharges(-activeCost);
    }
}

//------------------------------------------------------Standstill-------------------------------------------
Standstill::Standstill():
        Ritual(1, "Standstill", "Whenever a minion enter a play, destroy it", 4, 2){}


void Standstill::trigger(Trigger t, Player &){}

void Standstill::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer){
    if((t == Card::Trigger::MY_MINION_ENTER) && canPlay()){
        player.getMyBoard()->addToGraveyard(myMinion);
        mutateCharges(-activeCost);
    }
    else if((t == Card::Trigger::OTHER_MINION_ENTER)) && canPlay() && otherPlayer){
        otherPlayer.getMyBoard()->addToGraveyard(otherMinion);
        mutateCharges(-activeCost);
    }
}


