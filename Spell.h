#ifndef HEARTHSTONE_SPELL_H
#define HEARTHSTONE_SPELL_H


#include "Card.h"
#include "Board.h"

// Spell is the abstract base class for all the possible kinds of spells occur in Sorcery

class Spell : public Card {
public:
    Spell(int cost, std::string name, std::string description);
    virtual ~Spell() = default;
};

class Banish final: public Spell {
public:
    Banish();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
};

class Unsummon final: public Spell {
public:
    Unsummon();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
};

class Recharge final: public Spell {
public:
    Recharge();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
};

class Disenchant final: public Spell {
public:
    Disenchant();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
};

class RaiseDead final: public Spell {
public:
    RaiseDead();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
};

class Blizzard final: public Spell{
public:
    Blizzard();

    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
};


class ArcaneIntellect final : public Spell{
public:
    ArcaneIntellect();
    bool canPlay(Player &player) override;
    void effect(Player &player, Player &otherPlayer) override;
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
};

#endif
