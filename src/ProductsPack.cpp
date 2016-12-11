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

ProductsPack::ProductsPack(const std::shared_ptr<Product> &initialProduct)
{
    mProducts.push_back(initialProduct);
}

void ProductsPack::AddProducts(const std::vector<std::shared_ptr<Product>> &products)
{
    mProducts.insert( mProducts.end(), products.begin(), products.end() );
}

void ProductsPack::AddEdge(const std::shared_ptr<Edge> &edge)
{
    mEdges.push_back(edge);
}

unsigned long ProductsPack::GetPosition() const
{
    return mPosition;
}

void ProductsPack::SetPosition(const unsigned long position)
{
    mPosition = position;
}

void ProductsPack::Print() const
{
    std::cout << "Pack number " << std::to_string(mPosition) << "\n";
    std::cout << "=============" << "\n";
    for (std::shared_ptr<Product> product : mProducts)
        std::cout << *product << "\n";
    std::cout << "\n";
}
