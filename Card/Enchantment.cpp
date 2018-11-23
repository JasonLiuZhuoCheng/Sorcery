//
// Created by jason on 2018-11-20.
//

#include "Enchantment.h"
#include "Minion.h"

Enchantment::Enchantment(int cost, std::string name, std::string description, Minion *minion)
        : Card{cost, name, description}, minion{minion} {}

Enchantment::~Enchantment() {}

GiantStrength::GiantStrength(Minion *minion) : Enchantment{1, "Giant Strength", "", minion} {}

void GiantStrength::changeMinion() {
    this->minion->mutateAtt(2);   //add two attack
    this->minion->mutateDef(-2);  //add two defense
}

Enrage::Enrage(Minion *) : Enchantment{2, "Enrage", "", minion} {}

void Enrage::changeMinion() {
    this->minion->mutateAtt(this->minion->getAtt());  // doubles the attack
    this->minion->mutateDef(-1 * this->minion->getDef());  // doubles the defense
}

Haste::Haste(Minion *) : Enchantment{1, "Haste", "Enchanted minion gains +1 action each turn", minion} {}

void Haste::changeMinion() {}

void Haste::triggerChange(Card::Trigger t) {
    if (t == Card::Trigger::END_OF_TURN) {
        this->minion->setRecordActionValue(1);   // action value + 1 at the end of turn
    }
}

MagicFatigue::MagicFatigue(Minion *) : Enchantment{0, "Magic Fatigue",
                                                   "Enchanted minion's activated ability costs 2 more", minion} {}

void MagicFatigue::changeMinion() {
    this->minion->setMagic(this->minion->getMagic());  //double the magic used for active ability
}

Silence::Silence(Minion *) : Enchantment{1, "Silence", "Enchanted minion cannot use abilities", minion} {}

void Silence::changeMinion() {
    this->minion->setMagic(
            -1 * this->minion->getMagic() - 1); //set the magic needed for ability to -1. when use ability check if
    // it is negative. Negative means silenced, cannot use ability.
}