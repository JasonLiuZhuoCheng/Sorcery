//
// Created by jason on 2018-11-20.
//

#include "Enchantment.h"
#include "Minion.h"

Enchantment::Enchantment(int cost, std::string att, std::string def, std::string name, std::string description)
        : Card{cost, name, description},hasAttDef{true} {
}

Enchantment::~Enchantment() {}

void Enchantment::effect(Player &player, Player &otherPlayer) {}

bool Enchantment::hasStats() { return  hasAttDef; }

bool Enchantment::canPlay() { return true; }

std::string Enchantment::getAtt() { return att; }

std::string Enchantment::getDef() { return def; }

//------------------------------------Giant Strength-----------------------------------------------------------------
GiantStrength::GiantStrength() : Enchantment{1, "+2" , "+2",  "Giant Strength", ""} {}

void GiantStrength::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.mutateAtt(2);
    m.mutateDef(2);
}
//------------------------------------Enlarge-----------------------------------------------------------------
Enrage::Enrage() : Enchantment{2, "*2", "*2", "Enrage", ""} {}

void Enrage::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.mutateAtt(m.getAtt()); // doubles the attack
    m.mutateDef(m.getDef()); // doubles the defense
}
//------------------------------------Haste-----------------------------------------------------------------
Haste::Haste() : Enchantment{1, "Haste", "", "", "Enchanted minion gains +1 action each turn"} {}

void Haste::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.setRecordActionValue(m.getActionValue() + 1);
}
//------------------------------------Magic Fatigue-----------------------------------------------------------------
MagicFatigue::MagicFatigue() : Enchantment{0, "", "", "Magic Fatigue", "Enchanted minion's activated ability costs 2 more"} {}

void MagicFatigue::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.setMagic(m.getMagic() + 2); //double the magic used for active ability
}
//------------------------------------Silence-----------------------------------------------------------------
Silence::Silence() : Enchantment{1, "", "", "Silence", "Enchanted minion cannot use abilities"} {}

//set the magic needed for ability to -1. when use ability check if it is negative. Negative means silenced, cannot use ability.
void Silence::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.setMagic(-1);
}
