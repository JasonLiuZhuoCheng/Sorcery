#include <iostream>
#include <chrono>
#include <thread>
#include "View.h"
#include "Enchantment.h"
#include "Spell.h"
#include "Player.h"

//--------------------------------View--------------------------------
std::vector<std::string> View::convert(vector<card_template_t> &vec, bool printBoard){
    int size = vec.at(0).size();
    string border = printBoard ? EXTERNAL_BORDER_CHAR_UP_DOWN : "";
    vector<string> v;
    for(int i = 0; i < size; i++) {
        string str = border;
        for (auto &it : vec) {
            str += it.at(i);
        }
        str += border;
        v.emplace_back(str);
    }
    return v;
}

std::vector<card_template_t> View::convertHand(Player &player) {
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
    // Fill the rest of hand with Empty Cards
    for(int i = player.handSize(); i < maxHand; i++){
        Store.emplace_back(CARD_TEMPLATE_BORDER);
    }
    return Store;
}

std::vector<card_template_t> View::convertMinions(Player &player) {
    std::vector<card_template_t> minions;
    int numOfMinions = player.getMyBoard().numberOfMinions();
    for(int i = 0; i < numOfMinions; i++){
        minions.emplace_back(makeMinion(player.getMyBoard().getMinion(i)));
    }
    // Fill the rest of Minion Slots with Empty Cards
    for(int i = numOfMinions; i < 5; i++){
        minions.emplace_back(CARD_TEMPLATE_BORDER);
    }
    return minions;
}

std::vector<card_template_t> View::convertStatus(Player &player) {
    std::vector<card_template_t> status;
    player.getMyBoard().hasRitual() ? status.emplace_back(makeRitual(player.getMyBoard().getRitual()))
                                    : status.emplace_back(CARD_TEMPLATE_BORDER);
    status.emplace_back(CARD_TEMPLATE_EMPTY);
    status.emplace_back(makePlayer(player));
    status.emplace_back(CARD_TEMPLATE_EMPTY);
    player.getMyBoard().isGraveyardEmpty() ? status.emplace_back(CARD_TEMPLATE_BORDER)
                                           : status.emplace_back(makeMinion(player.getMyBoard().graveyardTop()));
    return status;
}
//-----------------------------------Graphic------------------------------------
Graphic::Graphic(std::unique_ptr<Xwindow> win):win{std::move(win)}{}

void Graphic::displayMinion(Minion &minion) {
    Xwindow xw = Xwindow{};
    card_template_t m = makeMinion(minion);
    int y = 10;
    for(auto &str : m){
        xw.drawString(10, y, str, Xwindow::Black);
        y += 15;
    }
    if(minion.hasEnchant()){
        std::vector<card_template_t> Store;
        for(int i = 0; i < minion.numOfEnchant(); i++){
            if(Store.size() == 5){
                draw(Store, 0, xw);
                Store.clear();
            }
            Store.emplace_back(makeEnchantment(minion.getEnchant(i)));
        }
        if(Store.size() <= 5) draw(Store, false, xw);
    }
    std::this_thread::sleep_for(15s);
}

void Graphic::displayHand(Player &player) {
    vector<card_template_t> hand = convertHand(player);
    draw(hand, 600, *win);
}

void Graphic::displayPlayer(Player &player, int num) {
    vector<card_template_t> minions = convertMinions(player);
    vector<card_template_t> status = convertStatus(player);
    if(num == 1){
        draw(status, 20, *win);
        draw(minions, 130, *win);
    }else{
        draw(minions, 340, *win);
        draw(status, 450, *win);
    }
}

void Graphic::display(Player &p1, Player &p2, int round) {
    // Top Border
    const int sizeOfBoard = 165;
    string str = EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for(int i = 0; i < sizeOfBoard; i++) {
        str += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    str += EXTERNAL_BORDER_CHAR_TOP_RIGHT;
    win->drawString(10, 10, str, Xwindow::Black);

    displayPlayer(p1, 1);

    int y = 240;
    for(auto &row : CENTRE_GRAPHIC){
        win->drawString(11, y, row, Xwindow::Black);
        y += 10;
    }
    displayPlayer(p2, 2);

    // Bottom Border
    str = EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for(int i = 0; i < sizeOfBoard; i++){
        str += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    str += EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
    win->drawString(11, 560, str, Xwindow::Black);

    if(round % 2){
        displayHand(p1);
    }else{
        displayHand(p2);
    }
}

//void Graphic::init(Player &p1, Player &p2) {
//    display(p1, p2, 0);
//}

void Graphic::draw(vector<card_template_t> &vec, int y, Xwindow &xw){
    vector<string> v = convert(vec, true);
    for(auto &str : v) {
        xw.drawString(11, y, str, Xwindow::Black);
        y = y + 10;
    }
}

void Graphic::clear() {
    win->fillRectangle(0, 0, 1050, 800, Xwindow::White);
}
//----------------------------------------Text--------------------------------------
void Text::print(card_template_t t1) {
    for(auto &it: t1){
        std::cout << it << endl;
    }
}

void Text::print(vector<card_template_t> &vec, bool printBoard) {
    vector<string> v = convert(vec, printBoard);
    for(auto &str : v) {
        std::cout << str << endl;
    }
}

void Text::displayMinion(Minion &minion) {
    print(makeMinion(minion));
    if(minion.hasEnchant()) {
        std::vector<card_template_t> Store;
        for (int i = 0; i < minion.numOfEnchant(); i++) {
            if (Store.size() == 5) {
                print(Store, false);
                Store.clear();
            }
            Store.emplace_back(makeEnchantment(minion.getEnchant(i)));
        }
        if (Store.size() <= 5) print(Store, false);
    }
}

void Text::displayHand(Player &player) {
    vector<card_template_t> t = convertHand(player);
    print(t, false);
}

void Text::displayPlayer(Player &player, int num){
    vector<card_template_t> status = convertStatus(player);
    vector<card_template_t> minions = convertMinions(player);
    if(num == 1){
        print(status, true);
        print(minions, true);
    }else{
        print(minions, true);
        print(status, true);
    }
}

void Text::display(Player &p1, Player &p2, int round) {
    // Top Border
    const int sizeOfBoard = 165;
    std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for(int i = 0; i < sizeOfBoard; i++) std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

    std::vector<std::string> c = CENTRE_GRAPHIC;
    displayPlayer(p1, 1);
    for(auto &row : CENTRE_GRAPHIC){
        std::cout << row << std::endl;
    }
    displayPlayer(p2, 2);

    // Bottom Border
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for(int i = 0; i < sizeOfBoard; i++)  std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

void Text::clear() {}

card_template_t View::makeMinion(Minion &minion){
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

card_template_t View::makeEnchantment(Enchantment &enchantment){
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

card_template_t View::makeSpell(Spell &spell){
    //display_spell(std::string name,int cost,std::string desc)
    return display_spell(
            spell.getName(),
            spell.getCost(),
            spell.getDescription());
}
card_template_t View::makeRitual(Ritual &ritual){
    //display_ritual(std::string name,int cost,int ritual_cost,std::string ritual_desc,
    // int ritual_charges)
    return display_ritual(
            ritual.getName(),
            ritual.getCost(),
            ritual.getActiveCost(),
            ritual.getDescription(),
            ritual.getCharges());
}

card_template_t View::makePlayer(Player &player) {
    return display_player_card(
            player.getID(),
            player.getName(),
            player.getLife(),
            player.getMagic());
}

