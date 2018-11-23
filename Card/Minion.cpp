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
    this->defense = this->defense - i;    //mutate defense. i is the damage
}

int Minion::getDef() {
    return this->defense;
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
    return -1 * this->att;
}

void Minion::mutateAtt(int i) {
    this->att = this->att + i;
}

void Minion::attack(Player &p) {
    if (this->actionValue > 0){
        p.mutateLife(this->getAtt());
        if (p.isDead()) {
            cout << "One player is dead." << endl;
        }
    } else {
        cout << this->name << "has no action value." << endl;
    }
    this->actionValue--;
}

void Minion::attack(Player &p, int i) {
    if (this->actionValue > 0){
        p.getMyBoard()->getMinion(i)->mutateDef(this->att);
        if (p.getMyBoard()->getMinion(i)->getDef() <= 0) {
            p.getMyBoard()->addToGraveyard(p.getMyBoard()->getMinion(i));
        }
        this->mutateDef(p.getMyBoard()->getMinion(i)->att);
        if (this->getDef() <= 0) {
            p.getOtherBoard()->addToGraveyard(this);
        }
    } else {
        cout << this->name <<"has no action value." << endl;
    }
    this->actionValue--;
}

bool Minion::play(Player &p) {
    if (p.getMyBoard()->numberOfMinions() == 5) {
        cout << "Minion slot is full" << endl;
        return false;
    }
    p.getMyBoard()->addMinion(this);
    return true;
}

bool Minion::play(Player &p, Card &c) {}

std::vector<Enchantment*> Minion::getEnchantment() {
    return this->recordEnchantment;
}

void Minion::pushEnchantment(Enchantment *e) {
    this->recordEnchantment.emplace_back(e);
}



AirElemental::AirElemental() :
        Minion{1, "Air Elemental", "", 1, 1, 0, 1, 0, false, false} {}

void AirElemental::trigger(Card::Trigger t, Player &p) {}
void AirElemental::trigger(Card::Trigger t, Player &p, Card &c) {}

bool AirElemental::ability(Player &p) { return false; }

bool AirElemental::ability(Player &p, Card &c) { return false; }


EarthElemental::EarthElemental() :
        Minion{3, "Earth Elemental", "", 4, 4, 0, 1, 0, false, false} {}

void EarthElemental::trigger(Card::Trigger t, Player &p) {}
void EarthElemental::trigger(Card::Trigger t, Player &p, Card &c) {}

bool EarthElemental::ability(Player &p) { return false; }

bool EarthElemental::ability(Player &p, Card &c) { return false; }

BoneGolem::BoneGolem() :
        Minion{2, "Bone Golem", "Gain +1/+1 whenever a minion leaves play.", 1, 3, 0, 1, 0, false, true} {}
void BoneGolem::trigger(Card::Trigger t, Player &p) {
    if (t == Card::Trigger::MINION_ENTER){
        this->mutateDef(-1);
        this->mutateAtt(1);
    }else return;
}
void BoneGolem::trigger(Card::Trigger t, Player &p, Card &c) {}

bool BoneGolem::ability(Player &p) { return false; }

bool BoneGolem::ability(Player &p, Card &c) { return false; }



FireElemental::FireElemental() :
        Minion{2, "Fire Elemental", "Whenever an opponent's minion enters play, deal 1 damage to it.", 2, 2, 0, 1, 0,
               false, true} {}

void FireElemental::trigger(Card::Trigger t, Player &p) {}

void FireElemental::trigger(Card::Trigger t, Player &p, Card &c) {
    if (t == Card::Trigger::MINION_ENTER){
        dynamic_cast<Minion&>(c).mutateDef(1);
        if (dynamic_cast<Minion &>(c).getDef() <= 0) {
            p.getMyBoard()->addToGraveyard(dynamic_cast<Minion *>(&c));
        }
    }
    else return;
}

bool FireElemental::ability(Player &p) { return false; }

bool FireElemental::ability(Player &p, Card &c) { return false; }


PotionSeller::PotionSeller() :
        Minion{2, "Potion Seller", "At the end of your turn, all your minions gain +0/+1", 1, 3, 0, 1, 0, false,
               true} {}

void PotionSeller::trigger(Card::Trigger t, Player &p) {
    if (t == Card::Trigger::END_OF_TURN){
        for (int i =0; i < p.getMyBoard()->numberOfMinions();i++){
            p.getMyBoard()->getMinion(i)->mutateAtt(0);
            p.getMyBoard()->getMinion(i)->mutateDef(-1);
        }
    }
}

void PotionSeller::trigger(Card::Trigger t, Player &p, Card &c) {}

NovicePyromancer::NovicePyromancer() :
        Minion{1, "Novice Pyromancer", "Deals 1 damage to target minion", 1, 1, 0, 1, 1, true, false} {}

void NovicePyromancer::trigger(Card::Trigger t, Player &p) {}

void NovicePyromancer::trigger(Card::Trigger t, Player &p, Card &c) {}

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

void ApprenticeSummoner::trigger(Card::Trigger t, Player &p, Card &c) {}

bool ApprenticeSummoner::ability(Player &p) {
    if (p.getMagic() == 0) return false;
    if (p.getMyBoard()->numberOfMinions() == 5) return false;
    else if (p.getMyBoard()->numberOfMinions() < 5) {
        Minion *m = new AirElemental;
        m->play(p);
        p.mutateMagic(-1);
        return true;
    }
}

bool ApprenticeSummoner::ability(Player &p, Card &c) {}

MasterSummoner::MasterSummoner() :
        Minion{3, "Master Summoner", "Summon up to three 1/1 air elementals", 2, 3, 0, 1, 2, true, false} {}

void MasterSummoner::trigger(Card::Trigger t, Player &p) {}

void MasterSummoner::trigger(Card::Trigger t, Player &p, Card &c) {}

bool MasterSummoner::ability(Player &p) {
    if (p.getMagic() < 2) return false;
    if (p.getMyBoard()->numberOfMinions() == 5) return false;
    else if (p.getMyBoard()->numberOfMinions() < 5) {
        Minion *m = new AirElemental;
        m->play(p);
        if (p.getMyBoard()->numberOfMinions() < 5) {
            Minion *n = new AirElemental;
            n->play(p);
        }
        if (p.getMyBoard()->numberOfMinions() < 5) {
            Minion *q = new AirElemental;
            q->play(p);
        }
        return true;
    }
}

bool MasterSummoner::ability(Player &p, Card &c) {}


