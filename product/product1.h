#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>


///Product
///
///Class which represents a product
class Product {
public:
    Product();
    //Product(const unsigned int& quality, const float& price);
    Product(const unsigned int& quality, const float& price, const std::string & type);
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
    static int totalId;
    std::string type; // catering, cleaning or other
};

#endif