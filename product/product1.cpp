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
    this->id = totalId;
    this->totalId++;
    this->stock = 100;
    this->name = "Product" + std::to_string(this->id);
}

Product::Product(const std::string &name, const unsigned int& quality, const float& price, const std::string & type, const unsigned int& stock,  const unsigned int& ID){
    this->quality = quality;
    this->price = price;
    this->type = type;
    if (ID > totalId) totalId = ID;
    this->id = ID;
    this->totalId++;
    this->stock = stock;
    this->name = name;
}

unsigned int Product::getQuality() const{
    return this->quality;
}
float Product::getPrice() const{
    return this->price;
}
unsigned int Product::getId() const{
    return this->id;
}
std::string Product::getType() const{
    return this->type;
}

void Product::reduceStock() {
    this->stock--;
}

void Product::setType(const std::string & type){
    this->type = type;
}

void Product::print() {
    std::cout  <<std::left<< std::setfill(' ') <<std::setw(7)<< this->getStock() << std::setw(10) << this->getType()<< std::setw(9) << this->getId() <<std::setw(7) <<this->getPrice()<< std::setw(7) << this->getQuality() <<std::endl;
}
unsigned int Product::getStock() const{
    return stock;
}
void Product::setStock(const unsigned int& stock){
    this->stock = stock;
}

void Product::setQuality(const unsigned int &quality) {
    this->quality = quality;
}

void Product::setPrice(const float &price) {
    this->price = price;
}

void Product::setId(const unsigned int &id) {
    this->id = id;
}

void Product::setName(const std::string &name) {
    Product::name = name;
}

const std::string &Product::getName() const {
    return name;
}

void BuyProduct::incrementStock() const {
    this->product->setStock(this->product->getStock() + 1);
}

BuyProduct::BuyProduct(Product *product, const std::string &providerName) {
    this->product = product;
    this->providerName = providerName;
}

const std::string &BuyProduct::getProductName() const {
    return this->product->getName();
}

const std::string &BuyProduct::getProviderName() const {
    return providerName;
}

unsigned int BuyProduct::getStock() const {
    return this->product->getStock();
}

unsigned int BuyProduct::getRating() const {
    return this->product->getQuality();
}

void BuyProduct::setProductName(const std::string &productName) {
    this->product->setName(productName);
}

void BuyProduct::setProviderName(const std::string &providerName) {
    BuyProduct::providerName = providerName;
}

void BuyProduct::setStock(unsigned int stock) {
    this->product->setStock(stock);
}

void BuyProduct::setRating(unsigned int rating) {
    this->product->setQuality(rating);
}

bool BuyProduct::operator<(const BuyProduct &bp1) const {
    if(this->getRating() == bp1.getRating()){
        return this->getStock() < bp1.getStock();
    }
    return this->getRating() < bp1.getRating();
}

std::ostream &operator<<(std::ostream &os, const BuyProduct &buyProduct) {
    os << std::setw(12) << buyProduct.getProductName() << std::setw(4) << buyProduct.getProduct()->getId() << std::setw(15)  << buyProduct.providerName << std::setw(7)
            << buyProduct.getStock() << std::setw(8) << buyProduct.getRating() << std::endl;
    return os;
}

Product *BuyProduct::getProduct() const {
    return product;
}

float BuyProduct::getPrice() const {
    return this->product->getPrice();
}

std::string BuyProduct::getType() const {
    return this->product->getType();
}