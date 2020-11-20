#ifndef PROVIDER_H
#define PROVIDER_H
#include <vector>
#include <string>
#include "../product/product1.h"
#include <iostream>
#include "../hotel/reservation.h"

///Provider
///
///Class which represents a provider
class Provider{
public:
    ///
    /// \param n - name of provider
    /// \param p - vector of products available
    Provider(const std::string &n,const std::vector<Product *> &p);

    ///
    /// \param n - name of provider
    /// \param size - number of products to create
    Provider(const std::string &n, const unsigned int &size);

    ///
    /// \return name of provider
    std::string getName() const;

    ///
    /// \return vector of products
    std::vector<Product *> getProducts() const;

    ///
    /// \return number of products
    unsigned getNumProducts() const;

    ///
    /// \param n - name of provider to set
    void setName(const std::string &n);

    ///
    /// \param p - vector of products to set
    void setProducts(const std::vector<Product *> &p);
    /// add product to vector
    void addProduct(Product* product);
    ///
    /// \param index - element to remove from products vector
    void removeProduct(unsigned &index);

    ///Prints the provider
    void print();

    ///Prints the provider (for the console)
    void printConsole();

    ///Restocks its' products'
    ///
    void restock();


private:
    /// name of provider
    std::string name;
    /// products available
    std::vector<Product *> products;
    /// number of products
    unsigned numProducts;

};

#endif
