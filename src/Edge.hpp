/** ---------------------------------------------------------------------------
 ** Edge.hpp
 ** Container for an edge in the graph.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_EDGE_HPP
#define MINIMUM_CUT_EDGE_HPP

#include <memory>
#include "ProductsPack.hpp"

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
     * @param p1 First pack of Amazon's product.
     * @param p2 Second pack of Amazon's product.
     * @return an edge between the two packs of Amazon's products [p1] and [p2].
     */
    Edge(const std::shared_ptr<ProductsPack> &p1, const std::shared_ptr<ProductsPack> &p2);

private:

    /** Packs of Amazon's products which products, at least one, have been bought together. */
    std::shared_ptr<ProductsPack> mP1, mP2;
};


#endif //MINIMUM_CUT_EDGE_HPP
