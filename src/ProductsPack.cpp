/** ---------------------------------------------------------------------------
 ** ProductsPack.cpp
 ** Implementation for Edge class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "ProductsPack.hpp"

ProductsPack::ProductsPack(const std::shared_ptr<Product> initialProduct)
{
    mProducts.push_back(initialProduct);
}

void ProductsPack::AddEdge(const std::shared_ptr<Edge> edge)
{
    mEdges.push_back(edge);
}