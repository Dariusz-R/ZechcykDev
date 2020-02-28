
#include <iostream>
#include "Choice.h"
#include <cmath>
#include <time.h>
#include "Text.h"
#include "GameWarsow.h"
#include "GameColour.h"
#include "GameMisery.h"
#include "GameDurh.h"
#include "Auction.h"
#include <vector>








class Run
{   
//PRIVATE DATA MEMBERS
    Card const  deck_pattern[24];        //  DECK OF CONSTANT CARDS
    Card const* deck_pointers[24];       //  24 pointers to constant cards from deck_pattern - they are copied by other classes to read constant cards
	short game_type;                     //  Number specyfing which type of game will be played
	Player players[3];                   //  Players who will play the game
	short player_who_begins_the_auction; //  Number specyfing which player will start the auction - he will be the first who will have oportunity to made any decision
// METHODS********************************************************************************************************************************
public:
    Run();
    void run_general();                  //  Function responsible for managing the overall program funcionality
private:
    void select_language();              
    void start();
    void meet_players();
    void players_introduction();                           
    void shuffle_cards() ;
    void give_cards_to_players() ;
};
