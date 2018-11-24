
#ifndef HEARTHSTONE_CARD_H
#define HEARTHSTONE_CARD_H

#include <string>

class Player;

// Card is the abstract base class for all the possible cards in Sorcery.

class Card {
protected:
    int cost; // cost of magic
    std::string name, description;
public:
    virtual bool play(Player &player, Player &otherPlayer) = 0;
    virtual bool play(Player &, Card &) = 0;
    int getCost();
    std::string getName();
    std::string getDescription();
    enum Trigger {
        START_OF_TURN, END_OF_TURN, MY_MINION_ENTER, OTHER_MINION_ENTER, OTHER_MINION_LEAVE, MY_MINION_LEAVE
    };

    Card(int, std::string &name, std::string &description);
};


#endif