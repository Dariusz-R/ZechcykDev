#include <iostream>
#include "Run.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>  
#include <cstdio>

using namespace std;
short contra_counter = NULL;

int main()
{
    srand((time(NULL)));
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 620, 600, TRUE);
    Run zechcyk ;
    zechcyk.run_general();



    return 0;
}
