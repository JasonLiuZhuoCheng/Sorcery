
#include <typeindex>
#include "Display.h"
#include "ascii_graphics.h"
using namespace std;

void Graphic::displayMinion(const Minion &minion){}

void Graphic::displayHand(const Player &player){
    for(int i=0; i<5; i++){

    }
}

void Graphic::displayBoard(const Board &board){

}


void Text::printMinion(const Minion &minion){
    if(minion.hasAbility()){
        // display_minion_activated_ability(std::string name,int cost,int attack, int defence,
        // int ability_cost,std::string ability_desc)
        display_minion_activated_ability(
                minion.getName(),
                minion.getCost(),
                minion.getAtt(),
                minion.getDef(),
                minion.getActionValue(),
                minion.getMagic(),
                minion.getDescription())
    }
    else if(minion.hasTrigger()){
        //display_minion_triggered_ability(std::string name,int cost,int attack,int defence,
        // std::string trigger_desc)
        display_minion_triggered_ability(
                minion.getName(),
                minion.getCost(),
                minion.getAtt(),
                minion.getDef(),
                minion.getDescription())
    }
    else{
       // display_minion_no_ability(std::string name,int cost,int attack,int defence);
        display_minion_no_ability(
                minion.getName(),
                minion.getCost(),
                minion.getAtt(),
                minion.getDef());
    }
}

void Text::printEnchantment(const Enchantment &enchantment){
    if(enchantment.hasAttDef()){
        //display_enchantment_attack_defence(std::string name,int cost,std::string desc,
        // std::string attack,std::string defence);
        display_enchantment_attack_defence(
                enchantment.getName(),
                enchantment.getCost(),
                enchantment.getDescription(),
                enchantment.getAttack(),
                enchantment.getDefence())
    }else{
       // display_enchantment(std::string name,int cost,std::string desc);
       display_enchantment(
               enchantment.getName(),
               enchantment.getCost(),
               enchantment.getDescription()
               )
    }
}

void Text::printSpell(const Spell &spell){
    //display_spell(std::string name,int cost,std::string desc)
    display_spell(
            spell.getName(),
            spell.getCost(),
            spell.getDescription());
}
void Text::printRitual(const Ritual &ritual){
    //display_ritual(std::string name,int cost,int ritual_cost,std::string ritual_desc,
    // int ritual_charges)
    display_ritual(
            ritual.getName(),
            ritual.getCost(),
            ritual.getActiveCost(),
            ritual.getDescription(),
            ritual.getCharges());
}

void Text::displayMinion(const Minion &minion){
    //TODO: need to check enchantment and display them
    printMinion(minion);
}

void Text::displayHand(const Player &player) {
    for(int i=0; i<5; i++){
        if(std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Minion))){
            printMinion(*player.getCard(i));
        }
        if(std::type_index(typeid(player.getCard(i)) == std::type_index(typeid(Minion))){

        }
        if(std::type_index(typeid(player.getCard(i)) == std::type_index(typeid(Minion))){

        }
        if(std::type_index(typeid(player.getCard(i)) == std::type_index(typeid(Minion))){

        }
    }
}

void Text::displayBoard(const Board &board) {

}


