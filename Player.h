#ifndef  HEARTHSTONE_PLAYER_H
#define HEARTHSTONE_PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Card/Card.h"
#include "Board.h"

using namespace std;

const int maxHand = 5;

class Player final {
    int life, magic;
    string name;
    Board *myBoard;
    Board *otherBoard;
    vector<unique_ptr<Card>> hand;
    vector<unique_ptr<Card>> deck;
    bool activeStatus;
    bool isHandfull();

    int maxMgaic;

public:
    Player();

    Board *getMyBoard(); // returns the pointer to "myBoard", allowing operations on "myBoard"
    Board *getOtherBoard(); // returns the pointer to "otherBoard", allowing operations on "otherBoard"
    unique_ptr<Card> getCard(int i); // gets the ith Card from "hand"
    int getMagic();
    bool isActive();

    void setDeck(vector<unique_ptr<Card>> &);
    void setName(std::string &);

    void setOtherBoard(Board *); // sets the "board" of the opposing player, use for Observer Pattern
    void mutateLife(int);

    void mutateMagic(int);
    void setMagic(int);

    void shuffle();

    bool isDead();

    void drawCard(); // player draws a card from "deck", given "hand" is not full and "deck" is not empty
    void addMinionToHand(unique_ptr<Minion> minion); // Adds a minion to the player's "hand"
    void discardCard(int); // discards ith card in a player's "hand"

    void notifyAll(Card::Trigger t, Player &); // using the Observer Pattern to notify "board" that Trigger "t" has happened
    void notifyAll(Card::Trigger t, Player &, Card &);

    void setMagic();

    void setMaxMagic();
};

#endif

