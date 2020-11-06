#include "buttons.h"
#include <algorithm>
#include <type_traits>



BaseButton::BaseButton(const int x, const int y, const int width, const int height, const std::string &text):
x(x),y(y),width(width),height(height),text(text){};

int BaseButton::getHeight() {
    return this->height;
}
int BaseButton::getWidth() {
    return this->width;
}

int BaseButton::getX() {
    return this->x;
}

int BaseButton::getY() {
    return this->y;
}

ParentButton::ParentButton(const int x, const int y, const int width, const int height, const std::string &text,
                           const std::vector<BaseButton *> &InitialButtons):
                           BaseButton(x,y,width,height,text){
    this->InitialButtons = InitialButtons;
}

void ParentButton::onClick(std::vector<BaseButton *> &CurrentButtons) {
    clearscreen();
    for(BaseButton* button: this->InitialButtons){
        button->DrawButton();
    }
    CurrentButtons = this->InitialButtons;
}

GoBackButton::GoBackButton(const int x, const int y, const int width, const int height, const std::string text,
                           BaseButton* ButtonsNext):
                           BaseButton(x,y,width,height,text){
    this->NextButtons = ButtonsNext;
}

void GoBackButton::onClick(std::vector<BaseButton*> &CurrentButtons) {
    clearscreen();
    this->NextButtons->onClick(CurrentButtons);
}

template <class N>
ModifyButton<N>::ModifyButton(const int x, const int y, const int width, const int height, const std::string text,
                              N *object):
                              BaseButton(x,y,width,height,text){
    this->object = object;
}

template <class N>
N * ModifyButton<N>::getObject() {
    return this->object;
}

template<class N>
void ModifyButton<N>::onClick(std::vector<BaseButton *> &CurrentButtons) {
    return ;

}

template<class N>
DeleteButton<N>::DeleteButton(const int x, const int y, const int width, const int height,
                                       const std::string text, N* object, MenuButton<N>* Button):
                                       ModifyButton<N>(x,y,width,height,text,object){
    this->Button = Button;

}

template <class N>
void DeleteButton<N>::onClick(std::vector<BaseButton*> &CurrentButtons) {
    this->Button->EraseObject(this->getObject());
    this->Button->onClick(CurrentButtons);

}


void BaseButton::DrawButton(){
    gotoxy(this->x,this->y);
    std::string str(this->width,'-');
    if(this->height > 0) std::cout << str;
    for(int i = 1; i < this->height; i++){
        gotoxy(this->x,this->y + i);
        std::cout << "|";
        gotoxy(this->x + this->width, this->y + i);
        std::cout << "|";
    }
    gotoxy((this->x + this->width/2) - this->text.length()/2, this->y + this->height/2);
    std::cout << this->text;
    gotoxy(this->x,this->y + this->height);
    if(this->height > 0) std::cout << str;
}


template <class N>
EditButton<N>::EditButton(const int x, const int y, const int width, const int height, const std::string text,
                                   N * object,BaseButton* button):ModifyButton<N>(x,y,width,height,text,object) {
    this->OriginalButton = button;
};
template <class N>
void EditButton<N>::onClick(std::vector<BaseButton*> &CurrentButtons) {
    clearscreen();
    this->getObject()->edit();
    this->OriginalButton->onClick(CurrentButtons);

}

template <typename N>
MenuButton<N>::MenuButton(const int x, const int y, const int width, const int height,
                          const std::string& text, const int currentPage,
                          std::vector<N *> &menu_items,BaseButton* ParentButton):
        BaseButton(x,y,width,height,text){
    this->menu_items = menu_items;
    this->CurrentPage = currentPage;
    this->Parent_Button = ParentButton;

}


template <typename N>
void MenuButton<N>::onClick(std::vector<BaseButton*> &CurrentButtons) {
    clearscreen();
    int edit_delete_x;
    gotoxy(1,1);
    if constexpr(std::is_same_v<N,Client>){
        edit_delete_x = 60;
        std::cout << "CLIENTS: ";
        gotoxy(1,3);
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Name" << std::setw(10) << "NIF" << std::endl;
    }
    else if constexpr (std::is_same_v<N,Reservation>){
        edit_delete_x = 90;
        std::cout << "Reservations: ";
        gotoxy(1,3);
        int increment_y = 0;
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation Id"
                  << std::setw(25) << "Reservation Size"
                  << std::setw(15) << "CheckIn" << std::setw(15) << "CheckOut" << std::setw(8) << "RoomId";
    }
    else if constexpr (std::is_same_v<N,Room>){
        edit_delete_x = 60;
        std::cout << "ROOMS: ";
        gotoxy(1,3);
        std::cout << std::left <<  std::setw(10) << std::setfill(' ') << "Room Id" << std::setw(15)
        << "Room Number" << std::setw(8)<< "Floor" << std::setw(10) << "Capacity" << std::setw(18)
        << "Price Per Night" << std::endl;

    }
    else if constexpr (std::is_same_v<N,Staff>){
        edit_delete_x = 110;
        std::cout << "STAFF: ";
        gotoxy(1,3);
        std::cout << std::left << std::setw(13) << "Type" <<  std::setw(20) << std::setfill(' ') << "Name" <<
        std::setw(10) << "NIF" << std::setw(7) << "Wage" << std::setw(19) << "Years Of Service"
        << std::setw(19) << "Floors Assigned" << std::setw(8) << "Shift" << std::setw(12) << "Evaluation";

    }

    BaseButton* InitialButton = new GoBackButton(85,0,10,2,"Go Back",this->Parent_Button);
    if(this->Parent_Button == NULL){
        InitialButton = new ParentButton(85,0,10,2,"Go Back",CurrentButtons);
    }
    CurrentButtons = {InitialButton};
    InitialButton->DrawButton();
    int increment_y = 0;
    for(N* item: this->menu_items){
        gotoxy(1,5 + increment_y);
        item->print();
        BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,4 + increment_y,8,0,"Edit",item,this);
        BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 5 + increment_y, 8,0,"Delete",item,this);
        if constexpr (std::is_same_v<N,Client>){
            BaseButton* ShowReservationButton = new MenuButton<Reservation>(35,4 + increment_y,15,2,"Show Reservations",1,item->getHistory(),this);
            CurrentButtons.push_back(ShowReservationButton);
            ShowReservationButton->DrawButton();
        }
        NewEditButton->DrawButton();
        NewDeleteButton->DrawButton();
        CurrentButtons.push_back(NewDeleteButton);
        CurrentButtons.push_back(NewEditButton);
        increment_y += 3;
    }
}

template <class N>
void MenuButton<N>::EraseObject(N * item) {
    typename std::vector<N *>::iterator find = std::find(this->menu_items.begin(),this->menu_items.end(),item);
    this->menu_items.erase(find);
}

bool ButtonWasPressed(BaseButton *button, INPUT_RECORD &Input_Record){
    if ( (Input_Record.Event.MouseEvent.dwMousePosition.X >= button->getX() &&
            Input_Record.Event.MouseEvent.dwMousePosition.X <= button->getX() + button->getWidth()) &&
            ( Input_Record.Event.MouseEvent.dwMousePosition.Y >= button->getY() &&
            Input_Record.Event.MouseEvent.dwMousePosition.Y <= button->getY() + button->getHeight()) ){
                    return true;
                        
         }
    return false;
}

void Authentication(Hotel* hotel){
    unsigned wait_new_attempt = 2000;
    std::string passwordAttempt = "";
    std::string name = "";
    while(!hotel->logIn(name,passwordAttempt)){
        std::cout << "Please write your name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "Please write your password: ";
        std::getline(std::cin,passwordAttempt);
        if(!hotel->logIn(name,passwordAttempt)){
            std::cout << std::endl;
            std::cout << "It seems you typed the wrong password. Please try again shortly!" << std::endl;
            Sleep(wait_new_attempt);
        }
        clearscreen();
    }

    std::cout << "Log In Was Successful! WELCOME" << std::endl;
    clearscreen();
}

template class MenuButton<Client>;
template class MenuButton<Staff>;
template class MenuButton<Room>;
