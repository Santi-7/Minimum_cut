/** ---------------------------------------------------------------------------
 ** ProductsPack.cpp
 ** Implementation for ProductsPack class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "ProductsPack.hpp"

#include <iostream>

ProductsPack::ProductsPack() {}

ProductsPack::ProductsPack(Product *initialProduct)
: mId(static_cast<unsigned int>(initialProduct))
{
    mProducts.push_back(initialProduct);
}

void ProductsPack::AddProducts(const std::vector<Product*> &products)
{
    mProducts.insert( mProducts.end(), products.begin(), products.end() );
}

void ProductsPack::Print() const
{
    std::cout << "Pack: " << "\n";
    for (Product *product : mProducts)
        std::cout << *product << ", ";
    std::cout << "\n";
}