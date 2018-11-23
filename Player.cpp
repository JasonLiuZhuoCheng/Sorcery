//
// Created by Matthew on 2018-11-14.
//

#include "Player.h"
using namespace std;

Player::Player() : life{20}, magic{3}, otherBoard{nullptr}, activeStatus{false}, maxMgaic{3} {
    myBoard = new Board();

}

unique_ptr<Card> Player::getCard(int i) {
    return std::move(hand.at(i));
    }

Board *Player::getMyBoard() { return myBoard; }

Board *Player::getOtherBoard() { return otherBoard; }

int Player::getMagic() { return magic; }
bool Player::isActive() { return activeStatus; }

void Player::mutateLife(int i) { this->life += i; }

void Player::mutateMagic(int i) { this->magic += i; }

void Player::setDeck(vector<unique_ptr<Card>> &deck) { this->deck = deck; }

void Player::setOtherBoard(Board *board) { this->otherBoard = board; }

void Player::setName(string &name) { this->name = name; }

bool Player::isDead() { return life <= 0; }

void Player::shuffle() {
    int size = deck.size();
    vector<unique_ptr<Card>> temp;
    for (int i = 0; i < size; i++) {
        int r = rand() % size; // generate a random position
        temp.emplace_back(std::move(deck.at(r)));
    }
    deck = temp;
}

void Player::drawCard() {
    if (!isHandfull() && !deck.empty()) {
        hand.emplace_back(deck.back());
        deck.pop_back();
    }else{
        cout << "unable to draw card (either hand is full or deck is empty)" << endl;
    }
}

void Player::discardCard(int i) {
    if (i > hand.size()) {
        cout << "Your hand is less than " << i << endl;
        return;
    }
    hand.erase(hand.begin() + (i - 1));
}

void Player::notifyAll(Card::Trigger t, Player &player) {
    myBoard->notifyAll(t, player);
    otherBoard->notifyAll(t, player);
}

void Player::notifyAll(Card::Trigger t, Player &player, Card &card) {
    myBoard->notifyAll(t, player, card);
    otherBoard->notifyAll(t, player, card);
}

void Player::addMinionToHand(Minion *minion) {
    if(!isHandfull()){
        hand.emplace_back(minion);
    }
}

bool Player::isHandfull() { return hand.size() < maxHand; }

void Player::setMagic() {
    magic = maxMgaic;
}

void Player::setMaxMagic() {
    maxMgaic++;
}





