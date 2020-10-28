#include <iostream>
#include <iomanip>
#include <chrono>
#include <map>
#include "GUI/buttons.h"
#include "GUI/utils.h"

using namespace std;

void fill_month_map(map<int,string> &map_month){
    map_month.insert(pair<int,string>(1,"January"));
    map_month.insert(pair<int,string>(2,"February"));
    map_month.insert(pair<int,string>(3,"March"));
    map_month.insert(pair<int,string>(4,"April"));
    map_month.insert(pair<int,string>(5,"May"));
    map_month.insert(pair<int,string>(6,"June"));
    map_month.insert(pair<int,string>(7,"July"));
    map_month.insert(pair<int,string>(8,"August"));
    map_month.insert(pair<int,string>(9,"September"));
    map_month.insert(pair<int,string>(10,"October"));
    map_month.insert(pair<int,string>(11,"November"));
    map_month.insert(pair<int,string>(12,"December"));
}


void runTime(float rate, chrono::steady_clock::time_point begin, double &prev_time, int &day, int &month, int &year, map<int,string> &map_month){
    double seconds;
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    seconds = chrono::duration<double>(end - begin).count();
    if(seconds >= prev_time + rate){
        prev_time = seconds;
        day++;
        if(day == 31){
            day = 1;
            month++;
            if(month == 13){
                month = 1;
                year++;
            }
        }
        printTime(day,month,year,map_month);
    }
    
}

bool ButtonWasPressed(Button *button, INPUT_RECORD &Input_Record){
    if ( (Input_Record.Event.MouseEvent.dwMousePosition.X >= button->x && 
            Input_Record.Event.MouseEvent.dwMousePosition.X <= button->x + button->width) && 
            ( Input_Record.Event.MouseEvent.dwMousePosition.Y >= button->y && 
            Input_Record.Event.MouseEvent.dwMousePosition.Y <= button->y + button->height) ){
                    return true;
                        
         }
    return false;
}

int main(){
    bool unpause;
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD fdwMode;
    INPUT_RECORD InputRecord;
    DWORD Events;
    COORD coord;
    CONSOLE_CURSOR_INFO cci;
    double prev_time = 0;
    int day,month;
    int year = 2020;
    day = month = 1;
    map <int,string> map_month;
    vector<Button *> buttons_vec = {buttonClients,buttonReservation};
    SetConsoleDefinitions(fdwMode,hin,hout,cci);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    fill_month_map(map_month);
    DisplayMenu(buttons_vec);
    printTime(day,month,year,map_month);
    while(true){
        unpause = false;
        gotoxy(60,1);
        cout << setfill(' ') <<  setw(30) << "Hit Enter to unpause!";
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        switch ( InputRecord.EventType ){
            case MOUSE_EVENT: // mouse input 
                 if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    for(Button* button: buttons_vec){
                        if (ButtonWasPressed(button,InputRecord) ){
                            button->Display_Next_Menu(buttons_vec);
                            printTime(day,month,year,map_month);
                        } 
                    }
                }
                break; 
            case KEY_EVENT: // keyboard input 
                switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
                    {
                        case VK_RETURN:
                            unpause = true;
                            break;
                    }
            
                     break; 
        }
        FlushConsoleInputBuffer(hin);
        
        if(unpause){
            gotoxy(60,1);
            cout << setfill(' ') <<  setw(30) << "Hit any key to pause!";
            while(true){
                runTime(0.01,begin,prev_time,day,month,year,map_month);
                if(waitForCharInput(30) != '_') break;
            }
        }
    }
    
}