#include "utils.h"
#include <iostream>
#include <conio.h>

using namespace std;

Hotel* createHotel(){
    while(true){
        string input;
        cout << "input the name of the hotel file (without .txt): "<< endl;
        std::getline(cin,input);
        clearscreen();
        try {
            Hotel *hotel = new Hotel(input);
            return hotel;
        }
        catch(FileNotFound& msg){
            cout <<msg;
        }
        catch(HotelFileHasWrongFormat& msg){
            cout << msg;
        }
        catch(NIFIsNotValid& msg){
            cout <<msg;
        }
    }
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
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    GetConsoleScreenBufferInfo(hout, &SBInfo);
    COORD scrollbar;
    scrollbar.X = SBInfo.srWindow.Right - SBInfo.srWindow.Left + 1;
    scrollbar.Y = SBInfo.srWindow.Bottom - SBInfo.srWindow.Top + 1;
    SetConsoleScreenBufferSize(hout, scrollbar);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(hout, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(hout, &cursorInfo);
}

void printTime(Date date, map<int,string> &map_month){
    gotoxy(100,0);
    cout << "Current Time: ";
    gotoxy(100,1);
    cout << "                                            ";
    gotoxy(100,1);
    cout << date.getDay() << " " << map_month[date.getMonth()] << " " << date.getYear();
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
                    case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN: case VK_TAB:
                    case VK_RCONTROL: case VK_RMENU: case VK_SHIFT: case VK_CLEAR:
                    case VK_LWIN: case VK_RWIN: case VK_APPS: case VK_CAPITAL: case VK_PAUSE:
                    case VK_MENU:
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
                            break;
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

bool CheckIfInteger(std::string input){
    for(int i = 0; i < input.length();i++){
        if(!isdigit(input[i]) ){
            return false;
        }
    }
    return true;
}

void checkIfPositiveInteger(std::string input, std::string check){
    try{
        checkIfInteger(input,check);
    }
    catch(...){
        throw NotAPositiveInt(check);
    }
    if (stoi(input) < 0){
        throw NotAPositiveInt(check);
    }
}

void checkIfValidPriceOrWage(std::string input,std::string check){
    bool isfloat = false;
    for(int i = 0; i < input.length();i++){
        if(input[i] == '.'){
            if(!isfloat){
                isfloat = true;
            }else{ //this is the second, this input is invalid
                throw NotAPositiveFloat(check);
            }
        }
        else if(!isdigit(input[i]) ){
            throw NotAPositiveFloat(check);
        }
    }
    try{
        if (stof(input) <= 0){
            throw NotAPositiveFloat(check);
        }
    }
    catch(...){
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
            gotoxy(x,y);
            std::cout << "                                                    ";
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
    o << "[";
    for (int i = 0; i < v.size(); ++i) {
        o << v[i];
        if (i != v.size() - 1)
            o << ", ";
    }
    o << "]";
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

std::vector<std::string> askClient() {
    std::string name;
    std::string NIF;
    std::cout << "Edit the client's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Name: " << std::endl;
    getStringInput(name, 6, 3);
    gotoxy(0, 5);
    std::cout << "NIF: " << std::endl;
    getStringInput(NIF,5,5);
    std::vector<std::string> vec = {name,NIF};
    return vec;


}

std::vector<std::string> askmodifyReservation(){
    std::vector<std::string> vec;
    std::string edit;
    std::cout << "Edit the Reservation's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    gotoxy(0,3);
    std::cout << "Room Id: " << std::endl;
    edit = GetNumberInput(22,3,CheckIfInteger);
    vec.push_back(edit);
    gotoxy(0,5);
    std::cout << "Check In Date (day-month-year): " << std::endl;
    getStringInput(edit,33,5);
    vec.push_back(edit);
    edit = " ";
    gotoxy(0,7);
    std::cout << "Check Out Date (day-month-year): " << std::endl;
    getStringInput(edit,33,7);
    vec.push_back(edit);
    gotoxy(0,9);
    std::cout << "Capacity : " << std::endl;
    edit = GetNumberInput(12,9,CheckIfInteger);
    vec.push_back(edit);
    return vec;

}

void askReservation(unsigned int& roomId,Date& checkIn,Date& checkOut,int& capacity,int& reservationId) {
    std::string edit;
    std::cout << "Edit the Reservation's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    gotoxy(0,3);
    unsigned long waitNewAttempt = 2000;
    std::cout << "Reservation Id: " << std::endl;
    edit = GetNumberInput(22,3,CheckIfInteger);
    if (edit != ".") reservationId = std::stoi(edit);
    gotoxy(0,5);
    std::cout << "Check In Date (day-month-year): " << std::endl;
    while(edit != "."){
        getStringInput(edit,33,5);
        if (edit != "."){
            try{
                checkIn = Date(edit);
                edit = ".";
            }
            catch (DateIsNotValid& msg) {
                gotoxy(0,7);
                std::cout << msg;
                Sleep(waitNewAttempt);
                gotoxy(0,7);
                std::cout << "                                                                         " << std::endl;
            }
        }
    }
    edit = " ";
    gotoxy(0,7);
    std::cout << "Check Out Date (day-month-year): " << std::endl;
    while(edit != "."){
        getStringInput(edit,33,7);
        if (edit != "."){
            try{
                checkOut = Date(edit);
                edit = ".";
            }
            catch (DateIsNotValid& msg) {
                gotoxy(0,9);
                std::cout << msg;
                Sleep(waitNewAttempt);
                gotoxy(0,9);
                std::cout << "                                                                      " << std::endl;
            }
        }
    }
    gotoxy(0,9);
    std::cout << "Room Id: " << std::endl;
    edit = GetNumberInput(10,9,CheckIfInteger);
    if (edit != ".") roomId = std::stoi(edit);
    edit = " ";
    gotoxy(0,11);
    std::cout << "Capacity : " << std::endl;
    edit = GetNumberInput(12,11,CheckIfInteger);
    if (edit != ".") capacity = std::stoi(edit);

}

std::vector<std::string> askRoom() {
    std::string edit;
    std::vector<std::string> vec;
    std::cout << "Edit the Room's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Capacity: " << std::endl;
    getStringInput(edit,15,3);
    vec.push_back(edit);
    gotoxy(0,5);
    std::cout << "Price Per Night: ";
    getStringInput(edit,10,5);
    vec.push_back(edit);
    return vec;

}

std::vector<std::string> createRoom(){
    std::string edit;
    std::vector<std::string> vec;
    std::cout << "Edit the Room's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Floor: " << std::endl;
    getStringInput(edit,10,3);
    vec.push_back(edit);
    gotoxy(0,5);
    std::cout << "Room Number: ";
    getStringInput(edit,10,5);
    vec.push_back(edit);
    gotoxy(0,7);
    std::cout << "Room Id: " << std::endl;
    getStringInput(edit,12,7);
    vec.push_back(edit);
    gotoxy(0,9);
    std::cout << "Capacity: " << std::endl;
    getStringInput(edit,10,9);
    vec.push_back(edit);
    gotoxy(0,11);
    std::cout << "Price per Night: " << std::endl;
    getStringInput(edit,24,11);
    vec.push_back(edit);
    gotoxy(0,13);
    std::cout << "Room Type(Suite,NoViewRoom,ViewRoom): " << std::endl;
    getStringInput(edit,40,13);
    vec.push_back(edit);
    return vec;
}

std::vector<std::string> askStaff(){
    std::vector<std::string> vec;
    std::string input;
    std::cout << "Insert the name of the staff member you wish to add:"<< std::endl;
    getStringInput(input,0,1);
    vec.push_back(input);
    gotoxy(0,3);
    std::cout << "Insert the NIF of the staff member you wish to add:"<< std::endl;
    getStringInput(input,0,4);
    vec.push_back(input);
    gotoxy(0,5);
    cout << "Insert the wage of the staff member you wish to add:"<<endl;
    getStringInput(input,0,6);
    vec.push_back(input);
    gotoxy(0,7);
    std::cout << "Insert the position of the staff member you wish to add:"<< std::endl;
    getStringInput(input,0,8);
    vec.push_back(input);
    if (input == "Manager"){
        gotoxy(0,9);
        std::cout << "This action will replace the manager. Write yes to proceed, and anything else to cancel" << std::endl;
        getStringInput(input,0,10);
        if (input != "yes"){
            return {};
        }
        gotoxy(0,11);
        cout << "Insert the password of the manager you wish to add:"<<endl;
        getStringInput(input,0,12);
        vec.push_back(input);
        gotoxy(0,13);
        cout << "Insert the evaluation of the manager you wish to add:"<<endl;
        getStringInput(input,0,14);
        vec.push_back(input);
    }
    else if (input == "Janitor"){
        gotoxy(0,9);
        cout << "Insert the shift of the janitor you wish to add:"<<endl;
        getStringInput(input,0,10);
        vec.push_back(input);
    }

    return vec;
}

void sortReservations(std::vector<Reservation*>& reserv_vec,const std::string& input,const std::string& order1){
    bool order;
    if (order1 == "Ascending"){
        order = true;
    }
    else if (order1 == "Descending"){
        order = false;
    }
    else throw SortingError();

    if (input == "Check In"){
        if (order){
            sort(reserv_vec.begin(),reserv_vec.end(),[](Reservation* r1, Reservation* r2){
                return r1->getCheckIn()< r2->getCheckIn();
            });
        }
        else{
            sort(reserv_vec.begin(),reserv_vec.end(),[](Reservation* r1, Reservation* r2){
                return r1->getCheckIn() > r2->getCheckIn();
            });
        }
    }else if(input == "Check Out"){
        if (order){
            sort(reserv_vec.begin(),reserv_vec.end(),[](Reservation* r1, Reservation* r2){
                return r1->getCheckOut()< r2->getCheckOut();
            });
        }
        else{
            sort(reserv_vec.begin(),reserv_vec.end(),[](Reservation* r1, Reservation* r2){
                return r1->getCheckOut() > r2->getCheckOut();
            });
        }
    }
    else if(input == "Room Id"){
        if (order){
            sort(reserv_vec.begin(),reserv_vec.end(),[](Reservation* r1, Reservation* r2){
                return r1->getRoomId()< r2->getRoomId();
            });
        }
        else{
            sort(reserv_vec.begin(),reserv_vec.end(),[](Reservation* r1, Reservation* r2){
                return r1->getRoomId() > r2->getRoomId();
            });
        }
    }
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v){
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

void checkIfValidPlate(const std::string& plate){
    if(plate.size() != 8 ){
        throw InvalidPlate(plate);
    }
    if(plate[2] != '-' || plate[5] != '-'){
        throw InvalidPlate(plate);
    }
    std::string st1 = plate.substr(0, 2);
    std::string st2 = plate.substr(3, 2);
    std::string st3 = plate.substr(6, 2);
    try{
        int first = checkIfIsNumber(st1);
        int second = checkIfIsNumber(st2);
        int third = checkIfIsNumber(st3);
        if(first + second + third != 4){
            throw InvalidPlate(plate);
        }
    }catch(...){
        throw InvalidPlate(plate);
    }


}

int checkIfIsNumber(const std::string& number){
    if(isdigit(number[0])){
        if(!isdigit(number[1])){
            throw ;
        }else{
            return 1;
        }
    }
    else if(isalpha(number[0])){
        if(!isupper(number[0])){
            throw ;
        }
        if(!isalpha(number[1])){
            throw ;
        }else if(isupper(number[1])){
            return 2;
        }
    }
    throw;
}