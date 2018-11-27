#include <iostream>
#include <typeindex>
#include "Display.h"
#include "Card/Enchantment.h"
#include "Card/Spell.h"
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

void Text::print(card_template_t t1, card_template_t t2, card_template_t t3, card_template_t t4, card_template_t t5) {
    for (int i = 0; i < t1.size(); i++){
        std::cout << t1.at(i)+t2.at(i)+t3.at(i)+t4.at(i)+t5.at(i) << endl;
    }
}

void Text::displayMinion(Minion &minion){
    int t = 0;
    int numberOfEnchant = minion.numOfEnchant();
    card_template_t Empty = CARD_TEMPLATE_EMPTY;
    if(minion.hasEnchant()){
        print(makeMinion(minion));
        while (numberOfEnchant >= 5){
            print(makeEnchantment(minion.getEnchant(t*5)),
                  makeEnchantment(minion.getEnchant(t*5+1)),
                  makeEnchantment(minion.getEnchant(t*5+2)),
                  makeEnchantment(minion.getEnchant(t*5+3)),
                  makeEnchantment(minion.getEnchant(t*5+4)));
            t++;
            numberOfEnchant = numberOfEnchant - 5;
        }
        if (numberOfEnchant == 0){
            return;
        }
        else if (numberOfEnchant == 1){
            print(makeEnchantment((minion.getEnchant(t*5))),Empty,Empty,Empty,Empty);
        } else if (numberOfEnchant == 2){
            print(makeEnchantment(minion.getEnchant(t*5)),makeEnchantment(minion.getEnchant(t*5+1)),Empty,Empty,Empty);
        } else if (numberOfEnchant == 3){
            print(makeEnchantment(minion.getEnchant(t*5)),makeEnchantment(minion.getEnchant(t*5+1))
                    ,makeEnchantment(minion.getEnchant(t*5+2)),Empty,Empty);
        } else {
            print(makeEnchantment(minion.getEnchant(t*5)),makeEnchantment(minion.getEnchant(t*5+1))
                    ,makeEnchantment(minion.getEnchant(t*5+2)),makeEnchantment((minion.getEnchant(t*5+3))),Empty);
        };
    }
    else {
        print(makeMinion(minion));
    }
}

void Text::displayHand(Player &player) {
    std::vector<std::string> Empty = CARD_TEMPLATE_EMPTY;
    std::vector<card_template_t> Store;
    for (int i = 0; i < player.handSize(); i++) {
        if (std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Minion))) {
            Store.emplace_back(makeMinion(dynamic_cast<Minion &>(player.getCard(i))));
        } else if (std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Ritual))) {
            Store.emplace_back(makeRitual(dynamic_cast<Ritual &>(player.getCard(i))));
        } else if (std::type_index(typeid(player.getCard(i))) == std::type_index(typeid(Enchantment))) {
            Store.emplace_back(makeEnchantment(dynamic_cast<Enchantment &>(player.getCard(i))));
        } else {
            Store.emplace_back(makeSpell(dynamic_cast<Spell &>(player.getCard(i))));
        }
    }
    if (Store.size() == 0){
        print(Empty,Empty,Empty,Empty,Empty);
    } else if (Store.size() == 1){
        print(Store.at(0),Empty,Empty,Empty,Empty);
    } else if (Store.size() == 2){
        print(Store.at(0),Store.at(1),Empty,Empty,Empty);
    } else if (Store.size() == 3){
        print(Store.at(0),Store.at(1),Store.at(2),Empty,Empty);
    } else if (Store.size() == 4){
        print(Store.at(0),Store.at(1),Store.at(2),Store.at(3),Empty);
    } else {
        print(Store.at(0),Store.at(1),Store.at(2),Store.at(3),Store.at(4));
    }
}


void Text::display(Player &p1, Player &p2) {
    std::vector<std::string> c = CENTRE_GRAPHIC;

    std::vector<std::string> Empty = CARD_TEMPLATE_BORDER;
    std::vector<std::string> RitualOne = !p1.getMyBoard()->hasRitual() ? CARD_TEMPLATE_BORDER : makeRitual(
            p1.getMyBoard()->getRitual());
    std::vector<std::string> RitualTwo = !p2.getMyBoard()->hasRitual() ? CARD_TEMPLATE_BORDER : makeRitual(
            p1.getMyBoard()->getRitual());
    std::vector<std::string> GraveOne = p1.getMyBoard()->isGraveyardEmpty() ? CARD_TEMPLATE_BORDER : makeMinion(p1.getMyBoard()->graveyardTop());
    std::vector<std::string> GraveTwo = p2.getMyBoard()->isGraveyardEmpty() ? CARD_TEMPLATE_BORDER : makeMinion(p2.getMyBoard()->graveyardTop());
    print(RitualOne,Empty,makePlayer(p1),Empty,GraveOne);

    if (p1.getMyBoard()->numberOfMinions() == 0){
        print(Empty,Empty,Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 1){
        print(makeMinion(p1.getMyBoard()->getMinion(0)),Empty,Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 2){
        print(makeMinion(p1.getMyBoard()->getMinion(0)),makeMinion(p1.getMyBoard()->getMinion(1)),Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 3){
        print(makeMinion(p1.getMyBoard()->getMinion(0)),makeMinion(p1.getMyBoard()->getMinion(1)),
              makeMinion(p1.getMyBoard()->getMinion(2)),Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 4){
        print(makeMinion(p1.getMyBoard()->getMinion(0)),makeMinion(p1.getMyBoard()->getMinion(1))
                ,makeMinion(p1.getMyBoard()->getMinion(2)),makeMinion(p1.getMyBoard()->getMinion(3)),Empty);
    } else {
        print(makeMinion(p1.getMyBoard()->getMinion(0)),makeMinion(p1.getMyBoard()->getMinion(1)),
              makeMinion(p1.getMyBoard()->getMinion(2)),makeMinion(p1.getMyBoard()->getMinion(3)),
              makeMinion(p1.getMyBoard()->getMinion(4)));
    }

    for(auto &row : c){
        std::cout << row << std::endl;
    }
    if (p2.getMyBoard()->numberOfMinions() == 0){
        print(Empty,Empty,Empty,Empty,Empty);
    } else if (p2.getMyBoard()->numberOfMinions() == 1){
        print(makeMinion(p2.getMyBoard()->getMinion(0)),Empty,Empty,Empty,Empty);
    } else if (p2.getMyBoard()->numberOfMinions() == 2){
        print(makeMinion(p2.getMyBoard()->getMinion(0)),makeMinion(p2.getMyBoard()->getMinion(1)),Empty,Empty,Empty);
    } else if (p1.getMyBoard()->numberOfMinions() == 3){
        print(makeMinion(p2.getMyBoard()->getMinion(0)),makeMinion(p2.getMyBoard()->getMinion(1)),
                makeMinion(p2.getMyBoard()->getMinion(2)),Empty,Empty);
    } else if (p2.getMyBoard()->numberOfMinions() == 4){
        print(makeMinion(p2.getMyBoard()->getMinion(0)),makeMinion(p2.getMyBoard()->getMinion(1))
                ,makeMinion(p2.getMyBoard()->getMinion(2)),makeMinion(p2.getMyBoard()->getMinion(3)),Empty);
    } else {
        print(makeMinion(p2.getMyBoard()->getMinion(0)),makeMinion(p2.getMyBoard()->getMinion(1)),
                makeMinion(p2.getMyBoard()->getMinion(2)),makeMinion(p2.getMyBoard()->getMinion(3)),
                makeMinion(p2.getMyBoard()->getMinion(4)));
    }
    print(RitualTwo,Empty,makePlayer(p2),Empty,GraveTwo);
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

