#include <iostream>
#include <iomanip>
#include <map>
#include "GUI/buttons.h"

using namespace std;

int main(){
    map<int,string> map_month;
    Hotel hotel("hotel_exemplo");
    //Authentication(&hotel);
    BaseButton* ClientsButton = new MenuButton<Client>(10,6,15,3,"Clients",1,hotel.getClients());
    BaseButton* StaffButton = new MenuButton<Staff>(10,10,15,3,"Staff",1,hotel.getStaff());
    BaseButton* RoomsButton = new MenuButton<Room>(10,14,15,3,"Rooms",1,hotel.getRooms());
    bool unpause;
    fill_month_map(map_month);
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD fdwMode;
    INPUT_RECORD InputRecord;
    DWORD Events;
    CONSOLE_CURSOR_INFO cci;
    double prev_time = 0;
    int day,month;
    int year = 2020;
    day = month = 1;
    SetConsoleDefinitions(fdwMode,hin,hout,cci);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    vector<BaseButton *> CurrentButtons = {ClientsButton,StaffButton,RoomsButton}; //vector with the initial menu buttons
    for(BaseButton* button: CurrentButtons){
        button->DrawButton();
    }
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
                    for(BaseButton* button: CurrentButtons){
                        if (ButtonWasPressed(button,InputRecord) ){
                            button->onClick(CurrentButtons);
                            printTime(day,month,year,map_month);
                        } 
                    }
                }
                break; 
            case KEY_EVENT: // keyboard input
            if(InputRecord.Event.KeyEvent.bKeyDown){
                switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
                {
                    case VK_RETURN:
                        unpause = true;
                        break;
                }
            }
            break;
        }
        FlushConsoleInputBuffer(hin);
        
        if(unpause){
            gotoxy(60,1);
            cout << setfill(' ') <<  setw(30) << "Hit any key to pause!";
            while(true){
                runTime(0.1,begin,prev_time,day,month,year,map_month);
                if(waitForCharInput(30) != '_') break;
            }
        }
    }
    
}