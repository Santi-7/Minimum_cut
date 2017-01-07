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
: mId(initialProduct->GetId())
{
    mProducts.push_back(initialProduct->GetId());
}

void ProductsPack::AddProducts(const std::vector<unsigned int> &products)
{
    mProducts.insert( mProducts.end(), products.begin(), products.end() );
}