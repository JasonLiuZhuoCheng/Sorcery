//
// Created by yawen on 2018-11-22.
//
#ifndef HEARTHSTONE_DISPLAY_H
#define HEARTHSTONE_DISPLAY_H

#include "Card/Minion.h"
#include "Card/Ritual.h"
#include "Card/Enchantment.h"
#include "Card/Spell.h"
#include "Board.h"
#include "Player.h"

class Display{
public:
    virtual void displayMinion(const Minion &minion) = 0;
    virtual void displayHand(const Player &player) = 0;
    virtual void displayBoard(const Board &board) = 0;
};


class Graphic : public Display{
public:
    void displayMinion(const Minion &minion) final;
    void displayHand(const Player &player) final;
    void displayBoard(const Board &board) final;
};

class Text: public Display{
public:
    void printMinion(const Minion &minion);
    void printEnchantment(const Enchantment &enchantment);
    void printSpell(const Spell &spell);
    void printRitual(const Ritual &ritual);
    void displayMinion(const Minion &minion) final;
    void displayHand(const Player &player) final;
    void displayBoard(const Board &board) final;
};
#endif //HEARTHSTONE_DISPLAY_H
