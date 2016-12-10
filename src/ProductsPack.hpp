/** ---------------------------------------------------------------------------
 ** ProductsPack.hpp
 ** Container for a doubly linked list of Products.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_PRODUCTSPACK_HPP
#define MINIMUM_CUT_PRODUCTSPACK_HPP

#include "Product.hpp"
#include "Edge.hpp"
#include <memory>
#include <vector>

class Edge;

/**
 * This class represents a pack of Amazon's products.
 */
class ProductsPack
{

public:

    /**
     * Creates a pack of products with an initial product [initialProduct].
     *
     * @param initialProduct of the pack.
     * @return a pack of products with an initial product [initialProduct].
     */
    ProductsPack(const std::shared_ptr<Product> initialProduct);

    /**
     * Adds the Edge [edge] to this pack.
     *
     * @param edge to be added to this pack.
     */
    void AddEdge(const std::shared_ptr<Edge> edge);

private:

    /** Amazon's products that belong to this pack. */
    std::vector<std::shared_ptr<Product>> mProducts;

    /** Packs of Amazon's products whose products, at least one, have been
     * bought with, at least, one product of this pack at least once. */
    std::vector<std::shared_ptr<Edge>> mEdges;

    /** In order to manage O(1) when deleting (fusing) a ProductsPack from a vector,
     * a ProductsPack has these two pointers to the previous and next pack in the vector.
     * Note: they will have to be filled when inserting the pack into the vector. */
    std::shared_ptr<ProductsPack> previousPack, nextPack;
};

#endif //MINIMUM_CUT_PRODUCTSPACK_HPP
