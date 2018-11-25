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

void GiantStrength::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &targetCard) {
    auto &minion = dynamic_cast<Minion &>(targetCard);
    minion.mutateAtt(2);
    minion.mutateDef(2);
}

void GiantStrength::removeEnchantment(Minion &minion) {
    minion.mutateAtt(-2);
    if(minion.getDef() - 2 > 0){
        minion.mutateDef(-2);
    }else{
        minion.mutateDef(-minion.getDef() + 1);
    }
}
//------------------------------------Enlarge-----------------------------------------------------------------
Enrage::Enrage() : Enchantment{2, "*2", "*2", "Enrage", ""} {}

void Enrage::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &targetCard) {
    auto &minion = dynamic_cast<Minion &>(targetCard);
    minion.mutateAtt(minion.getAtt()); // doubles the attack
    minion.mutateDef(minion.getDef()); // doubles the defense
}

void Enrage::removeEnchantment(Minion &minion) {
    minion.mutateAtt(minion.getAtt() / 2);
    if(minion.getDef() / 2 > 0){
        minion.mutateDef(minion.getDef() / 2);
    }else{
        minion.mutateDef(-minion.getDef() + 1);
    }
}
//------------------------------------Haste-----------------------------------------------------------------
Haste::Haste() : Enchantment{1, "Haste", "", "", "Enchanted minion gains +1 action each turn"} {}

void Haste::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.setActionValue(m.getActionValue() + 1);
    m.setRecordActionValue(m.getActionValue() + 1);
}

void Haste::removeEnchantment(Minion &minion) {
    minion.setRecordActionValue(minion.getRecordActionValue() - 1);
    minion.setActionValue(minion.getActionValue() - 1);
}
//------------------------------------Magic Fatigue-----------------------------------------------------------------
MagicFatigue::MagicFatigue() : Enchantment{0, "", "", "Magic Fatigue", "Enchanted minion's activated ability costs 2 more"} {}

void MagicFatigue::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.setMagic(m.getMagic() + 2);
}

void MagicFatigue::removeEnchantment(Minion &minion) {
    minion.setMagic(minion.getMagic() - 2);
}
//------------------------------------Silence-----------------------------------------------------------------
Silence::Silence() : Enchantment{1, "", "", "Silence", "Enchanted minion cannot use abilities"} {}

void Silence::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    auto &m = dynamic_cast<Minion &>(card);
    m.setSilence(m.getSilence() + 1);
}

void Silence::removeEnchantment(Minion &minion) {
    minion.setSilence(minion.getSilence() - 1);
}
