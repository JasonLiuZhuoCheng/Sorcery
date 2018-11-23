#include "Spell.h"
#include "../Player.h"
#include <typeindex>

Spell::Spell(int cost, std::string name, std::string description) : Card(cost, name, description) {}

Banish::Banish() : Spell(2, "Banish", "Destroy target minion or ritual") {}

bool Banish::play(Player &) { return false; }

bool Banish::play(Player &player, Card &card) {
    cout << "This might not work" << endl;
    Board *temp = player.getMyBoard();
    if(std::type_index(typeid(card)) == std::type_index(typeid(Minion))){
        temp->addToGraveyard(temp->removeMinion(temp->getMinion(dynamic_cast<Minion &>(card))));
    }else{ // card must be a Ritual type

    }
    return true;
}

Unsummon::Unsummon() : Spell(1, "Unsummon", "Return target minion to its owner's hand") {}

bool Unsummon::play(Player &) { return false; }

bool Unsummon::play(Player &player, Card &card) {
    int index = player.getMyBoard()->getMinion(dynamic_cast<Minion &>(card));
    player.addMinionToHand(player.getMyBoard()->removeMinion(index));
    return true;
}

Recharge::Recharge() : Spell(1, "Recharge", "Your ritual gains 3 charges") {}

bool Recharge::play(Player &player) {
    if(player.getMyBoard()->hasRitual()){ // Ritual slot is not empty
        player.getMyBoard()->getRitual().mutateCharges(3);
        return true;
    }
    cout << "Ritual slot is empty" << endl;
    return false;
}

bool Recharge::play(Player &, Card &) { return false; }

Disenchant::Disenchant() : Spell(1, "Disenchant", "Destroy the top enchantment on target minion") {}

bool Disenchant::play(Player &) { return  false; }

bool Disenchant::play(Player &, Card &) {
    //TODO will be implement after Enchantment
}

RaiseDead::RaiseDead(): Spell(1, "Raise Dead", "Resurrect the top minion in your graveyard and set its defense to 1") {}

bool RaiseDead::play(Player &player) {
    Board *board = player.getMyBoard();
    if(!board->isGraveyardEmpty()) { // Graveyard is not empty
        board->addMinion(board->removeFromGraveyard());
        board->getMinion(board->numberOfMinions() - 1).setDef();
        return true;
    }
    cout << "Graveyard is empty" << endl;
    return false;
}

bool RaiseDead::play(Player &, Card &) { return false; }

Blizzard::Blizzard(): Spell(3, "Blizzard", "Deal 2 damage to all minions") {}

bool Blizzard::play(Player &player) {
    for(int i = 0; i < player.getMyBoard()->numberOfMinions(); i++){
        player.getMyBoard()->getMinion(i).mutateDef(2);
    }

    for(int i = 0; i < player.getOtherBoard()->numberOfMinions(); i++){
        player.getOtherBoard()->getMinion(i).mutateDef(2);
    }
    return true;
}

bool Blizzard::play(Player &, Card &) { return  false; }

