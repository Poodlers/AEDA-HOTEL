#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product {
public:
    //Product(const unsigned int& quality, const float& price);
    Product(const unsigned int& quality, const float& price, const std::string & type, const unsigned int& Id);
    unsigned int getQuality() const;
    float getPrice() const;
    unsigned int getId() const;

    void setQuality(const unsigned int& quality);
    void setPrice(const float& price);
    void setId(const unsigned int& Id);

    std::string getType() const;
    void setType(const std::string & type);

private:
    unsigned int quality;
    float price;
    unsigned int Id;

    std::string type; // hygiene, cleaning or other
};

//Worth using inheritance?
/*
class Cleaning: public Product{
public:
    Cleaning(const unsigned int& quality, const float& price);
};
class Hygiene: public Product{
public:
    Hygiene(const unsigned int& quality, const float& price);
};

 */
#endif