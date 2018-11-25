#ifndef HEARTHSTONE_MINION_H
#define HEARTHSTONE_MINION_H


#include "Card.h"
#include <vector>
#include <memory>
class Player;
class Enchantment;

class Minion : public Card {

private:
    int att, defense, actionValue, recordActionValue, magic, silence;   //magic is the cost of ability
    bool haveAbility, haveTrigger;
    std::vector<std::unique_ptr<Enchantment>> recordEnchantment;

public:
    Minion(int cost, std::string name, std::string description, int att, int def, int actionValue,
           int recordActionValue, int magic, int silence, bool haveAbility, bool haveTrigger);

    bool canAttack();
    bool isDead();
    int getActionValue();
    int getRecordActionValue();
    int getMagic();
    int getDef();
    int getAtt();
    int getSilence();

    bool hasEnchant();
    bool hasAbility();
    bool hasTrigger();
    bool isSilence();

    void resetActionValue();
    void setActionValue(int i);
    void setRecordActionValue(int);
    void setDef(int i);
    void setMagic(int);
    void setSilence(int i);

    Enchantment &getEnchant(int i);
    int numOfEnchant();
    void pushEnchantment(std::unique_ptr<Enchantment> e);
    void dischant(); // Dischant the top layer of enchantment

    void mutateDef(int);   // i is the damage source. When i is positive, it is receiving damage.
    void mutateAtt(int);   // i is the buff effect. When i is positive, it is buffing attack

    void attack(Player &); // attacks the opposing player
    void attack(Minion &otherMinion, Player &player, Player &otherPlayer); // attacks the ith minion of the opposing player

    bool canPlay(Player &) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;  //This will never be call

    virtual void trigger(Trigger t  , Player &) {};          // did not implement these two
    virtual void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {};

    virtual bool canUseAbility(Player &) = 0;
    virtual void ability(Player &) = 0;
    virtual void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) = 0;
};


class AirElemental final : public Minion {
public:
    AirElemental();
    void trigger(Trigger t,Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};


class EarthElemental final : public Minion {
public:
    EarthElemental();
    void trigger(Trigger t, Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};


class BoneGolem final : public Minion {
public:
    BoneGolem();
    void trigger(Trigger t, Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};

class FireElemental final : public Minion {
public:
    FireElemental();
    void trigger(Trigger t, Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};


class PotionSeller final: public Minion {
public:
    PotionSeller();
    void trigger(Trigger t,Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};


class NovicePyromancer : public Minion {
public:
    NovicePyromancer();
    void trigger(Trigger t,Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};


class ApprenticeSummoner : public Minion {
public:
    ApprenticeSummoner();
    void trigger(Trigger t,Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};


class MasterSummoner : public Minion {
public:
    MasterSummoner();
    void trigger(Trigger t,Player&) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;

    bool canUseAbility(Player &) override;
    void ability(Player &) override;
    void ability(Player &player, Player &other, Player &targetPlayer, Minion &targetminion) override;
};

#endif