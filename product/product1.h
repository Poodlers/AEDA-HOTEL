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
    ///\param stock amount of the product in existence.
    Product(const std::string &name, const unsigned int& quality, const float& price, const std::string & type,const unsigned int& stock, const unsigned int& ID = totalId);

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
    /// Sets new name.
    ///
    /// \param name new name.
    void setName(const std::string &name);
    /// Returns name.
    ///
    /// \return name.
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


/// Class which represents bought products.
///
/// Defined by Product pointer and provider.
class BuyProduct{
public:
    /// BuyProduct constructor.
    ///
    /// \param product Product pointer.
    /// \param providerName name of the provider.
    BuyProduct(Product* product, const std::string& providerName);
    /// returns name of the product.
    ///
    /// \return product name.
    const std::string &getProductName() const;
    /// returns name of the provider.
    ///
    /// \return provider name.
    const std::string &getProviderName() const;


    /// returns stock.
    ///
    /// \return stock.
    unsigned int getStock() const;
    /// returns rating.
    ///
    /// \return rating.
    unsigned int getRating() const;
    /// returns price.
    ///
    /// \return price.
    float getPrice() const;
    /// returns type.
    ///
    /// \return type.
    std::string getType() const;
    /// sets new product name.
    ///
    /// \param productName new product name.
    void setProductName(const std::string &productName);
    /// sets new provider name.
    ///
    /// \param providerName new provider name.
    void setProviderName(const std::string &providerName);
    /// sets new stock.
    ///
    /// \param stock new stock.
    void setStock(unsigned int stock);
    /// increments stock.
    void incrementStock() const;
    /// sets new rating.
    ///
    /// \param rating new rating
    void setRating(unsigned int rating);
    /// overload for <
    ///
    /// \param bp1
    /// \return this-> < BuyProduct.
    bool operator< (const BuyProduct& bp1) const;
    ///
    /// \param os ostream
    /// \param buyProduct product to print
    /// \return message
    friend std::ostream &operator<<(std::ostream &os, const BuyProduct &buyProduct);
    /// returns Product.
    ///
    /// \return Product.
    Product *getProduct() const;


private:
    /// Product pointer.
    Product* product;
    /// Provider name.
    std::string providerName;

};

#endif