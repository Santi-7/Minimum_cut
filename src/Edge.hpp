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

class Product;
class ProductsPack;

/**
 * An edge between two packs of Amazon's products, [mP1] and [mP2], means
 * that at least one product of each pack has been bought together at least once.
 */
class Edge
{

public:

    /** Default constructor. */
    Edge() {}

    /**
     * Creates an edge between the two packs of Amazon's products [p1] and [p2].
     *
     * @param p1 First pack of Amazon's products.
     * @param p2 Second pack of Amazon's products.
     * @param weight Times that the two packs have been bought together.
     * @return an edge between the two packs of Amazon's products [p1] and [p2].
     */
    Edge(const unsigned int p1, const unsigned int p2, const unsigned int weight = 1);

    /**
     * Returns the first pack.
     * @return the first pack.
     */
    unsigned int GetPack1() const;

    /**
     * Returns the second pack.
     * @return the second pack.
     */
    unsigned int GetPack2() const;

    /**
     * Sets the first pack to [pack].
     *
     * @param pack to be set as the first pack.
     */
    void SetPack1(const unsigned int pack);

    /**
     * Sets the second pack to [pack].
     *
     * @param pack to be set as the second pack.
     */
    void SetPack2(const unsigned int pack);

    /**
     * Returns the edge's weight.
     * @return the edge's weight.
     */
    unsigned int GetWeight() const;

    /**
     * Overloads == operator to return true if both edges, [edge1] and [edge2],
     * have the same ProductsPack as the two verteces, no matter the order.
     *
     * @param edge1 first edge in the comparison.
     * @param edge2 second edge in the comparison.
     * @return true if both edges, [edge1] and [edge2], have the same ProductsPack
     *  as the two verteces, no matter the order.
     */
    friend bool operator==(const Edge &edge1, const Edge &edge2);

private:

    /** Packs of Amazon's products which products, at least one, have been bought together. */
    unsigned int mP1, mP2;

    /** Weight of the edge: Times that the two packs of Amazon's products have been bought together. */
    // Although there is a version of a Karger's Graph with no weights, an edge has always a weight
    // (by default 1 when it's an unweighted graph), so that the list of edges is in compact memory instead
    // of pointers to types of edges (normal edge, and a child edge with weight). This is done
    // by efficiency when looping the list of edges.
    unsigned int mWeight;
};

#endif // MINIMUM_CUT_EDGE_HPP