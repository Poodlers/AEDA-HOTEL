#include <iostream>
#include <iomanip>
#include <map>
#include "GUI/buttons.h"
#include "GUI/console.h"
#include <algorithm>

using namespace std;

int main(){
    srand(time(nullptr));
    std::string input;
    std::cout << "Do you wish to boot up in Console Mode or GUI mode? (Console/GUI): " << std::endl;
    std::getline(cin,input);
    if(input == "Console"){
        Hotel* hotel = createHotel();
        system(hotel);
        return 0;
    }
    map<int,string> map_month;
    Hotel* hotel = createHotel();
    auto ClientsButton = new MenuButton<Client>(10,6,15,3,"Clients",1,hotel,nullptr);
    auto RoomsButton =  new MenuButton<Room>(10,14,15,3,"Rooms",1,hotel, nullptr);
    auto ReservationsButton = new MenuButton<Reservation>(10,18,15,3,"Reservations",1,hotel,nullptr);
    auto SaveHotel = new SaveHotelFileButton(45,6,12,3,"Save Hotel",hotel);
    auto StaffButton =  new MenuButton<Staff>(10,10,15,3,"Staff",1,hotel, nullptr);
    auto ProvidersButton = new MenuButton<Provider>(10,22,15,3,"Providers",1,hotel,nullptr);
    auto TransactionsButton = new MenuButton<Transaction>(45,13,12,3,"Transactions",1,hotel,nullptr);
    auto LogInButton = new LogInOutButton(45,10,12,3,"Log In",hotel,StaffButton,ProvidersButton,TransactionsButton);
    LogInButton->DrawButton();
    ClientsButton->DrawButton();
    SaveHotel->DrawButton();
    RoomsButton->DrawButton();
    ReservationsButton->DrawButton();
    fill_month_map(map_month);
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD fdwMode;
    INPUT_RECORD InputRecord;
    DWORD Events;
    CONSOLE_CURSOR_INFO cci;
    SetConsoleDefinitions(fdwMode,hin,hout,cci);
    vector<BaseButton*> InitialButtons = {ClientsButton,RoomsButton,ReservationsButton,SaveHotel,LogInButton};
    vector<BaseButton*> InitialButtons2 = {ClientsButton,RoomsButton,ReservationsButton,SaveHotel,LogInButton,StaffButton,ProvidersButton,TransactionsButton};
    ButtonHandler ButtonHandler(InitialButtons);
    printTime(hotel->getDate(),map_month);
    while(true){
        gotoxy(70, 1);
        cout << setfill(' ') << setw(20) << "              ";
        if(ButtonHandler.getButtons() == InitialButtons || ButtonHandler.getButtons() == InitialButtons2) {
            gotoxy(70, 1);
            cout << setfill(' ') << setw(20) << "Hit Enter to advance one day!";
        }
        printTime(hotel->getDate(),map_month);
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        switch ( InputRecord.EventType ){
            case MOUSE_EVENT: // mouse input 
                 if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    for(const auto& button: ButtonHandler.getButtons()){
                        if (ButtonWasPressed(button,InputRecord) )
                        {
                            button->onClick(ButtonHandler);
                            printTime(hotel->getDate(),map_month);
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
                        if(ButtonHandler.getButtons() == InitialButtons || ButtonHandler.getButtons() == InitialButtons2) {
                            hotel->incrementDate(1);
                        }
                        break;
                }
            }
            break;
        }
        FlushConsoleInputBuffer(hin);
    }
}
