//
// Created by jason on 2018-11-20.
//

#ifndef HEARTHSTONE_ENCHANTMENT_H
#define HEARTHSTONE_ENCHANTMENT_H

#include "Card.h"
class Minion;


class Enchantment : public Card {
protected:
    Minion* minion;
public:
    Enchantment(int cost, std::string name, std::string description, Minion *);
    virtual ~Enchantment();

    virtual void changeMinion();

};

class GiantStrength final : public Enchantment {
public:
    explicit GiantStrength(Minion *);

    void changeMinion() override;
};

class Enrage final : public Enchantment {
public:
    explicit Enrage(Minion *);

    void changeMinion() override;
};

class Haste final : public Enchantment {
public:
    explicit Haste(Minion *);

    void changeMinion() override;

    void triggerChange(Card::Trigger);
};

class MagicFatigue final : public Enchantment {
public:
    explicit MagicFatigue(Minion *);

    void changeMinion() override;
};

class Silence final : public Enchantment {
public:
    explicit Silence(Minion *);

    void changeMinion() override;
};

#endif //HEARTHSTONE_ENCHANTMENT_H
