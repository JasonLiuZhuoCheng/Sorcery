//
// Created by jason on 2018-11-20.
//

#include "Enchantment.h"
#include "Minion.h"

Enchantment::Enchantment(int cost, std::string att, std::string def, std::string name, std::string description, Minion *minion)
        : Card{cost, name, description}, minion{minion},hasAttDef{true} {
}

Enchantment::~Enchantment() {}

void Enchantment::effect(Player &player, Player &otherPlayer) {}

bool Enchantment::hasStats() { return  hasAttDef; }

bool Enchantment::canPlay() { return true; }

std::string Enchantment::getAtt() { return att; }

std::string Enchantment::getDef() { return def; }

GiantStrength::GiantStrength(Minion *minion) : Enchantment{1, "+2" , "+2",  "Giant Strength", "", minion} {
    minion->pushEnchantment(this);
}

void GiantStrength::changeMinion() {
    this->minion->mutateAtt(2);   //add two attack
    this->minion->mutateDef(-2);  //add two defense
}

Enrage::Enrage(Minion *minion) : Enchantment{2, "*2", "*2", "Enrage", "", minion} {
    minion->pushEnchantment(this);
}

void Enrage::changeMinion() {
    this->minion->mutateAtt(this->minion->getAtt());  // doubles the attack
    this->minion->mutateDef(-1 * this->minion->getDef());  // doubles the defense
}

Haste::Haste(Minion *minion) : Enchantment{1, "Haste", "", "", "Enchanted minion gains +1 action each turn", minion} {
    this->hasAttDef = false;
    minion->pushEnchantment(this);
}

void Haste::changeMinion() {
    this->minion->setRecordActionValue(1);
}

MagicFatigue::MagicFatigue(Minion *minion) : Enchantment{0, "", "", "Magic Fatigue",
                                                   "Enchanted minion's activated ability costs 2 more", minion} {
    this->hasAttDef = false;
    minion->pushEnchantment(this);
}

void MagicFatigue::changeMinion() {
    this->minion->setMagic(this->minion->getMagic());  //double the magic used for active ability
}

Silence::Silence(Minion *minion) : Enchantment{1, "", "", "Silence", "Enchanted minion cannot use abilities", minion} {
    this->hasAttDef = false;
    minion->pushEnchantment(this);
}

void Silence::changeMinion() {
    this->minion->setMagic(
            -1 * this->minion->getMagic() - 1); //set the magic needed for ability to -1. when use ability check if
    // it is negative. Negative means silenced, cannot use ability.
}