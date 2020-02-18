#ifndef PLAYER
#define PLAYER

#include <iostream>
#include "Card.h"
#include <vector>


using namespace std;

class Player
{
    string name;
    short player_number, trick_points, game_points ;


   
 //**********************************************************************************************************************************************
 // ENCAPSULATION PURPOSES FUNCTIONS
public:
    vector <const Card*> player_cards;
    void set_name(string);
    string get_name();

	void add_trick_points(short);
	short get_trick_points();
	void reset_trick_points();


	void add_game_points(short);
	short get_game_points();

	void set_player_number(short);
	short get_player_number();

    void throw_out_all_remain_cards(short = 8);
        
        
        
    Player();
    void name_player(short number);
    void take_card(const Card*) ;
    void sort_cards(string) ;
    void show(short, string) ;
    //int choice_game_type(short&) ;
    
    //short other_player_asked(short*, short&) ;
    //vector <short> which_card_you_may_throw(Card&, short = NULL);
    //Card compare_two(Card&, Card&);
    //Card which_card_you_throw(short, short = NULL);
    //Card which_card_you_throw(short, Card&, string, short = NULL);
    //Card which_card_you_throw(short, Card&, Card&, string, short = NULL);
    //void destroy_thrown_card();

};

#endif