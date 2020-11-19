#include "provider.h"

Provider::Provider(const std::string &n, std::vector<Product *> &p) {
    this->name = n;
    this->products = p;
    this->numProducts = p.size();
}

Provider::Provider(const std::string &n, unsigned int &size) {
    this->name = n;
    for(size_t i = 0; i < size; i++){
        Product * n = new Product();
        this->products.push_back(n);
    }
}

std::string Provider::getName() const {
    return this->name;
}

std::vector<Product *> Provider::getProducts() const {
    return this->products;
}

unsigned Provider::getNumProducts() const {
    return this->numProducts;
}

void Provider::setName(const std::string &n) {
    this->name = n;
}

void Provider::setProducts(const std::vector<Product *> &p) {
    this->products = p;
}

void Provider::addProduct() {
    Product * n = new Product();
    this->products.push_back(n);
}

void Provider::removeProduct(unsigned &index){
    this->products.erase(products.begin() + index);
}
