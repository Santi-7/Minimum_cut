/** ---------------------------------------------------------------------------
 ** Product.cpp
 ** Implementation for Product class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "Product.hpp"

Product::Product()
: mName("") {}

Product::Product(const std::string &name, const unsigned int id)
: mName(name), mId(id) {}

unsigned int Product::GetId() const
{
    return mId;
}

std::ostream& operator<<(std::ostream &out, const Product &product)
{
    out << product.mName;
    return out;
}