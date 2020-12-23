#include "buttons.h"
#include <algorithm>
#include <cmath>
#include <type_traits>


BaseButton::BaseButton(const int x, const int y, const int width, const int height, const std::string &text):
        x(x),y(y),width(width),height(height),text(text){};

int BaseButton::getHeight() const {
    return this->height;
}

int BaseButton::getWidth() const {
    return this->width;
}

int BaseButton::getX() const{
    return this->x;
}

int BaseButton::getY() const{
    return this->y;
}

std::string BaseButton::getText() const{
    return this->text;
}

void BaseButton::setText(const std::string& text) {
    this->text = text;
}

ButtonHandler::ButtonHandler(std::vector<BaseButton*> InitialButtons) {
    this->CurrentButtons = InitialButtons;
}

void ButtonHandler::AddButton(BaseButton* button) {
    this->CurrentButtons.push_back(button);
}

void ButtonHandler::DeleteButton(BaseButton* button) {
    auto find = std::find(this->CurrentButtons.begin(),this->CurrentButtons.end(),button);
    this->CurrentButtons.erase(find);
}

void ButtonHandler::SpecialGoBackClear() {
    for(auto& button: this->CurrentButtons){
        if(button->getText() != "Transactions"  && button->getText() != "Clients"&& button->getText() != "Log Out" &&button->getText() != "Log In" &&button->getText() != "Save Hotel" && button->getText() != "Providers" && button->getText() != "Search" && button->getText() != "Reservations" && button->getText() != "Rooms" && button->getText() != "Staff" && button->getText() != "Back")
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

LogInOutButton::LogInOutButton(const int x, const int y, const int width, const int height, const std::string text,
                               Hotel *hotel, MenuButton<Staff> *StaffButton, MenuButton<Provider>* ProviderButton,MenuButton<Transaction>* TransButton) :BaseButton(x,y,width,height,text) {
    this->hotel = hotel;
    this->StaffButton =  StaffButton;
    this->ProvidersButton = ProviderButton;
    this->TransactionsButton = TransButton;
}

void LogInOutButton::onClick(ButtonHandler &handler) {
    if(this->hotel->getLoggedInState()){
        handler.DeleteButton(this->StaffButton);
        handler.DeleteButton(this->ProvidersButton);
        handler.DeleteButton(this->TransactionsButton);
        hotel->logOut();
        this->setText("Log In ");
        clearscreen();
        for(auto button: handler.getButtons()){
            button->DrawButton();
        }
    }else{
        try{
            clearscreen();
            std::string username, password;
            std::cout << "Insert Username"<< std::endl;
            getStringInput(username,0,1);
            gotoxy(0,3);
            std::cout << "Insert Password"<< std::endl;
            getStringInput(password,0,4);
            hotel->logIn(username,password);
            clearscreen();
            handler.AddButton(this->StaffButton);
            handler.AddButton(this->ProvidersButton);
            handler.AddButton(this->TransactionsButton);
            this->setText("Log Out");
            for(auto button: handler.getButtons()){
                button->DrawButton();
            }
        }
        catch(IncorrectCredentials& msg){
            gotoxy(0,6);
            std::cout << msg;
            Sleep(2000);
            clearscreen();
            for(auto button: handler.getButtons()){
                button->DrawButton();
            }
        }
    }
}

template <class N>
EditButton<N>::EditButton(const int x, const int y, const int width, const int height, const std::string text,
                          N * object,MenuButton<N>* button):ModifyButton<N>(x,y,width,height,text,object) {
    this->OriginalButton = button;
};

template <class N>
void EditButton<N>::onClick(ButtonHandler& handler) {
    clearscreen();
    int waitSeeMessage = 2000;
    std::vector<std::string> fields;
    if constexpr (std::is_same_v<N,Staff>){
        int pos = std::find(this->OriginalButton->getHotel()->getStaff().begin(),this->OriginalButton->getHotel()->getStaff().end(),this->getObject()
        ) -  this->OriginalButton->getHotel()->getStaff().begin();
        try {
            fields = askStaff();
            fields.push_back(" ");
            fields.push_back(" ");
            fields.push_back(" ");
            fields.push_back(" ");
            this->OriginalButton->getHotel()->modifyStaffMember(fields[0],fields[1],fields[2],pos,fields[3],fields[4],fields[4],fields[5]);

        } catch(NIFIsNotValid& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(NotAPositiveFloat& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(NotAnInt& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(StaffMemberWithThisNIFAlreadyExists& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(StaffMemberDoesNotExist& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(StaffMemberAlreadyExists& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(InvalidShift& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(InvalidPosition& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(InvalidEvaluation& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
    }else if constexpr (std::is_same_v<N,Room>){
        int pos = std::find(this->OriginalButton->getHotel()->getRooms().begin(),this->OriginalButton->getHotel()->getRooms().end(),this->getObject()
        ) -  this->OriginalButton->getHotel()->getRooms().begin();
        fields = askRoom();
        try{
            this->OriginalButton->getHotel()->modifyRoom(fields[0],fields[1],pos);
        }catch(NotAPositiveInt& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(NotAnInt& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(RoomDoesNotExist& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(RoomAlreadyExists& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(FloorDoesNotExist& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(InvalidRoomType& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(NotAPositiveFloat& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
    }else if constexpr (std::is_same_v<N,Client>){
        int pos = std::find(this->OriginalButton->getHotel()->getClients().begin(),this->OriginalButton->getHotel()->getClients().end(),this->getObject()
        ) -  this->OriginalButton->getHotel()->getClients().begin();
        fields = askClient();
        try{
            this->OriginalButton->getHotel()->modifyClient(fields[0],fields[1],pos);
        }catch(NIFIsNotValid& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(ClientDoesNotExist& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(ClientAlreadyExists& msg){
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
    }else if constexpr (std::is_same_v<N,Reservation>){
        int pos = std::find(this->OriginalButton->getHotel()->getClients().begin(),this->OriginalButton->getHotel()->getClients().end(),this->OriginalButton->getClient()
        ) -  this->OriginalButton->getHotel()->getClients().begin();
        fields = askmodifyReservation();
        try{
            this->OriginalButton->getHotel()->modifyReservation(this->getObject(),fields[0],fields[1],fields[2],fields[3],pos);
        }
        catch(NotAPositiveInt& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(NotAnInt& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(DateIsNotValid& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(ReservationHasInvalidDates& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(RoomDoesNotHaveTheNecessaryCapacity& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(ClientCantMakeThisReservation& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(AnotherReservationForThisRoomAlreadyExistsAtThisTime& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
        catch(NoReservationsToCheckIn& msg) {
            gotoxy(0, 15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }
    catch(RoomDoesNotExist& msg){
        gotoxy(0,15);
        std::cout << msg;
        Sleep(waitSeeMessage);
    }catch(CantMakeNewResevOldResev& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitSeeMessage);
        }

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
    this->GoBack_Button = ParentButton;
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
    this->GoBack_Button = ParentButton;
    this->hotel = hotel;
    this->type_id = 0;
    this->order_id = 0;
}

template<class N>
MenuButton<N>::MenuButton(const int x, const int y, const int width, const int height, const std::string &text,const int currentPage, Hotel* hotel,Provider *provider, BaseButton *ParentButton):BaseButton(x,y,width,height,text) {
    this->provider = provider;
    this->GoBack_Button = ParentButton;
    this->client = nullptr;
    this->hotel = hotel;
    this->type_id = 0;
    this->order_id = 0;
    this->CurrentPage = currentPage;

}

BuyButton::BuyButton(const int x, const int y, const int width, const int height, const std::string text, Hotel* hotel,Product *product, MenuButton<Product> *menu_button):BaseButton(x,y,width,height,text) {
                         this->product = product;
                         this->GoBackButton = menu_button;
                         this->hotel = hotel;
}
void BuyButton::onClick(ButtonHandler &handler) {
    this->hotel->buy(this->product->getId());
    this->GoBackButton->onClick(handler);
}


template <typename N>
void MenuButton<N>::onClick(ButtonHandler& handler) {
    std::vector <N*> menu_items = {};
    if(this->GoBack_Button == nullptr){
        this->GoBack_Button = new ParentButton(90,0,6,2,"Back",handler.getButtons());
    }
    else{
        this->GoBack_Button = new GoBackButton(90,0,6,2,"Back",this->GoBack_Button);
    }
    handler.ClearButtons();
    int MaxObjectsOnScreen = 7;
    clearscreen();
    int edit_delete_x;
    int increment_y = 0;
    this->GoBack_Button->DrawButton();
    handler.AddButton(this->GoBack_Button);
    ChangePage<N>* ChangePagesBack;
    ChangePage<N>* ChangePagesFront;
    if constexpr (std::is_same_v<N,Reservation>){
        SearchButton<N>* searchButton = new SearchButton<N>(30,0,8,2,"Search",this->hotel,this);
        handler.AddButton(searchButton);
        searchButton->DrawButton();
        if(this->client != nullptr){
            auto addButton = new AddButton<N>(20,0,4,2,"+",this);
            addButton->DrawButton();
            handler.AddButton(addButton);
        }
    }
    else if constexpr (!std::is_same_v<N,Provider> && !std::is_same_v<N,Product> && !std::is_same_v<N,Transaction>){
        auto addButton = new AddButton<N>(20,0,4,2,"+",this);
        addButton->DrawButton();
        handler.AddButton(addButton);
        SearchButton<N>* searchButton = new SearchButton<N>(30,0,8,2,"Search",this->hotel,this);
        handler.AddButton(searchButton);
        searchButton->DrawButton();
    }

    std::vector<std::string> order = {"Ascending","Descending"};
    if(this->order_id >= order.size()) {
        this->order_id = 0;
    }
    else if(this->order_id < 0){
        this->order_id = order.size() - 1;
    }
    if constexpr(std::is_same_v<N,Client>){
        menu_items = this->hotel->getClients();
        edit_delete_x = 60;
        int max_page = std::ceil((menu_items.size()) / (double)MaxObjectsOnScreen);
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        else if(this->CurrentPage > max_page) this->CurrentPage = 1;
        ChangePagesBack = new ChangePage<N>(17,3,2,0,"<","page_id",this);
        ChangePagesFront = new ChangePage<N>(29,3,2,0,">","page_id",this);
        gotoxy(1,1);
        std::cout << "CLIENTS: ";
        gotoxy(20,3);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        gotoxy(1,8);
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Name" << std::setw(10) << "NIF" << std::endl;
        std::vector<std::string> typeOfSort {"Name", "NIF","Future reservations", "Past reservations"};
        if(this->type_id >= typeOfSort.size()){
            this->type_id = 0;
        }
        else if(this->type_id < 0){
            this->type_id = typeOfSort.size() - 1;
        }
        gotoxy(edit_delete_x + 35,14);
        std::cout << std::left << std::setw(15) << order[this->order_id];
        gotoxy(edit_delete_x + 35,16);
        std::cout << std::setw(15) << typeOfSort[this->type_id];
        SortButton<N>* sortClientsButton = new SortButton<N>(edit_delete_x + 40,11,5,2,"Sort by: ",this->hotel,order[order_id],typeOfSort[type_id],this);
        ChangePage<N>* ChangePage1 = new ChangePage<N>(edit_delete_x + 32,14,2,0,"<","order_id",this);
        ChangePage<N>* ChangePage2 = new ChangePage<N>(edit_delete_x + 44,14,2,0,">","order_id",this);
        ChangePage<N>* ChangePage3 = new ChangePage<N>(edit_delete_x + 32,16,2,0,"<","type_id",this);
        ChangePage<N>* ChangePage4 = new ChangePage<N>(edit_delete_x + 35 + typeOfSort[this->type_id].size() + 1,16,2,0,">","type_id",this);
        handler.AddButton(ChangePage1);
        ChangePage1->DrawButton();
        ChangePage2->DrawButton();
        ChangePage3->DrawButton();
        ChangePage4->DrawButton();
        handler.AddButton(ChangePage2);
        handler.AddButton(ChangePage3);
        handler.AddButton(ChangePage4);
        sortClientsButton->DrawButton();
        handler.AddButton(sortClientsButton);
    }
    else if constexpr (std::is_same_v<N,Transaction>){
        menu_items = this->hotel->getAccounting();
        MaxObjectsOnScreen = 7;
        int max_page = std::ceil((menu_items.size()) / (double)MaxObjectsOnScreen);
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        else if(this->CurrentPage > max_page) this->CurrentPage = 1;
        gotoxy(10,3);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        ChangePagesBack = new ChangePage<N>(8,3,2,0,"<","page_id",this);
        ChangePagesFront = new ChangePage<N>(18,3,2,0,">","page_id",this);
        ChangePagesFront->DrawButton();
        ChangePagesBack->DrawButton();
        handler.AddButton(ChangePagesBack);
        handler.AddButton(ChangePagesFront);
        gotoxy(1,1);
        std::cout << "Hotel Transactions: ";
        gotoxy(1,5);
        std::cout << std::setw(8) << std::setfill(' ') <<"Value  " << "Description"<< std::endl;
        for(int i = 0 + (this->CurrentPage-1) * MaxObjectsOnScreen; i < this->CurrentPage* MaxObjectsOnScreen;i++) {
            if (i >= menu_items.size()) {
                break;
            }
            gotoxy(1,increment_y + 7);
            std::cout << std::setw(8) << std::setfill(' ')<< menu_items[i]->value << "  " << menu_items[i]->description<< std::endl;
            increment_y += 3;
        }
        return;
    }

    else if constexpr (std::is_same_v<N,Provider>){
        menu_items = this->hotel->getProviders();
        MaxObjectsOnScreen = 7;
        edit_delete_x = 50;
        int max_page = std::ceil((menu_items.size()) / (double)MaxObjectsOnScreen);
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        else if(this->CurrentPage > max_page) this->CurrentPage = 1;
        gotoxy(70,8);
        std::cout << "Current Budget: " << this->hotel->getProfit() << std::endl;
        gotoxy(70,10);
        std::cout << "Cleaning Products Necessary: " << this->hotel->getCleaningNecessity() << std::endl;
        gotoxy(70,12);
        std::cout << "Catering Products Necessary: " << this->hotel->getCateringNecessity() << std::endl;
        gotoxy(70,14);
        std::cout << "Other Products Necessary: " << this->hotel->getOtherNecessity() << std::endl;
        gotoxy(1,3);
        std::cout << "Providers: ";
        gotoxy(10,5);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        ChangePagesBack = new ChangePage<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangePage<N>(19,5,2,0,">","page_id",this);
        auto autoBuyButton = new AutoBuyButton(70,16,8,2,"Auto Buy",this->hotel,this);
        autoBuyButton->DrawButton();
        handler.AddButton(autoBuyButton);

    }
    else if constexpr (std::is_same_v<N,Product>){
        menu_items = this->provider->getProducts();
        MaxObjectsOnScreen = 7;
        edit_delete_x = 60;
        int max_page = std::ceil((menu_items.size()) / (double)MaxObjectsOnScreen);
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        else if(this->CurrentPage > max_page) this->CurrentPage = 1;
        gotoxy(1,3);
        std::cout << "Products for Provider " << this->provider->getName();
        gotoxy(10,5);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        ChangePagesBack = new ChangePage<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangePage<N>(19,5,2,0,">","page_id",this);
        gotoxy(1,8);
        std::cout  <<std::left<< std::setfill(' ') <<std::setw(7)<< "Stock" << std::setw(10) << "Type"
        << std::setw(9) << "ID" <<std::setw(7) << "Price" << std::setw(7) << "Quality" <<std::endl;

    }
    else if constexpr (std::is_same_v<N,Reservation>){
        if(this->client != nullptr){
            menu_items = this->client->getAllReservations();
        }
        else menu_items = this->hotel->getReservations();
        int max_page = std::ceil((menu_items.size()) / (double)MaxObjectsOnScreen);
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        } else if(this->CurrentPage > max_page) this->CurrentPage = 1;
        std::vector<std::string> typeOfSort {"Room Id", "Check In","Check Out"};
        if(this->type_id >= typeOfSort.size()){
            this->type_id = 0;
        }
        else if(this->type_id < 0){
            this->type_id = typeOfSort.size() - 1;
        }

        gotoxy(40,4);
        std::cout << std::left << std::setw(17) << order[this->order_id];
        gotoxy(62,4);
        std::cout << std::setw(20) << typeOfSort[this->type_id];

        SortButton<N>* sortReservationsButton = new SortButton<N>(50,1,5,2,"Sort by: ",this->hotel,order[order_id],typeOfSort[type_id],this);
        ChangePage<N>* ChangePage1 = new ChangePage<N>(38,4,2,0,"<","order_id",this);
        ChangePage<N>* ChangePage2 = new ChangePage<N>(40 + order[this->order_id].size() + 1,4,2,0,">","order_id",this);
        ChangePage<N>* ChangePage3 = new ChangePage<N>(60,4,2,0,"<","type_id",this);
        ChangePage<N>* ChangePage4 = new ChangePage<N>(62 + typeOfSort[this->type_id].size() + 1,4,2,0,">","type_id",this);
        handler.AddButton(ChangePage1);
        ChangePage1->DrawButton();
        ChangePage2->DrawButton();
        ChangePage3->DrawButton();
        ChangePage4->DrawButton();
        handler.AddButton(ChangePage2);
        handler.AddButton(ChangePage3);
        handler.AddButton(ChangePage4);
        sortReservationsButton->DrawButton();
        handler.AddButton(sortReservationsButton);

        ChangePagesBack = new ChangePage<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangePage<N>(19,5,2,0,">","page_id",this);
        gotoxy(1,3);
        std::cout << "Reservations: ";
        gotoxy(10,5);
        std::cout << "Page " << this->CurrentPage << "/" << max_page;
        edit_delete_x = 110;
        gotoxy(1,8);
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation Id"
                  << std::setw(25) << "Reservation Size"
                  << std::setw(15) << "CheckIn" << std::setw(15) << "CheckOut" << std::setw(8) << "RoomId";
    }
    else if constexpr (std::is_same_v<N,Room>){
        menu_items = this->hotel->getRooms();
        int max_page = std::ceil((menu_items.size()) / (double)MaxObjectsOnScreen);
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }
        else if(this->CurrentPage > max_page){this->CurrentPage = 1;}

        std::vector<std::string> typeOfSort {"Room ID", "Room Number", "Floor", "Capacity", "Price", "Type"};
        if(this->type_id >= typeOfSort.size()){
            this->type_id = 0;
        }
        else if(this->type_id < 0){
            this->type_id = typeOfSort.size() - 1;
        }
        gotoxy(40,4);
        std::cout << std::left << std::setw(17) << order[this->order_id];
        gotoxy(62,4);
        std::cout << std::setw(20) << typeOfSort[this->type_id];
        SortButton<N>* sortRoomsButton = new SortButton<N>(50,1,5,2,"Sort by: ",this->hotel,order[order_id],typeOfSort[type_id],this);
        ChangePage<N>* ChangePage1 = new ChangePage<N>(38,4,2,0,"<","order_id",this);
        ChangePage<N>* ChangePage2 = new ChangePage<N>(40 + order[this->order_id].size() + 1,4,2,0,">","order_id",this);
        ChangePage<N>* ChangePage3 = new ChangePage<N>(60,4,2,0,"<","type_id",this);
        ChangePage<N>* ChangePage4 = new ChangePage<N>(62 + typeOfSort[this->type_id].size() + 1,4,2,0,">","type_id",this);
        handler.AddButton(ChangePage1);
        ChangePage1->DrawButton();
        ChangePage2->DrawButton();
        ChangePage3->DrawButton();
        ChangePage4->DrawButton();
        handler.AddButton(ChangePage2);
        handler.AddButton(ChangePage3);
        handler.AddButton(ChangePage4);
        sortRoomsButton->DrawButton();
        handler.AddButton(sortRoomsButton);
        if(this->hotel->getLoggedInState()) {
            auto ApplyMultipleDiscount = new ApplyDiscountToTypeOfRoom(40, 5, 10, 2, "Suite", this->hotel, this);
            auto ApplyMultipleDiscount2 = new ApplyDiscountToTypeOfRoom(55, 5, 12, 2, "ViewRoom", this->hotel, this);
            auto ApplyMultipleDiscount3 = new ApplyDiscountToTypeOfRoom(68, 5, 12, 2, "NoViewRoom", this->hotel, this);
            ApplyMultipleDiscount->DrawButton();
            handler.AddButton(ApplyMultipleDiscount);
            ApplyMultipleDiscount2->DrawButton();
            handler.AddButton(ApplyMultipleDiscount2);
            ApplyMultipleDiscount3->DrawButton();
            handler.AddButton(ApplyMultipleDiscount3);
        }
        ChangePagesBack = new ChangePage<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangePage<N>(18,5,2,0,">","page_id",this);
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
        int max_page = std::ceil((menu_items.size()) / (double)MaxObjectsOnScreen);
        if(this->CurrentPage == 0){
            this->CurrentPage = max_page;
        }else if(this->CurrentPage > max_page){this->CurrentPage = 1;}
        std::vector<std::string> typeOfSort {"Name", "NIF", "Wage", "Years of service", "Position"};
        if(this->type_id >= typeOfSort.size()){
            this->type_id = 0;
        }
        else if(this->type_id < 0){
            this->type_id = typeOfSort.size() - 1;
        }
        gotoxy(50,5);
        std::cout << std::left << std::setw(15) << order[this->order_id] << std::setw(20) << typeOfSort[this->type_id];
        SortButton<N>* sortStaffButton = new SortButton<N>(60,2,5,2,"Sort by: ",this->hotel,order[order_id],typeOfSort[type_id],this);
        ChangePage<N>* ChangePage1 = new ChangePage<N>(48,5,2,0,"<","order_id",this);
        ChangePage<N>* ChangePage2 = new ChangePage<N>(60,5,2,0,">","order_id",this);
        ChangePage<N>* ChangePage3 = new ChangePage<N>(63,5,2,0,"<","type_id",this);
        ChangePage<N>* ChangePage4 = new ChangePage<N>(63 + typeOfSort[this->type_id].size() + 2,5,2,0,">","type_id",this);
        handler.AddButton(ChangePage1);
        ChangePage1->DrawButton();
        ChangePage2->DrawButton();
        ChangePage3->DrawButton();
        ChangePage4->DrawButton();
        handler.AddButton(ChangePage2);
        handler.AddButton(ChangePage3);
        handler.AddButton(ChangePage4);
        sortStaffButton->DrawButton();
        handler.AddButton(sortStaffButton);
        ChangePagesBack = new ChangePage<N>(8,5,2,0,"<","page_id",this);
        ChangePagesFront = new ChangePage<N>(19,5,2,0,">","page_id",this);
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
    handler.AddButton(ChangePagesBack);
    handler.AddButton(ChangePagesFront);
    ChangePagesBack->DrawButton();
    ChangePagesFront->DrawButton();
    for(int i = 0 + (this->CurrentPage-1) * MaxObjectsOnScreen; i < this->CurrentPage* MaxObjectsOnScreen;i++){
        if (i >= menu_items.size()) {
            break;
        }
        gotoxy(1, 10 + increment_y);
        menu_items[i]->print();
        BaseButton *NewEditButton = new EditButton<N>(edit_delete_x, 9 + increment_y, 8, 0, "Edit", menu_items[i],
                                                      this);
        BaseButton *NewDeleteButton = new DeleteButton<N>(edit_delete_x, 10 + increment_y, 8, 0, "Delete",
                                                          menu_items[i], this);
        if constexpr (std::is_same_v<N, Room>) {
            if(this->hotel->getLoggedInState()){

            if (menu_items[i]->getDiscountState()) {
                ApplyDiscountButton *applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20,
                                                                                   9 + increment_y, 19, 2,
                                                                                   "Remove Discount", menu_items[i],
                                                                                   this);
                handler.AddButton(applyDiscountButton);
                applyDiscountButton->DrawButton();
            } else {
                ApplyDiscountButton *applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20,
                                                                                   9 + increment_y, 19, 2,
                                                                                   "Apply Discount", menu_items[i],
                                                                                   this);
                handler.AddButton(applyDiscountButton);
                applyDiscountButton->DrawButton();
            }
            if(menu_items[i]->getAvailability()){
                handler.AddButton(NewEditButton);
                NewEditButton->DrawButton();
                handler.AddButton(NewDeleteButton);
                NewDeleteButton->DrawButton();
            }
            }
           else if constexpr (std::is_same_v<N,Staff>){
               if (menu_items[i]->getType() != "Manager"){
                   NewDeleteButton->DrawButton();
                   handler.AddButton(NewDeleteButton);
               }
               NewEditButton->DrawButton();
               handler.AddButton(NewEditButton);
           }
        }else if constexpr (std::is_same_v<N,Product>){
            if(this->hotel->getProfit() - menu_items[i]->getPrice() <= 0.0){
                gotoxy(edit_delete_x,10 + increment_y);
                std::cout << "No money to buy this!";
            }
            else if(menu_items[i]->getStock() > 0){
                auto buyButton = new BuyButton(edit_delete_x,9 + increment_y,5,2,"Buy",this->hotel,menu_items[i],this);
                buyButton->DrawButton();
                handler.AddButton(buyButton);
            }else{
                gotoxy(edit_delete_x,10 + increment_y);
                std::cout << "Sold Out!";
            }

        }
        else if constexpr (std::is_same_v<N,Reservation>){
             if(menu_items[i]->getIsCurrent() && this->client != nullptr){
                int pos = std::find(this->hotel->getClients().begin(), this->hotel->getClients().end(), this->client
                ) - this->hotel->getClients().begin();
                CheckInCheckOut *checkIn = new CheckInCheckOut(edit_delete_x - 20, 9 + increment_y, 8, 2, "Check Out",
                                                               pos, this);
                checkIn->DrawButton();
                handler.AddButton(checkIn);
            }else if( this->client != nullptr && (menu_items[i]->getCheckIn() == this->hotel->getDate() || menu_items[i]->getCheckIn() < this->hotel->getDate()) && menu_items[i]->getCheckOut() > this->hotel->getDate()) {
                int pos = std::find(this->hotel->getClients().begin(), this->hotel->getClients().end(), this->client
                ) - this->hotel->getClients().begin();
                CheckInCheckOut *checkIn = new CheckInCheckOut(edit_delete_x - 20, 9 + increment_y, 8, 2, "Check In",
                                                               pos, this);
                checkIn->DrawButton();
                handler.AddButton(checkIn);
            }
             else if(!menu_items[i]->getIsCurrent()){
                 if (this->client != nullptr && menu_items[i]->getCheckOut() > this->hotel->getDate()){
                     handler.AddButton(NewEditButton);
                     NewEditButton->DrawButton();
                 }
                handler.AddButton(NewDeleteButton);
                NewDeleteButton->DrawButton();
            }

        }
        else if constexpr (std::is_same_v<N,Provider>){
            BaseButton* ShowProducts = new MenuButton<Product>(edit_delete_x,9 + increment_y,14,2,"Show Products",1,this->hotel,menu_items[i],this);
            handler.AddButton(ShowProducts);
            ShowProducts->DrawButton();
        }
        else if constexpr (std::is_same_v<N, Client>) {
            handler.AddButton(NewEditButton);
            NewEditButton->DrawButton();
            handler.AddButton(NewDeleteButton);
            NewDeleteButton->DrawButton();
            BaseButton *ShowReservationButton = new MenuButton<Reservation>(35, 9 + increment_y, 15, 2,
                                                                            "Show Reservations", 1, menu_items[i],
                                                                            this->hotel, this);
            handler.AddButton(ShowReservationButton);
            ShowReservationButton->DrawButton();
        }
        else if constexpr (!std::is_same_v<N, Provider>){
            handler.AddButton(NewEditButton);
            NewEditButton->DrawButton();
            handler.AddButton(NewDeleteButton);
            NewDeleteButton->DrawButton();
        }

        increment_y += 3;
    }
}


ApplyDiscountToTypeOfRoom::ApplyDiscountToTypeOfRoom(const int x, const int y, const int width, const int height,
                                                     const std::string text, Hotel *hotel, MenuButton<Room> *menu_button):BaseButton(x,y,width,height,text) {
                                                         this->hotel = hotel;
                                                         this->GoBackButton = menu_button;
                                                     }
void ApplyDiscountToTypeOfRoom::onClick(ButtonHandler &handler) {
    this->hotel->activateDiscount(this->getText());
    clearscreen();
    handler.SpecialGoBackClear();
    this->GoBackButton->onClick(handler);
}

AutoBuyButton::AutoBuyButton(const int x, const int y, const int width, const int height, const std::string text, Hotel *hotel, MenuButton<Provider> *menu_button): BaseButton(x,y,width,height,text){
    this->hotel = hotel;
    this->ProviderButton = menu_button;
}

void AutoBuyButton::onClick(ButtonHandler &handler) {
    this->hotel->autoBuy();
    this->ProviderButton->onClick(handler);
}

template <class N>
SearchButton<N>::SearchButton(const int x, const int y, const int width, const int height,
                                       const std::string text, Hotel *hotel, MenuButton<N> *menu_button): BaseButton(x,y,width,height,text) {
                                           this->hotel = hotel;
                                           this->goBackButton = menu_button;
                                       }

template <class N>
void SearchButton<N>::onClick(ButtonHandler &handler) {
    clearscreen();
    std::string type;
    int pos;
    int waitForNewAttempt = 3000;
    int edit_delete_x = 0;
    handler.SpecialGoBackClear();
    auto GoBackButton_ = new GoBackButton(90,0,6,2,"Go Back",this->goBackButton);
    handler.AddButton(GoBackButton_);
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
            BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8,8,0,"Edit",client,this->goBackButton);
            BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9, 8,0,"Delete",client,this->goBackButton);
            handler.AddButton(NewEditButton);
            handler.AddButton(NewDeleteButton);
            BaseButton* ShowReservationButton = new MenuButton<Reservation>(35,8,15,2,"Show Reservations",1,client,this->hotel,this->goBackButton);
            handler.AddButton(ShowReservationButton);
            ShowReservationButton->DrawButton();
            NewEditButton->DrawButton();
            NewDeleteButton->DrawButton();
        }
        catch(NIFIsNotValid& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(ClientDoesNotExist& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(ClientAlreadyExists& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
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
        BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8,8,0,"Edit",staff,this->goBackButton);
        BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9, 8,0,"Delete",staff,this->goBackButton);
        handler.AddButton(NewEditButton);
        handler.AddButton(NewDeleteButton);
        NewEditButton->DrawButton();
        NewDeleteButton->DrawButton();
    }
        catch(NIFIsNotValid& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(StaffMemberWithThisNIFAlreadyExists& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(StaffMemberDoesNotExist& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(StaffMemberAlreadyExists& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
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
        BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8,8,0,"Edit",room,  this->goBackButton);
        BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9, 8,0,"Delete",room,this->goBackButton);
        if(room->getDiscountState()){
            ApplyDiscountButton* applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20, 9,19,2,"Remove Discount",room,this->goBackButton);
            handler.AddButton(applyDiscountButton);
            applyDiscountButton->DrawButton();
        }else{
            ApplyDiscountButton* applyDiscountButton = new ApplyDiscountButton(edit_delete_x - 20, 8,19,2,"Apply Discount",room,this->goBackButton);
            handler.AddButton(applyDiscountButton);
            applyDiscountButton->DrawButton();
        }
        handler.AddButton(NewEditButton);
        handler.AddButton(NewDeleteButton);
        NewEditButton->DrawButton();
        NewDeleteButton->DrawButton();
    }catch(NotAPositiveInt& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(NotAnInt& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(RoomDoesNotExist& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
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
                this->goBackButton->onClick(handler);
                return;
            }
            gotoxy(0,3);
            std::cout << criteria << " : " << std::endl;
            getStringInput(value,7,3);
            positions = this->hotel->searchReservations(criteria,value);
            if(positions.size() == 0){
                gotoxy(0,5);
                std::cout << "No Reservation matching your search!" << std::endl;
                Sleep(waitForNewAttempt);
                this->goBackButton->onClick(handler);
                return;
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
                gotoxy(1,7 + increment_y);
                reservation->print();
                if(!reservation->getIsCurrent()){
                    BaseButton* NewEditButton = new EditButton<N>(edit_delete_x,8 + increment_y,8,0,"Edit",reservation,this->goBackButton);
                    BaseButton* NewDeleteButton = new DeleteButton<N>(edit_delete_x, 9 + increment_y, 8,0,"Delete",reservation,this->goBackButton);
                    handler.AddButton(NewEditButton);
                    handler.AddButton(NewDeleteButton);
                    NewEditButton->DrawButton();
                    NewDeleteButton->DrawButton();
                }
                increment_y += 3;
            }
        }
        catch(DateIsNotValid& msg){
            gotoxy(0,9);
            std::cout << msg;
            Sleep(waitForNewAttempt);
            this->goBackButton->onClick(handler);
            return;
        }
    }
    GoBackButton_->DrawButton();

}

template <class N>
ChangePage<N>::ChangePage(const int x, const int y, const int width, const int height, const std::string text,std::string type, MenuButton<N> *menu_button):BaseButton(x,y,width,height,text) {
    this->menu_button = menu_button;
    this->type = type;
}

template <class N>
void ChangePage<N>::onClick(ButtonHandler &handler) {
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

SaveHotelFileButton::SaveHotelFileButton(const int x, const int y, const int width, const int height, const std::string text, Hotel *hotel):BaseButton(x,y,width,height,text) {
    this->hotel = hotel;
}

void SaveHotelFileButton::onClick(ButtonHandler &handler) {
    int waitSeeMessage = 2000;
    gotoxy(70,8);
    std::cout << "Filename(w/o .txt): ";
    std::string edit;
    getStringInput(edit,70,9);
    this->hotel->saveHotel(edit);
    gotoxy(70,11);
    std::cout << "Saved Hotel File successfully!";
    Sleep(waitSeeMessage);
    gotoxy(70,8);
    std::cout << "                       ";
    gotoxy(70,11);
    std::cout << "                               ";
    gotoxy(70,9);
    std::cout << "                               ";

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
    }else if constexpr (std::is_same_v<N,Reservation>){
        if(this->menu_button->getClient() == nullptr)
            sortReservations(this->hotel->getReservations(),this->type,this->order);
        else
            sortReservations(this->menu_button->getClient()->getAllReservations(),this->type,this->order);
    }else if constexpr (std::is_same_v<N,Staff>){
        this->hotel->staffSort(this->type,this->order);
    }
    clearscreen();
    handler.SpecialGoBackClear();
    this->menu_button->onClick(handler);
}


template <class N>
void MenuButton<N>::EraseObject(N* item) {
    if constexpr (std::is_same_v<N,Client>){
        this->hotel->removeClient(item);
    }
    else if constexpr (std::is_same_v<N,Staff>){
        try {
            this->hotel->removeStaffMember(item);
        }catch(CantRemoveManager& msg){
            clearscreen();
            gotoxy(0,0);
            std::cout << msg << std::endl;
            Sleep(2000);
        }
        }
    else if constexpr (std::is_same_v<N,Room>){
        this->hotel->removeRoom(item);
    }else if constexpr (std::is_same_v<N,Reservation>){
        if(this->client == nullptr){
            this->hotel->deleteReservation(item);
        }else{
            this->client->deleteReservation(item);
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
AddButton<N>::AddButton(const int x, const int y, const int width, const int height, const std::string text,
                        MenuButton<N>* Button) : BaseButton(x,y,width,height,text){
    this->Button = Button;
}

template <class N>
void AddButton<N>::onClick(ButtonHandler& handler) {
    clearscreen();
    int waitForRead = 3000;
    std::vector<std::string> fields;
    if constexpr (std::is_same_v<N,Staff>){
        fields = askStaff();
        if(!fields.empty()){
            fields.push_back("");
            fields.push_back("");
            fields.push_back(" ");
            try{
                this->Button->getHotel()->addStaffMember(fields[0],fields[1],fields[3],fields[4],fields[4],fields[2],fields[5]);
            }
            catch(NIFIsNotValid& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(NotAPositiveFloat& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(NotAnInt& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(StaffMemberWithThisNIFAlreadyExists& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(StaffMemberDoesNotExist& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(StaffMemberAlreadyExists& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(InvalidShift& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(InvalidPosition& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
            catch(InvalidEvaluation& msg){
                gotoxy(0,16);
                std::cout << msg;
                Sleep(waitForRead);
            }
        }

    }else if constexpr (std::is_same_v<N,Client>){
        fields = askClient();
        try{
            this->Button->getHotel()->addClient(fields[0],fields[1]);
        }catch(NIFIsNotValid& msg){
            gotoxy(0,10);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            gotoxy(0,10);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(ClientDoesNotExist& msg){
            gotoxy(0,10);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(ClientAlreadyExists& msg){
            gotoxy(0,10);
            std::cout << msg;
            Sleep(waitForRead);
        }

    }else if constexpr (std::is_same_v<N,Room>){
        fields = askRoom();
        try{
            this->Button->getHotel()->addRoom(fields[0],fields[1],fields[2],fields[3],fields[4],fields[5]);
        }catch(NotAPositiveInt& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(NotAnInt& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(RoomDoesNotExist& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(RoomAlreadyExists& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(AccessRestricted& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(FloorDoesNotExist& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(InvalidRoomType& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(NotAPositiveFloat& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }

    }else if constexpr (std::is_same_v<N,Reservation>){
        int pos = std::find(this->Button->getHotel()->getClients().begin(),this->Button->getHotel()->getClients().end(),this->Button->getClient()
        ) -  this->Button->getHotel()->getClients().begin();
        unsigned int roomId;
        Date checkIn;
        Date checkOut;
        int capacity;
        int posClient;
        int reservationId;
        askReservation(roomId,checkIn,checkOut,capacity,reservationId);
        try{
            this->Button->getHotel()->makeReservation(roomId,&checkIn,&checkOut,capacity,pos,reservationId,false);
        }catch(RoomDoesNotExist& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(NotAPositiveInt& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(NotAnInt& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(DateIsNotValid& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(NIFIsNotValid& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(ReservationHasInvalidDates& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(RoomDoesNotHaveTheNecessaryCapacity& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(ClientCantMakeThisReservation& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(AnotherReservationForThisRoomAlreadyExistsAtThisTime& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }
        catch(NoReservationsToCheckIn& msg){
            gotoxy(0,15);
            std::cout << msg;
            Sleep(waitForRead);
        }

    }

    this->Button->onClick(handler);

}

CheckInCheckOut::CheckInCheckOut(const int x, const int y, const int width, const int height, const std::string text, int pos,MenuButton<Reservation>* menu_button):BaseButton(x,y,width,height,text) {
                                     this->Button = menu_button;
                                     this->pos = pos;
}

void CheckInCheckOut::onClick(ButtonHandler &handler) {
    if(this->getText() == "Check In") {
        this->Button->getHotel()->checkIn(this->pos, true);
    }else{
        this->Button->getHotel()->checkOut(this->pos);
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


template class MenuButton<Client>;
template class MenuButton<Staff>;
template class MenuButton<Room>;
template class MenuButton<Reservation>;
template class MenuButton<Provider>;
template class MenuButton<Transaction>;