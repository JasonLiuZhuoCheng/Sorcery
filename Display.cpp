#include <iostream>
#include <typeindex>
#include "Display.h"
#include "ascii_graphics.h"
using namespace std;

void Text::print(card_template_t t1) {
    for (int i = 0; i < t1.size(); i++) {
        std::cout << t1.at(i) << endl;
    }
}

void Text::print(card_template_t t1, card_template_t t2, card_template_t t3, card_template_t t4, card_template_t t5) {
    for (int i = 0; i < t1.size(); i++){
        std::cout << t1.at(i)+t2.at(i)+t3.at(i)+t4.at(i)+t5.at(i) << endl;
    }
}

void Text::displayMinion(Minion &minion){
    if(minion.hasEnchant()){
        print(makeMinion(minion));
        for(int i = 0; i < minion.numOfEnchant(); i++){
            print(makeEnchantment(minion.getEnchant(i)));
        }
    }
}

void Text::displayHand(Player &player) {
    for(int i = 0; i < player.handSize(); i++){
        if(std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Minion))){
            print(makeMinion(dynamic_cast<Minion &>(player.getCard(i))));
        }
        else if(std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Ritual))){
            print(makeRitual(dynamic_cast<Ritual &>(player.getCard(i))));
        }
        else if(std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Enchantment))){
            print(makeEnchantment(dynamic_cast<Enchantment &>(player.getCard(i))));
        }
        else{
            print(makeSpell(dynamic_cast<Spell &>(player.getCard(i))));
        }
    }
}


void Text::display(Player &p1, Player &p2) {
    std::vector<std::string> c = CENTRE_GRAPHIC;
    std::vector<std::string> Empty = CARD_TEMPLATE_EMPTY
    print((makeRitual(p1.getMyBoard()->getRitual())),Empty,makePlayer(p1),Empty,makeMinion(p1.getMyBoard()->graveyardTop()));
    if (p1.getMyBoard()->numberOfMinions() == 0){
        print(Empty,Empty,Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 1){
        print(p1.getMyBoard()->getMinion(1),Empty,Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 2){
        print(p1.getMyBoard()->getMinion(1),p1.getMyBoard()->getMinion(2),Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 3){
        print(p1.getMyBoard()->getMinion(1),p1.getMyBoard()->getMinion(2),p1.getMyBoard()->getMinion(3),Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 4){
        print(p1.getMyBoard()->getMinion(1),p1.getMyBoard()->getMinion(2),p1.getMyBoard()->getMinion(3),p1.getMyBoard()->getMinion(4),Empty);
    } else {
        print(p1.getMyBoard()->getMinion(1),p1.getMyBoard()->getMinion(2),p1.getMyBoard()->getMinion(3),p1.getMyBoard()->getMinion(4),p1.getMyBoard()->getMinion(5));
    }

    for(auto &row : c){
        std::cout << row << std::endl;
    }
    if (p2.getMyBoard()->numberOfMinions() == 0){
        print(Empty,Empty,Empty,Empty,Empty);
    } else if (p2.getMyBoard()->numberOfMinions() == 1){
        print(p2.getMyBoard()->getMinion(1),Empty,Empty,Empty,Empty);
    } else if (p2.getMyBoard()->numberOfMinions() == 2){
        print(p2.getMyBoard()->getMinion(1),p2.getMyBoard()->getMinion(2),Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 3){
        print(p2.getMyBoard()->getMinion(1),p2.getMyBoard()->getMinion(2),p2.getMyBoard()->getMinion(3),Empty,Empty);
    } else if (p2.getMyBoard()->numberOfMinions() == 4){
        print(p2.getMyBoard()->getMinion(1),p2.getMyBoard()->getMinion(2),p2.getMyBoard()->getMinion(3),p2.getMyBoard()->getMinion(4),Empty);
    } else {
        print(p2.getMyBoard()->getMinion(1),p2.getMyBoard()->getMinion(2),p2.getMyBoard()->getMinion(3),p2.getMyBoard()->getMinion(4),p2.getMyBoard()->getMinion(5));
    }
    print((makeRitual(p2.getMyBoard()->getRitual())),Empty,makePlayer(p2),Empty,makeMinion(p2.getMyBoard()->graveyardTop()));
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
    if(enchantment.hasAttDef()){
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
               )
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

