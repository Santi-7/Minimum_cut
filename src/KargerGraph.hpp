/** ---------------------------------------------------------------------------
 ** KargerGraph.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_KARGERGRAPH_HPP
#define MINIMUM_CUT_KARGERGRAPH_HPP

#include "Edge.hpp"
#include "Product.hpp"
#include "ProductsPack.hpp"

#include <deque>

class KargerGraph
{

public:

    /**
     * Creates a Karger's Graph.
     *
     * @return a Karger's Graph.
     */
    KargerGraph();

    /**
     * Adds the Amazon's product [product] to the Karger's Graph as a vertice.
     *
     * @param product to be added to the Karger's Graph as a vertice.
     */
    void AddProduct(Product *product);

    /**
     * Adds the Edge [edge] to the Karger's Graph as an edge.
     *
     * @param edge to be added to the Karger's Graph as an edge.
     */
    void AddEdge(Edge &edge);

    /**
     * TODO: Add doc.
     */
    void FuseStep();

    /**
     * @return The ProductPacks of this Graph.
     */
    std::deque<ProductsPack> GetPacks() const;

    /**
     * @return The Edges of this Graph.
     */
    std::deque<Edge> GetEdges() const;

private:

    /** Packs of Amazon's products (vertices of the graph). */
    std::deque<ProductsPack> mPacks;

    /** Edges between the packs (edges of the graph). */
    std::deque<Edge> mEdges;
};

#endif // MINIMUM_CUT_KARGERGRAPH_HPP