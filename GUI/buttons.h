#ifndef BUTTONS_H
#define BUTTONS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "utils.h"
#include "../hotel/hotel.h"

class ButtonHandler;

/// \class BaseButton
/// The base class from which all buttons will inherit.
///
/// Only prints out a Button, without any onClick() event
class BaseButton{
private:
    ///top left x coordinate of the button
    int x;
    ///top left y coordinate of the button
    int y;
    ///width of the button to be drawn
    int width;
    ///height of the button to be drawn
    int height;
    ///text to be displayed inside of the button
    std::string text;

public:
    /// Constructor for BaseButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    BaseButton(const int x, const int y, const int width,const int height,const std::string &text);
    ///Virtual function for the on Click() event that derived classes will instantiate
    ///
    /// \param handler ButtonHandler responsible for keeping track of what buttons are currently on Screen
    virtual void onClick(ButtonHandler& handler) = 0;
    ///Draws the Button to the Screen
    void DrawButton();
    ///Gets the top left x coordinate of the Button
    int getX() const;
    ///Gets the top left y coordinate of the Button
    int getY() const;
    ///Gets the width of the button
    int getWidth() const;
    ///Gets the height of the button
    int getHeight() const;
    ///Gets text that the button is displaying
    ///\return text
    std::string getText() const;
    ///Alters the text that the button will display
    void setText(const std::string& text);

};

/// \class ButtonHandler
/// Class responsible for keeping track of the buttons on Screen and deleting the ones that
/// leave the Screen after a button press
class ButtonHandler{
private:
    ///vector storing the buttons that are currently on the screen
    std::vector<BaseButton*> CurrentButtons;
public:
    ///Initialize the ButtonHandler object with a vector of Initial Buttons
    explicit ButtonHandler(std::vector<BaseButton*>  InitialButtons);
    ///Add a button to the Current Buttons on Screen
    ///
    /// \param button button to be added to the Current Buttons
    void AddButton(BaseButton* button);
    ///\return Buttons that are currently on screen
    std::vector<BaseButton*> getButtons();
    ///Deletes all buttons from the Current Buttons vector, but doesn't free the memory, because the program
    ///is still using the button objects somewhere else
    void ClearButtons();
    ///Clears the Current Buttons vector, calling delete on the buttons inside
    void SpecialGoBackClear();
    ///Delete a particular button
    ///
    /// \param button button to be removed from Current Buttons vec
    void DeleteButton(BaseButton* button);
};

///\class ParentButton
/// Button used to store the initial menu buttons
/// to revive them at a later point when the user returns to the initial menu
class ParentButton: public BaseButton{
private:
    ///vector where the Initial Menu buttons are stored
    std::vector<BaseButton*> InitialButtons;
public:
    ///Initialize the ParentButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param InitialButtons takes the Initial Buttons
    ParentButton(const int x, const int y, const int width,const int height,const std::string &text,const std::vector<BaseButton*> InitialButtons);
    ///OnClick() for ParentButton displays the initial menu
    ///
    /// \param handler ButtonHandler responsible for keeping track of what buttons are currently on Screen
    void onClick(ButtonHandler& handler) override;
};

///Button that goes to the previous menu
class GoBackButton: public BaseButton{
private:
    ///pointer of the button that when clicked will display the previous menu
    BaseButton* NextButton;
public:
    ///Initialize the GoBackButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param ButtonNext the previous button
    GoBackButton(const int x, const int y, const int width,const int height,const std::string text,BaseButton * ButtonNext );
    ///OnClick() for GoBackButton displays the previous menu, by calling onClick() on the Previous Button stored by the class
    ///
    /// \param handler ButtonHandler responsible for keeping track of what buttons are currently on Screen
    void onClick(ButtonHandler& handler) override;
};

///Menu Button class that deals with displaying most of the information to the screen
/// as well as generating the right Edit, Delete,Add, Search and Sort Buttons for each object
template<class N>
class MenuButton : public BaseButton{
private:
    ///pointer to the hotel object
    Hotel* hotel;
    ///points to a particular client object
    Client* client;
    ///points to a particular provider object
    Provider* provider;
    ///the current Page of objects that the MenuButton is currently displaying
    int CurrentPage;
    ///the previous button
    BaseButton* GoBack_Button;
    ///index of the type of sort to perform(varies according to class)
    int type_id;
    ///index of the order of the sort (can only be 0 - Ascending 1-Descending)
    int order_id;
public:
    ///Initialize the MenuButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param currentPage the Page of objects to be displayed
    /// \param hotel pointer to the Hotel object
    /// \param ParentButton pointer to the last button pressed, if nullptr, then it becomes the Parent Button
    MenuButton(const int x, const int y, const int width,const int height,const std::string &text,const int currentPage,
               Hotel* hotel,BaseButton* ParentButton);
    ///Initialize MenuButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param currentPage the Page of objects to be displayed
    /// \param client points to a client object
    /// \param hotel points to Hotel object
    /// \param ParentButton pointer to the last button pressed, if nullptr, then it becomes the Parent Button
    MenuButton(const int x, const int y, const int width,const int height,const std::string &text,const int currentPage,
               Client* client,Hotel* hotel,BaseButton* ParentButton);
    ///Initialize Menu Button
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param currentPage the Page of objects to be displayed
    /// \param hotel points to Hotel object
    /// \param provider pointer to a Provider Object
    /// \param ParentButton pointer to the last button pressed, if nullptr, then it becomes the Parent Button
    MenuButton(const int x, const int y, const int width,const int height,const std::string &text,const int currentPage,Hotel* hotel,
               Provider* provider,BaseButton* ParentButton);
    ///onClick() event will display the list of whatever whatever template the class was instantiated with
    ///
    /// \param handler ButtonHandler responsible for keeping track of what buttons are currently on Screen
    void onClick(ButtonHandler& handler) override;
    /// Handles removing an object from a given class from the hotel object
    ///
    /// \param item pointer to object to be removed
    void EraseObject(N* item);
    ///\return pointer to the Hotel object
    Hotel* getHotel();
    ///\return pointer to the Client object
    Client* getClient();
    /// Modify the page that's being displayed, called after a press of the ChangePage button
    ///
    /// \param page number of pages to be added to CurrentPage
    void ChangeCurrentPage(int page);
    ///\return CurrentPage that is on display
    int getCurrentPage();
    /// Updates the typeId altering a parameter for the Sort Method
    ///
    /// \param i number to add to our typeId index
    void ChangeTypeId(int i);
    /// Updates the orderId altering the order for the Sort Method
    ///
    /// \param i number to add to our typeId index
    void ChangeOrderId(int i);

};

/// Button responsible for calling the Hotel's logIn and logOut methods
class LogInOutButton: public BaseButton{
private:
    ///pointer to the hotel object that stores the loggedIn state
    Hotel* hotel;
    ///The StaffButton can only be accessed when the Manager is LoggedIn, so it is stored here, to be added to the CurrentButtons when log In is completed
    MenuButton<Staff>* StaffButton;
    ///The ProvidersButton can only be accessed when the Manager is LoggedIn, so it is stored here, to be added to the CurrentButtons when log In is completed
    MenuButton<Provider>* ProvidersButton;
    ///The TransactionsButton can only be accessed when the Manager is LoggedIn, so it is stored here, to be added to the CurrentButtons when log In is completed
    MenuButton<Transaction>* TransactionsButton;
public:
    ///Initialize the LogIn Button's attributes
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param hotel points to Hotel object
    /// \param StaffButton pointer to a MenuButton of the Staff type
    /// \param ProviderButton pointer to a MenuButton of the Provider type
    /// \param TransButton pointer to a MenuButton of the Transactions type
    LogInOutButton(const int x, const int y, const int width,const int height,const std::string text,Hotel* hotel,MenuButton<Staff>* StaffButton,MenuButton<Provider>* ProviderButton,MenuButton<Transaction>* TransButton);
    ///onClick method will perform the LogIn if not LoggedIn, LogOut if otherwise
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Handles checkIn and checkOut of a Reservation
class CheckInCheckOut: public BaseButton{
private:
    ///used as the GoBackButton
    MenuButton<Reservation>* Button;
    ///position of the Reservation to checkOut on the Reservation vector
    int pos;
public:
    ///Initialize the CheckInCheckOut Button
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param pos index of the Reservation object to be checkedIn or checkedOut
    /// \param menu_button the GoBack Button
    CheckInCheckOut(const int x, const int y, const int width,const int height,const std::string text,int pos,MenuButton<Reservation>* menu_button);
    ///Upon a mouse click, will call checkIn of the reservation or if already checkedIn and if it's not past its checkOut date, call checkOut() method instead
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Handles the purchase of a Product
class BuyButton: public BaseButton{
private:
    ///product to be bought when button is clicked
    Product* product;
    ///button to display after a click
    MenuButton<Product>* GoBackButton;
    ///hotel object needed to call the buy() method
    Hotel* hotel;
public:
    ///Initialize the BuyButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param hotel Hotel object
    /// \param product Product to be bought upon clicking
    /// \param menu_button button whose on Click() will be called after button calls buy() method on Product
    BuyButton(const int x, const int y, const int width,const int height,const std::string text,Hotel* hotel,Product* product,MenuButton<Product>* menu_button);
    ///calls buy() method on Product
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Handle the auto Buy feature
class AutoBuyButton: public BaseButton{
private:
    ///GoBack Button
    MenuButton<Provider>* ProviderButton;
    ///pointer to hotel object which has the autoBuy() method
    Hotel* hotel;
public:
    ///Initialize the AutoBuyButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param hotel Hotel object to initialize the hotel attribute
    /// \param menu_button initialize the ProviderButton that will refresh the Screen upon clicking
    AutoBuyButton(const int x, const int y, const int width,const int height,const std::string text,Hotel* hotel,MenuButton<Provider>* menu_button);
    ///calls autoBuy() method
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Button that calls the SaveHotel() method that saves the hotel's info to a file
class SaveHotelFileButton: public BaseButton{
private:
    ///Hotel to be written to a file
    Hotel* hotel;
public:
    ///Initialize the SaveHotelFileButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param hotel initialize the hotel button
    SaveHotelFileButton(const int x, const int y, const int width,const int height,const std::string text,Hotel* hotel);
    ///calls the SaveHotel() method
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Button Responsible for applying a discount to all Rooms of a given type
class ApplyDiscountToTypeOfRoom: public BaseButton{
private:
    ///Button whose onClick() method will be called upon finishing applying the discount to refresh the screen
    MenuButton<Room>* GoBackButton;
    ///Hotel object which stores the Rooms
    Hotel* hotel;
public:
    ///Initialize ApplyDiscountToTypeOfRoom
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param hotel initialize the hotel attribute
    /// \param menu_button initialize the MenuButton of Room Type that will update the info to the screen
    ApplyDiscountToTypeOfRoom(const int x, const int y, const int width,const int height,const std::string text,Hotel* hotel,MenuButton<Room>* menu_button);
    ///calls activateDiscount()
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Handles calling the different Search Methods corresponding to each class
template <class N>
class SearchButton: public BaseButton{
private:
    ///button to call onClick() to return to previous menu
    MenuButton<N>* goBackButton;
    ///Hotel object containing the Search methods for each class
    Hotel* hotel;
public:
    ///Initialize SearchButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param hotel initialize the hotel attribute
    /// \param menu_button initialize the MenuButton of template instance to return to previous menu
    SearchButton(const int x, const int y, const int width,const int height,const std::string text,Hotel* hotel,MenuButton<N>* menu_button);
    ///calls the corresponding search method for the template instance
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Calls the sort Method for a given class, taking in the parameter of that class to sort by and the order to sort, Ascending or Descending
template <class N>
class SortButton: public BaseButton{
private:
    ///button to call onClick() method after sorting is done to display the sorted list of objects
    MenuButton<N>* menu_button;
    ///hotel method that holds the sort methods
    Hotel* hotel;
    ///can be either Ascending or Descending
    std::string order;
    ///parameter by which to sort
    std::string type;
public:
    ///Initialize the SortButton
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param hotel initialize the hotel attribute
    /// \param order Ascending or Descending
    /// \param type parameter by which to sort
    /// \param menu_button initialize the button that will display the sorted list of objects
    SortButton(const int x, const int y, const int width,const int height,const std::string text,Hotel* hotel,std::string order,std::string type,MenuButton<N>* menu_button);
    ///call the corresponding SortMethod
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

/// Button that will update the CurrentPage of a MenuButton or changes a parameter
template <class N>
class ChangePage: public BaseButton{
private:
    ///MenuButton whose currentPage will be updated
    MenuButton<N>* menu_button;
    /// type of parameter that will be updated(either a PageNumber, SortParameter or OrderParameter)
    std::string type;
public:
    ///Initialize the ChangePage Button
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param type type of parameter to increment or decrement upon clicking
    /// \param menu_button MenuButton associated to the type
    ChangePage(const int x, const int y, const int width,const int height,const std::string text,std::string type,MenuButton<N>* menu_button);
    ///update the corresponding parameter
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

///Button responsible for applying a discount on a given Room
class ApplyDiscountButton: public BaseButton{
private:
    ///Room pointer to the room to be discounted
    Room* room;
    /// Button to be invoked to refresh the screen
    MenuButton<Room>* menu_button;
public:
    /// Initialize apply discount button
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param room pointer to room where the discount will be applied
    /// \param button called button to refresh screen
    ApplyDiscountButton(const int x, const int y, const int width,const int height,const std::string text, Room* room,MenuButton<Room>* button);
    /// Calls toggle discount on room
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

/// Base class for edit and delete buttons
template<class N>
class ModifyButton: public BaseButton{
private:
    /// Pointer to object that will be modified/ deleted
    N* object;
public:
    ///
    /// \return pointer to the modified object/ deleted
    N* getObject();
    /// Calls correspondent modify/ delete method on the object
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
    /// Initialize base class
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param object pointer to object to modify/ delete
    ModifyButton(const int x, const int y, const int width,const int height,const std::string text,N* object);
};

/// Button that calls the delete method correspondent to a given class
template <class N>
class DeleteButton: public ModifyButton<N>{
private:
    /// Pointer to menu button that will refresh the screen
    MenuButton<N>* Button;
public:
    /// Initialize delete button
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param object pointer to object to delete
    /// \param Button pointer to menu button that will refresh the screen
    DeleteButton(const int x, const int y, const int width,const int height,const std::string text,N* object,MenuButton<N>* Button);

    /// Calls correspondent delete method on the object
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

/// Button that calls the edit method correspondent to a given class
template <class N>
class EditButton: public ModifyButton<N>{
private:
    /// Pointer to menu button that will refresh the screen
    MenuButton<N>* OriginalButton;
public:
    /// Initialize edit button
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param object pointer to object to edit
    /// \param button pointer to menu button that will refresh the screen
    EditButton(const int x, const int y, const int width,const int height,const std::string text,N* object,MenuButton<N>* button);

    /// Calls correspondent edit method on the object
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};

/// Button that calls the add method correspondent to a given class
template <class N>
class AddButton: public BaseButton{
private:
    /// Pointer to menu button that will refresh the screen
    MenuButton<N>* Button;
public:
    /// Initialize add button
    ///
    /// \param x top left x coordinate of the button
    /// \param y top left y coordinate of the button
    /// \param width width of the button to be drawn
    /// \param height height of the button to be drawn
    /// \param text text to be displayed inside of the button
    /// \param Button pointer to menu button that will refresh the screen
    AddButton(const int x, const int y, const int width,const int height,const std::string text,MenuButton<N>* Button);

    /// Calls correspondent add method on the object
    ///
    /// \param handler ButtonHandler updating the buttons on Screen
    void onClick(ButtonHandler& handler) override;
};


/// Checks whether a button is pressed or not
bool ButtonWasPressed(BaseButton *button, INPUT_RECORD &Input_Record);


#endif

