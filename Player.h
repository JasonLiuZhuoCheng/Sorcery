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
public:
    Player(int id);
    ~Player();

    int getID();
    Board *getMyBoard(); // returns the pointer to "myBoard", allowing operations on "myBoard"
    Card &getCard(int i); // gets the ith Card from "hand"
    std::string getName();
    int getLife();
    int getMagic();

    void setName(std::string &);
    void mutateLife(int);
    void mutateMagic(int);
    void setMagic(int);

    bool isDead();
    bool isActive();
    int handSize();

    void addToDeck(std::unique_ptr<Card> card); // Adds a "card" to "deck"
    void moveCardToBoard(int i);
    void shuffle();
    void drawCard(); // player draws a card from "deck", given "hand" is not full and "deck" is not empty
    void addMinionToHand(unique_ptr<Minion> minion); // Adds a minion to the player's "hand"
    void discardCard(int); // discards ith card in a player's "hand"
};

#endif

