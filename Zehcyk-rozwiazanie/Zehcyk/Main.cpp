#include <iostream>
#include "Run.h"

using namespace std;
short contra_counter = NULL;
void contra()
{
    contra_counter++;
}

void contra_reset()
{
    contra_counter = NULL;
}

int main()
{
    Run zechcyk ;
    zechcyk.start(zechcyk.select_language()) ; // Tworzy menu i pyta czy chcesz grac
    zechcyk.meet_players() ;
    zechcyk.create_cards() ;
    zechcyk.shuffle_cards() ;
    zechcyk.give_cards_to_players() ;
    zechcyk.run_game(zechcyk.which_gametype());


    return 0;
}
