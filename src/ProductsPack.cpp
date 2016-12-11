/** ---------------------------------------------------------------------------
 ** ProductsPack.cpp
 ** Implementation for ProductsPack class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <iostream>
#include "ProductsPack.hpp"

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

std::vector<std::shared_ptr<Product>> ProductsPack::GetProducts() const
{
    return mProducts;
}

std::vector<std::shared_ptr<Edge>> ProductsPack::GetEdges() const
{
    return mEdges;
}

unsigned long ProductsPack::GetPosition() const
{
    return mPosition;
}

void ProductsPack::SetPosition(const unsigned long position)
{
    mPosition = position;
}

void ProductsPack::Print()
{
    std::cout << "Pack number " << std::to_string(mPosition) << "\n";
    std::cout << "=============" << "\n";
    for (std::shared_ptr<Product> product : mProducts)
    {
        std::cout << *product << "\n";
    }
    std::cout << "\n";
}
