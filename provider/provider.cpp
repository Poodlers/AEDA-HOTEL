#include "provider.h"

Provider::Provider(const std::string &name, std::vector<Product> products) {
    this->name = name;
    this->products = products;
}

