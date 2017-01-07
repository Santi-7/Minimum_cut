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

Product::Product(const std::string &name)
: mName(name) {}

std::ostream& operator<<(std::ostream &out, const Product &product)
{
    out << product.mName;
    return out;
}