#ifndef PLAYER
#define PLAYER

#include <iostream>
#include "Card.h"
#include <vector>




class Player
{   //PRIVATE DATA MEMBERS
    std::string name;
    std::string nameShortcut;
    short  trickPoints, gamePoints ;
    std::vector <const Card*> playerCards;
    short lastThrownCardIterator;
    short const SORT_LIKE_FOR_MISERY;

    //PUBLIC METHODS ORDERED CHRONOLOGICALLY
    // METHODS DIVIDED IN THREE PHASES:
    // 1 - begining
    // 2 - auction
    // 3 - game

public:
    // USED IN PHASE 1:
    Player();
    void namePlayer(short);
    std::string getName();
    void takeCardFromTheDeck( Card const *);
    // USED IN PHASE 1 AND 2:
    void sortCards(short);
    // USED IN PHASE 2 AND 3:
    void show(short, std::string);
    void throwOutAllRemainInHandCards();
    void addGamePoints(short);
    short getGamePoints();
    // USED IN PHASE 3:
    Card const* whichCardPlayerThrow(std::vector<short> = {});
    void showMeWhatICanThrow(std::vector<short>);
    std::vector<short> checkHowManyCardsInThrownCardColourPlayerHave(short);
    Card const* shareCard(short);
    bool checkIfPlayerHaveAKingAndQueenInOneColour();
    bool askPlayerIfHeWantToMeld();
    void addTrickPoints(short);
    short getTrickPoints();
    std::string getNameShortcut();
    void resetTrickPoints();
    void eraseThrownCardFromPlayerHand();

};

#endif