
#include <iostream>
#include "Choice.h"
#include "Deck.h"
#include <cmath>
#include <time.h>
#include "Text.h"
#include "Game_Warsow.h"
#include "Game_Colour.h"
#include "Auction.h"






using namespace std ;

class Run
{   
    private:
    short game_type = NULL;
    short which_player = NULL;
    Player players[3];
    public:
    short warsow = NULL;
    Card deck_pattern[24];
    Card deck_temp[24];
   
    void run_general();
    void set_game_type(short);
    short* get_game_type_pointer();
    short  get_game_type();
    //Player[] get_players();
    

    void who_plays();
    void select_language();
    void start() ;
    void meet_players() ;
    void create_cards() ;
    void shuffle_cards() ;
    void give_cards_to_players() ;

        
        //void run_game(short);
        //void check_if(short&, short, short);




};
