/** ---------------------------------------------------------------------------
 ** Product.cpp
 ** Implementation for Product class
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "Product.hpp"

Product::Product(const std::string& name)
: mName(name) {}

std::shared_ptr<ProductsPack> Product::GetPack()
{
    return mPack;
}

void Product::SetPack(std::shared_ptr<ProductsPack> pack)
{
    mPack = pack;
}