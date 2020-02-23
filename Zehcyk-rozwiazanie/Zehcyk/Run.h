
#include <iostream>
#include "Choice.h"
#include "Deck.h"
#include <cmath>
#include <time.h>
#include "Text.h"
#include "Game_Warsow.h"
#include "Game_Colour.h"
#include "Auction.h"
#include <vector>






using namespace std ;

class Run
{   
//PRIVATE DATA MEMBERS
    Card const  deck_pattern[24];               //  DECK OF CONSTANT CARDS
    Card const* deck_pointers[24];              //  24 pointers to constant cards from deck_pattern - they are copied by other classes to read constant cards
	short game_type;                            //  Number specyfing which type of game will be played
	Player players[3];                          //  Players who will play the game
	short player_who_begins_the_auction;        //  Number specyfing which player will start the auction - he will be the first who will have oportunity to made any decision
                                                //  Number specyfing which player will throw his card as a first and who will play against other two other players
                                                    // If players are playing warsow - it will be id of the person who as a last increased the stake

// METHODS********************************************************************************************************************************
public:
    



    Run();
    void run_general();                         //  Function responsible for managing the overall program funcionality
private:
    void select_language();                     
    void start();
    void meet_players();
    void who_plays();                           
    void shuffle_cards() ;
    void give_cards_to_players() ;
    //void run_game()
};
