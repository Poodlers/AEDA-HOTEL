#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <iomanip>


///Product
///
///Class which represents a product
class Product {
public:
    /// Product Initializer - random product
    Product();
    ///
    /// \param quality - quality of the product
    /// \param price - price of the product
    /// \param type - type of product
    Product(const unsigned int& quality, const float& price, const std::string & type);
    ///
    /// \return quality of the product
    unsigned int getQuality() const;
    ///
    /// \return price of the product
    float getPrice() const;
    ///
    /// \return id of the product
    unsigned int getId() const;
    ///
    /// \return type of product
    std::string getType() const;
    ///
    /// \param quality - quality to set to product
    void setQuality(const unsigned int& quality);
    ///
    /// \param price - price to set to product
    void setPrice(const float& price);
    ///
    /// \param type - type to set to product
    void setType(const std::string & type);

    void reduceStock();

    unsigned int getStock() const;

    void setStock(const unsigned int& stock);


    friend std::ostream& operator <<(std::ostream& o, Product& product);

private:
    /// quality of the product
    unsigned int quality;
    /// price of the product
    float price;
    /// id of the product
    unsigned int Id;
    /// variable to keep product ids unique
    static int totalId;
    /// type of product
    /// can be catering, cleaning or other
    std::string type;
    unsigned int stock;
};

#endif