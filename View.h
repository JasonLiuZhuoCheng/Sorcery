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
    virtual void displayMinion(Minion &minion) = 0;
    virtual void displayHand(Player &player) = 0;
    virtual void display(Player &p1, Player &p2, int round) = 0;

    card_template_t makePlayer(Player &player);
    card_template_t makeMinion(Minion &minion);
    card_template_t makeEnchantment(Enchantment &enchantment);
    card_template_t makeSpell(Spell &spell);
    card_template_t makeRitual(Ritual &ritual);

    std::vector<std::string> convert(std::vector<card_template_t> &vec, bool printBoard);
    std::vector<card_template_t> convertHand(Player &player);
    std::vector<card_template_t> convertMinions(Player &player);
    std::vector<card_template_t> convertStatus(Player &player);
};



class Graphic final: public View{
    std::unique_ptr<Xwindow> win;
    void displayPlayer(Player &player, int num);
public:
    explicit Graphic(std::unique_ptr<Xwindow>);
    void displayMinion(Minion &minion) override;
    void displayHand(Player &player) override;
    void display(Player &p1, Player &p2, int round) override;

    void draw(std::vector<card_template_t> &vec, int x, Xwindow&); // Display 5 cards on window
    void init(Player &p1, Player &p2);
    //void notify(Player &p1, Player &p2);
};

class Text final: public View{


    void print(card_template_t); // prints one card
    void print(std::vector<card_template_t> &, bool); // prints 5 cards
    void displayPlayer(Player &player, int num);
public:
    void displayMinion(Minion &minion) override;
    void displayHand(Player &player) override;
    void display(Player &p1, Player &p2, int round) override;

};
#endif //HEARTHSTONE_DISPLAY_H
