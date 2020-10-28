#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <conio.h>
#include <string>
#include <windows.h>
#include <map>

using namespace std;

int day = 1 ;
int month = 1;
int hour = 0;
int year = 2020;
double prev_time = 0;
HANDLE hout= GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
DWORD fdwMode;
DWORD Events;
COORD coord;
CONSOLE_CURSOR_INFO cci;
map <int,string> map_month;

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

void printTime(){
    gotoxy(100,0);
    cout << "Current Time: ";
    gotoxy(100,1);
    cout << day << " " << map_month[month] << " " << year;
    gotoxy(100,2);
    cout << setfill('0') << setw(2) << hour << " : " << setfill('0') <<  setw(2) << "";
}

void runTime(float rate, chrono::steady_clock::time_point begin){
    double seconds;
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    seconds = chrono::duration<double>(end - begin).count();
    if(seconds >= prev_time + rate){
        prev_time = seconds;
        hour++;
        if(hour == 24){
            hour = 0;
            day++;
            if(day == 31){
                day = 0;
                month++;
                if(month == 13){
                    month = 0;
                    year++;
                }
            }
        }
        printTime();
    }
    
}
struct Button{
    int x;
    int y;
    int width;
    int height;
    string text;
    void (*Display_Next_Menu)(vector<Button*> &button_vec);

};
Button* button1 = new Button;
Button* button2 = new Button;
void DrawButton(Button* button){
    gotoxy(button->x,button->y);
    string str(button->width,'-');
    cout << str;
    for(int i = 1; i < button->height; i++){
        gotoxy(button->x,button->y + i);
        cout << "|";
        gotoxy(button->x + button->width, button->y + i);
        cout << "|";
    }
    gotoxy((button->x + button->width/2) - button->text.length()/2, button->y + button->height/2);
    cout << button->text;
    gotoxy(button->x,button->y + button->height);
    cout << str;
}

void DisplayMenu(vector<Button*>& button_vec){
    clearscreen();
    printTime();
    button_vec = {button1};
    for(Button * button: button_vec){
        DrawButton(button);
    }

}

INPUT_RECORD InputRecord;

bool ButtonWasPressed(Button *button, INPUT_RECORD &Input_Record){
    if ( (Input_Record.Event.MouseEvent.dwMousePosition.X >= button->x && 
            Input_Record.Event.MouseEvent.dwMousePosition.X <= button->x + button->width) && 
            ( Input_Record.Event.MouseEvent.dwMousePosition.Y >= button->y && 
            Input_Record.Event.MouseEvent.dwMousePosition.Y <= button->y + button->height) ){
                    return true;
                        
         }
    return false;
}

void Display_Reservations_Menu(vector<Button*>& button_vec){
    button_vec = {button2};
    clearscreen();
    printTime();
    gotoxy(1,1);
    cout << "RESERVATIONS";
    for(Button * button: button_vec){
        DrawButton(button);
    }
    for(int i = 2; i < 10; i++){
        gotoxy(1, 1+ i);
        cout << "Reservation n: " << i -1;
    }
}

void fill_month_map(){
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

void CreateButtons(){
    button1->x = 10;
    button1->y = 10;
    button1->height = 4;
    button1->text = "Reservations";
    button1->width = 15;
    button1->Display_Next_Menu = Display_Reservations_Menu;

    button2->x = 40;
    button2->y = 1;
    button2->height = 4;
    button2->width = 10;
    button2->text = "Go Back";
    button2->Display_Next_Menu = DisplayMenu;
}

void SetConsoleDefinitions(){
    cci.dwSize = 25;
    cci.bVisible = FALSE;
    fdwMode = ENABLE_EXTENDED_FLAGS;
    SetConsoleMode(hin, fdwMode);
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hin, fdwMode);
    SetConsoleCursorInfo(hout, &cci);
    SetConsoleMode(hin, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
}

int main(){
    bool unpause;
    SetConsoleDefinitions();
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    fill_month_map();
    CreateButtons();
    vector<Button*> button_vec = {button1}; //vector with the current buttons on screen

    DisplayMenu(button_vec);
    while(true){
        unpause = false;
        gotoxy(60,1);
        cout << setfill(' ') <<  setw(30) << "Hit Enter to unpause!";
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        switch ( InputRecord.EventType ){
            case MOUSE_EVENT: // mouse input 
                 if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    for(Button* button: button_vec){
                        if (ButtonWasPressed(button,InputRecord) ){
                            button->Display_Next_Menu(button_vec);
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
                runTime(0.01,begin);
                if(waitForCharInput(30) != '_') break;
            }

        }
        
    }
}