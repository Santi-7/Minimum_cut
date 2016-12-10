/** ---------------------------------------------------------------------------
 ** ProductsPack.hpp
 ** Container for a doubly linked list of Products.
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
     * Returns true if the pack has no products.
     *
     * @return true if the pack has no products.
     */
    bool IsEmpty() const;

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
     * Returns the previous pack.
     *
     * @return the previous pack.
     */
    std::shared_ptr<ProductsPack> GetPrevious() const;

    /**
     * Returns the next pack.
     *
     * @return the next pack.
     */
    std::shared_ptr<ProductsPack> GetNext() const;

    /**
     * Sets [previous] to the previous ProductsPack.
     *
     * @param previous ProductsPack to be set as the previous pack.
     */
    void SetPrevious(const std::shared_ptr<ProductsPack> &previous);

    /**
     * Sets [next] to the next ProductsPack.
     *
     * @param next ProductsPack to be set as the next pack.
     */
    void SetNext(const std::shared_ptr<ProductsPack> &next);

    /**
     * Overloads == operator to return true if both packs are the same, this is for example,
     * in the fastest way, they share the same position in the array.
     *
     * @param pack1 first ProductsPack in the comparison.
     * @param pack2 second ProductsPack in the comparison.
     * @return true if both packs are the same,
     */
    friend bool operator==(const ProductsPack &pack1, const ProductsPack &pack2);

private:

    /** Amazon's products that belong to this pack. */
    std::vector<std::shared_ptr<Product>> mProducts;

    /** Packs of Amazon's products whose products, at least one, have been
     * bought with, at least, one product of this pack at least once. */
    std::vector<std::shared_ptr<Edge>> mEdges;

    /** In order to manage O(1) when deleting (fusing) a ProductsPack from an array,
     * a ProductsPack has these two pointers to the previous and next pack in the array.
     * Note: they will have to be filled when inserting the pack into the array. */
    std::shared_ptr<ProductsPack> mPreviousPack = nullptr, mNextPack = nullptr;
};

#endif // MINIMUM_CUT_PRODUCTSPACK_HPP