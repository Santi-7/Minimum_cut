/** ---------------------------------------------------------------------------
 ** ProductsPack.hpp
 ** Container for a list of Products.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_PRODUCTSPACK_HPP
#define MINIMUM_CUT_PRODUCTSPACK_HPP

#include "Edge.hpp"
#include "Product.hpp"

#include <vector>

class Edge;
class Product;

/**
 * This class represents a pack of Amazon's products.
 */
class ProductsPack
{

public:

    ProductsPack();

    /**
     * Creates a pack of products with an initial product [initialProduct].
     *
     * @param initialProduct of the pack.
     * @return a pack of products with an initial product [initialProduct].
     */
    ProductsPack(Product *initialProduct);

    /**
     * Adds the Products [products] to this pack.
     *
     * @param products to be added to this pack.
     */
    void AddProducts(const std::vector<unsigned int> &products);

public:

    /** Amazon's products that belong to this pack. */
    std::vector<unsigned int> mProducts;

    /** Id of the pack. */
    unsigned int mId;
};

#endif // MINIMUM_CUT_PRODUCTSPACK_HPP