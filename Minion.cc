#include <iostream>
#include "Card.h"
#include "Minion.h"
#include "Player.h"
#include "Enchantment.h"


using namespace std;

Minion::Minion(int cost, string name, string description, int attack, int defense, int actionValue,
               int recordActionValue, int magic, int silence, bool haveAbility, bool haveTrigger)
        : Card{cost, name, description}, att{attack}, defense{defense}, actionValue{actionValue},
          recordActionValue{recordActionValue}, magic{magic}, silence{silence}, haveAbility{haveAbility}, haveTrigger{haveTrigger}{}

void Minion::mutateDef(int i) { defense += i; }

int Minion::getDef() { return defense; }

bool Minion::isDead(){ return defense <= 0; }

void Minion::setDef(int i) { defense = i; } //only for Raised Dead

//when the turn ends, call this function and set every minions' action value = recordAction value;
void Minion::resetActionValue() { actionValue = recordActionValue; }

void Minion::setActionValue(int i) { actionValue = i; }

int Minion::getActionValue() { return actionValue; }

void Minion::setRecordActionValue(int i) { recordActionValue = i; }

int Minion::getRecordActionValue() { return recordActionValue; }

int Minion::getSilence() { return silence; }

void Minion::setSilence(int i) { silence = i; }

bool Minion::isSilence() { return silence > 0; }

int Minion::getMagic() { return magic; }

void Minion::setMagic(int i) { magic = i; }

int Minion::getAtt() { return att; }

bool Minion::hasAbility() { return haveAbility; }

bool Minion::hasTrigger() { return haveTrigger; }

bool Minion::hasEnchant() { return !recordEnchantment.empty(); }

Enchantment &Minion::getEnchant(int i) { return  *(recordEnchantment.at(i)); }

int Minion::numOfEnchant() { return recordEnchantment.size(); }

void Minion::dischant() {
    if(hasEnchant()){
        unique_ptr<Enchantment> e = std::move(recordEnchantment.back());
        recordEnchantment.erase(recordEnchantment.end());
        e->removeEnchantment(*this);
    }
}

void Minion::mutateAtt(int i) { att += i; }

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
            player.getMyBoard().addToGraveyard(*this);
            player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, *this, otherMinion, player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, otherMinion, *this, otherPlayer, player);
        }
        if(otherMinion.getDef() <=0){
            otherPlayer.getMyBoard().addToGraveyard(otherMinion);
            player.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, *this, otherMinion, player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, otherMinion, *this, player, otherPlayer);
        }
        actionValue --;
    }
    else {
        cout << name << " action value = 0." << endl;
    }
}

bool Minion::canPlay(Player &player){ return !player.getMyBoard().minionFull(); }

void Minion::effect(Player &player, Player &otherPlayer) {
    player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_ENTER, *this, *this, player, otherPlayer);
    otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_ENTER, *this, *this, otherPlayer, player);
}
void Minion::effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) {}

void Minion::pushEnchantment(std::unique_ptr<Enchantment> e) { recordEnchantment.emplace_back(std::move(e)); }

//----------------------------------------Air Elemental--------------------------------------------------------
bool Minion::canAttack() { return actionValue > 0; }

//cost, name, description, att, def, actionValue, recordActionValue, magic, silence, haveAbility, haveTrigger
AirElemental::AirElemental() :
        Minion{0, "Air Elemental", "", 1, 1, 0, 1, 0, 0, false, false} {}

void AirElemental::trigger(Card::Trigger t, Player &p) {}
void AirElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool AirElemental::canUseAbility(Player &) { return !this->isSilence(); }
void AirElemental::ability(Player &p, Player&) {}
void AirElemental::ability(Player &, Player &, Player &, Minion &) {}

//---------------------------------------Earth Elemental----------------------------------------------------------
//cost, name, description, att, def, actionValue, recordActionValue, magic, silence, haveAbility, haveTrigger
EarthElemental::EarthElemental() :
        Minion{3, "Earth Elemental", "", 4, 4, 0, 1, 0, 0, false, false} {}

void EarthElemental::trigger(Card::Trigger t, Player &p) {}
void EarthElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool EarthElemental::canUseAbility(Player &) { return !this->isSilence(); }
void EarthElemental::ability(Player &p, Player&) {}
void EarthElemental::ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) { }

//---------------------------------------------Bone Golem-----------------------------------------
//cost, name, description, att, def, actionValue, recordActionValue, magic, silence, haveAbility, haveTrigger
BoneGolem::BoneGolem() :
        Minion{2, "Bone Golem", "Gain +1/+1 whenever a minion leaves play.", 1, 3, 0, 1, 0, 0, false, true} {}

void BoneGolem::trigger(Card::Trigger t, Player &p) {}
void BoneGolem::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {
    if ((t == Card::Trigger::MY_MINION_LEAVE) || (t == Card::Trigger::OTHER_MINION_LEAVE)) {
        mutateDef(1);
        mutateAtt(1);
    }
}

bool BoneGolem::canUseAbility(Player &) { return !this->isSilence(); }
void BoneGolem::ability(Player &p, Player &) {}
void BoneGolem::ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) {}
//------------------------------------------Fire Elemental-----------------------------------------------
FireElemental::FireElemental() :
        Minion{2, "Fire Elemental", "Whenever an opponent's minion enters play, deal 1 damage to it.", 2, 2, 0, 1, 0, 0,
               false, true} {}

void FireElemental::trigger(Card::Trigger t, Player &p) {}

void FireElemental::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {
    if (t == Card::Trigger::OTHER_MINION_ENTER){
        otherMinion.mutateDef(-1);
        if (otherMinion.getDef() <= 0) {
            otherPlayer.getMyBoard().addToGraveyard(otherMinion);
            player.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, otherMinion, otherMinion, player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, otherMinion, otherMinion, otherPlayer, player);
        }
    }
}

bool FireElemental::canUseAbility(Player &) { return !this->isSilence(); }
void FireElemental::ability(Player &p, Player &) {}
void FireElemental::ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) {}
//---------------------------------------------Potion Seller---------------------------------------------------
PotionSeller::PotionSeller() :
        Minion{2, "Potion Seller", "At the end of your turn, all your minions gain +0/+1", 1, 3, 0, 1, 0, 0, false,
               true} {}

void PotionSeller::trigger(Card::Trigger t, Player &p) {
    if (t == Card::Trigger::END_OF_TURN){
        for (int i =0; i < p.getMyBoard().numberOfMinions();i++){
            p.getMyBoard().getMinion(i).mutateAtt(0);
            p.getMyBoard().getMinion(i).mutateDef(1);
        }
    }
}

void PotionSeller::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool PotionSeller::canUseAbility(Player &) { return !this->isSilence(); }
void PotionSeller::ability(Player &p, Player&) {}
void PotionSeller::ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) { }
//--------------------------------------------Novice Pyromancer------------------------------------------------
//cost, name, description, att, def, actionValue, recordActionValue, magic, silence, haveAbility, haveTrigger
NovicePyromancer::NovicePyromancer() :
        Minion{1, "Novice Pyromancer", "Deals 1 damage to target minion", 0, 1, 0, 1, 1, 0, true, false} {}

void NovicePyromancer::trigger(Card::Trigger t, Player &p) {}

void NovicePyromancer::trigger(Trigger t, Minion&, Minion&, Player&, Player&) {}

bool NovicePyromancer::canUseAbility(Player &player){ return !this->isSilence();  }

void NovicePyromancer::ability(Player &p, Player&) {}

void NovicePyromancer::ability(Player &player, Player &otherPlayer, Player &targetPlayer, Minion &targetMinion) {
        targetMinion.mutateDef(-1);
        if(targetMinion.isDead()) {
            if (&targetPlayer == &player) {
                // Triggers when my Minion is dead
                player.getMyBoard().addToGraveyard(targetMinion);
                player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, targetMinion, targetMinion, player, otherPlayer);
                otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, targetMinion, targetMinion, otherPlayer, player);
            }else{
                // Triggers when oppoenent's Minion is dead
                otherPlayer.getMyBoard().addToGraveyard(targetMinion);
                player.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_LEAVE, targetMinion, targetMinion, player, otherPlayer);
                otherPlayer.getMyBoard().notifyAll(Card::Trigger::MY_MINION_LEAVE, targetMinion, targetMinion, otherPlayer, player);
            }
        }
}
//---------------------------------------------Apprentice Summoner-----------------------------------------------
ApprenticeSummoner::ApprenticeSummoner() :
        Minion{1, "Apprentice Summoner", "Summon a 1/1 air elemental", 1, 1, 0, 1, 1, 0, true, false} {}

void ApprenticeSummoner::trigger(Card::Trigger t, Player &p) {}

void ApprenticeSummoner::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool ApprenticeSummoner::canUseAbility(Player &player) { return !player.getMyBoard().minionFull() && !this->isSilence(); }

void ApprenticeSummoner::ability(Player &player, Player &otherPlayer) {
        //unique_ptr<Minion> m{new AirElemental};
        //player.getMyBoard().addMinion(std::move(m));
        player.getMyBoard().addMinion(make_unique<AirElemental>());
        int lastMinionIndex = player.getMyBoard().numberOfMinions() - 1;
        player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_ENTER, player.getMyBoard().getMinion(lastMinionIndex),
                                      player.getMyBoard().getMinion(lastMinionIndex), player, otherPlayer);
        otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_ENTER, player.getMyBoard().getMinion(lastMinionIndex),
                                           player.getMyBoard().getMinion(lastMinionIndex), otherPlayer, player);
}

void ApprenticeSummoner::ability(Player &, Player &, Player &, Minion &) {}
//--------------------------------------------------Master Summoner--------------------------------------
MasterSummoner::MasterSummoner() :
        Minion{3, "Master Summoner", "Summon up to three 1/1 air elementals", 2, 3, 0, 1, 2, 0, true, false} {}

void MasterSummoner::trigger(Card::Trigger t, Player &p) {}

void MasterSummoner::trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool MasterSummoner::canUseAbility(Player &player) { return !player.getMyBoard().minionFull() && !this->isSilence(); }

void MasterSummoner::ability(Player &player, Player &otherPlayer) {
        for (int i = 0; i < 3; i++) {
            if (player.getMyBoard().minionFull()) break;
            //unique_ptr<Minion> m{new AirElemental};
            //player.getMyBoard().addMinion(std::move(m));
            player.getMyBoard().addMinion(make_unique<AirElemental>());

            int lastMinionIndex = player.getMyBoard().numberOfMinions() - 1;
            player.getMyBoard().notifyAll(Card::Trigger::MY_MINION_ENTER, player.getMyBoard().getMinion(lastMinionIndex),
                                          player.getMyBoard().getMinion(lastMinionIndex), player, otherPlayer);
            otherPlayer.getMyBoard().notifyAll(Card::Trigger::OTHER_MINION_ENTER, player.getMyBoard().getMinion(lastMinionIndex),
                                               player.getMyBoard().getMinion(lastMinionIndex), otherPlayer, player);
        }
}

void MasterSummoner::ability(Player &, Player &, Player &, Minion &) {}


//--------------------------------------------------Acidic Swamp--------------------------------------
AcidicSwamp::AcidicSwamp() : Minion(2,"Acidic Swamp","Destroy opponent's Ritual",3,2,0,1,0,0,false,true){}

void AcidicSwamp::trigger(Card::Trigger t, Player &p) {}

void AcidicSwamp::trigger(Card::Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {
    if (t == Card::Trigger::MY_MINION_ENTER){
        if (otherPlayer.getMyBoard().hasRitual()){
            otherPlayer.getMyBoard().setRitual(nullptr);
        }
    }
}

bool AcidicSwamp::canUseAbility(Player &player) { return !this->isSilence();}

void AcidicSwamp::ability(Player &, Player &) {}

void AcidicSwamp::ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) {}



//--------------------------------------------------Wolf Rider--------------------------------------
Wolfrider::Wolfrider() : Minion(3,"Wolf Rider","Charge",3,1,1,1,0,0,true,false){}

void Wolfrider::trigger(Card::Trigger t, Player &) {}

void Wolfrider::trigger(Card::Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {}

bool Wolfrider::canUseAbility(Player &player) { return !this->isSilence();}

void Wolfrider::ability(Player &, Player &) {}

void Wolfrider::ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) {}


//--------------------------------------------------Gnomish Inventor--------------------------------------
GnomishInventor::GnomishInventor(): Minion{4,"Gnomish Inventor","Draw a Card",2,4,0,1,0,0,false,true} {}

void GnomishInventor::trigger(Card::Trigger t, Player &player) {}

void GnomishInventor::trigger(Card::Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {
    if (t == Card::Trigger::MY_MINION_ENTER){
        player.drawCard();
    }
}

bool GnomishInventor::canUseAbility(Player &player) {return !this->isSilence();}

void GnomishInventor::ability(Player &, Player &player) {}

void GnomishInventor::ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) {}

