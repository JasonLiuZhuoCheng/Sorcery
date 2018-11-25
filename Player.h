#ifndef  HEARTHSTONE_PLAYER_H
#define HEARTHSTONE_PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Card/Card.h"
#include "Board.h"

using namespace std;

const int maxHand = 5;

class Player final {
    int id,life, magic;
    string name;
    Board *myBoard;
    vector<unique_ptr<Card>> hand;
    vector<unique_ptr<Card>> deck;
    bool activeStatus;
    bool isHandfull();

    int maxMgaic;
public:
    Player(int id);
    ~Player();
    int getID();
    Board *getMyBoard(); // returns the pointer to "myBoard", allowing operations on "myBoard"
    Card &getCard(int i); // gets the ith Card from "hand"
    std::string getName();
    int getLife();
    void moveCardToBoard(int i);
    int getMagic();
    bool isActive();
    int handSize();
    void addToDeck(std::unique_ptr<Card> card); // Adds a "card" to "deck"
    void setName(std::string &);
    void mutateLife(int);
    void mutateMagic(int);
    void setMagic(int);
    void shuffle();
    bool isDead();
    void drawCard(); // player draws a card from "deck", given "hand" is not full and "deck" is not empty
    void addMinionToHand(unique_ptr<Minion> minion); // Adds a minion to the player's "hand"
    void discardCard(int); // discards ith card in a player's "hand"

    void setMagic();

    void setMaxMagic();
};

#endif

