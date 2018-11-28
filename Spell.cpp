#include "Spell.h"
#include "Player.h"
#include "Enchantment.h"
#include <iostream>
#include <typeindex>

using namespace std;

Spell::Spell(int cost, std::string name, std::string description) : Card(cost, name, description) {}

//---------------------------------------------Banish Class----------------------------------------
Banish::Banish() : Spell(2, "Banish", "Destroy target minion or ritual") {}

bool Banish::canPlay(Player &player) { return true; }
void Banish::effect(Player &player, Player &otherPlayer) {}
void Banish::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &targetCard) {
    auto minion = dynamic_cast<Minion*>(&targetCard);
    if(minion){
        targetPlayer.getMyBoard().addToGraveyard(*minion);
        if(&targetPlayer == &player){
            player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, *minion, *minion, player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, *minion, *minion, otherPlayer, player);
        }else{
            player.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, *minion, *minion, player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, *minion, *minion, otherPlayer, player);
        }
    }else{ // card must be a Ritual type
        targetPlayer.getMyBoard().setRitual(nullptr);
    }
}

//--------------------------------------------Unsommon Class----------------------------------------------
Unsummon::Unsummon() : Spell(1, "Unsummon", "Return target minion to its owner's hand") {}

bool Unsummon::canPlay(Player &player) { return !player.isHandfull(); }

void Unsummon::effect(Player &player, Player &otherPlayer) { }

void Unsummon::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &targetCard) {
    auto minion = dynamic_cast<Minion*>(&targetCard);
    while(minion->hasEnchant()){
        minion->dischant();
    }
    int index = targetPlayer.getMyBoard().getMinion(*minion);//get the index of targetCard
    targetPlayer.addMinionToHand(std::move(targetPlayer.getMyBoard().removeMinion(index)));//added the minion to the player's hand
    if(&targetPlayer == &player){
        player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, *minion, *minion, player, otherPlayer);
        otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, *minion, *minion, otherPlayer, player);
    }else{
        player.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, *minion, *minion, player, otherPlayer);
        otherPlayer.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, *minion, *minion, otherPlayer, player);
    }
}

//-------------------------------------------Recharge Class------------------------------------------------
Recharge::Recharge() : Spell(1, "Recharge", "Your ritual gains 3 charges") {}

// Ritual slot is not empty
bool Recharge::canPlay(Player &player) { return player.getMyBoard().hasRitual(); }

void Recharge::effect(Player &player, Player &otherPlayer) { player.getMyBoard().getRitual().mutateCharges(3); }

void Recharge::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {}

//-------------------------------------------Disenchant Class----------------------------------------------
Disenchant::Disenchant() : Spell(1, "Disenchant", "Destroy the top enchantment on target minion") {}

bool Disenchant::canPlay(Player &player) { return true; }

void Disenchant::effect(Player &player, Player &otherPlayer) {}

void Disenchant::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {
    int index = targetPlayer.getMyBoard().getMinion(dynamic_cast<Minion &>(card));
    targetPlayer.getMyBoard().getMinion(index).dischant();
}

//--------------------------------------------Raise Dead---------------------------------------------
RaiseDead::RaiseDead(): Spell(1, "Raise Dead", "Resurrect the top minion in your graveyard and set its defense to 1") {}

// Graveyard is not empty and minion slot is not full(if not, then do the remove and add its defence to 1)
bool RaiseDead::canPlay(Player &player) { return (!(player.getMyBoard().isGraveyardEmpty()) && !(player.getMyBoard().minionFull())); }

void RaiseDead::effect(Player &player, Player &otherPlayer) {
    Minion &minionRemoved = player.getMyBoard().graveyardTop();
    player.getMyBoard().removeFromGraveyard();
    player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_ENTER, minionRemoved, minionRemoved, player, otherPlayer);
    player.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_ENTER, minionRemoved, minionRemoved, otherPlayer, player);
}

void RaiseDead::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) { }


//------------------------------------------------Blizzard Class--------------------------------------------------
Blizzard::Blizzard(): Spell(3, "Blizzard", "Deal 2 damage to all minions") {}

bool Blizzard::canPlay(Player &player) { return true; }

void Blizzard::effect(Player &player, Player &otherPlayer) {
    for(int i = 0; i < player.getMyBoard().numberOfMinions(); ++i){
        Minion &effectedMinion = player.getMyBoard().getMinion(i);
        effectedMinion.mutateDef(-2);
        if(effectedMinion.isDead()){
            --i;
            player.getMyBoard().addToGraveyard(effectedMinion);
            player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_ENTER, effectedMinion, effectedMinion, player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_ENTER, effectedMinion, effectedMinion, otherPlayer, player);
        }
    }

    for(int i = 0; i < otherPlayer.getMyBoard().numberOfMinions(); ++i){
        Minion &effectedMinion = player.getMyBoard().getMinion(i);
        effectedMinion.mutateDef(-2);
        if(effectedMinion.isDead()){
            --i;
            otherPlayer.getMyBoard().addToGraveyard(effectedMinion);
            player.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, effectedMinion, effectedMinion, player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::MY_MINION_ENTER, effectedMinion, effectedMinion, otherPlayer, player);
        }
    }
}

void Blizzard::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {}

