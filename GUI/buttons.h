#ifndef BUTTONS_H
#define BUTTONS_H

#include <string>
#include <vector>
#include <iostream>
#include "utils.h"

struct Button{
    Button(const int x, const int y, const int width,const int height,const std::string text,void (*onClick)(std::vector<Button*> &button_vec)):
     x(x), y(y),width(width),height(height),text(text), Display_Next_Menu(onClick){}
    int x;
    int y;
    int width;
    int height;
    std::string text;
    void (*Display_Next_Menu)(std::vector<Button*> &button_vec);

};

void DisplayMenu(std::vector<Button*>& button_vec);
void DrawButton(Button* button);
void DisplayReservationsMenu(std::vector<Button*>& button_vec);
void DisplayClientsMenu(std::vector<Button*>& button_vec);

extern Button* buttonReservation;
extern Button* buttonGoBack;
extern Button* buttonClients;

#endif
