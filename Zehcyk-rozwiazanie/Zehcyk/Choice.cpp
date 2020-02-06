#include <iostream>
#include "Choice.h"
#include <fstream>
#include <cstdlib>
#include <Windows.h>
#include "Player.h"

using namespace std;
void name_players();

void Choice::first_menu()
{
    fstream menu1;
    menu1.open("Tekst_Menu1.txt", ios::in);

    if( menu1.good() == false )
    {
        cout << "Blad podczas otwierania skryptu do menu glownego" << endl ;
        exit(0);
    }

    string linia ;

    while( getline( menu1, linia ))
    {
        cout << linia << endl ;
    }

    menu1.close();

    cout <<"\tTwoja odpowiedz: ";
    short want_to_play ;
    bool loop_choice ;

    do
    {

        loop_choice = false ;
        cin >> want_to_play ;
        cout << endl << endl ;

        switch ( want_to_play )
        {
            case 1 :
                cout << "To gramy!" << endl ;
                Sleep(1000);
                loop_choice = true;
                system("CLS");

            break ;

            case 2 :
                cout << "No to nie gramy! Czesc!" << endl ;
                exit(0);
                break ;

            default :
                cout << "Dokonales wyboru, ktorego nie uwzglednia program. Sprobuj ponownie." << endl ;
                break ;
        }

    }while(loop_choice == false);
}


