//#ifndef RUN
//#define RUN

#include <iostream>
#include "Choice.h"
//#include "Player.h"
#include "Deck.h"
#include <cmath>
#include <time.h>
#include "Functions.h"
#include "Game_Warsow.h"
#include "Game_Colour.h"






using namespace std ;

class Run
{
public:
    short which_game = NULL, which_player = NULL, which_trumph = NULL, warsow = NULL, final_decision = NULL; 

        void start() ;
        void meet_players() ;
        void create_cards() ;
        void shuffle_cards() ;
        void give_cards_to_players() ;
        short which_gametype() ;
        void run_game(short);
        void check_if(short&, short, short);
        //void contra();
        //void contra_reset();




};
//#endif