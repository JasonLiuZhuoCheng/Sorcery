#ifndef HEARTHSTONE_BOARD_H
#define HEARTHSTONE_BOARD_H

#include "Minion.h"
#include "Ritual.h"
#include <vector>
#include <memory>

class Board final{
    std::vector<std::unique_ptr<Minion>> graveyard;
    std::unique_ptr<Ritual> ritual;
    std::vector<std::unique_ptr<Minion>> minions;

public:
    // "Graveyard" Functions
    void removeFromGraveyard(); // removes the last dead minion from "graveyard", and put it on board
    void addToGraveyard(Minion &minion); // adds the minion to the top of "graveyard"
    Minion &graveyardTop(); // Peak at the top of the graveyard
    bool isGraveyardEmpty();
    // "Minions" Functions
    std::unique_ptr<Minion> removeMinion(int i); // removes the ith minion from "minions"
    void addMinion(std::unique_ptr<Minion> minion); // adds the minion to the back of "minions"
    Minion &getMinion(int i); // gets the ith minion from "minions"
    int getMinion(Minion &); // gets the index of a minion from "minions"
    int numberOfMinions();
    bool minionFull();
    // "Ritual" Functions
    Ritual &getRitual();
    void setRitual(std::unique_ptr<Ritual> ritual);
    bool hasRitual();
    // Board Trigger Functions
    void notifyAll(Card::Trigger t, Player &); // Trigger for "Start of turn" and "End of turn"
    void notifyAll(Card::Trigger t, Minion  &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer); // Trigger for Minions
};
#endif
