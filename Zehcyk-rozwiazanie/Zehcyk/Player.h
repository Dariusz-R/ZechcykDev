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
    vector<Card> player_cards ;
    short choice;


   
 //**********************************************************************************************************************************************
 // ENCAPSULATION PURPOSES FUNCTIONS
public:
    //void set_name(string&);
    string get_name();

	void add_trick_points(short);
	short get_trick_points();
	void reset_trick_points();

	void add_game_points(short);
	short get_game_points();

	void set_player_number(short);
	short get_player_number();

	void set_choice(short);
	short get_choice();
        
        
        
        
        
    void name_player(short number, string);
    void take_card(Card) ;
    void sort_cards() ;
    void show(short, short) ;
    int choice_game_type(short&) ;
    bool ask_or_not () ;
    short other_player_asked(short*, short&) ;
    vector <short> which_card_you_may_throw(Card&, short = NULL);
    Card compare_two(Card&, Card&);
    Card which_card_you_throw(short, short = NULL);
    Card which_card_you_throw(short, Card&, string, short = NULL);
    Card which_card_you_throw(short, Card&, Card&, string, short = NULL);
    void destroy_thrown_card();

};

#endif