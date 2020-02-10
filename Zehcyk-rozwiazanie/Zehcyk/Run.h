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
    private:
    short game_type = NULL;
    short which_player = NULL;
    public:
    short warsow = NULL;
    Player players[3];
        
    void set_game_type(short);
    short* get_game_type_pointer();
    short  get_game_type();
    //Player[] get_players();
    

    void who_plays();
    string select_language();
        void start(string) ;
        void meet_players() ;
        void create_cards() ;
        void shuffle_cards() ;
        void give_cards_to_players() ;

        short which_gametype() ;
        void run_game(short);
        void check_if(short&, short, short);




};
