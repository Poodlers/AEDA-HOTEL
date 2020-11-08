#ifndef PROVIDER_H
#define PROVIDER_H
#include <vector>
#include <string>
#include "../product/product1.h"

class Provider{
public:
    Provider(const std::string & name, std::vector<Product> products);
private:
    std::string name;
    std::vector<Product> products;
};

#endif
