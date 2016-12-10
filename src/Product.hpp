/** ---------------------------------------------------------------------------
 ** Product.hpp
 ** Contains all the information needed to describe a product.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_PRODUCT_HPP
#define MINIMUM_CUT_PRODUCT_HPP

#include <string>

/**
 * This class represents an Amazon's product.
 */
class Product
{

public:

    /**
     * Creates an Amazon's product with name [name].
     *
     * @param name of the Amazon's product created.
     * @return an Amazon's product with name [name].
     */
    Product(const std::string &name);

private:

    /** Name of the Amazon's product. */
    std::string mName;
};

#endif // MINIMUM_CUT_PRODUCT_HPP
