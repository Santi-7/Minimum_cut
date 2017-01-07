/** ---------------------------------------------------------------------------
 ** Product.hpp
 ** Contains all the information needed to describe an Amazon's product.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_PRODUCT_HPP
#define MINIMUM_CUT_PRODUCT_HPP

#include "ProductsPack.hpp"

#include <string>

class ProductsPack;

/**
 * This class represents an Amazon's product.
 */
class Product
{

public:

    /**
     * Default constructor with empty product name.
     */
    Product();

    /**
     * Creates an Amazon's product with name [name].
     *
     * @param name of the Amazon's product created.
     * @return an Amazon's product with name [name].
     */
    Product(const std::string &name);

    /**
     * Pretty print.
     *
     * @param out Stream that will receive the Product [product] as a string.
     * @param product Product to send to the stream as a string.
     * @return Stream with a string version of [product].
     */
    friend std::ostream& operator<<(std::ostream &out, const Product &product);

private:

    /** Name of the Amazon's product. */
    std::string mName;
};

#endif // MINIMUM_CUT_PRODUCT_HPP