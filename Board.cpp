//
// Created by Matthew on 2018-11-14.
//
#include "Board.h"

Minion &Board::getMinion(int i) { return *(minions.at(i)); }

int Board::getMinion(Minion &minion) {
    for (int i = 0; i < minions.size(); i++) {
        if (&getMinion(i) == &minion) {
            return i;
        }
    }
    return -1;
}

Ritual &Board::getRitual() { return *ritual; };

void Board::addMinion(std::unique_ptr<Minion> minion) { minions.emplace_back(minion); }

/*std::unique_ptr<Minion> Board::removeMinion(int i) {
    Minion m = getMinion(i);
    std::unique_ptr<Minion> temp = std::make_unique<Minion>(m);
    minions.erase(minions.begin() + (i - 1));
    return std::move(temp);
}*/

std::unique_ptr<Minion> Board::removeFromGraveyard() {
    if(!isGraveyardEmpty()) {
        return std::move(graveyard.back());
    }
    return nullptr;
}

void Board::addToGraveyard(Minion &minion) {
    int deadMinionIndex = getMinion(minion);
    std::unique_ptr<Minion> deadMinion = std::move(minions.at(deadMinionIndex));// minion minion nullptr minion
    minions.erase(minions.begin() + deadMinionIndex);// remove nullptr
    graveyard.emplace_back(std::move(deadMinion));
}

void Board::setRitual(std::unique_ptr<Ritual> ritual) {
    this->ritual.swap(ritual);
}

bool Board::hasRitual() { return ritual != nullptr; }

bool Board::isGraveyardEmpty() { return graveyard.empty(); }

int Board::numberOfMinions() { return minions.size(); }

void Board::notifyAll(Card::Trigger t, Player &player) {
    for (int i = 0; i < minions.size(); i++) {
        getMinion(i).trigger(t, player);
    }
    getRitual().trigger(t, player);
}

void Board::notifyAll(Card::Trigger t, Minion  &myMinion, Minion &otherMinion, Player &player, Player &otherPlayer) {
    for(int i = 0; i < minions.size(); i++){
        getMinion(i).trigger(t, myMinion, otherMinion, player, otherPlayer);
    }
    getRitual().trigger(t, myMinion, player, otherPlayer);
}


