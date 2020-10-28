#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <map>
#include <string>

char waitForCharInput( int mili_seconds );
void clearscreen();
void printTime(int day, int month,int year, std::map<int,std::string> &map_month);
void gotoxy(int x, int y);
void SetConsoleDefinitions(DWORD &fdwMode,HANDLE &hin,HANDLE &hout, CONSOLE_CURSOR_INFO &cci);

#endif