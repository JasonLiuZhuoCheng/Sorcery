#include <iostream>
#include <typeindex>
#include "Display.h"
#include "ascii_graphics.h"
using namespace std;

void Graphic::displayMinion(Minion &minion){}

void Graphic::displayHand(Player &player){
    for(int i=0; i<5; i++){

    }
}

void Graphic::displayBoard(Board &board){

}
//---------------------------------------------------Text-----------------------------------

void Text::displayMinion(Minion &minion){
    if(minion.hasEnchant()){
        printMinion(minion);
        for(int i = 0; i < minion.numOfEnchant(); i++){
            printEnchantment(minion.getEnchant(i));
        }
    }
}

void Text::displayHand(Player &player) {
    for(int i = 0; i < player.handSize(); i++){
        if(std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Minion))){
            printMinion(dynamic_cast<Minion &>(player.getCard(i)));
        }
        else if(std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Ritual))){
            printRitual(dynamic_cast<Ritual &>(player.getCard(i)));
        }
        else if(std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Enchantment))){
            printEnchantment(dynamic_cast<Enchantment &>(player.getCard(i)));
        }
        else{
            printSpell(dynamic_cast<Spell &>(player.getCard(i)));
        }
    }
}

void Text::display(Player &p1, Player &p2) {
    printBoard(p1);
    CENTRE_GRAPHIC;
    printBoard(p2);
}

static void print(card_template_t t1, card_template_t t2, card_template_t t3, card_template_t t4, card_template_t t5){
    for (int i = 0; i < t1.size(); i++){
        std::cout << t1.at(i)+t2.at(i)+t3.at(i)+t4.at(i)+t5.at(i) << std::endl;
    }

}


void Text::printBoard(Player &player) {
    Board *b = player.getMyBoard();
    // Display the first row of board

}




card_template_t Text::printMinion(Minion &minion){
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

card_template_t Text::printEnchantment(Enchantment &enchantment){
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
                enchantment.getDescription());
    }
}

card_template_t Text::printSpell(Spell &spell){
    //display_spell(std::string name,int cost,std::string desc)
    return display_spell(
            spell.getName(),
            spell.getCost(),
            spell.getDescription());
}

card_template_t Text::printRitual(Ritual &ritual){
    //display_ritual(std::string name,int cost,int ritual_cost,std::string ritual_desc,
    // int ritual_charges)
    return display_ritual(
            ritual.getName(),
            ritual.getCost(),
            ritual.getActiveCost(),
            ritual.getDescription(),
            ritual.getCharges());
}

void Text::printMinionsOnBoard(Board &board) {
    for(int i = 0; i < board.numberOfMinions(); i++){
        printMinion(board.getMinion(i));
    }
    for(int i = 0; i < 5 - board.numberOfMinions(); i++){
        CARD_TEMPLATE_BORDER;
    }
}

