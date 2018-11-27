#include <iostream>
#include <typeindex>
#include "Display.h"
#include "Enchantment.h"
#include "Spell.h"
#include "Player.h"

using namespace std;

void Graphic::display(Player &p1, Player &p2) {}

void Graphic::displayHand(Player &player) {}

void Graphic::displayMinion(Minion &minion) {}

void Text::print(card_template_t t1) {
    for (int i = 0; i < t1.size(); i++) {
        std::cout << t1.at(i) << endl;
    }
}

void Text::print(vector<card_template_t> &vec, bool printBoard) {
    int size = vec.at(0).size();
    string border = printBoard ? EXTERNAL_BORDER_CHAR_UP_DOWN : "";
    for(int i = 0; i < size; i++) {
        std::cout << border;
        string str = "";
        for (int j = 0; j < vec.size(); j++) {
            str += vec.at(j).at(i);
        }
        std::cout << str << border << endl;
    }
}

void Text::displayMinion(Minion &minion) {
    print(makeMinion(minion));
    std::vector<card_template_t> Store;
    for(int i = 0; i < minion.numOfEnchant(); i++){
        if(Store.size() == 5) {
            print(Store, false);
            Store.clear();
        }
        Store.emplace_back(makeEnchantment(minion.getEnchant(i)));
    }
}

void Text::displayHand(Player &player) {
    std::vector<card_template_t> Store;
    for (int i = 0; i < player.handSize(); i++) {
        Card &card = player.getCard(i);
        if (dynamic_cast<Minion *>(&card)) {
            Store.emplace_back(makeMinion(dynamic_cast<Minion &>(card)));
        } else if (dynamic_cast<Ritual *>(&card)) {
            Store.emplace_back(makeRitual(dynamic_cast<Ritual &>(card)));
        } else if (dynamic_cast<Enchantment *>(&card)) {
            Store.emplace_back(makeEnchantment(dynamic_cast<Enchantment &>(card)));
        } else {
            Store.emplace_back(makeSpell(dynamic_cast<Spell &>(card)));
        }
    }
    for(int i = player.handSize(); i < maxHand; i++){
        Store.emplace_back(CARD_TEMPLATE_BORDER);
    }
    print(Store, false);
}

void Text::displayPlayer(Player &player, int num){
    std::vector<card_template_t> minions;
    std::vector<card_template_t> status;
    int numOfMinions = player.getMyBoard()->numberOfMinions();
    for(int i = 0; i < numOfMinions; i++){
        minions.emplace_back(makeMinion(player.getMyBoard()->getMinion(i)));
    }
    for(int i = numOfMinions; i < 5; i++){
        minions.emplace_back(CARD_TEMPLATE_BORDER);
    }

    player.getMyBoard()->hasRitual() ? status.emplace_back(makeRitual(player.getMyBoard()->getRitual()))
    : status.emplace_back(CARD_TEMPLATE_BORDER);
    status.emplace_back(CARD_TEMPLATE_EMPTY);
    status.emplace_back(makePlayer(player));
    status.emplace_back(CARD_TEMPLATE_EMPTY);
    player.getMyBoard()->isGraveyardEmpty() ? status.emplace_back(CARD_TEMPLATE_BORDER)
    : status.emplace_back(makeMinion(player.getMyBoard()->graveyardTop()));

    if(num == 1){
        print(status, true);
        print(minions, true);
    }else{
        print(minions, true);
        print(status, true);
    }
}

void Text::display(Player &p1, Player &p2) {
    // Top Border
    std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for(int i = 0; i < 165; i++) std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

    std::vector<std::string> c = CENTRE_GRAPHIC;
    displayPlayer(p1, 1);
    for(auto &row : CENTRE_GRAPHIC){
        std::cout << row << std::endl;
    }
    displayPlayer(p2, 2);

    // Bottom Border
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for(int i = 0; i < 165; i++)  std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

card_template_t Text::makeMinion(Minion &minion){
    if(minion.hasAbility()){
        // display_minion_activated_ability(std::string name,int cost,int attack, int defence,
        // int ability_cost,std::string ability_desc)
        return display_minion_activated_ability(
                minion.getName(),
                minion.getCost(),
                minion.getAtt(),
                minion.getDef(),
                minion.getMagic(),
                minion.getDescription());
    }
    else if(minion.hasTrigger()){
        //display_minion_triggered_ability(std::string name,int cost,int attack,int defence,
        // std::string trigger_desc)
        return display_minion_triggered_ability(
                minion.getName(),
                minion.getCost(),
                minion.getAtt(),
                minion.getDef(),
                minion.getDescription());
    }
    else{
       // display_minion_no_ability(std::string name,int cost,int attack,int defence);
        return display_minion_no_ability(
                minion.getName(),
                minion.getCost(),
                minion.getAtt(),
                minion.getDef());
    }
}

card_template_t Text::makeEnchantment(Enchantment &enchantment){
    if(enchantment.hasStats()){
        //display_enchantment_attack_defence(std::string name,int cost,std::string desc,
        // std::string attack,std::string defence);
        return display_enchantment_attack_defence(
                enchantment.getName(),
                enchantment.getCost(),
                enchantment.getDescription(),
                enchantment.getAtt(),
                enchantment.getDef());
    }else{
       // display_enchantment(std::string name,int cost,std::string desc);
       return display_enchantment(
               enchantment.getName(),
               enchantment.getCost(),
               enchantment.getDescription()
               );
    }
}

card_template_t Text::makeSpell(Spell &spell){
    //display_spell(std::string name,int cost,std::string desc)
    return display_spell(
            spell.getName(),
            spell.getCost(),
            spell.getDescription());
}
card_template_t Text::makeRitual(Ritual &ritual){
    //display_ritual(std::string name,int cost,int ritual_cost,std::string ritual_desc,
    // int ritual_charges)
    return display_ritual(
            ritual.getName(),
            ritual.getCost(),
            ritual.getActiveCost(),
            ritual.getDescription(),
            ritual.getCharges());
}

card_template_t Text::makePlayer(Player &player) {
    return display_player_card(
            player.getID(),
            player.getName(),
            player.getLife(),
            player.getMagic()
            );
}

