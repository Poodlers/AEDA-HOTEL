#ifndef PROVIDER_H
#define PROVIDER_H
#include <vector>
#include <string>
#include "../product/product1.h"
#include <iostream>
#include "../hotel/reservation.h"

/// Class which represents a Provider.
///
/// Defined by name and products.
class Provider{
public:

    /// Provider constructor for making a more specific provider.
    ///
    /// \param name  name of provider.
    /// \param products  vector of products available.
    Provider(const std::string &name,const std::vector<Product *> &products);

    /// Provider constructor for making a provider with 'size' random products.
    ///
    /// \param name  name of provider.
    /// \param size  number of products to create.
    Provider(const std::string &name, const unsigned int &size);

    /// Returns name.
    ///
    /// \return name of provider.
    std::string getName() const;

    /// Returns products.
    ///
    /// \return vector of products.
    std::vector<Product *> getProducts() const;

    /// returns numProducts
    ///
    /// \return number of products
    unsigned getNumProducts() const;

    /// Changes name.
    ///
    /// \param name  new name.
    void setName(const std::string &name);

    /// Changes products and numProducts
    ///
    /// \param products  new products
    void setProducts(const std::vector<Product*> &products);

    /// Prints the provider in format
    ///
    /// Provider: name
    /// Stock Type ID Price Quality
    /// product
    /// ...
    void printConsole();

    void print();

    /// Restocks its products.
    void restock();

    ///Adds a single product to the Provider's products
    ///
    /// \param product product to add to the provider's products
    void addProduct(Product* product);

private:
    /// Mame of provider.
    std::string name;
    /// Products available.
    std::vector<Product *> products;
    /// Number of products.
    unsigned numProducts;

};

#endif
