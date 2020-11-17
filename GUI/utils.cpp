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


void getStringInput(std::string& input, int x, int y){
    input = "";
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    char charName[128];
    DWORD Events;
    INPUT_RECORD InputRecord;
    while(true){
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        switch ( InputRecord.EventType ){
            case KEY_EVENT: // keyboard input
                if(InputRecord.Event.KeyEvent.bKeyDown){
                    switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
                    {
                        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
                        case VK_RCONTROL: case VK_RMENU:
                        case VK_LWIN: case VK_RWIN: case VK_APPS: case VK_CAPITAL:
                        case VK_PRIOR: case VK_NEXT:
                        case VK_END: case VK_HOME:
                        case VK_INSERT: case VK_DELETE:
                        case VK_DIVIDE:
                        case VK_NUMLOCK:
                            break;
                        case VK_RETURN:
                            return;
                        case VK_SPACE:
                            input += " ";
                        case VK_BACK:
                            input = input.substr(0, input.size()-1);
                            gotoxy(x,y);
                            std::cout << "                                                                  ";
                            gotoxy(x,y);
                            std::cout << input;
                            break;
                        default:
                            UINT scanCode = MapVirtualKey(InputRecord.Event.KeyEvent.wVirtualKeyCode, MAPVK_VK_TO_VSC);
                            GetKeyNameTextA(scanCode << 16,charName,128);
                            if(GetKeyState(VK_CAPITAL) & 0x01)
                                input += std::string(charName);
                            else
                                input += std::tolower(charName[0]);
                            gotoxy(x,y);
                            std::cout << "                                                                      ";
                            gotoxy(x,y);
                            std::cout << input;

                            break;
                    }
                }
                break;
        }
        FlushConsoleInputBuffer(hin);

    }
}
void checkIfInteger(std::string input, std::string check){
    for(int i = 0; i < input.length();i++){
        if(!isdigit(input[i]) ){
            throw NotAnInt(check);
        }
    }
}

void checkIfPositiveInteger(std::string input, std::string check){
    try{
        checkIfInteger(input,check);
    }
    catch(...){
        throw;
    }
    if (stoi(input) < 0){
        throw NotAPositiveInt(check);
    }
}

void checkIfValidPriceOrWage(std::string input, std::string check){
    bool isfloat = false;
    for(int i = 0; i < input.length();i++){
        if(input[i] == '.'){
            if(!isfloat){
                isfloat = true;
            }else{ //this is the second . and this input is invalid
                throw NotAPositiveFloat(check);
            }
        }
        else if(!isdigit(input[i]) ){
            throw NotAPositiveFloat(check);
        }
    }
    if (stoi(input) <= 0){
        throw NotAPositiveFloat(check);
    }
}

std::string GetNumberInput(int x,int y,bool(*CheckCorrectType)(std::string input)){
    std::string output;
    while (true) {
        getStringInput(output, x, y);
        if (output == "." || CheckCorrectType(output)){
            return output;
        }
        else{
            gotoxy(0,y + 2);
            std::cout << "It seems you haven't typed a correct number!" << std::endl;
            gotoxy(0,y+3);
            std::cout << "Please try again shortly!" << std::endl;
            Sleep(2000);
            gotoxy(0,y+2);
            std::cout << "                                                                    ";
            gotoxy(0,y+3);
            std::cout << "                                                                    ";
            }
        }
    }


std::ostream& operator<<(std::ostream &o, std::vector<int> v){
    o << "{";
    for (int i = 0; i < v.size(); ++i) {
        o << v[i];
        if (i != v.size() - 1)
            o << ", ";
    }
    o << "}";
    return o;
}

void validateNIF(const std::string& NIF,const std:: string& name) {
    try{
        checkIfPositiveInteger(NIF,"NIF");
        if (NIF.size() != 9) throw  NIFIsNotValid(name, NIF);
    }
    catch(...){
        throw NIFIsNotValid(name, NIF);
    }
    if (
            NIF.substr(0,1) != "1" && // pessoa singular
            NIF.substr(0,1) != "2" && // pessoa singular
            NIF.substr(0,1) != "3" && // pessoa singular
            NIF.substr(0,2) != "45" && // pessoa singular não residente
            NIF.substr(0,1) != "5" && // pessoa colectiva
            NIF.substr(0,1) != "6" && // administração pública
            NIF.substr(0,2) != "70" && // herança indivisa
            NIF.substr(0,2) != "71" && // pessoa colectiva não residente
            NIF.substr(0,2) != "72" && // fundos de investimento
            NIF.substr(0,2) != "77" && // atribuição oficiosa
            NIF.substr(0,2) != "79" && // regime excepcional
            NIF.substr(0,1) != "8" && // empresário em nome individual (extinto)
            NIF.substr(0,2) != "90" && // condominios e sociedades irregulares
            NIF.substr(0,2) != "91" && // condominios e sociedades irregulares
            NIF.substr(0,2) != "98" && // não residentes
            NIF.substr(0,2) != "99" // sociedades civis
            ) { throw NIFIsNotValid(name, NIF);}
    int check1 = std::stoi(NIF.substr(0,1))*9;
    int check2 = std::stoi(NIF.substr(1,1))*8;
    int check3 = std::stoi(NIF.substr(2,1))*7;
    int check4 = std::stoi(NIF.substr(3,1))*6;
    int check5 = std::stoi(NIF.substr(4,1))*5;
    int check6 = std::stoi(NIF.substr(5,1))*4;
    int check7 = std::stoi(NIF.substr(6,1))*3;
    int check8 = std::stoi(NIF.substr(7,1))*2;

    int total= check1 + check2 + check3 + check4 + check5 + check6 + check7 + check8;
    int divisao = total / 11;
    int modulo11= total - divisao * 11;
    int comparador;
    if ( modulo11==1 || modulo11==0){ comparador=0; } // excepção
    else { comparador= 11-modulo11;}

    int ultimoDigito= std::stoi(NIF.substr(8,1))*1;
    if ( ultimoDigito != comparador ){
        throw NIFIsNotValid(name, NIF);
    }
}


void cleanCinBuffer(){
    cin.clear();
    cin.ignore(1000000000,'\n');
}