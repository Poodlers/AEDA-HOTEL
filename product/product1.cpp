#include "product1.h"
#include <string>

Product::Product(const unsigned int& quality, const float& price, const std::string & type, const unsigned int& Id){
    this->quality = quality;
    this->price = price;
    this->type = type;
    this->Id = Id;
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

void Product::setQuality(const unsigned int& quality) {
    this->quality = quality;
}
void Product::setPrice(const float& price) {
    this->price = price;
}
void Product::setId(const unsigned int& Id){
    this->Id = Id;
}

std::string Product::getType() const{
    return this->type;
}

void Product::setType(const std::string & type){
    this->type = type;
}

