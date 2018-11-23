#ifndef HEARTHSTONE_RITUAL_H
#define HEARTHSTONE_RITUAL_H

#include "Card.h"

class Ritual : public Card {
protected:
    int charges;//how many times can you still use
    int activeCost;//magic you need

public:
    Ritual(int cost, std::string name, std::string description, int charges, int activeCost);

    void mutateCharges(int);
    bool play(Player&);
    bool canPlay();
    bool play(Player&, Card &);
    virtual void trigger(Trigger t, Player &) = 0;
    virtual void trigger(Trigger t, Player &, Card &) = 0;
};


class DarkRitual: public Ritual{
public:
    DarkRitual();
    void trigger(Trigger t, Player &) override;
    void trigger(Trigger t, Player &, Card &) override;
};

class AuraOfPower: public Ritual{
public:
    AuraOfPower();
    void trigger(Trigger t, Player &) override;
    void trigger(Trigger t, Player &, Card &) override;
};

class Standstill: public Ritual{
public:
    Standstill();
    void trigger(Trigger t, Player &) override;
    void trigger(Trigger t, Player &, Card &) override;
};

#endif