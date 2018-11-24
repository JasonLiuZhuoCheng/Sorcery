#include "Card.h"

Card::Card(int cost, std::string &name, std::string &description) : cost{cost}, name{name}, description{description} {}

int Card::getCost(){
    return cost;
}

std::string Card::getName(){
    return name;
}

std::string Card::getDescription() {
    return description;
}