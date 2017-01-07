/** ---------------------------------------------------------------------------
 ** KargerGraph.cpp
 ** Implementation for KargerGraph class.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "KargerGraph.hpp"

#include <assert.h>
#include <stdlib.h>
#include <valarray>

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

    for (auto it = mEdges.begin(); it < mEdges.end(); ++it)
    {
        // Remove self-loop edges.
        if (randomEdge == *it) {
            it = mEdges.erase(it);
            --it;
        }
        // Update edges of the deleted node to the new fused node.
        else if (it->GetPack1() == randomEdge.GetPack2())
            it->SetPack1(randomEdge.GetPack1());
        else if (it->GetPack2() == randomEdge.GetPack2())
            it->SetPack2(randomEdge.GetPack1());
    }

    /* Remove randomEdge.GetPack2() from mPacks. */
    mPacks.erase(randomEdge.GetPack2());
}

unsigned int KargerGraph::KargerAlgorithm(unsigned int t)
{
    // Fuse until t (2 by default) nodes are remaining.
    unsigned long vertices = mPacks.size();
    while (vertices --> t) FuseStep();

    // Return the remaining edges.
    return static_cast<unsigned int>(mEdges.size());
}

unsigned int KargerGraph::KargerSteinAlgorithm()
{
    if (mPacks.size() < 6)
    {
        return KargerAlgorithm();
    }
    else
    {
        unsigned int t = 1 + static_cast<unsigned int>(std::ceil(mPacks.size() / std::sqrt(2)));
        KargerGraph copy; // TODO: Implement the copy of a graph.
        KargerAlgorithm(t);
        copy.KargerAlgorithm(t);
        unsigned int cut1 = KargerSteinAlgorithm();
        unsigned int cut2 = copy.KargerSteinAlgorithm();
        if (cut1 <= cut2)
        {
            return cut1;
        }
        else
        {
            //this = copy; // TODO: Implement this.
            return cut2;
        }
    }
}

std::map<Product*, ProductsPack> KargerGraph::GetPacks() const
{
    return mPacks;
}

std::vector<Edge> KargerGraph::GetEdges() const
{
    return mEdges;
}