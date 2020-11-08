#ifndef BUTTONS_H
#define BUTTONS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "utils.h"
#include "../hotel/hotel.h"

class BaseButton{
protected:
    int x;
    int y;
    int width;
    int height;
    std::string text;

public:
    BaseButton(const int x, const int y, const int width,const int height,const std::string &text);
    virtual void onClick(std::vector<BaseButton*> &CurrentButtons) = 0;
    void DrawButton();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

};

class ParentButton: public BaseButton{
private:
    std::vector<BaseButton*> InitialButtons;
public:
    ParentButton(const int x, const int y, const int width,const int height,const std::string &text,const std::vector<BaseButton*>& InitialButtons);
    void onClick(std::vector<BaseButton*> &CurrentButtons) override;
};

class GoBackButton: public BaseButton{
private:
    BaseButton* NextButtons;
public:
    GoBackButton(const int x, const int y, const int width,const int height,const std::string text,BaseButton * ButtonsNext );
    void onClick(std::vector<BaseButton*> &CurrentButtons) override;
};


template<class N>
class MenuButton : public BaseButton{
private:
    std::vector<N *> menu_items;
    int CurrentPage;
    BaseButton* Parent_Button;
    BaseButton* GoBack_Button;
public:
    MenuButton(const int x, const int y, const int width,const int height,const std::string &text,const int currentPage,
                       std::vector<N *>& menu_items,BaseButton * ParentButton);
    void onClick(std::vector<BaseButton*> &CurrentButtons) override;
    void EraseObject(N * item);

};

template<class N>
class ModifyButton: public BaseButton{
private:
    N* object;
public:
    N* getObject();
    void onClick(std::vector<BaseButton*> &CurrentButtons) override;
    ModifyButton(const int x, const int y, const int width,const int height,const std::string text,N* object);
};


template <class N>
class DeleteButton: public ModifyButton<N>{
private:
    MenuButton<N>* Button;
public:
    DeleteButton(const int x, const int y, const int width,const int height,const std::string text,N* object,MenuButton<N>* Button);
    void onClick(std::vector<BaseButton*> &CurrentButtons) override;
};

template <class N>
class EditButton: public ModifyButton<N>{
private:
    BaseButton* OriginalButton;
public:
    EditButton(const int x, const int y, const int width,const int height,const std::string text,N* object,BaseButton* button);
    void onClick(std::vector<BaseButton*> &CurrentButtons) override;
};


bool ButtonWasPressed(BaseButton *button, INPUT_RECORD &Input_Record);
void Authentication(Hotel* hotel);


#endif
