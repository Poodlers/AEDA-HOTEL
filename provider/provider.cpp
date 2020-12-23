#include "provider.h"
#include <algorithm>

void Provider::restock(){
    for (Product* product: products){
        product->setStock(100);
    }
}

Provider::Provider(const std::string &n, const std::vector<Product *> &p) {
    this->name = n;
    this->products = p;
    this->numProducts = p.size();
}

Provider::Provider(const std::string &n,const unsigned int &size) {
    this->name = n;
    this->numProducts = size;
    for(size_t i = 0; i < size; i++){
        Product * n = new Product();
        this->products.push_back(n);
    }
}

void Provider::printConsole() {
    this->print();
    std::cout<<std::left<< std::setfill(' ') <<std::setw(7) << "Stock"<< std::setw(10) << "Type"<< std::setw(9) << "ID" <<std::setw(7) <<"Price"<< std::setw(4) << "Quality"<<std::endl;
    for (Product* product: products){
        product->print();
    }
}

void Provider::print() {
    std::cout <<"Provider: "  << name <<std::endl;
}

std::string Provider::getName() const {
    return this->name;
}

void Provider::addProduct(Product *product) {
    this->products.push_back(product);
}
std::vector<Product *> Provider::getProducts() const {
    return this->products;
}

void Provider::setName(const std::string &n) {
    this->name = n;
}

unsigned Provider::getNumProducts() const {
    return this->numProducts;
}

void Provider::setProducts(const std::vector<Product *> &products) {
    this->products = products;
    this->numProducts = products.size();
}

