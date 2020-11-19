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

std::string BaseButton::getText() {
    return this->text;
}

ButtonHandler::ButtonHandler(std::vector<BaseButton*>  InitialButtons) {
    this->CurrentButtons = InitialButtons;
}

void ButtonHandler::AddButton(BaseButton* button) {
    this->CurrentButtons.push_back(button);
}

void ButtonHandler::DeleteButton(int index) {
    this->CurrentButtons.erase(this->CurrentButtons.begin() + index);
}

void ButtonHandler::SpecialGoBackClear() {
    for(auto& button: this->CurrentButtons){
        if(button->getText() != "Clients" && button->getText() != "Search" && button->getText() != "Reservations" && button->getText() != "Rooms" && button->getText() != "Staff" && button->getText() != "Go Back")
            delete button;
    }
    this->CurrentButtons.clear();
}

std::vector<BaseButton*> ButtonHandler::getButtons() {
    return this->CurrentButtons;
}

void ButtonHandler::ClearButtons() {
    this->CurrentButtons.clear();
}


ParentButton::ParentButton(const int x, const int y, const int width, const int height, const std::string &text,
                           const std::vector<BaseButton *> InitialButtons):
        BaseButton(x,y,width,height,text){
    this->InitialButtons = InitialButtons;
}

void ParentButton::onClick(ButtonHandler& handler) {
    clearscreen();
    handler.SpecialGoBackClear();
    for(BaseButton* button: this->InitialButtons){
        button->DrawButton();
        handler.AddButton(button);
    }
}

GoBackButton::GoBackButton(const int x, const int y, const int width, const int height, const std::string text,
                           BaseButton* ButtonNext):
        BaseButton(x,y,width,height,text){
    this->NextButton = ButtonNext;
}

void GoBackButton::onClick(ButtonHandler& handler) {
    clearscreen();
    handler.SpecialGoBackClear();
    this->NextButton->onClick(handler);
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
void ModifyButton<N>::onClick(ButtonHandler& handler) {
    return ;

}

template<class N>
DeleteButton<N>::DeleteButton(const int x, const int y, const int width, const int height,
                              const std::string text, N* object, MenuButton<N>* Button):
        ModifyButton<N>(x,y,width,height,text,object){
    this->Button = Button;

}

template <class N>
void DeleteButton<N>::onClick(ButtonHandler& handler) {
    this->Button->EraseObject(this->getObject());
    this->Button->onClick(handler);

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
                          N * object,MenuButton<N>* button):ModifyButton<N>(x,y,width,height,text,object) {
    this->OriginalButton = button;
};

template <class N>
void EditButton<N>::onClick(ButtonHandler& handler) {
    clearscreen();
    if constexpr (std::is_same_v<N,Staff>){
        if(this->getObject()->getType() == "Receptionist"){
            edit(dynamic_cast<Receptionist*>(this->getObject()));
        }else if(this->getObject()->getType() == "Responsible"){
            edit(dynamic_cast<Responsible*>(this->getObject()),this->OriginalButton->getHotel());
        }else if(this->getObject()->getType() == "Manager"){
            edit(dynamic_cast<Manager*>(this->getObject()));
        }else if(this->getObject()->getType() == "Janitor"){
            edit(dynamic_cast<Janitor*>(this->getObject()));
        }
    }else if constexpr (std::is_same_v<N,Room>){
        edit(this->getObject(),this->OriginalButton->getHotel());
    }else if constexpr (std::is_same_v<N,Client>){
        edit(this->getObject());
    }else if constexpr (std::is_same_v<N,Reservation>){
        edit(this->getObject(),this->OriginalButton->getHotel(),this->OriginalButton->getClient());
    }
    this->OriginalButton->onClick(handler);

}

ApplyDiscountButton::ApplyDiscountButton(const int x, const int y, const int width, const int height, const std::string text, Room* room,MenuButton<Room>* menu_button):BaseButton(x,y,width,height,text) {
    this->room = room;
    this->menu_button = menu_button;
}

void ApplyDiscountButton::onClick(ButtonHandler &handler) {
    this->room->toggleDiscount();
    clearscreen();
    handler.SpecialGoBackClear();
    this->menu_button->onClick(handler);
}

template <typename N>
MenuButton<N>::MenuButton(const int x, const int y, const int width, const int height,
                          const std::string& text, const int currentPage,
                          Hotel* hotel,BaseButton* ParentButton):
        BaseButton(x,y,width,height,text){
    this->hotel = hotel;
    this->CurrentPage = currentPage;
    this->Parent_Button = ParentButton;
    this->GoBack_Button = nullptr;
    this->client = nullptr;
    this->type_id = 0;
    this->order_id = 0;
}

template <class N>
void MenuButton<N>::ChangeCurrentPage(int page) {
    this->CurrentPage = this->CurrentPage + page;
}

template <class N>
int MenuButton<N>::getCurrentPage() {
    return this->CurrentPage;
}

template <class N>
void MenuButton<N>::ChangeOrderId(int i) {
    this->order_id = this->order_id + i;
}

template <class N>
void MenuButton<N>::ChangeTypeId(int i) {
    this->type_id = this->type_id + i;
}

template<class N>
MenuButton<N>::MenuButton(const int x, const int y, const int width, const int height,
                          const std::string &text, const int currentPage,Client* client,Hotel* hotel,
                          BaseButton* ParentButton): BaseButton(x,y,width,height,text){
    this->client = client;
    this->CurrentPage = currentPage;
    this->Parent_Button = ParentButton;
    this->GoBack_Button = nullptr;
    this->hotel = hotel;
    this->type_id = 0;
    this->order_id = 0;
}


template <typename N>
void MenuButton<N>::onClick(ButtonHandler& handler) {
    std::vector <N*> menu_items = {};
    if(this->GoBack_Button == nullptr){
        if(this->Parent_Button == nullptr){
            this->GoBack_Button = new ParentButton(85,0,10,2,"Go Back",handler.getButtons());
        }else{
            this->GoBack_Button = new GoBackButton(85,0,10,2,"Go Back",this->Parent_Button);
        }
    }
    handler.ClearButtons();
    int MaxObjectsOnScreen = 7;
    clearscreen();
    int edit_delete_x;
    auto addButton = new AddButton<N>(20,0,4,2,"+",this);
    ChangeTypeOfSort<N>* ChangePagesBack;
    ChangeTypeOfSort<N>* ChangePagesFront;
    SearchButton<N>* searchButton = new SearchButton<N>(30,0,7,2,"Search",this->hotel,this);
    handler.AddButton(searchButton);
    searchButton->DrawButton();
    if constexpr(std::is_same_v<N,Client>){
        menu_items = this->hotel->getClients();
        edit_delete_x = 60;
        int max_page = (menu_items.size() - 1) / MaxObjectsOnScreen + 1;
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        ChangePagesBack = new ChangeTypeOfSort<N>(17,3,2,0,"<","page_id",this);
        ChangePagesFront = new ChangeTypeOfSort<N>(29,3,2,0,">","page_id",this);
        gotoxy(1,1);
        std::cout << "CLIENTS: ";
        gotoxy(20,3);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        gotoxy(1,8);
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Name" << std::setw(10) << "NIF" << std::endl;
        std::vector<std::string> order = {"Ascending","Descending"};
        if(this->order_id >= order.size()) {
            this->order_id = 0;
        }
        else if(this->order_id < 0){
            this->order_id = order.size() - 1;
        }
        std::vector<std::string> typeOfSort {"Name", "NIF","Future reservations", "Past reservations"};
        if(this->type_id >= typeOfSort.size()){
            this->type_id = 0;
        }
        else if(this->type_id < 0){
            this->type_id = typeOfSort.size() - 1;
        }
        gotoxy(edit_delete_x + 35,14);
        std::cout << std::setw(15) << order[this->order_id] << std::setw(20) << typeOfSort[this->type_id];
        SortButton<N>* sortClientsButton = new SortButton<N>(edit_delete_x + 40,11,5,2,"Sort by: ",this->hotel,order[order_id],typeOfSort[type_id],this);
        ChangeTypeOfSort<N>* changeTypeOfSort1 = new ChangeTypeOfSort<N>(edit_delete_x + 32,14,2,0,"<","order_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort2 = new ChangeTypeOfSort<N>(edit_delete_x + 44,14,2,0,">","order_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort3 = new ChangeTypeOfSort<N>(edit_delete_x + 46,14,2,0,"<","type_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort4 = new ChangeTypeOfSort<N>(edit_delete_x + 55,14,2,0,">","type_id",this);
        handler.AddButton(changeTypeOfSort1);
        changeTypeOfSort1->DrawButton();
        changeTypeOfSort2->DrawButton();
        changeTypeOfSort3->DrawButton();
        changeTypeOfSort4->DrawButton();
        handler.AddButton(changeTypeOfSort2);
        handler.AddButton(changeTypeOfSort3);
        handler.AddButton(changeTypeOfSort4);
        sortClientsButton->DrawButton();
        handler.AddButton(sortClientsButton);
    }
    else if constexpr (std::is_same_v<N,Reservation>){
        if(this->client != nullptr)
            menu_items = this->client->getHistory();
        else
            menu_items = this->hotel->getReservations();
        int max_page = (menu_items.size() - 1) / MaxObjectsOnScreen + 1;
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        ChangePagesBack = new ChangeTypeOfSort<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangeTypeOfSort<N>(14,5,2,0,">","page_id",this);
        gotoxy(1,3);
        std::cout << "Reservations: ";
        gotoxy(10,5);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        edit_delete_x = 90;
        gotoxy(1,8);
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation Id"
                  << std::setw(25) << "Reservation Size"
                  << std::setw(15) << "CheckIn" << std::setw(15) << "CheckOut" << std::setw(8) << "RoomId";
    }
    else if constexpr (std::is_same_v<N,Room>){
        menu_items = this->hotel->getRooms();
        int max_page = (menu_items.size() - 1) / MaxObjectsOnScreen + 1;
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        std::vector<std::string> order = {"Ascending","Descending"};
        if(this->order_id >= order.size()) {
            this->order_id = 0;
        }
        else if(this->order_id < 0){
            this->order_id = order.size() - 1;
        }
        std::vector<std::string> typeOfSort {"Room ID", "Room Number", "Floor", "Capacity", "Price", "Type"};
        if(this->type_id >= typeOfSort.size()){
            this->type_id = 0;
        }
        else if(this->type_id < 0){
            this->type_id = typeOfSort.size() - 1;
        }
        gotoxy(40,4);
        std::cout << std::setw(17) << order[this->order_id] << std::setw(20) << typeOfSort[this->type_id];
        SortButton<N>* sortRoomsButton = new SortButton<N>(40,1,5,2,"Sort by: ",this->hotel,order[order_id],typeOfSort[type_id],this);
        ChangeTypeOfSort<N>* changeTypeOfSort1 = new ChangeTypeOfSort<N>(48,4,2,0,"<","order_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort2 = new ChangeTypeOfSort<N>(60,4,2,0,">","order_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort3 = new ChangeTypeOfSort<N>(67,4,2,0,"<","type_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort4 = new ChangeTypeOfSort<N>(80,4,2,0,">","type_id",this);
        handler.AddButton(changeTypeOfSort1);
        changeTypeOfSort1->DrawButton();
        changeTypeOfSort2->DrawButton();
        changeTypeOfSort3->DrawButton();
        changeTypeOfSort4->DrawButton();
        handler.AddButton(changeTypeOfSort2);
        handler.AddButton(changeTypeOfSort3);
        handler.AddButton(changeTypeOfSort4);
        sortRoomsButton->DrawButton();
        handler.AddButton(sortRoomsButton);
        auto ApplyMultipleDiscount = new ApplyDiscountToTypeOfRoom(40,5,10,2,"Suite",this->hotel,this);
        auto ApplyMultipleDiscount2 = new ApplyDiscountToTypeOfRoom(52,5,12,2,"ViewRoom",this->hotel,this);
        auto ApplyMultipleDiscount3 = new ApplyDiscountToTypeOfRoom(63,5,12,2,"NoViewRoom",this->hotel,this);
        ApplyMultipleDiscount->DrawButton();
        handler.AddButton(ApplyMultipleDiscount);
        ApplyMultipleDiscount2->DrawButton();
        handler.AddButton(ApplyMultipleDiscount2);
        ApplyMultipleDiscount3->DrawButton();
        handler.AddButton(ApplyMultipleDiscount3);
        ChangePagesBack = new ChangeTypeOfSort<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangeTypeOfSort<N>(14,5,2,0,">","page_id",this);
        gotoxy(1,3);
        std::cout << "ROOMS: ";
        gotoxy(10,5);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        edit_delete_x = 110;
        gotoxy(1,8);
        std::cout << std::left << std::setw(12) << "Type" << std::setw(10) << std::setfill(' ') << "Room Id" << std::setw(15)
                  << "Room Number" << std::setw(8)<< "Floor" << std::setw(10) << "Capacity" << std::setw(18)
                  << "Price Per Night" << std::setw(9) << "Availabilty" <<  std::endl;

    }
    else if constexpr (std::is_same_v<N,Staff>){
        menu_items = this->hotel->getStaff();
        int max_page = (menu_items.size() - 1) / MaxObjectsOnScreen + 1;
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }

        std::vector<std::string> order = {"Ascending","Descending"};
        if(this->order_id >= order.size()) {
            this->order_id = 0;
        }
        else if(this->order_id < 0){
            this->order_id = order.size() - 1;
        }
        std::vector<std::string> typeOfSort {"Name", "NIF", "Wage", "Years of service", "Position"};
        if(this->type_id >= typeOfSort.size()){
            this->type_id = 0;
        }
        else if(this->type_id < 0){
            this->type_id = typeOfSort.size() - 1;
        }
        gotoxy(50,5);
        std::cout << std::setw(15) << order[this->order_id] << std::setw(20) << typeOfSort[this->type_id];
        SortButton<N>* sortStaffButton = new SortButton<N>(60,2,5,2,"Sort by: ",this->hotel,order[order_id],typeOfSort[type_id],this);
        ChangeTypeOfSort<N>* changeTypeOfSort1 = new ChangeTypeOfSort<N>(48,5,2,0,"<","order_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort2 = new ChangeTypeOfSort<N>(65,5,2,0,">","order_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort3 = new ChangeTypeOfSort<N>(67,5,2,0,"<","type_id",this);
        ChangeTypeOfSort<N>* changeTypeOfSort4 = new ChangeTypeOfSort<N>(90,5,2,0,">","type_id",this);
        handler.AddButton(changeTypeOfSort1);
        changeTypeOfSort1->DrawButton();
        changeTypeOfSort2->DrawButton();
        changeTypeOfSort3->DrawButton();
        changeTypeOfSort4->DrawButton();
        handler.AddButton(changeTypeOfSort2);
        handler.AddButton(changeTypeOfSort3);
        handler.AddButton(changeTypeOfSort4);
        sortStaffButton->DrawButton();
        handler.AddButton(sortStaffButton);
        ChangePagesBack = new ChangeTypeOfSort<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangeTypeOfSort<N>(15,5,2,0,">","page_id",this);
        gotoxy(1,3);
        std::cout << "STAFF: ";
        gotoxy(10,5);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        edit_delete_x = 110;
        gotoxy(1,8);
        std::cout << std::left << std::setw(13) << "Type" <<  std::setw(20) << std::setfill(' ') << "Name" <<
                  std::setw(10) << "NIF" << std::setw(7) << "Wage" << std::setw(19) << "Years Of Service"
                  << std::setw(19) << "Floors Assigned" << std::setw(8) << "Shift" << std::setw(12) << "Evaluation";

    }
    handler.AddButton(this->GoBack_Button);
    handler.AddButton(addButton);
    handler.AddButton(ChangePagesBack);
    handler.AddButton(ChangePagesFront);
    ChangePagesBack->DrawButton();
    ChangePagesFront->DrawButton();
    addButton->DrawButton();
    this->GoBack_Button->DrawButton();
    int increment_y = 0;
    for(int i = 0 + (this->CurrentPage-1) * MaxObjectsOnScreen; i < this->CurrentPage* MaxObjectsOnScreen;i++){
        if(i >= menu_items.size()){
            break;
        }
        gotoxy(1,10 + increment_y);
        menu_items[i]->print();
        if constexpr (std::is_same_v<N,Room>){
            if(menu_items[i]->getDiscountState()){
                ApplyDiscountButton* applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20, 9 + increment_y,19,2,"Remove Discount",menu_items[i],this);
                handler.AddButton(applyDiscountButton);
                applyDiscountButton->DrawButton();
            }else{
                ApplyDiscountButton* applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20, 9 + increment_y,19,2,"Apply Discount",menu_items[i],this);
                handler.AddButton(applyDiscountButton);
                applyDiscountButton->DrawButton();
            }

        }
        BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,9 + increment_y,8,0,"Edit",menu_items[i],this);
        BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 10 + increment_y, 8,0,"Delete",menu_items[i],this);
        handler.AddButton(NewEditButton);
        handler.AddButton(NewDeleteButton);
        if constexpr (std::is_same_v<N,Client>){
            BaseButton* ShowReservationButton = new MenuButton<Reservation>(35,9 + increment_y,15,2,"Show Reservations",1,menu_items[i],this->hotel,this);
            handler.AddButton(ShowReservationButton);
            ShowReservationButton->DrawButton();
        }
        NewEditButton->DrawButton();
        NewDeleteButton->DrawButton();
        increment_y += 3;
    }
}

ApplyDiscountToTypeOfRoom::ApplyDiscountToTypeOfRoom(const int x, const int y, const int width, const int height,
                                                     const std::string text, Hotel *hotel, MenuButton<Room> *menu_button):BaseButton(x,y,width,height,text) {
                                                         this->hotel = hotel;
                                                         this->GoBackButton = menu_button;
                                                     }
void ApplyDiscountToTypeOfRoom::onClick(ButtonHandler &handler) {
    for(auto room: this->hotel->getRooms()){
        if(room->getType() == this->getText()){
            room->toggleDiscount();
        }
    }
    clearscreen();
    handler.SpecialGoBackClear();
    this->GoBackButton->onClick(handler);
}

template <class N>
SearchButton<N>::SearchButton(const int x, const int y, const int width, const int height,
                                       const std::string text, Hotel *hotel, MenuButton<N> *menu_button): BaseButton(x,y,width,height,text) {
                                           this->hotel = hotel;
                                           this->GoBackButton = menu_button;
                                       }

template <class N>
void SearchButton<N>::onClick(ButtonHandler &handler) {
    clearscreen();
    std::string type;
    int pos;
    int waitForNewAttempt = 3000;
    int edit_delete_x = 0;
    handler.SpecialGoBackClear();
    if constexpr (std::is_same_v<N,Client>){
        try{
            type = "Client";
            gotoxy(0,1);
            std::cout << "Fill in with the data of the person you're looking for please!" << std::endl;
            std::string name;
            std::string NIF;
            gotoxy(0,3);
            std::cout << "Name: " << std::endl;
            getStringInput(name,6,3);
            gotoxy(0,5);
            std::cout << "NIF: " << std::endl;
            getStringInput(NIF,5,5);
            pos = this->hotel->search(name,NIF,type);
            gotoxy(1,9);
            Client* client = this->hotel->getClients()[pos];
            client->print();
            edit_delete_x = 60;
            BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8,8,0,"Edit",client,this->GoBackButton);
            BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9, 8,0,"Delete",client,this->GoBackButton);
            handler.AddButton(NewEditButton);
            handler.AddButton(NewDeleteButton);
            BaseButton* ShowReservationButton = new MenuButton<Reservation>(35,8,15,2,"Show Reservations",1,client,this->hotel,this->GoBackButton);
            handler.AddButton(ShowReservationButton);
            ShowReservationButton->DrawButton();
            NewEditButton->DrawButton();
            NewDeleteButton->DrawButton();
        }
        catch(...){
            gotoxy(0,9);
            std::cout << "Sorry but the person you're looking for doesn't exist or the data you typed was invalid!" << std::endl;
            Sleep(waitForNewAttempt);
            this->GoBackButton->onClick(handler);
        }
    }
    else if constexpr (std::is_same_v<N,Staff>){
        try{
        type = "Staff";
        gotoxy(0,1);
        std::cout << "Fill in with the data of the Staff you're looking for please!" << std::endl;
        std::string name;
        std::string NIF;
        gotoxy(0,3);
        std::cout << "Name: " << std::endl;
        getStringInput(name,6,3);
        gotoxy(0,5);
        std::cout << "NIF: " << std::endl;
        getStringInput(NIF,5,5);
        pos = this->hotel->search(name,NIF,type);
        gotoxy(1,9);
        Staff* staff = this->hotel->getStaff()[pos];
        staff->print();
        edit_delete_x = 110;
        BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8,8,0,"Edit",staff,this->GoBackButton);
        BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9, 8,0,"Delete",staff,this->GoBackButton);
        handler.AddButton(NewEditButton);
        handler.AddButton(NewDeleteButton);
        NewEditButton->DrawButton();
        NewDeleteButton->DrawButton();
    }
    catch(...){
        gotoxy(0,9);
        std::cout << "Sorry but the person you're looking for doesn't exist or the data you typed was invalid!" << std::endl;
        Sleep(waitForNewAttempt);
        this->GoBackButton->onClick(handler);
        }
    }
    else if constexpr (std::is_same_v<N,Room>){
        try{
        gotoxy(0,1);
        std::cout << "Fill in with the data of the Room you're looking for please!" << std::endl;
        std::string roomId;
        std::string roomNumber;
        gotoxy(0,3);
        std::cout << "RoomId: " << std::endl;
        getStringInput(roomId,6,3);
        gotoxy(0,5);
        std::cout << "RoomNumber: " << std::endl;
        getStringInput(roomNumber,5,5);
        pos = this->hotel->searchForRoom(roomId,roomNumber);
        gotoxy(1,9);
        Room* room = this->hotel->getRooms()[pos];
        room->print();
        edit_delete_x = 110;
        BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8,8,0,"Edit",room,this->GoBackButton);
        BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9, 8,0,"Delete",room,this->GoBackButton);
        if(room->getDiscountState()){
            ApplyDiscountButton* applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20, 9,19,2,"Remove Discount",room,this->GoBackButton);
            handler.AddButton(applyDiscountButton);
            applyDiscountButton->DrawButton();
        }else{
            ApplyDiscountButton* applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20, 8,19,2,"Apply Discount",room,this->GoBackButton);
            handler.AddButton(applyDiscountButton);
            applyDiscountButton->DrawButton();
        }
        handler.AddButton(NewEditButton);
        handler.AddButton(NewDeleteButton);
        NewEditButton->DrawButton();
        NewDeleteButton->DrawButton();
    }
    catch(...){
        gotoxy(0,9);
        std::cout << "Sorry but the room you're looking for doesn't exist or the data you typed was invalid!" << std::endl;
        Sleep(waitForNewAttempt);
        this->GoBackButton->onClick(handler);
    }
    }else if constexpr (std::is_same_v<N,Reservation>){
        try{
            gotoxy(0,1);
            std::vector<int> positions;
            std::cout << "Which criteria do you want to look for Reservations for?" << std::endl;
            std::string criteria;
            std::string value;
            getStringInput(criteria,50,1);
            if(criteria != "Date" && criteria != "ID" && criteria != "Room"){
                gotoxy(0,3);
                std::cout << "Not a valid criteria! Aborting search process!" << std::endl;
                Sleep(waitForNewAttempt);
                this->GoBackButton->onClick(handler);
            }
            gotoxy(0,3);
            std::cout << criteria << " : " << std::endl;
            getStringInput(value,7,3);
            positions = this->hotel->searchReservations(criteria,value);
            if(positions.size() == 0){
                gotoxy(0,5);
                std::cout << "No Reservation matching your search!" << std::endl;
                Sleep(waitForNewAttempt);
                this->GoBackButton->onClick(handler);
            }
            gotoxy(1,5);
            int increment_y = 0;
            edit_delete_x = 90;
            gotoxy(1,1);
            std::cout << "Reservations: ";
            gotoxy(20,3);
            edit_delete_x = 90;
            gotoxy(1,5);
            std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation Id"
                      << std::setw(25) << "Reservation Size"
                      << std::setw(15) << "CheckIn" << std::setw(15) << "CheckOut" << std::setw(8) << "RoomId";
            for(auto pos: positions){
                Reservation* reservation = this->hotel->getReservations()[pos];
                reservation->print();
                BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8 + increment_y,8,0,"Edit",reservation,this->GoBackButton);
                BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9 + increment_y, 8,0,"Delete",reservation,this->GoBackButton);
                handler.AddButton(NewEditButton);
                handler.AddButton(NewDeleteButton);
                NewEditButton->DrawButton();
                NewDeleteButton->DrawButton();
                increment_y += 3;
            }
        }
        catch(...){
            gotoxy(0,9);
            std::cout << "Sorry but the room you're looking for doesn't exist or the data you typed was invalid!" << std::endl;
            Sleep(waitForNewAttempt);
            this->GoBackButton->onClick(handler);
        }
    }

}

template <class N>
ChangeTypeOfSort<N>::ChangeTypeOfSort(const int x, const int y, const int width, const int height, const std::string text,std::string type, MenuButton<N> *menu_button):BaseButton(x,y,width,height,text) {
    this->menu_button = menu_button;
    this->type = type;
}

template <class N>
void ChangeTypeOfSort<N>::onClick(ButtonHandler &handler) {
    if(this->getText() == "<"){
        if(this->type == "type_id"){
            this->menu_button->ChangeTypeId(-1);
        }else if(this->type == "order_id"){
            this->menu_button->ChangeOrderId(-1);
        }else{
            this->menu_button->ChangeCurrentPage(-1);
        }
    }else{
        if(this->type == "type_id"){
            this->menu_button->ChangeTypeId(1);
        }else if(this->type == "order_id"){
            this->menu_button->ChangeOrderId(1);
        }else{
            this->menu_button->ChangeCurrentPage(1);
        }
    }

    clearscreen();
    handler.SpecialGoBackClear();
    this->menu_button->onClick(handler);
}

template <class N>
SortButton<N>::SortButton(const int x, const int y, const int width, const int height, const std::string text, Hotel* hotel,std::string order,std::string type,MenuButton<N> *menu_button): BaseButton(x,y,width,height,text) {
    this->menu_button = menu_button;
    this->hotel = hotel;
    this->order = order;
    this->type = type;
}

template <class N>
void SortButton<N>::onClick(ButtonHandler &handler) {
    if constexpr (std::is_same_v<N,Client>)
        this->hotel->clientSort(this->type,this->order);
    else if constexpr (std::is_same_v<N,Room>){
        this->hotel->sortRooms(this->type,this->order);
    }
    clearscreen();
    handler.SpecialGoBackClear();
    this->menu_button->onClick(handler);
}


template <class N>
void MenuButton<N>::EraseObject(N* item) {
    if constexpr (std::is_same_v<N,Client>){
        this->hotel->eraseClient(item);
    }
    else if constexpr (std::is_same_v<N,Staff>){
        this->hotel->eraseStaff(item);
    }
    else if constexpr (std::is_same_v<N,Room>){
        this->hotel->eraseRoom(item);
    }else if constexpr (std::is_same_v<N,Reservation>){
        if(this->client == nullptr){
            this->hotel->deleteReservation(item);
        }else{
            this->client->removeReservation(item);
        }

    }
}

template <class N>
Hotel * MenuButton<N>::getHotel() {
    return this->hotel;
}

template <class N>
Client * MenuButton<N>::getClient() {
    return this->client;
}

template <class N>
void MenuButton<N>::AddObject(N*  item) {
    if constexpr (std::is_same_v<N,Client>){
        this->hotel->addClient(item);
    }
    else if constexpr (std::is_same_v<N,Staff>){
        this->hotel->addStaff(item);
    }
    else if constexpr (std::is_same_v<N,Room>){
        this->hotel->addRoom(item);
    }
    else if constexpr (std::is_same_v<N,Reservation>){
        this->client->addToHistory(item);
    }
}

template <class N>
AddButton<N>::AddButton(const int x, const int y, const int width, const int height, const std::string text,
                        MenuButton<N>* Button) : BaseButton(x,y,width,height,text){
    this->Button = Button;
}

template <class N>
void AddButton<N>::onClick(ButtonHandler& handler) {
    clearscreen();
    if constexpr (std::is_same_v<N,Staff>){
        std::string input = "5";
        while(input != "1" && input != "2" && input != "3" && input != "4") {
            gotoxy(0,0);
            std::cout << "Which type of staff member would you like to add?" << std::endl;
            std::cout << "1- Receptionist" << std::endl;
            std::cout << "2- Responsible" << std::endl;
            std::cout << "3- Manager" << std::endl;
            std::cout << "4- Janitor" << std::endl;
            std::cout << "Your choice:                                      ";
            getStringInput(input, 12, 5);

        }
        clearscreen();
        int input_ = std::stoi(input);
        switch(input_){
            case 1:{
                Receptionist* receptionist = new Receptionist("",0,0);
                edit(receptionist);
                this->Button->AddObject(receptionist);
                break;

            }
            case 2:{
                Responsible* responsible = new Responsible("",0,0);
                edit(responsible);
                this->Button->AddObject(responsible);
                break;
            }

            case 3:{
                Manager* manager = new Manager("",0,0,"balls");
                edit(manager);
                this->Button->AddObject(manager);
                break;
            }

            case 4:{
                Janitor* janitor = new Janitor(true,"",0,0);
                edit(janitor);
                this->Button->AddObject(janitor);
                break;
            }

        }

    }else if constexpr (std::is_same_v<N,Client>){
        Client* client = new Client("",0);
        edit(client);
        this->Button->AddObject(client);
    }else if constexpr (std::is_same_v<N,Room>){
        std::string input = "5";
        while(input != "1" && input != "2" && input != "3") {
            gotoxy(0,0);
            std::cout << "Which type of Room would you like to add?" << std::endl;
            std::cout << "1- NoViewRoom" << std::endl;
            std::cout << "2- ViewRoom" << std::endl;
            std::cout << "3- Suite" << std::endl;
            std::cout << "Your choice:                                      ";
            getStringInput(input, 12, 5);

        }
        int input_ = std::stoi(input);
        clearscreen();
        switch(input_){
            case 1:{
                NoViewRoom* NoViewRoom_ = new NoViewRoom(0,0,0,0,0);
                edit(NoViewRoom_,this->Button->getHotel());
                this->Button->AddObject(NoViewRoom_);
                break;

            }
            case 2:{
                ViewRoom* ViewRoom_ = new ViewRoom(0,0,0,0,0);
                edit(ViewRoom_,this->Button->getHotel());
                this->Button->AddObject(ViewRoom_);
                break;
            }

            case 3:{
                Suite* suite = new Suite(0,0,0,0,0);
                edit(suite,this->Button->getHotel());
                this->Button->AddObject(suite);
                break;
            }

        }
    }else if constexpr (std::is_same_v<N,Reservation>){
        Reservation* reservation = new Reservation(0,0,0,0,0,0,0,0);
        edit(reservation,this->Button->getHotel(),this->Button->getClient());
        this->Button->AddObject(reservation);
    }

    this->Button->onClick(handler);

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
    while(!hotel->getLoggedInState()){
        std::cout << "Please write your name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "Please write your password: ";
        std::getline(std::cin,passwordAttempt);
        try{
            hotel->logIn(name,passwordAttempt);
            break;
        }
        catch(IncorrectCredentials& msg){
            std::cout << msg;
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
template class MenuButton<Reservation>;