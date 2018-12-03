//
// Created by Matthew on 2018-11-14.
//

#include "Player.h"
#include "Enchantment.h"

#include <algorithm>
#include <iostream>
using namespace std;


Player::Player(int id) : id{id},life{20}, magic{3}{
    myBoard = make_unique<Board>();
}

std::string Player::getName() { return name; }

int Player::getLife() { return life; }

Card & Player::getCard(int i) { return *(hand.at(i)); }

int Player::getID() { return id; }

Board &Player::getMyBoard() { return *myBoard; }

int Player::getMagic() { return magic; }

int Player::handSize() { return hand.size(); }

void Player::addMinionToHand(unique_ptr<Minion> minion) {
    if(!isHandfull()){
        hand.emplace_back(std::move(minion));
    }
}

void Player::moveEnchantmentToMinion(int i, Card &ifMinion) {
    auto *card = hand[i].release();
    auto *enchantment = dynamic_cast<Enchantment *>(card);
    if(enchantment != nullptr && dynamic_cast<Minion*>(&ifMinion)){
        dynamic_cast<Minion&>(ifMinion).pushEnchantment(unique_ptr<Enchantment>(enchantment));
    }else{
        garbage.emplace_back(unique_ptr<Card>(card));
    }
    hand.erase(hand.begin() + i);
}

/*
 * playCard: Will only be invoked if card[i] is played successfully
 */
void Player::moveCardToBoard(int i) {
    auto *card = hand[i].release();
    auto *minion = dynamic_cast<Minion *>(card);
    auto *ritual = dynamic_cast<Ritual*>(card);

    if (minion != nullptr) myBoard->addMinion(unique_ptr<Minion>(minion));
    else if (ritual != nullptr) myBoard->setRitual(unique_ptr<Ritual>(ritual));
    else garbage.emplace_back(unique_ptr<Card>(card));
    // Remove card from hand
    hand.erase(hand.begin() + i);
}

void Player::mutateLife(int i) { life += i; }

void Player::mutateMagic(int i) { magic += i; }

void Player::addToDeck(std::unique_ptr<Card> card) { deck.emplace_back(std::move(card)); }

void Player::setName(string &name) { this->name = name; }

void Player::setMagic(int i) { magic = i; }

bool Player::isDead() { return life <= 0; }

void Player::shuffle() { std::random_shuffle(deck.begin(), deck.end()); }

void Player::drawCard() {
    if(isHandfull()){
        cout << "Your hand is full, unable to draw card" << endl;
    }else if(deck.empty()) {
        cout << "Your deck is empty, unable to draw card" << endl;
    }else{
        hand.emplace_back(std::move(deck.at(0)));
        deck.erase(deck.begin());
    }
}

void Player::discardCard(int i) {
    if (i > hand.size()) {
        cout << "Cannot discard card, your hand is less than " << i << endl;
        return;
    }
    hand.erase(hand.begin() + i);
}

bool Player::isHandfull() { return hand.size() == maxHand; }
