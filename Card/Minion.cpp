#include <iostream>
#include "Card.h"
#include "Minion.h"
#include "../Player.h"

using namespace std;

Minion::Minion(int cost, string name, string description, int attack, int defense, int actionValue,
               int recordActionValue, int magic, bool haveAbility, bool haveTrigger)
        : Card{cost, name, description}, att{attack}, defense{defense}, actionValue{actionValue},
          recordActionValue{recordActionValue}, magic{magic}, haveAbility{haveAbility}, haveTrigger{haveTrigger} {}

void Minion::mutateDef(int i) {
    defense += i;    //mutate defense. i is the damage
}

int Minion::getDef() { return defense; }

bool Minion::isDead(){ return defense <= 0; }

void Minion::setDef(int i) { defense = i; } //only for Raised Dead

void Minion::setActionValue() {   //when the turn ends, call this function and set every minions' action value = recordAction value;
    actionValue = recordActionValue;
}

int Minion::getActionValue() { return actionValue; }

void Minion::setRecordActionValue(int i) {
    recordActionValue = recordActionValue + i;
}

int Minion::getMagic() { return magic; }

void Minion::setMagic(int i) {
    this->magic = magic + i;
}

int Minion::getAtt() { return att; }

bool Minion::hasAbility() { return haveAbility; }

bool Minion::hasTrigger() { return haveTrigger; }

bool Minion::hasEnchant() { return !recordEnchantment.empty(); }

Enchantment &Minion::getEnchant(int i) { return  *(recordEnchantment.at(i)); }

int Minion::numOfEnchant() { return recordEnchantment.size(); }

void Minion::mutateAtt(int i) {
    att = att + i;
}

void Minion::attack(Player &p) {
    if (canAttack()){
        p.mutateLife(-getAtt());
        actionValue--;
    } else {
        cout << name << " action value = 0." << endl;
    }
}

void Minion::attack(Minion &otherMinion, Player &player, Player &otherPlayer) {
    if(canAttack()){
        mutateDef(-(otherMinion.getAtt()));
        otherMinion.mutateDef(-att);
        if(defense <= 0){
            player.getMyBoard()->addToGraveyard(*this);
            player.getMyBoard()->notifyAll(Card::Trigger::MY_MINION_LEAVE, *this, otherMinion, player, otherPlayer);
            otherPlayer.getMyBoard()->notifyAll(Card::Trigger::OTHER_MINION_LEAVE, otherMinion, *this, otherPlayer, player);
        }
        if(otherMinion.getDef() <=0){
            otherPlayer.getMyBoard()->addToGraveyard(otherMinion);
            player.getMyBoard()->notifyAll(Card::Trigger::OTHER_MINION_LEAVE, *this, otherMinion, player, otherPlayer);
            otherPlayer.getMyBoard()->notifyAll(Card::Trigger::MY_MINION_LEAVE, otherMinion, *this, player, otherPlayer);
        }
        actionValue --;
    }
    else {
        cout << this->name <<" not enough ." << endl;
    }
}


bool Minion::canPlay(Player &player){
    if (player.getMyBoard()->minionFull()) {
        cout << "Minion slot is full" << endl;
    }
}

void Minion::effect(Player &player, Player &otherPlayer) {
   player.moveCardToBoard(*this);
}

//CANNOT PLAY WITH A TARGET
void Minion::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) { }

void Minion::pushEnchantment(std::unique_ptr<Enchantment> e) { recordEnchantment.emplace_back(e); }

//----------------------------------------Air Elemental--------------------------------------------------------
bool Minion::canAttack() { return actionValue > 0; }

AirElemental::AirElemental() :
        Minion{1, "Air Elemental", "", 1, 1, 0, 1, 0, false, false} {}

void AirElemental::trigger(Card::Trigger t, Player &p) {}
void AirElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool AirElemental::ability(Player &p) { return false; }

bool AirElemental::ability(Player &p, Card &c) { return false; }

//---------------------------------------Earth Elemental----------------------------------------------------------
EarthElemental::EarthElemental() :
        Minion{3, "Earth Elemental", "", 4, 4, 0, 1, 0, false, false} {}

void EarthElemental::trigger(Card::Trigger t, Player &p) {}
void EarthElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool EarthElemental::ability(Player &p) { return false; }

bool EarthElemental::ability(Player &p, Card &c) { return false; }

//---------------------------------------------Bone Golem-----------------------------------------
BoneGolem::BoneGolem() :
        Minion{2, "Bone Golem", "Gain +1/+1 whenever a minion leaves play.", 1, 3, 0, 1, 0, false, true} {}

void BoneGolem::trigger(Card::Trigger t, Player &p) {}
void BoneGolem::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {
    if((t == Card::Trigger::MY_MINION_LEAVE) || (t == Card::Trigger::OTHER_MINION_ENTER)){
        mutateDef(1);
        mutateAtt(1);
    }
}

bool BoneGolem::ability(Player &p) { return false; }

bool BoneGolem::ability(Player &p, Card &c) { return false; }


//------------------------------------------Fire Elemental-----------------------------------------------
FireElemental::FireElemental() :
        Minion{2, "Fire Elemental", "Whenever an opponent's minion enters play, deal 1 damage to it.", 2, 2, 0, 1, 0,
               false, true} {}

void FireElemental::trigger(Card::Trigger t, Player &p) {}

void FireElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &other) {
    if (t == Card::Trigger::OTHER_MINION_ENTER){
        otherMinion.mutateDef(-1);
        if (otherMinion.getDef() <= 0) {
            other.getMyBoard()->addToGraveyard(otherMinion);
        }
    }
}


bool FireElemental::ability(Player &p) { return false; }

bool FireElemental::ability(Player &p, Card &c) { return false; }


PotionSeller::PotionSeller() :
        Minion{2, "Potion Seller", "At the end of your turn, all your minions gain +0/+1", 1, 3, 0, 1, 0, false,
               true} {}

//---------------------------------------------Potion Seller---------------------------------------------------
void PotionSeller::trigger(Card::Trigger t, Player &p) {
    if (t == Card::Trigger::END_OF_TURN){
        for (int i =0; i < p.getMyBoard()->numberOfMinions();i++){
            p.getMyBoard()->getMinion(i).mutateAtt(0);
            p.getMyBoard()->getMinion(i).mutateDef(1);
        }
    }
}

void PotionSeller::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

//--------------------------------------------Novice Pyromancer------------------------------------------------
NovicePyromancer::NovicePyromancer() :
        Minion{1, "Novice Pyromancer", "Deals 1 damage to target minion", 1, 1, 0, 1, 1, true, false} {}

void NovicePyromancer::trigger(Card::Trigger t, Player &p) {}

void NovicePyromancer::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool NovicePyromancer::ability(Player &p) { return false; }

bool NovicePyromancer::ability(Player &p, Card &c) {
    if (p.getMagic() > 1) {
        dynamic_cast<Minion &>(c).mutateDef(1);
        p.mutateMagic(-1);
        return true;
    } else return false;
}

//---------------------------------------------Apprentice Summoner-----------------------------------------------
ApprenticeSummoner::ApprenticeSummoner() :
        Minion{1, "Apprentice Summoner", "Summon a 1/1 air elemental", 1, 1, 0, 1, 1, true, false} {}

void ApprenticeSummoner::trigger(Card::Trigger t, Player &p) {}

void ApprenticeSummoner::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool ApprenticeSummoner::ability(Player &p) {
    if (p.getMagic() == 0) return false;
    if (p.getMyBoard()->numberOfMinions() == 5) return false;
    else if (p.getMyBoard()->numberOfMinions() < 5) {
        unique_ptr<Minion> m{new AirElemental};
        p.getMyBoard()->addMinion(std::move(m));
        p.mutateMagic(-1);
        return true;
    } else return false;
}

bool ApprenticeSummoner::ability(Player &p, Card &c) { return false; }

//--------------------------------------------------Master Summoner--------------------------------------
MasterSummoner::MasterSummoner() :
        Minion{3, "Master Summoner", "Summon up to three 1/1 air elementals", 2, 3, 0, 1, 2, true, false} {}

void MasterSummoner::trigger(Card::Trigger t, Player &p) {}

void MasterSummoner::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool MasterSummoner::ability(Player &p) {
    if (p.getMagic() < 2) return false;
    if (p.getMyBoard()->numberOfMinions() == 5) return false;
    else if (p.getMyBoard()->numberOfMinions() < 5) {
        unique_ptr<Minion> m{new AirElemental};
        p.getMyBoard()->addMinion(std::move(m));
        if (p.getMyBoard()->numberOfMinions() < 5) {
            unique_ptr<Minion> n{new AirElemental};
            p.getMyBoard()->addMinion(std::move(n));
        }
        if (p.getMyBoard()->numberOfMinions() < 5) {
            unique_ptr<Minion> q{new AirElemental};
            p.getMyBoard()->addMinion(std::move(q));
        }
        return true;
    } else return false;
}

bool MasterSummoner::ability(Player &p, Card &c) { return false; }
