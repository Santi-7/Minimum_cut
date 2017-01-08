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
#include "RandomNumberEngine.hpp"

#include <map>

class KargerGraph
{

public:

    /** Default constructor. */
    KargerGraph() : mRng(CLASSIC_C) {}

    /**
     * Creates a Karger's Graph.
     *
     * @param isWeighted True if the graph is weighted, false otherwise.
     * @return a Karger's Graph.
     */
    KargerGraph(const bool isWeighted, RandomNumberEngine &rng);

    /**
     * Copy constructor.
     *
     * @param copy A Karger Graph which is being copied into the new one.
     * @return A Karger Graph copy of [copy].
     */
    KargerGraph(const KargerGraph &copy, RandomNumberEngine &rng);

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
     * An implementation of Karger's algorithm.
     *
     * @return Possible minimum cut for the input graph. It's not guaranteed to be correct.
     */
    unsigned int KargerAlgorithm(unsigned int t = 2);

    /**
     * An implementation of Karger-Stein's algorithm.
     *
     * @return Possible minimum cut for the input graph. It's not guaranteed to be correct.
     */
    unsigned int KargerSteinAlgorithm();

    /**
     * @return The ProductPacks of this Graph.
     */
    std::map<unsigned int, ProductsPack> GetPacks() const;

    /**
     * @return The Edges of this Graph.
     */
    std::vector<Edge> GetEdges() const;

private:

    /** Packs of Amazon's products (vertices of the graph). */
    std::map<unsigned int, ProductsPack> mPacks;

    /** Edges between the packs (edges of the graph). */
    std::vector<Edge> mEdges;

    /** True if the graph is weighted, false otherwise. */
    bool mIsWeighted;

    /** Random number generator. */
    RandomNumberEngine mRng;

    /* Cached values */

    unsigned int mSumWeights;
};

#endif // MINIMUM_CUT_KARGERGRAPH_HPP