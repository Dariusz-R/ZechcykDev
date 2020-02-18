
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
    private:
        short game_type;
        short which_player;
    Player players[3];
    short first_player_this_round;
    public:
    const Card  deck_pattern[24];
    const Card* deck_pointers[24];

    //static vector <Card> deck_temp;
   
    Run();
    void run_general();
    void set_game_type(short);
    short* get_game_type_pointer();
    short  get_game_type();
    void copy_deck_pointers();
    //Player[] get_players();
    

    void who_plays();
    void select_language();
    void start() ;
    void meet_players() ;
    void shuffle_cards() ;
    void give_cards_to_players() ;

        
        //void run_game(short);
        //void check_if(short&, short, short);




};
