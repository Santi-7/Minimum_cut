/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for KargerGraph class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "KargerGraph.hpp"

#include <stdlib.h>
#include <assert.h>

KargerGraph::KargerGraph(const bool isWeighted)
: mIsWeighted(isWeighted)
{
    // Initializes the random numbers generator's seed.
    srand(time(NULL));
}

void KargerGraph::AddProduct(Product *product)
{
    // Add the pack to the map of packs.
    mPacks.emplace(product, ProductsPack(product));
}

void KargerGraph::AddEdge(Edge &edge)
{
    // Add it to the vector of edges.
    mEdges.push_back(edge);
}

void KargerGraph::FuseStep()
{
    // Avoid division by zero.
    assert(mEdges.size() > 0);

    // Get a random edge of the graph.
    Edge randomEdge;
    if (mIsWeighted)
    {
        // TODO: Take an edge.
    }
    else {
        randomEdge = mEdges[rand() % mEdges.size()];
    }

    // Fuses the products of both packs into the first one.
    mPacks[randomEdge.GetPack1()].AddProducts(mPacks[randomEdge.GetPack2()].mProducts);
    // Remove self-loop edges.
    for (auto it = mEdges.begin(); it < mEdges.end(); ++it)
    {
        // TODO: Check this comparison. --it needs to be done? erase doesn't do it?
        if (randomEdge == it)
        {
            it = mEdges.erase(it);
            --it;
        }
    }
    /* Remove randomEdge.GetPack2() from mPacks. */
    mPacks.erase(randomEdge.GetPack2());
}

std::map<unsigned int, ProductsPack> KargerGraph::GetPacks() const
{
    return mPacks;
}

std::vector<Edge> KargerGraph::GetEdges() const
{
    return mEdges;
}