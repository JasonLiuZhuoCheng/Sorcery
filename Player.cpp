//
// Created by Matthew on 2018-11-14.
//

#include "Player.h"
#include "Card/Enchantment.h"
#include <algorithm>
#include <iostream>
using namespace std;


Player::Player() : life{20}, magic{3}, otherBoard{nullptr}, activeStatus{false}, maxMgaic{3} {
    myBoard = new Board();
}

Card & Player::getCard(int i) { return *(hand.at(i)); }

/*
 * playCard: Will only be invoked if card[i] is played successfully
 */
void Player::moveCardToBoard(int i) {
    // Get ith card
    Card *card = hand[i].release();
    Minion *minion = nullptr;
    Ritual *ritual = nullptr;
    // Insert accordingly
    if ((minion = dynamic_cast<Minion*>(card)) != nullptr) myBoard->addMinion(unique_ptr<Minion>(minion));
    else if ((ritual = dynamic_cast<Ritual*>(card)) != nullptr) myBoard->setRitual(unique_ptr<Ritual>(ritual));
    // Remove card from hand
    hand.erase(hand.begin() + i);
}

Board *Player::getMyBoard() { return myBoard; }

//Board *Player::getOtherBoard() { return otherBoard; }

int Player::getMagic() { return magic; }

bool Player::isActive() { return activeStatus; }

void Player::mutateLife(int i) { this->life += i; }

void Player::mutateMagic(int i) { this->magic += i; }

void Player::addToDeck(std::unique_ptr<Card> card) {
    deck.emplace_back(card);
}

//void Player::setOtherBoard(Board *board) { this->otherBoard = board; }

void Player::setName(string &name) { this->name = name; }

bool Player::isDead() { return life <= 0; }

void Player::shuffle() {
    std::random_shuffle(deck.begin(), deck.end());
}

void Player::drawCard() {
    if (!isHandfull() && !deck.empty()) {
        hand.emplace_back(std::move(deck.back()));
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

/*void Player::notifyAll(Card::Trigger t, Player &player) {
    myBoard->notifyAll(t, player);
    //otherBoard->notifyAll(t, player);
}

void Player::notifyAll(Card::Trigger t, Player &player, Card &card) {
    myBoard->notifyAll(t, player, card);
    //otherBoard->notifyAll(t, player, card);
}*/

void Player::addMinionToHand(unique_ptr<Minion> minion) {
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





