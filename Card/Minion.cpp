#include <iostream>
#include "Card.h"
#include "Minion.h"
#include "../Player.h"

using namespace std;

Minion::Minion(int cost, string name, string description, int attack, int defense, int actionValue,
               int recordActionValue, int magic, bool hasAbility, bool hasTrigger)
        : Card{cost, name, description}, att{attack}, defense{defense}, actionValue{actionValue},
          recordActionValue{recordActionValue}, magic{magic}, hasAbility{hasAbility}, hasTrigger{hasTrigger} {}

Minion::~Minion() {}

void Minion::mutateDef(int i) {
    this->defense = this->defense + i;    //mutate defense. i is the damage
}

int Minion::getDef() {
    return this->defense;
}

bool Minion::isDead(){
    return (defense <= 0);
}

void Minion::setDef() {   //raise dead
    this->defense = 1;
}

void Minion::setActionValue() {   //when the turn ends, call this function and set every minions' action value = recordAction value;
    this->actionValue == this->recordActionValue;
}

int Minion::getActionValue() {
    return this->actionValue;
}

void Minion::setRecordActionValue(int i) {
    this->recordActionValue = this->recordActionValue + i;
}

int Minion::getMagic() {
    return this->magic;
}

void Minion::setMagic(int i) {
    this->magic = this->magic + i;
}

int Minion::getAtt() {
    return this->att;
}

void Minion::mutateAtt(int i) {
    this->att = this->att + i;
}

void Minion::attack(Player &p) {
    if (actionValue > 0){
        p.mutateLife(-getAtt());
        actionValue--;
    } else {
        cout << name << " action value = 0." << endl;
    }
}

void Minion::attack(Minion &otherMinion, Player &player, Player &otherPlayer) {
    if(actionValue > 0){
        mutateDef(-(otherMinion.att));
        if(){

        }

    }
    else {
        cout << this->name <<" action value = 0." << endl;
    }
    /*if (actionValue > 0){
        b->getMinion(i).mutateDef(-att);
        if (b->getMinion(i).getDef() <= 0) {
            b->addToGraveyard();
        }
        this->mutateDef(b->getMinion(i).att);
        if (getDef() <= 0) {
            b->addToGraveyard(p.getOtherBoard()->removeMinion(i));
        }
        actionValue--;
    } else {
        cout << this->name <<" action value = 0." << endl;
    }*/
}

bool Minion::play(Player &p) {
    if (p.getMyBoard()->numberOfMinions() == 5) {
        cout << "Minion slot is full" << endl;
        return false;
    }
    //p.getMyBoard()->addMinion(this);
    return true;
}

bool Minion::play(Player &p, Card &c) { return false; }

std::vector<Enchantment*> Minion::getEnchantment() {
    return this->recordEnchantment;
}

void Minion::pushEnchantment(Enchantment *e) {
    this->recordEnchantment.emplace_back(e);
}



AirElemental::AirElemental() :
        Minion{1, "Air Elemental", "", 1, 1, 0, 1, 0, false, false} {}

void AirElemental::trigger(Card::Trigger t, Player &p) {}
void AirElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool AirElemental::ability(Player &p) { return false; }

bool AirElemental::ability(Player &p, Card &c) { return false; }


EarthElemental::EarthElemental() :
        Minion{3, "Earth Elemental", "", 4, 4, 0, 1, 0, false, false} {}

void EarthElemental::trigger(Card::Trigger t, Player &p) {}
void EarthElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool EarthElemental::ability(Player &p) { return false; }

bool EarthElemental::ability(Player &p, Card &c) { return false; }

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

void PotionSeller::trigger(Card::Trigger t, Player &p) {
    if (t == Card::Trigger::END_OF_TURN){
        for (int i =0; i < p.getMyBoard()->numberOfMinions();i++){
            p.getMyBoard()->getMinion(i).mutateAtt(0);
            p.getMyBoard()->getMinion(i).mutateDef(1);
        }
    }
}

void PotionSeller::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

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




ApprenticeSummoner::ApprenticeSummoner() :
        Minion{1, "Apprentice Summoner", "Summon a 1/1 air elemental", 1, 1, 0, 1, 1, true, false} {}

void ApprenticeSummoner::trigger(Card::Trigger t, Player &p) {}

void ApprenticeSummoner::trigger(Trigger t, Minion &myMinion, Minion &otherMinion) {}

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

MasterSummoner::MasterSummoner() :
        Minion{3, "Master Summoner", "Summon up to three 1/1 air elementals", 2, 3, 0, 1, 2, true, false} {}

void MasterSummoner::trigger(Card::Trigger t, Player &p) {}

void MasterSummoner::trigger(Card::Trigger t, Player &p, Card &c) {}

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


