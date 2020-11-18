#ifndef AEDA_HOTEL_PROJETO_BUTTONS_H
#define AEDA_HOTEL_PROJETO_BUTTONS_H

#ifndef BUTTONS_H
#define BUTTONS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "utils.h"
#include "../hotel/hotel.h"

class ButtonHandler;

class BaseButton{
private:
    int x;
    int y;
    int width;
    int height;
    std::string text;

public:
    BaseButton(const int x, const int y, const int width,const int height,const std::string &text);
    virtual void onClick(ButtonHandler& handler) = 0;
    void DrawButton();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    std::string getText();

};

class ButtonHandler{
private:
    std::vector<BaseButton*> CurrentButtons;
public:
    ButtonHandler(std::vector<BaseButton*>  InitialButtons);
    void AddButton(BaseButton* button);
    std::vector<BaseButton*> getButtons();
    void ClearButtons();
    void SpecialGoBackClear();
    void DeleteButton(int index);
};

class ParentButton: public BaseButton{
private:
    std::vector<BaseButton*> InitialButtons;
public:
    ParentButton(const int x, const int y, const int width,const int height,const std::string &text,const std::vector<BaseButton*> InitialButtons);
    void onClick(ButtonHandler& handler) override;
};

class GoBackButton: public BaseButton{
private:
    BaseButton* NextButton;
public:
    GoBackButton(const int x, const int y, const int width,const int height,const std::string text,BaseButton * ButtonNext );
    void onClick(ButtonHandler& handler) override;
};


template<class N>
class MenuButton : public BaseButton{
private:
    Hotel* hotel;
    Client* client;
    int CurrentPage;
    BaseButton* Parent_Button;
    BaseButton* GoBack_Button;
public:
    MenuButton(const int x, const int y, const int width,const int height,const std::string &text,const int currentPage,
               Hotel* hotel,BaseButton* ParentButton);
    MenuButton(const int x, const int y, const int width,const int height,const std::string &text,const int currentPage,
               Client* client,BaseButton* ParentButton);
    void onClick(ButtonHandler& handler) override;
    void EraseObject(N* item);
    void AddObject(N* item);
    void SetCurrentPage(int page);
    int getCurrentPage();


};

template <class N>
class ChangePageButton: public BaseButton{
private:
    MenuButton<N>* menu_button;
    int max_page;
public:
    ChangePageButton(const int x, const int y, const int width,const int height,const std::string text,int max_page, MenuButton<N>* button);
    void onClick(ButtonHandler& handler) override;
};

template<class N>
class ModifyButton: public BaseButton{
private:
    N* object;
public:
    N* getObject();
    void onClick(ButtonHandler& handler) override;
    ModifyButton(const int x, const int y, const int width,const int height,const std::string text,N* object);
};


template <class N>
class DeleteButton: public ModifyButton<N>{
private:
    MenuButton<N>* Button;
public:
    DeleteButton(const int x, const int y, const int width,const int height,const std::string text,N* object,MenuButton<N>* Button);
    void onClick(ButtonHandler& handler) override;
};

template <class N>
class EditButton: public ModifyButton<N>{
private:
    BaseButton* OriginalButton;
public:
    EditButton(const int x, const int y, const int width,const int height,const std::string text,N* object,BaseButton* button);
    void onClick(ButtonHandler& handler) override;
};

template <class N>
class AddButton: public BaseButton{
private:
    MenuButton<N>* Button;
public:
    AddButton(const int x, const int y, const int width,const int height,const std::string text,MenuButton<N>* Button);
    void onClick(ButtonHandler& handler) override;
};



bool ButtonWasPressed(BaseButton *button, INPUT_RECORD &Input_Record);
void Authentication(Hotel* hotel);


#endif


#endif //AEDA_HOTEL_PROJETO_BUTTONS_H
