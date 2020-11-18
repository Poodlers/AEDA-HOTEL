#include "product1.h"
#include <string>
#include <random>

int Product::totalId = 0;

Product::Product(){
    this->quality = rand() % 6;
    this->price = (rand() % 100) + 0.01 * (rand() % 99 + 1);
    this->type = (rand() % 2) ? "catering" : "cleaning";
    this->Id = totalId;
    this->totalId++;
}

Product::Product(const unsigned int& quality, const float& price, const std::string & type){
    this->quality = quality;
    this->price = price;
    this->type = type;
    this->Id = totalId;
    this->totalId++;
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

void Product::setQuality(const unsigned int& quality) {
    this->quality = quality;
}
void Product::setPrice(const float& price) {
    this->price = price;
}
void Product::setType(const std::string & type){
    this->type = type;
}

