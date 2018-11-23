//
// Created by yawen on 2018-11-22.
//
#ifndef HEARTHSTONE_DISPLAY_H
#define HEARTHSTONE_DISPLAY_H

#include "Card/Minion.h"
#include "Card/Ritual.h"
#include "Board.h"
#include "Player.h"

class Display{
public:
    virtual void displayMinion(Minion * minion) = 0;
    virtual void displayHand(Player *player) = 0;
    virtual void displayBoard(Board *board) = 0;
};


class Graphic: public Display{
public:
    void displayMinion(Minion * minion) final;
    void displayHand(Player *player) final;
    void displayBoard(Board *board) final;
};

class Text: public Display{
public:
    void displayMinion(Minion * minion) final;
    void displayHand(Player *player) final;
    void displayBoard(Board *board) final;
};
#endif //HEARTHSTONE_DISPLAY_H
