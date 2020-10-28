#include "buttons.h"
#include <iostream>

using namespace std;

Button* buttonReservation = new Button(10,3,15,4,"Reservations", DisplayReservationsMenu);
Button* buttonGoBack = new Button(40,1,10,4,"Go Back",DisplayMenu);
Button* buttonClients = new Button(10,10,15,4,"Clients", DisplayClientsMenu);

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
    button_vec = {buttonReservation,buttonClients};
    for(Button * button: button_vec){
        DrawButton(button);
    }

}

void DisplayReservationsMenu(vector<Button*>& button_vec){
    button_vec = {buttonGoBack};
    clearscreen();
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

void DisplayClientsMenu(vector<Button*>& button_vec){
    button_vec = {buttonGoBack};
    clearscreen();
    gotoxy(1,1);
    cout << "CLIENTS";
    for(Button * button: button_vec){
        DrawButton(button);
    }
    for(int i = 2; i < 10; i++){
        gotoxy(1, 1+ i);
        cout << "Client n: " << i -1;
    }
}
