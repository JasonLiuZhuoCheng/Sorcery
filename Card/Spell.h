#ifndef HEARTHSTONE_SPELL_H
#define HEARTHSTONE_SPELL_H


#include "Card.h"
#include "../Board.h"

// Spell is the abstract base class for all the possible kinds of spells occur in Sorcery

class Spell : public Card {
public:
    Spell(int cost, std::string name, std::string description);
};

class Banish final: public Spell {
public:
    Banish();

    bool canPlay(Player &player);
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &, Card &) override;
};

class Unsummon final: public Spell {
public:
    Unsummon();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &, Card &) override;
};

class Recharge final: public Spell {
public:
    Recharge();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &, Card &) override;
};

class Disenchant final: public Spell {
public:
    Disenchant();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &, Card &) override;
};

class RaiseDead final: public Spell {
public:
    RaiseDead();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &, Card &) override;
};

class Blizzard final: public Spell{
public:
    Blizzard();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &, Card&) override;
};

#endif
