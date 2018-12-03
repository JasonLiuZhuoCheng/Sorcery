#ifndef  HEARTHSTONE_PLAYER_H
#define HEARTHSTONE_PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Card.h"
#include "Board.h"

using namespace std;

const int maxHand = 5;

class Player{
    int id,life, magic;
    string name;
    unique_ptr<Board> myBoard;
    vector<unique_ptr<Card>> deck;

public:
    Player(int id);
    int getID();
    Board &getMyBoard();
    Card &getCard(int i); // gets the ith Card from "hand"
    std::string getName();
    int getLife();
    int getMagic();

    void setName(std::string &);
    void mutateLife(int);
    void mutateMagic(int);
    void setMagic(int);

    bool isHandfull();
    bool isDead();
    int handSize();

    void addToDeck(std::unique_ptr<Card> card); // Adds a "Card" to "deck"
    void moveCardToBoard(int i);
    void moveEnchantmentToMinion(int i, Card &ifMinion);
    void shuffle();
    void drawCard(); // player draws a card from "deck", given "hand" is not full and "deck" is not empty
    void addMinionToHand(unique_ptr<Minion> minion); //Adds a minion to the player's "hand"
    void discardCard(int); // discards ith card in a player's "hand"
    vector<unique_ptr<Card>> hand;

};

#endif


