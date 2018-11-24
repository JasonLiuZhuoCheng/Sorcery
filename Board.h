#ifndef HEARTHSTONE_BOARD_H
#define HEARTHSTONE_BOARD_H

#include "Card/Minion.h"
#include "Card/Ritual.h"
#include <vector>
#include <memory>


class Board final{
    std::vector<std::unique_ptr<Minion>> minions;
    std::vector<std::unique_ptr<Minion>> graveyard;
    std::unique_ptr<Ritual> ritual;

public:
    bool removeFromGraveyard(); // removes the last dead minion from "graveyard", and return its pointer

    void addToGraveyard(Minion &minion); // adds the minion to the top of "graveyard"

    std::unique_ptr<Minion> removeMinion(int i); // removes the ith minion from "minions"

    void addMinion(std::unique_ptr<Minion> minion); // adds the minion to the back of "minions"

    Minion &getMinion(int i); // gets the ith minion from "minions"

    int getMinion(Minion &); // gets the index of a minion from "minions"

    Ritual &getRitual();

    void setRitual(std::unique_ptr<Ritual> ritual);

    bool hasRitual();

    bool isGraveyardEmpty();

    int numberOfMinions();
    bool minionFull();

    void notifyAll(Card::Trigger t, Player &); // Using the Observer Pattern to notify all Minions and Ritual that Trigger "t" has happened
    //void notifyAll(Card::Trigger t, Player &, Card &);
    void notifyAll(Card::Trigger t, Minion  &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer);
};


#endif
