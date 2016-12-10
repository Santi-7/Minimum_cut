/** ---------------------------------------------------------------------------
 ** Product.hpp
 ** Contains all the information needed to describe a product.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_PRODUCT_HPP
#define MINIMUM_CUT_PRODUCT_HPP

#include "ProductsPack.hpp"

#include <memory>

class ProductsPack;

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

    /**
     * Returns the ProductsPack this product belongs to initially.
     *
     * @return the ProductsPack this product belongs to initially.
     */
    std::shared_ptr<ProductsPack> GetPack() const;

    /**
     * Sets the initial ProductsPack of this product to [pack].
     *
     * @param pack this product belongs to initially.
     */
    void SetPack(const std::shared_ptr<ProductsPack> &pack);

private:

    /** Name of the Amazon's product. */
    std::string mName;

    /** ProductsPack this product belongs to initially. This attribute is
     * only used in the construction of the initial Karger's Graph. */
    std::shared_ptr<ProductsPack> mPack;
};

#endif // MINIMUM_CUT_PRODUCT_HPP
