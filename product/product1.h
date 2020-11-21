#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <iomanip>


/// Class which represents a Product.
///
/// Defined by quality, price, ID, type and stock.
class Product {
public:
    /// Product constructor.
    ///
    /// Creates a random product with stock of 100.
    Product();

    /// Product constructor for a specific product.
    ///
    /// \param quality  quality of the product.
    /// \param price  price of the product.
    /// \param type  type of product.
    Product(const unsigned int& quality, const float& price, const std::string & type);

    /// Returns the quality.
    ///
    /// \return quality of the product.
    unsigned int getQuality() const;

    /// Returns the price.
    ///
    /// \return price of the product.
    float getPrice() const;

    /// Returns the ID.
    ///
    /// \return id of the product.
    unsigned int getId() const;

    /// Returns the product type.
    ///
    /// \return type of product.
    std::string getType() const;

    /// Changes the type.
    ///
    /// \param type  type to set to product.
    void setType(const std::string & type);

    /// Reduces the parameter stock of the product by 1.
    void reduceStock();

    /// Returns the stock of the product.
    ///
    /// \return stock.
    unsigned int getStock() const;

    /// Changes the stock of the product.
    /// \param stock.
    void setStock(const unsigned int& stock);

    /// Operator overload <<.
    ///
    /// Format: stock type id price quality
    /// \param o
    /// \param product
    /// \return o
    friend std::ostream& operator <<(std::ostream& o, Product& product);

private:
    /// Quality of the product
    unsigned int quality;
    /// Price of the product
    float price;
    /// ID of the product
    unsigned int id;
    /// Variable to keep product ids unique
    static int totalId;
    /// Type of product
    /// Can be catering, cleaning or other
    std::string type;
    /// Amount of the product in the provider
    unsigned int stock;
};

#endif