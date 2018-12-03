#ifndef HEARTHSTONE_RITUAL_H
#define HEARTHSTONE_RITUAL_H

#include "Card.h"
#include "Minion.h"

class Ritual : public Card {
protected:
    int charges;//how many times can you still use
    int activeCost;//magic you need

public:
    Ritual(int cost, std::string name, std::string description, int charges, int activeCost);
    virtual ~Ritual()= default;

    void mutateCharges(int);
    bool canPlay(Player &) override;
    bool canUse();
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
    int getActiveCost();
    int getCharges();
    virtual void trigger(Trigger t, Player &) = 0;
    virtual void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) = 0;
};


class DarkRitual final: public Ritual{
public:
    DarkRitual();
    void trigger(Trigger t, Player &) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;
};

class AuraOfPower final: public Ritual{
public:
    AuraOfPower();
    void trigger(Trigger t, Player &) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;
};

class Standstill final: public Ritual{
public:
    Standstill();
    void trigger(Trigger t, Player &) override;
    void trigger(Trigger t, Minion &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) override;
};

#endif
