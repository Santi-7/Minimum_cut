/** ---------------------------------------------------------------------------
 ** ProductsPack.cpp
 ** Implementation for ProductsPack class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "ProductsPack.hpp"

ProductsPack::ProductsPack() {}

ProductsPack::ProductsPack(const std::shared_ptr<Product> &initialProduct)
{
    mProducts.push_back(initialProduct);
}

void ProductsPack::AddEdge(const std::shared_ptr<Edge> &edge)
{
    mEdges.push_back(edge);
}

bool ProductsPack::IsEmpty() const
{
    return mProducts.empty();
}

std::shared_ptr<ProductsPack> ProductsPack::GetPrevious() const
{
    return mPreviousPack;
}

std::shared_ptr<ProductsPack> ProductsPack::GetNext() const
{
    return mNextPack;
}

void ProductsPack::SetPrevious(const std::shared_ptr<ProductsPack> &previous)
{
    mPreviousPack = previous;
}

void ProductsPack::SetNext(const std::shared_ptr<ProductsPack> &next)
{
    mNextPack = next;
}