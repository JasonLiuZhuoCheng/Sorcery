#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <string>
#include <unordered_set>

#include "Board.h"
#include "Player.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "window.h"
#include "View.h"
using namespace std;

bool checkValidInputHand(Player &player, int i){
    return (i <= player.handSize());
}

bool checkValidInputMinion(Player &player, int i){
    return (i <= player.getMyBoard().numberOfMinions());
}

void endOfGame(bool quit, Player &p1, Player &p2){
    if(quit) { cout << "You have quitted the game, no player wins" << endl; }
    else if(p1.isDead()){
        //player 1 is dead and player 2 wins
        cout << "player 2 has win! " << p1.getName() << " is dead!"  << endl;
    }
    else if(p2.isDead()){
        //player 2 is dead and player 1 wins
        cout << "player 1 has win! " << p2.getName() << " is dead!" << endl;
    }
}

void startTurn(Player &player, Player &otherPlayer, int round){
    cout << "startTurn Function called" << endl;
    player.drawCard(); // Draws one card at begin of turn

    // Resets active player's minions' actionValue
    for(int i = 0; i < player.getMyBoard().numberOfMinions(); i++){
        player.getMyBoard().getMinion(i).resetActionValue();
    }

    // Resets active player's magic for the current turn
    player.setMagic((round - 1)/2 + 3);
    player.getMyBoard().notifyAll(Card::Trigger::START_OF_TURN, player);
}

//Make a deck from the file
void makeDeck(string deckPath, Player &p, bool featureMode) {
    ifstream fin{deckPath};
    string name;

    //loop to make a deck
    while (getline(fin, name, '\n')) {
        //Spell
        if(name == "Banish"){ p.addToDeck(make_unique<Banish>()); cout << "Banish is made" << endl; }  //Banish has been made
        else if(name == "Unsummon"){ p.addToDeck(make_unique<Unsummon>());  cout << "Unsummon is made" << endl; } // Unsummon has been made
        else if(name == "Recharge"){ p.addToDeck(make_unique<Recharge>());cout << "Recharge is made" << endl; } //Recharge has been made
        else if(name == "Disenchant"){ p.addToDeck(make_unique<Disenchant>());cout << "Disenchant is made" << endl; } // Disenchant has been made
        else if(name == "Raise Dead"){ p.addToDeck(make_unique<RaiseDead>()); cout << "Raise Dead is made" << endl;} // Raise Dead has been made
        else if(name == "Blizzard"){ p.addToDeck(make_unique<Blizzard>()); cout << "Blizzard is made" << endl;}// Blizzard has been made
        else if(name == "Arcane Intellect" && featureMode) {p.addToDeck(make_unique<ArcaneIntellect>()); cout << "Arcane Intellect is made" << endl;}//Arcane Intellect has been made
        //Minions
        else if(name == "Air Elemental"){ p.addToDeck(make_unique<AirElemental>()); cout << "Air Elemental is made" << endl;}// Air Elemental has been made
        else if(name == "Earth Elemental"){ p.addToDeck(make_unique<EarthElemental>()); cout << "Earth Elemental is made" << endl;}// Earth Elemental has been made
        else if(name == "Bone Golem"){ p.addToDeck(make_unique<BoneGolem>()); cout << "Bone Golem is made" << endl;}// Bone Golem has been made
        else if(name == "Fire Elemental"){ p.addToDeck(make_unique<FireElemental>()); cout << "Fire Elemental is made" << endl;} //Fire Elemental Elemental has been made
        else if(name == "Potion Seller"){ p.addToDeck(make_unique<PotionSeller>()); cout << "Potion Seller is made" << endl;} //Potion Seller has been made
        else if(name == "Novice Pyromancer"){ p.addToDeck(make_unique<NovicePyromancer>()); cout << "Novice Pyromancer is made" << endl;} //Novice Pyromancer has been made
        else if(name == "Apprentice Summoner"){ p.addToDeck(make_unique<ApprenticeSummoner>()); cout << "Apprentice Summoner is made" << endl;} //Apprentice Summoner has been made
        else if(name == "Master Summoner"){ p.addToDeck(make_unique<MasterSummoner>());  cout << "Master Summoner is made" << endl;} //Master Summoner has been made
        //Enchantments
        else if(name == "Giant Strength"){ p.addToDeck(make_unique<GiantStrength>()); cout << "Giant Strength is made" << endl;} //Giant Strength has been made
        else if(name == "Enrage"){ p.addToDeck(make_unique<Enrage>()); cout << "Enrage is made" << endl;}//Enrage has been made
        else if(name == "Haste"){ p.addToDeck(make_unique<Haste>()); cout << "Haste is made" << endl;}//Haste has been made
        else if(name == "Magic Fatigue"){ p.addToDeck(make_unique<MagicFatigue>()); cout << "Magic Fatigue is made" << endl;}//Magic Fatigue has been made
        else if(name == "Silence"){ p.addToDeck(make_unique<Silence>()); cout << "Silence is made" << endl;}//Silence has been made
        else if(name == "Hunter's Mark" && featureMode){p.addToDeck(make_unique<HunterMark>()); cout << "Hunter's Mark is made" << endl;}//Hunter's mark is made
        //Ritual
        else if(name == "Dark Ritual"){ p.addToDeck(make_unique<DarkRitual>()); cout << "Dark Ritual is made" << endl;}//Dark Ritual has been made
        else if(name == "Aura of Power"){ p.addToDeck(make_unique<AuraOfPower>()); cout << "Aura of Power is made" << endl;}//Aura of Power has been made
        else if(name == "Standstill"){ p.addToDeck(make_unique<Standstill>()); cout << "Standstill is made" << endl;}//Standstill has been made
        else if(name == "Acidic Swamp" && featureMode) {p.addToDeck(make_unique<AcidicSwamp>()); cout << "Acidic is made" << endl;}//Acidic Swamp has been made
        else if(name == "Wolf Rider" && featureMode) {p.addToDeck(make_unique<Wolfrider>()); cout << "Wolf Rider is made" << endl;}//Wolf Rider has been made
        else if(name == "Gnomish Inventor" && featureMode) {p.addToDeck(make_unique<GnomishInventor>()); cout << "Gnomish Inventor is made" << endl;} //Gnomish Inventor has been made
    }
     cout << endl;
}

// Use for displaying "help.txt"
void displayFile(const string &path) {
    ifstream fin(path);
    string s;
    while(getline(fin, s)){
        cout << s << endl;
    }
}

void playGame(istream &in, Player &p1, Player &p2, bool testMode, bool graphicMode, bool featureMode) {
    // Use to track cards that can play without a target
    unordered_set<string> noTargetCards =
            {"Recharge", "Raise Dead", "Blizzard", "Air Elemental", "Earth Elemental", "Bone Golem", "Fire Elemental",
             "Potion Seller", "Novice Pyromancer", "Apprentice Summoner", "Master Summoner", "Dark Ritual",
             "Aura Of Power", "Standstill","Acidic Swamp","Wolf Rider","Gnomish Inventor","Arcane Intellect"};
    // Use to track cards that must play on a target
    unordered_set<string> targetCards =
            {"Banish", "Unsummon", "Disenchant", "Giant Strength", "Enrage", "Haste", "Magic Fatigue", "Silence","Hunter's Mark"};

    string input; // only use with cin for input purpose
    int i, j, p; // only use with cin for input purpose
    bool quit = false; // if the player choose to quit the game so no winner
    bool startGame = true;
    vector<unique_ptr<View>> view;//vector for different displays



    cout << "Welcome to sorcery, type help to see the commands" << endl;
    cout << "Please indicate both players' name" << endl;

    //get the names of the players
    in >> input;
    p1.setName(input);
    in >> input;
    p2.setName(input);

    if(!testMode) {
        //shuffle the deck from the players, disable in -testing mode
        p1.shuffle();
        p2.shuffle();
    }

   //Draws 5 cards at the start of game
    for(int count = 0; count < 5; count++){
        p1.drawCard();
        p2.drawCard();
    }

    view.emplace_back(make_unique<Text>());
    if(graphicMode) {
        unique_ptr<Graphic> graphic = make_unique<Graphic>(make_unique<Xwindow>(1050, 800));
        view.emplace_back(std::move(graphic));
    }

    int round = 0; //count the # of rounds the game has occur, use to track which player is active player
    while ((!p1.isDead() && !p2.isDead()) && !quit) {
        //Game Loop
        round++;

        Player &player = round % 2 ? p1 : p2; // This is the active player in current round
        Player &other = (&player == &p1) ? p2 : p1;

        cout << "Round Number: " << round  << " Active Player: " << player.getName() << endl;
        startTurn(player, other, round);

        if(featureMode&& (player.getMagic()>10)){
                player.setMagic(10);
        }

        while((!p1.isDead() && !p2.isDead()) && !quit) {
            if(graphicMode) {
                view.at(1)->clear();
                view.at(1)->display(p1, p2, round);
            }
            //loop for a round of one player
            string cmd;
            if (getline(in, input)) {}
            else if(&in != &cin && getline(cin, input)) {}
            else { break; }

            istringstream iss(input);
            iss>>cmd;

            if (cmd == "help") {
                 displayFile("help.txt");
            } else if (cmd == "end") {
                cout << "END OF TURN" << endl;
                player.getMyBoard().notifyAll(Card::Trigger::END_OF_TURN, player);
                break;
            } else if (cmd == "quit") {
                quit = true;
            } else if (cmd == "draw" && testMode) {
                cout << "draw is called and it is in testMode" << endl;
                player.drawCard();
            } else if (cmd == "discard" && testMode) {
                cout << "Discard is called and you are in testMode" << endl;
                iss >> i;
                player.discardCard(i - 1);
            } else if (cmd == "attack") {
                iss >> i;
                if(!checkValidInputMinion(player, i)){
                    cout << "ERROR The " << i << "'s MINION DOES NOT EXIT, CANNOT ATTACK" << endl;
                    continue;
                }
                if(iss >> j){
                    if(!checkValidInputMinion(other, j)){
                        cout << "ERROR: Other player's Minion" << j  << " DOES NOT EXIT, CANNOT BE ATTACKED"  << endl;
                        continue;
                    }
                    player.getMyBoard().getMinion(i - 1)
                    .attack(other.getMyBoard().getMinion(j - 1), player, other);
                    cout << "Your Minion "<< i << " attacked " << other.getName() << "'s Minion" << j << endl;
                }else{
                    player.getMyBoard().getMinion(i - 1).attack(other);
                    cout << "Your Minion "<< i << " attacked " << other.getName() << endl;
                }
            } else if (cmd == "play") {
                iss >> i;
                if(!checkValidInputHand(player, i)){
                    cout << "ERROR: The " << i << "'s card in you hand DOES NOT EXIT, CANNOT PLAY" << endl;
                    continue;
                }
                Card &playedCard = player.getCard(i - 1);
                if(playedCard.getCost() > player.getMagic()){
                    cout << "Oops, you do not have enough magic to play this card" << endl;
                    if(testMode && dynamic_cast<Spell *>(&playedCard)){
                        cout << "Testing Mode: Still allow to play this spell" << endl;
                        player.setMagic(playedCard.getCost());
                    }else{
                        continue;
                    }
                }
                bool success = playedCard.canPlay(player) &&
                        noTargetCards.find(playedCard.getName()) != noTargetCards.end();

                //PLAYER HAS ENOUGH MAGIC TO PLAY THIS CARD
                if(iss >> p){  // play i p t
                    //uses on Enchantment, and Spell(Banish, Unsommon, Dischantment)
                    if(p != 1 && p!= 2){
                        cout << "ERROR: VALUE FOR p NEED TO BE 1 OR 2" << endl;
                        continue;
                    }
                     Player &targetPlayer = (p == 1) ? p1 : p2;
                     success = playedCard.canPlay(targetPlayer) &&targetCards.find(playedCard.getName()) != noTargetCards.end();
                     if(iss >> j) { // play i p t(number), target on a Minion
                        //uses on Enchantments, Spell(Banish, Unsommon, Dischantment)
                        if(!checkValidInputMinion(targetPlayer, j)) {
                            cout << "ERROR: Other player's Minion" << j << " DOES NOT EXIT, CANNOT BE PLAYED ON" << endl;
                            continue;
                        }
                        Card &targetCard = targetPlayer.getMyBoard().getMinion(j - 1);
                        if (success) {
                            player.moveEnchantmentToMinion(i - 1, targetCard);
                            playedCard.effect(player, targetPlayer, other, targetCard);
                        }
                    } else{// play i p t(r)
                         cout << "Play a ritual" << endl;
                        //uses on Banish
                        Card &targetRitual = targetPlayer.getMyBoard().getRitual();
                        if (success) {
                            player.moveEnchantmentToMinion(i - 1, targetRitual);
                            playedCard.effect(player, targetPlayer, other, targetRitual);
                        }
                    }
                } else{ //play i
                    //play Minion, Ritual, Spell(Recharge, RaiseDead, Blizzard)
                    if(success) {
                        player.moveCardToBoard(i - 1);
                        playedCard.effect(player, other);
                    }
                }
                if(!success) {
                    cout << "Did not play this card successfully" << endl;
                } else {
                    player.mutateMagic(-playedCard.getCost());
                    cout << "Played Card: " <<  playedCard.getName() << endl;
                }
            } else if (cmd == "use") {
                cout << "use ability is called" << endl;
                iss >> i;
                if(!checkValidInputMinion(player, i)){
                    cout << "ERROR The " << i << "'s MINION DOES NOT EXIT, CANNOT USE ABILITY" << endl;
                    continue;
                }
                Minion &playedMinion = player.getMyBoard().getMinion(i - 1);
                if(playedMinion.getMagic() > player.getMagic()){
                    cout << "Oops, you do not have enough magic to use the ability of this minion" << endl;
                    if(testMode){
                        cout << "Testing Mode: Still allow to use this abilitiy" << endl;
                        player.setMagic(playedMinion.getMagic());
                    }else{
                        continue;
                    }
                }
                bool success = playedMinion.canUseAbility(player);

                if(iss >> p){// use i p t
                    //for Novice Pyromancer
                    if(p!= 1 && p!=2){
                        cout << "ERROR: VALUE FOR p NEED TO BE 1 OR 2" << endl;
                        continue;
                    }
                    iss >> j;

                    Player &targetPlayer = (p == 1) ? p1 : p2;
                    if(!checkValidInputMinion(targetPlayer, j)){
                        cout << "ERROR: MINION" << j << " DOES NOT EXIT, CANNOT USE ABILITY ON IT" << endl;
                        continue;
                    }
                    Minion &targetMinion = targetPlayer.getMyBoard().getMinion(j - 1);
                    if(success){
                        playedMinion.ability(player, other, targetPlayer, targetMinion);
                        player.mutateMagic(-playedMinion.getMagic());//mutate magic
                    }
                }else{//use i
                    //for Apprentice Summoner and Master Summoner
                    if(success){
                        playedMinion.ability(player, other);
                        player.mutateMagic(-playedMinion.getMagic());//mutate magic
                    }
                }
            } else if (cmd == "inspect") {
                iss >> i;
               //loop through to output the interface
                for(auto &it: view){
                    cout << "Displaying inspected Minion" << endl;
                    it->displayMinion(player.getMyBoard().getMinion(i - 1));
                }
            } else if (cmd == "hand") {
                //displays the hand of an active player
                for(auto &it: view){
                    it->displayHand(player);
                }
            } else if (cmd == "board") {
                for(auto &it: view){
                    cout << "";
                    it->display(p1,p2, round);
                }
            }else{
                if(startGame){
                    startGame = false;
                }else{
                    cout << "Unrecognized command. Enter help for instructions" << endl;
                }
            }
        }
    }
    endOfGame(quit, p1, p2);
}

int main(int argc, char *argv[]) {
    auto p1 = make_unique<Player>(1);
    auto p2 = make_unique<Player>(2);

    //5.2 all the command line arguments
    string initPath;
    bool readFile = false;
    string deckPath1 = "default.deck";
    string deckPath2 = "default.deck";
    bool testMode = false;
    bool graphicMode = false;
    bool featureMode = false;

    //for loop to do the arguments
    for (int i = 0; i < argc; ++i) {
        string argument =argv[i];
        if (argument == "-deck1") { //player1's deck < filename
            deckPath1 = argv[++i];
            cout << "player1 gets deck from " << deckPath1  << endl;
        } else if (argument == "-deck2") { //player2's deck < filename
            deckPath2 = argv[++i];
            cout << "player2 gets deck from " << deckPath2  << endl;
        } else if (argument == "-init") {//want to read commands first from a file
            readFile = true;
            initPath = argv[++i];
            cout << "The initial command are from "  << initPath << endl;
        } else if (argument == "-testing") {
            testMode = true;
            cout << "You are in Testing Mode" << endl;
        } else if (argument == "-graphics") {
            graphicMode = true;
            cout << "You are in Graphic Mode" << endl;
        } else if (argument == "-feature"){
            featureMode = true;
            cout << "You are in Extra Feature Mode" << endl;
        }
    }

    makeDeck(deckPath1, *p1, featureMode);
    makeDeck(deckPath2, *p2, featureMode);

    ifstream f{initPath};
    if (readFile) {
        playGame(f, *p1, *p2, testMode, graphicMode, featureMode);
    } else {
        playGame(cin, *p1, *p2, testMode, graphicMode, featureMode);
    }
}

