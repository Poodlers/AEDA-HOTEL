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
    Product(const std::string &name, const unsigned int& quality, const float& price, const std::string & type);

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

    /// sets quality
    ///
    /// \param quality  new quality
    void setQuality(const unsigned int &quality);

    /// sets price
    ///
    /// \param price  new price
    void setPrice(const float &price);

    /// sets id
    ///
    /// \param id  new id
    void setId(const unsigned int &id);

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
    /// \param stock
    void setStock(const unsigned int& stock);

    /// Prints product in format:
    ///
    /// stock type id price quality
    void print();

    void setName(const std::string &name);

    const std::string &getName() const;

private:
    /// Quality of the product.
    unsigned int quality;
    /// Price of the product.
    float price;
    /// ID of the product.
    unsigned int id;
    /// name of the product.
    std::string name;
    /// Variable to keep product ids unique.
    static int totalId;
    /// Type of product.
    /// Can be catering, cleaning or other.
    std::string type;
    /// Amount of the product in the provider.
    unsigned int stock;
};

class BuyProduct{
public:
    BuyProduct(Product* product, const std::string& providerName);

    const std::string &getProductName() const;

    const std::string &getProviderName() const;

    unsigned int getStock() const;

    unsigned int getRating() const;

    void setProductName(const std::string &productName);

    void setProviderName(const std::string &providerName);

    void setStock(unsigned int stock);

    void setRating(unsigned int rating);

    bool operator< (const BuyProduct& bp1) const;

    friend std::ostream &operator<<(std::ostream &os, const BuyProduct &buyProduct);

    Product *getProduct() const;


private:
    Product* product;
    std::string providerName;

};

#endif