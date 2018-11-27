#ifndef HEARTHSTONE_DISPLAY_H
#define HEARTHSTONE_DISPLAY_H


#include "Board.h"
#include "ascii_graphics.h"
#include "Card.h"

class Player;
class Minion;
class Enchantment;
class Spell;
class Ritual;

class Display{
public:
    virtual void displayMinion(Minion &minion) = 0;
    virtual void displayHand(Player &player) = 0;
    virtual void display(Player &p1, Player &p2) = 0;
};


class Graphic final: public Display{
public:
    void displayMinion(Minion &minion) override;
    void displayHand(Player &player) override;
    void display(Player &p1, Player &p2);
};

class Text final: public Display{
    card_template_t makePlayer(Player &player);
    card_template_t makeMinion(Minion &minion);
    card_template_t makeEnchantment(Enchantment &enchantment);
    card_template_t makeSpell(Spell &spell);
    card_template_t makeRitual(Ritual &ritual);
public:
    void displayMinion(Minion &minion) override;
    void displayHand(Player &player) override;
    void displayPlayer(Player &player, int num);
    void display(Player &p1, Player &p2) override;
    void print(card_template_t);
    void print(std::vector<card_template_t> &, bool);
};
#endif //HEARTHSTONE_DISPLAY_H