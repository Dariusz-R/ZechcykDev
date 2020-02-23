#ifndef PLAYER
#define PLAYER

#include <iostream>
#include "Card.h"
#include <vector>


using namespace std;

class Player
{   //PRIVATE DATA MEMBERS
    string name;
    short  trick_points, game_points ;
    vector <const Card*> player_cards;
    short last_thrown_card;
    short const SORT_LIKE_FOR_MISERY;

    //PUBLIC METHODS ORDERED BY THE SEQUENCE OF THE APPLICATION
public:
    void show_me_what_I_can_throw(vector<short>);
    Player();
    void name_player(short);
    string get_name();
    void take_card( Card const *);
    void sort_cards(short);
    void show(short, string);

    void throw_out_all_remain_cards();

	void add_game_points(short);
	short get_game_points();

    void add_trick_points(short);
    short get_trick_points();
    void reset_trick_points();

    vector<short> how_many_card_in_colour_i_have(short);
        
    Card const * share_card(short);
    //int choice_game_type(short&) ;
    
    //short other_player_asked(short*, short&) ;
    //vector <short> which_card_you_may_throw(Card&, short = NULL);
    Card const* which_card_I_throw(vector<short> = {});
    //Card which_card_you_throw(short, Card&, string, short = NULL);
    //Card which_card_you_throw(short, Card&, Card&, string, short = NULL);
    void erase_thrown_card();

};

#endif