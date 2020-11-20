#include "utils.h"
#include <iostream>
#include <conio.h>
#include "../exceptions/exceptions.h"

using namespace std;

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

bool CheckIfFloat(std::string input){
    bool isfloat = false;
    for(int i = 0; i < input.length();i++){
        if(input[i] == '.'){
            if(!isfloat){
                isfloat = true;
            }else{ //this is the second . and this input is invalid
                return false;
            }
        }
        else if(!isdigit(input[i])){
            return false;
        }
    }
    return true;
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

