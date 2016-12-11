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

#include <memory>
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
    ProductsPack(const std::shared_ptr<Product> &initialProduct);

    /**
     * Adds the Products [products] to this pack.
     *
     * @param products to be added to this pack.
     */
    void AddProducts(const std::vector<std::shared_ptr<Product>> &products);

    /**
     * Adds the Edge [edge] to this pack.
     *
     * @param edge to be added to this pack.
     */
    void AddEdge(const std::shared_ptr<Edge> &edge);

    /**
     * Returns the products of this pack.
     *
     * @return the products of this pack.
     */
    std::vector<std::shared_ptr<Product>> GetProducts() const;

    /**
     * Returns the edges of this pack.
     *
     * @return the edges of this pack.
     */
    std::vector<std::shared_ptr<Edge>> GetEdges() const;

    /**
     * Returns the pack's position in the vector of packs of the Karger's Graph.
     *
     * @return the pack's position in the vector of packs of the Karger's Graph.
     */
    unsigned long GetPosition() const;

    /**
     * Sets the pack's position in the vector of packs of the Karger's Graph to [position].
     *
     * @param position to be set as the new position of this pack in the vector of packs
     *                 of the Karger's Graph to [position].
     */
    void SetPosition(const unsigned long position);

private:

    /** Amazon's products that belong to this pack. */
    std::vector<std::shared_ptr<Product>> mProducts;

    /** Packs of Amazon's products whose products, at least one, have been
     * bought with, at least, one product of this pack at least once. */
    std::vector<std::shared_ptr<Edge>> mEdges;

    /** In order to manage O(1) when deleting a pack from the vector, a ProductsPack must
     * maintain the position it has in the vector of packs of the Karger's Graph.
     * Note: It must be updated. */
    unsigned long mPosition;
};

#endif // MINIMUM_CUT_PRODUCTSPACK_HPP