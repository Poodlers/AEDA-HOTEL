#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include "../exceptions/exceptions.h"

char waitForCharInput( int mili_seconds );
void clearscreen();
void printTime(int day, int month,int year, std::map<int,std::string> &map_month);
void gotoxy(int x, int y);
void SetConsoleDefinitions(DWORD &fdwMode,HANDLE &hin,HANDLE &hout, CONSOLE_CURSOR_INFO &cci);
void runTime(float rate, std::chrono::steady_clock::time_point begin, double &prev_time, int &day, int &month, int &year, std::map<int,std::string> &map_month);
void fill_month_map(std::map<int,std::string> &map_month);
void getStringInput(std::string& input, int x, int y);
std::string GetNumberInput(int x,int y,bool(*CheckCorrectType)(std::string input));


bool CheckIfInteger(std::string input);
bool CheckIfFloat(std::string input);
void checkIfInteger(std::string input, std::string check);
void checkIfPositiveInteger(std::string input, std::string check);
void checkIfValidPriceOrWage(std::string input, std::string check);

std::ostream& operator<<(std::ostream &o, std::vector<int> v);

void validateNIF(const std::string& NIF,const std:: string& name);

void cleanCinBuffer();

#endif