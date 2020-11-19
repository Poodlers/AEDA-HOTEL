#include <iostream>
#include <iomanip>
#include <map>
#include "GUI/buttons.h"
#include <algorithm>

using namespace std;

int main(){
    map<int,string> map_month;
    Hotel hotel("hotel_exemplo_2");
    //Authentication(&hotel);
    auto ClientsButton = new MenuButton<Client>(10,6,15,3,"Clients",1,&hotel,nullptr);
    auto StaffButton =  new MenuButton<Staff>(10,10,15,3,"Staff",1,&hotel, nullptr);
    auto RoomsButton =  new MenuButton<Room>(10,14,15,3,"Rooms",1,&hotel, nullptr);
    auto ReservationsButton = new MenuButton<Reservation>(10,18,15,3,"Reservations",1,&hotel,nullptr);
    auto ProvidersButton = new MenuButton<Provider>(10,22,15,3,"Providers",1,&hotel,nullptr);
    ClientsButton->DrawButton();
    StaffButton->DrawButton();
    RoomsButton->DrawButton();
    ReservationsButton->DrawButton();
    ProvidersButton->DrawButton();
    fill_month_map(map_month);
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD fdwMode;
    INPUT_RECORD InputRecord;
    DWORD Events;
    CONSOLE_CURSOR_INFO cci;
    SetConsoleDefinitions(fdwMode,hin,hout,cci);
    vector<BaseButton*> CurrentButtons = {ClientsButton,StaffButton,RoomsButton,ReservationsButton,ProvidersButton};
    ButtonHandler ButtonHandler(CurrentButtons);
    printTime(hotel.getDate(),map_month);
    while(true){
        gotoxy(60,1);
        cout << setfill(' ') <<  setw(20) << "Hit Enter to advance one day!";
        printTime(hotel.getDate(),map_month);
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        switch ( InputRecord.EventType ){
            case MOUSE_EVENT: // mouse input 
                 if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    for(const auto& button: ButtonHandler.getButtons()){
                        if (ButtonWasPressed(button,InputRecord) )
                        {
                            button->onClick(ButtonHandler);
                            printTime(hotel.getDate(),map_month);
                            break;
                        } 
                    }
                }
                 break;
            case KEY_EVENT: // keyboard input
            if(InputRecord.Event.KeyEvent.bKeyDown){
                switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
                {
                    case VK_RETURN:
                        hotel.incrementDate(1);
                        break;
                }
            }
            break;
        }
        FlushConsoleInputBuffer(hin);
    }
}