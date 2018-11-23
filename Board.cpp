//
// Created by Matthew on 2018-11-14.
//
#include "Board.h"

Minion *Board::getMinion(int i) { return minions.at(i); }

int Board::getMinion(Minion &minion) {
    for (int i = 0; i < minions.size(); i++) {
        if (getMinion(i) == &minion) {
            return i;
        }
    }
    return -1;
}

Ritual *Board::getRitual() { return ritual; };

void Board::addMinion(Minion *minion) { minions.emplace_back(minion); }

Minion *Board::removeMinion(int i) {
    Minion *temp = getMinion(i);
    minions.erase(minions.begin() + (i - 1));
    return temp;
}

Minion *Board::removeFromGraveyard() {
    if(!graveyard.empty()) {
        Minion *temp = graveyard.back();
        graveyard.pop_back();
        return temp;
    }
    return nullptr;
}

void Board::addToGraveyard(Minion *minion) { graveyard.emplace_back(minion); }

void Board::setRitual(Ritual *ritual) {
    delete this->ritual;
    this->ritual = ritual;
}

int Board::numberOfMinions() { return minions.size(); }

void Board::notifyAll(Card::Trigger t, Player &player) {
    for (Minion *m : minions) {
        m->trigger(t, player);
    }
    ritual->trigger(t, player);
}

void Board::notifyAll(Card::Trigger t, Player &player, Card &card) {
    for(Minion *m : minions){
        m->trigger(t, player, card);
    }
    ritual->trigger(t, player, card);
}


