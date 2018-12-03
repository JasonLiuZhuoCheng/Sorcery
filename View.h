#ifndef HEARTHSTONE_VIEW_H
#define HEARTHSTONE_VIEW_H


#include "Board.h"
#include "ascii_graphics.h"
#include "Card.h"
#include "window.h"

class Player;
class Minion;
class Enchantment;
class Spell;
class Ritual;

class View{
public:
    virtual ~View() = default;
    virtual void displayMinion(Minion &minion) = 0; // Display a single minion with the command "inspect"
    virtual void displayHand(Player &player) = 0; // Display the hand of the active player
    virtual void display(Player &p1, Player &p2, int round) = 0; // Display the current stae of the game (i.e the Board)
    virtual void clear() = 0; // clear for the graphic user interface

protected:
    virtual void displayPlayer(Player &player, int num) = 0; // Display one player with id "num"

    // These functions use methods in "ascii_graphics" to build appropriate "card templates"
    card_template_t makePlayer(Player &player);
    card_template_t makeMinion(Minion &minion);
    card_template_t makeEnchantment(Enchantment &enchantment);
    card_template_t makeSpell(Spell &spell);
    card_template_t makeRitual(Ritual &ritual);

    // These functions are to extract data from the current player
    std::vector<card_template_t> convertHand(Player &player); // extract the "hand" of current player
    std::vector<card_template_t> convertMinions(Player &player); // extract the "minions" of current player
    std::vector<card_template_t> convertStatus(Player &player); // extract the "graveyard, ritual, player status" of current player
    std::vector<card_template_t> convertEnchantment(Minion &minion); // extract the "enchantment" of a minion

    // converts a vector of "card_template" (usually size of 5) to vector of string to allow displaying them in different
    // user interface more convenience.
    std::vector<std::string> convert(std::vector<card_template_t> &vec, bool printBoard);
};



class Graphic final: public View{
    std::unique_ptr<Xwindow> win;
    void displayPlayer(Player &player, int num) override;
    void draw(std::vector<card_template_t> &vec, int x, Xwindow&, bool printBoard); // Display 5 cards on window
public:
    explicit Graphic(std::unique_ptr<Xwindow>);
    void displayMinion(Minion &minion) override;
    void displayHand(Player &player) override;
    void display(Player &p1, Player &p2, int round) override;
    void clear() override;
};

class Text final: public View{
    void print(card_template_t); // prints one card on Text user interface
    void print(std::vector<card_template_t> &, bool printBoard); // prints 5 cards
    void displayPlayer(Player &player, int num) override;
public:
    void displayMinion(Minion &minion) override;
    void displayHand(Player &player) override;
    void display(Player &p1, Player &p2, int round) override;
    void clear() override;
};
#endif
