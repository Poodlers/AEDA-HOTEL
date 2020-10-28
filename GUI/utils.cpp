#include "utils.h"
#include <iostream>
#include <conio.h>

using namespace std;

char waitForCharInput( int mili_seconds ){
    int time_elapsed = 0;
    char c = '_'; //default return
    while( time_elapsed <= mili_seconds ) {
        if( _kbhit() ) { 
            c = _getch(); 
            break; 
        }
        Sleep(10); 
        time_elapsed += 10; 
    }
    return c;
}

void SetConsoleDefinitions(DWORD &fdwMode,HANDLE &hin,HANDLE &hout, CONSOLE_CURSOR_INFO &cci){
    cci.dwSize = 25;
    cci.bVisible = FALSE;
    fdwMode = ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hin, fdwMode);
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hin, fdwMode);
    SetConsoleCursorInfo(hout, &cci);
    SetConsoleMode(hin, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
}

void printTime(int day, int month,int year, map<int,string> &map_month){
    gotoxy(100,0);
    cout << "Current Time: ";
    gotoxy(100,1);
    cout << "                                            ";
    gotoxy(100,1);
    cout << day << " " << map_month[month] << " " << year;

}

void clearscreen(){ 
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = (csbi.dwSize.X) * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
    return;
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};