#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <memory>
#include <typeindex>

#include "Board.h"
#include "Player.h"
#include "Card/Spell.h"
#include "Card/Ritual.h"
#include "Card/Enchantment.h"
#include "Display.h"
using namespace std;

void endOfGame(bool quit, Player &p1, Player &p2){
    if(quit) { cout << "the player has quitted the game" << endl; }
    else if(p1.isDead()){
        //player 1 is dead and player 2 wins
        cout << "player 2 has win!" << endl;
    }
    else if(p2.isDead()){
        //player 2 is dead and player 1 wins
        cout << "player 1 has win!" << endl;
    }
}

void startTurn(Player &player, Player &otherPlayer, int round){
    cout << "startTurn Function called" << endl;
    // Resets all active player's minion actionValue
    for(int i = 0; i < player.getMyBoard()->numberOfMinions(); i++){
        player.getMyBoard()->getMinion(i).resetActionValue();
    }
    player.setMagic((round - 1)/2 + 3);
    player.getMyBoard()->notifyAll(Card::Trigger::START_OF_TURN, player);
    //otherPlayer.getMyBoard()->notifyAll(Card::Trigger::START_OF_TURN, player);
}

//Make a deck from the file
void makeDeck(string deckPath, Player &p) {
    ifstream fin{deckPath};
    string name;

    //loop to make a deck
    while (getline(fin, name)) {
        //Spell
        if(name == "Banish"){ p.addToDeck(make_unique<Banish>());  cout << "Banish has been made"<< endl; }
        else if(name == "Unsummon"){ p.addToDeck(make_unique<Unsummon>());  cout << "Unsommon has been made"<< endl;}
        else if(name == "Recharge"){ p.addToDeck(make_unique<Recharge>());  cout << "Recharge has been made"<< endl;}
        else if(name == "Disenchant"){ p.addToDeck(make_unique<Disenchant>());  cout << "Disenchant has been made"<< endl;}
        else if(name == "Raise Dead"){ p.addToDeck(make_unique<RaiseDead>());   cout << "Raise Dead has been made"<< endl;}
        else if(name == "Blizzard"){ p.addToDeck(make_unique<Blizzard>());  cout << "Blizzard has been made"<< endl;}
        //Minions
        else if(name == "Air Elemental"){ p.addToDeck(make_unique<AirElemental>());  cout << "Air Elemental has been made"<< endl;}
        else if(name == "Earth Elemental"){ p.addToDeck(make_unique<EarthElemental>());  cout << "Earth Elemental has been made"<< endl;}
        else if(name == "Bone Golem"){ p.addToDeck(make_unique<BoneGolem>()); cout << "Bone Golem has been made"<< endl;}
        else if(name == "Fire Elemental"){ p.addToDeck(make_unique<FireElemental>()); cout << "Fire Elemental Elemental has been made"<< endl;}
        else if(name == "Potion Seller"){ p.addToDeck(make_unique<PotionSeller>()); cout << "Potion Seller has been made"<< endl;}
        else if(name == "Novice Pyromancer"){ p.addToDeck(make_unique<NovicePyromancer>()); cout << "Novice Pyromancer has been made"<< endl;}
        else if(name == "Apprentice Summoner"){ p.addToDeck(make_unique<ApprenticeSummoner>()); cout << "Apprentice Summoner has been made"<< endl;}
        else if(name == "Master Summoner"){ p.addToDeck(make_unique<MasterSummoner>()); cout << "Master Summoner has been made"<< endl;}
        //Enchantments
        else if(name == "Giant Strength"){ p.addToDeck(make_unique<GiantStrength>()); cout << "Giant Strength has been made"<< endl;}
        else if(name == "Enrarge"){ p.addToDeck(make_unique<Enrage>()); cout << "Enrarge has been made"<< endl;}
        else if(name == "Haste"){ p.addToDeck(make_unique<Haste>()); cout << "Haste has been made"<< endl;}
        else if(name == "Magic Fatigue"){ p.addToDeck(make_unique<MagicFatigue>()); cout << "Magic Fatigue has been made"<< endl;}
        else if(name == "Silence"){ p.addToDeck(make_unique<Silence>()); cout << "Silence has been made"<< endl;}
        //Ritual
        else if(name == "Dark Ritual"){ p.addToDeck(make_unique<DarkRitual>()); cout << "Dark Ritual has been made"<< endl;}
        else if(name == "Aura of Power"){ p.addToDeck(make_unique<AuraOfPower>()); cout << "Aura of Power has been made"<< endl;}
        else if(name == "Standstill"){ p.addToDeck(make_unique<Standstill>()); cout << "Standstill has been made"<< endl;}
    }
    cout << endl;
}

void displayFile(const string &path) {
    ifstream fin(path);
    string s;
    while(getline(fin, s)){
        cout << s << endl;
    }
}

void playGame(istream &in, Player *p1, Player *p2, bool testMode, bool graphicMode) {
    string input; // only use with cin for input purpose
    int i, j, p; // only use with cin for input purpose
    bool quit = false; // if the player choose to quit the game so no winner
    vector<unique_ptr<Display>> view;//vector for different displays
    if(graphicMode){
        //Display graphic = new Graphic();
       unique_ptr<Display> graphic = make_unique<Graphic>();
       view.emplace_back(std::move(graphic));
    }

    //display text
    unique_ptr<Display> text = make_unique<Text>();
    view.emplace_back(std::move(text));

    cout << "Welcome to sorcery" << endl;
    cout << "Please indicate both players' name" << endl;

    //get the names of the players
    in >> input;
    p1->setName(input);
    in >> input;
    p2->setName(input);
    //shuffle the deck from the players
    p1->shuffle();
    p2->shuffle();

   //Draws 5 cards at the start of turn
    for(int i = 0; i < 5; i++){
        p1->drawCard();
        cout << p1->getCard(i).getName() << endl;
        p2->drawCard();
    }

    int round = 0; //count the # of rounds the game has occur, use to track which player is active player
    while ((!p1->isDead() && !p2->isDead()) && !quit) {

        //Game Loop
        round++;
        cout << "round" << round << endl;
        Player *player = round % 2 ? p1 : p2; // This is the active player in current round
        Player *other = (player == p1) ? p2 : p1;
        startTurn(*player, *other, round);

        while(!quit) {
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
                cout << "end is called" << endl;
                player->getMyBoard()->notifyAll(Card::Trigger::END_OF_TURN, *player);
                break;
            } else if (cmd == "quit") {
                cout << "quit is called" << endl;
                quit = true;
            } else if (cmd == "draw" && testMode) {
                cout << "draw is called and it is in testMode" << endl;
                player->drawCard();// 5.1.4
            } else if (cmd == "discard" && testMode) {
                cout << "discard is called and it is in testMode" << endl;
                cin >> i;  // 5.1.5
                player->discardCard(i);
            } else if (cmd == "attack") {
                iss >> i;
                cout << "attack is called" << endl;
                if(iss >> j){
                    Minion &myMinion = player->getMyBoard()->getMinion(i);
                    Minion &otherMinion = other->getMyBoard()->getMinion(j);
                    myMinion.attack(otherMinion, *player, *other);
                }else{
                    player->getMyBoard()->getMinion(i).attack(*other);
                }
            } else if (cmd == "play") {
                iss >> i;
                Card &playedCard = player->getCard(i-1);
                cout << "play " <<  playedCard.getName() << endl;
                if(playedCard.getCost() > player->getMagic()){
                    cout << "Do not have enough magic to play this card" << endl;
                     continue;
                }
                bool success = playedCard.canPlay(*player);
                cout << player->getMyBoard()->numberOfMinions();
                cout << success << endl;

                //PLAYER HAS ENOUGH MAGIC TO PLAY THIS CARD
                if(iss >> p){  // play i p t
                    //uses on Enchantment, and Spell(Banish, Unsommon, Dischantment)
                    Player *targetPlayer = (p == 1) ? p1 : p2;
                    if(iss >> j) { // play i p t(number)
                        //uses on Enchantments, Spell(Banish, Unsommon, Dischantment)
                        Card &targetCard = targetPlayer->getMyBoard()->getMinion(j-1);
                        if (success) {
                            player->moveEnchantmentToMinion(i, targetCard);
                            playedCard.effect(*player, *targetPlayer, *other, targetCard);
                            player->mutateMagic(-playedCard.getCost());//mutate magic
                        }
                    }
                    else{// play i p t(r)
                        //uses on Banish
                        Card &targetRitual = targetPlayer->getMyBoard()->getRitual();
                        if (success) {
                            player->moveEnchantmentToMinion(i, targetRitual);
                            playedCard.effect(*player, *targetPlayer, *other, targetRitual);
                            player->mutateMagic(-playedCard.getCost());//mutate magic
                        }
                    }
                }
                else{ //play i
                    //play Minion, Ritual, Spell(Recharge, RaiseDead, Blizzard)
                    if(success) {//The user is able to play this card
                        player->moveCardToBoard(i-1);
                        playedCard.effect(*player, *other);
                        player->mutateMagic(-playedCard.getCost());//mutate magic
                        cout << playedCard.getName() << "is successfully being played" << endl;
                    }
                }

            } else if (input == "use") {
                cout << "use ability is called" << endl;
                iss >> i;
                Minion &playedMinion = player->getMyBoard()->getMinion(i-1);

                if(playedMinion.getMagic() > player->getMagic()){
                    cout << "Do not have enough magic to use the ability of this minion" << endl;
                    continue;
                }
                bool success = playedMinion.canUseAbility(*player);

                if(iss >> p){// use i p t
                    //for Novice Pyromancer
                    iss>>j;
                    Player *targetPlayer = (p == 1) ? p1 : p2;
                    Minion &targetMinion = targetPlayer->getMyBoard()->getMinion(j-1);
                    if(success){
                        playedMinion.ability(*player, *other, *targetPlayer, targetMinion);
                        player->mutateMagic(-playedMinion.getMagic());//mutate magic
                    }
                }else{//use i
                    //for Apprentice Summoner and Master Summoner
                    if(success){
                        playedMinion.ability(*player);
                        player->mutateMagic(-playedMinion.getMagic());//mutate magic
                    }
                }
            } else if (input == "inspect") {
                cin >> i;
               //loop through to output the interface
                for(auto &it: view){
                    it->displayMinion(player->getMyBoard()->getMinion(i));
                }
            } else if (input == "hand") {
                //displays the hand of an active player
                for(auto &it: view){
                    it->displayHand(*player);
                }
            } else if (input == "board") {
                for(auto &it: view){
                    cout << "";
                    it->display(*p1,*p2);
                }
            }
        }
    }
    endOfGame(quit, *p1, *p2);
}

int main(int argc, char *argv[]) {
    auto *p1 = new Player{1};
    auto *p2 = new Player{2};

    //5.2 all the command line arguments
    int numArgs = argc - 1;
    string initPath;
    bool readFile = false;
    string deckPath1 = "default.deck";
    string deckPath2 = "default.deck";
    bool testMode = false;
    bool graphicMode = false;


    //for loop to do the arguments
    for (int i = 0; i < numArgs; ++i) {
        string argument =argv[i];
        cout << argument << " arugument got" << endl;
        if (argument == "-deck1") { //player1 uses another deck
            cout << "player1 gets deck from another file" << endl;
            deckPath1 = argv[++i];
        } else if (argument == "-deck2") { //player2's deck < filename
            cout << "player2 gets deck from another file" << endl;
            deckPath2 = argv[++i];
        } else if (argument == "-init") {//want to read commands first from a file
            cout << "init mode" << endl;
            readFile = true;
            initPath = argv[++i];
        } else if (argument == "-testing") {
            cout << "testing mode" << endl;
            testMode = true;
        } else if (argument == "-graphics") {
            graphicMode = true;
            cout << "graphic mode" << endl;
        }
    }

    makeDeck(deckPath1, *p1);
    makeDeck(deckPath2, *p2);

    ifstream f{initPath};
    if (readFile) {
        playGame(f, p1, p2, testMode, graphicMode);
    } else {
        playGame(cin, p1, p2, testMode, graphicMode);
    }
}
