//
// Created by jason on 2018-11-20.
//

#ifndef HEARTHSTONE_ENCHANTMENT_H
#define HEARTHSTONE_ENCHANTMENT_H

#include "Card.h"

class Minion;


class Enchantment : public Card {
protected:
    std::string att, def;
    bool hasAttDef;
public:
    Enchantment(int cost, std::string att, std::string def, std::string name, std::string description, bool hasAttDef);
    void effect(Player &, Player&) override;
    ~Enchantment() override = default;

    virtual void removeEnchantment(Minion &minion) = 0;
    bool canPlay(Player &) override;
    bool hasStats();
    std::string getAtt();
    std::string getDef();
};

class GiantStrength final : public Enchantment {
public:
    GiantStrength();
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
    void removeEnchantment(Minion &minion) override;
    ~GiantStrength() override = default;
};

class Enrage final : public Enchantment {
public:
    Enrage();
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
    void removeEnchantment(Minion &minion) override;
    ~Enrage() override = default;
};

class Haste final : public Enchantment {
public:
    Haste();
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
    void removeEnchantment(Minion &minion) override;
    ~Haste() override = default;
};

class MagicFatigue final : public Enchantment {
public:
    MagicFatigue();
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
    void removeEnchantment(Minion &minion) override;
    ~MagicFatigue() override = default;
};

class Silence final : public Enchantment {
public:
    Silence();
    void effect(Player &player, Player &targetPlayer, Player &otherPlayer, Card &card) override;
    void removeEnchantment(Minion &minion) override;
    ~Silence() override = default;
};

#endif //HEARTHSTONE_ENCHANTMENT_H
