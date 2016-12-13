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
    Edge(ProductsPack *p1, ProductsPack *p2);

    /**
     * Returns the first pack.
     * @return the first pack.
     */
    ProductsPack* GetPack1() const;

    /**
     * Returns the second pack.
     * @return the second pack.
     */
    ProductsPack* GetPack2() const;

    /**
     * Sets the first pack to [pack].
     *
     * @param pack to be set as the first pack.
     */
    void SetPack1(ProductsPack *pack);

    /**
     * Sets the second pack to [pack].
     *
     * @param pack to be set as the second pack.
     */
    void SetPack2(ProductsPack *pack);

    /**
     * Returns the edge's position in the vector of edges of the Karger's Graph.
     *
     * @return the edge's position in the vector of edges of the Karger's Graph.
     */
    unsigned long GetPosition() const;

    /**
     * Sets the edge's position in the vector of edges of the Karger's Graph to [position].
     *
     * @param position to be set as the new position of this edge in the vector of edges
     *                 of the Karger's Graph to [position].
     */
    void SetPosition(const unsigned long position);

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
    ProductsPack *mP1, *mP2;

    /** In order to manage O(1) when deleting an edge from the vector, an edge must maintain
     * the position it has in the vector of edges of the Karger's Graph.
     * Note: It must be updated. */
    unsigned long mPosition;
};

#endif // MINIMUM_CUT_EDGE_HPP