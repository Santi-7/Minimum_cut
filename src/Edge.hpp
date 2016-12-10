/** ---------------------------------------------------------------------------
 ** Edge.hpp
 ** Container for an edge in the graph.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_EDGE_HPP
#define MINIMUM_CUT_EDGE_HPP

#include "ProductsPack.hpp"

#include <memory>

class ProductsPack;

/**
 * An edge between two packs of Amazon's products, [mP1] and [mP2], means
 * that at least one product of each pack has been bought together at least once.
 */
class Edge
{

public:

    /**
     * Creates an edge between the two packs of Amazon's products [p1] and [p2].
     *
     * @param p1 First pack of Amazon's products.
     * @param p2 Second pack of Amazon's products.
     * @return an edge between the two packs of Amazon's products [p1] and [p2].
     */
    Edge(const std::shared_ptr<ProductsPack> &p1,
         const std::shared_ptr<ProductsPack> &p2);

    /**
     * Returns the first pack.
     * @return the first pack.
     */
    std::shared_ptr<ProductsPack> GetPack1() const;

    /**
     * Returns the second pack.
     * @return the second pack.
     */
    std::shared_ptr<ProductsPack> GetPack2() const;

    /**
     * Sets the first pack to [pack].
     *
     * @param pack to be set as the first pack.
     */
    void SetPack1(std::shared_ptr<ProductsPack> pack);

    /**
     * Sets the second pack to [pack].
     *
     * @param pack to be set as the second pack.
     */
    void SetPack2(std::shared_ptr<ProductsPack> pack);

    /**
     * Overloads == operator to return true if both edges, [edge1] and [edge2],
     * have the same ProductsPack as the two verteces, no matter the order.
     *
     * @param edge1 first edge in the comparison.
     * @param edge2 second edge in the comparison.
     * @return true if both edges, [edge1] and [edge2], have the same ProductsPack
     * as the two verteces, no matter the order.
     */
    friend bool operator==(const Edge &edge1, const Edge &edge2);

private:

    /** Packs of Amazon's products which products, at least one, have been bought together. */
    std::shared_ptr<ProductsPack> mP1, mP2;
};

#endif // MINIMUM_CUT_EDGE_HPP