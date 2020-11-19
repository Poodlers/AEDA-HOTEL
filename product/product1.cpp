#include "product1.h"
#include <string>
#include <random>

int Product::totalId = 0;

Product::Product(){
    this->quality = rand() % 6;
    this->price = (rand() % 100) + 0.01 * (rand() % 99 + 1);
    int n = rand() % 3;
    switch(n){
        case 2:
            this->type = "Cleaning";
            break;
        case 1:
            this->type = "Catering";
            break;
        case 0:
            this->type = "Other";
            break;
    }
    this->Id = totalId;
    this->totalId++;
    this->stock = 100;
}

Product::Product(const unsigned int& quality, const float& price, const std::string & type){
    this->quality = quality;
    this->price = price;
    this->type = type;
    this->Id = totalId;
    this->totalId++;
    this->stock = 100;
}
unsigned int Product::getQuality() const{
    return this->quality;
}
float Product::getPrice() const{
    return this->price;
}
unsigned int Product::getId() const{
    return this->Id;
}
std::string Product::getType() const{
    return this->type;
}

void Product::reduceStock() {
    this->stock--;
}

void Product::setQuality(const unsigned int& quality) {
    this->quality = quality;
}
void Product::setPrice(const float& price) {
    this->price = price;
}
void Product::setType(const std::string & type){
    this->type = type;
}

std::ostream& operator<<(std::ostream& o, Product& product){
    return o <<std::left<< std::setfill(' ') <<std::setw(7)<<product.getStock() << std::setw(10) << product.getType()<< std::setw(9) << product.getId() <<std::setw(7) <<product.getPrice()<< std::setw(4) << product.getQuality() <<std::endl;
}
unsigned int Product::getStock() const{
    return stock;
}
void Product::setStock(const unsigned int& stock){
    this->stock = stock;
}


